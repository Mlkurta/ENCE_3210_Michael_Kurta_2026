#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- Pins ----------------
static const uint8_t TEMP_PIN   = A0;  // ADC input (DSP Shield Pot 1 to control)
static const uint8_t PWM_PIN    = 6;   // Timer2 PWM pin on Uno (D3)
static const uint8_t BTN1_PIN   = 2;   // Fan on/off toggle
static const uint8_t BTN2_PIN   = 3;   // Sensitivity cycle

// ---------------- Sampling spec ----------------
// 100 samples / 5 seconds => 50 ms per sample
static const uint16_t NUM_SAMPLES = 100;
static const uint32_t SAMPLE_PERIOD_MS = 50;

// ---------------- Fan / LED state ----------------
volatile bool fanEnabled = true;     // toggled by Button 1
volatile uint8_t sensitivity = 1;    // 0=low, 1=med, 2=high

// Smoothed ADC average (0..1023)
uint16_t avgAdc = 0;
// Output PWM duty cycle
uint8_t duty = 0;

// Lasdt duty cycle
uint8_t lastDuty = 0;   // last computed duty (0..255)

// ---------------- Simple button debounce ----------------
struct DebouncedButton {
  uint8_t pin;              // pin # used
  bool lastStable;          // stable logic level
  bool lastRead;            // last raw read
  uint32_t lastChangeMs;
  static const uint16_t debounceMs = 35;

  void begin(uint8_t p) {
    pin = p;
    pinMode(pin, INPUT);
    lastStable = digitalRead(pin);
    lastRead = lastStable;
    lastChangeMs = millis();
  }

  // Returns true only on a stable falling edge (button press with pullup)
  bool pressed() {
    bool raw = digitalRead(pin);
    uint32_t now = millis();

    if (raw != lastRead) {
      lastRead = raw;
      lastChangeMs = now;
    }

    if ((now - lastChangeMs) >= debounceMs && raw != lastStable) {
      lastStable = raw;
      if (lastStable == LOW) return true; // falling edge = press
    }
    return false;
  }
};

DebouncedButton btn1, btn2;

// ---------------- PWM @ ~250 Hz on D3 (Timer2) ----------------
// Uno defaults: PWM on D3 is ~490 Hz. We reconfigure Timer2 to ~244 Hz.
// Frequency for Fast PWM, TOP=255: f = 16MHz / (N * 256)
// Choose prescaler N=256 => f = 16e6 / (256*256) = 244.14 Hz (close to 250)
static void setupPwm250Hz_OnD6()
{
  // Set D3 (OC2B) as output
  pinMode(PWM_PIN, OUTPUT);

  // Stop Timer2
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  // Fast PWM mode (WGM21:0 = 3), TOP=0xFF
  // Clear OC2B on compare match, set at BOTTOM (non-inverting) for D3
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1);

  // Prescaler = 256 (CS22=1, CS21=1, CS20=0)
  TCCR2B = (1 << CS22) | (1 << CS21);

  // Start at 0 duty
  OCR2B = 0;
}

// Set duty 0..255 on D3 (OC2B)
static inline void pwmWrite8(uint8_t duty)
{
  OCR0A = duty;
}

// ---------------- Temperature mapping ----------------
// Since the prompt doesn't specify sensor type, we treat ADC as "temperature proxy".
// If you have an LM35/TMP36, tell me and I’ll convert to °C properly.
static uint8_t computeDutyFromAvgAdc(uint16_t adc, uint8_t sensLevel)
{
  const uint16_t adcLow  = 200;
  const uint16_t adcHigh = 800;

  uint16_t clamped = adc;
  if (clamped < adcLow) clamped = adcLow;
  if (clamped > adcHigh) clamped = adcHigh;

  uint16_t span = adcHigh - adcLow;
  uint16_t x = clamped - adcLow;

  uint16_t baseDuty = (uint32_t)x * 255UL / span; // 0..255

  // low sensitivity -> lower duty
  static const float gain[3] = {0.40f, 0.70f, .90f};
  float scaled = baseDuty * gain[sensLevel];
  if (scaled > 255) scaled = 255;

  return (uint8_t)(scaled + 0.5f);
}

// ---------------- Sampling state machine ----------------
enum SampleState { IDLE, SAMPLING, READY };
SampleState sampleState = IDLE;

uint16_t sampleCount = 0;
uint32_t sampleSum = 0;
uint32_t lastSampleMs = 0;

static void startSampling()
{
  sampleState = SAMPLING;
  sampleCount = 0;
  sampleSum = 0;
  lastSampleMs = millis();
}

static void updateSampling()
{
  if (sampleState == IDLE) {
    startSampling();
    return;
  }

  if (sampleState != SAMPLING) return;

  uint32_t now = millis();
  if (now - lastSampleMs >= SAMPLE_PERIOD_MS) {
    lastSampleMs += SAMPLE_PERIOD_MS;

    int raw = analogRead(TEMP_PIN);   // 0..1023
    sampleSum += (uint16_t)raw;
    sampleCount++;

    if (sampleCount >= NUM_SAMPLES) {
      avgAdc = (uint16_t)(sampleSum / NUM_SAMPLES);
      sampleState = READY;
    }
  }
}

// ---------------- UI/logic update ----------------
static void handleButtons()
{
  if (btn1.pressed()) {
    fanEnabled = !fanEnabled;

    if (!fanEnabled) {
      analogWrite(PWM_PIN, 0);         // immediate OFF
      lastDuty = 0;
    } else {
      applyDutyFromLastAverage();  // instant ON using last avg + current sensitivity
    }
    Serial.print(F("BTN1: fanEnabled="));
    Serial.println(fanEnabled ? F("ON") : F("OFF"));

  }
  if (btn2.pressed()) {
    sensitivity = (sensitivity + 1) % 3;

    Serial.print(F("BTN2: sensitivity="));
    Serial.println(sensitivity);

    // Immediate effect on output (this is what you’re missing)
    applyDutyFromLastAverage();
  }

}

static void applyDutyFromLastAverage()
{
  duty = 0;

  if (fanEnabled) {
    duty = computeDutyFromAvgAdc(avgAdc, sensitivity);
  } else {
    duty = 0;
  }

  lastDuty = duty;
  analogWrite(PWM_PIN, duty);   // IMPORTANT: if PWM_PIN is D6, this is the correct write
}

static void updateFanOutput()
{
  // Only update output when we have a fresh average
  if (sampleState == READY) {
    uint8_t duty = 0;

    if (fanEnabled) duty = computeDutyFromAvgAdc(avgAdc, sensitivity);
    else duty = 0;

    lastDuty = duty;
    pwmWrite8(duty);

    // Start next 5-second window
    sampleState = IDLE;
  }
}

void setup()
{
  Serial.begin(115200);
  delay(500);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.display();

  btn1.begin(BTN1_PIN);
  btn2.begin(BTN2_PIN);

  setupPwm250Hz_OnD6();

  analogReference(DEFAULT); // 5V ref on Uno by default
  pinMode(TEMP_PIN, INPUT);

  // Timer0 setup
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0  = 0;

  // Fast PWM mode (WGM01 + WGM00)
  TCCR0A = (1 << WGM00) | (1 << WGM01);

  // Non-inverting mode on OC0A (D6)
  TCCR0A |= (1 << COM0A1);

  // Prescaler = 256  (CS02=1)
  TCCR0B |= (1 << CS02);

  Serial.println(F("Fan controller sim (LED PWM) - 14-bit style spec adapted to Uno"));
  Serial.println(F("BTN1 toggles fan, BTN2 cycles sensitivity (0 low,1 med,2 high)."));
}

void loop()
{
  handleButtons();
  updateSampling();
  updateFanOutput();

  // Optional status print (not required, but helpful)
  static uint32_t lastPrint = 0;
  uint32_t now = millis();
  if (now - lastPrint >= 500) {
    lastPrint = now;

    Serial.print(F("fan=")); Serial.print(fanEnabled ? F("ON ") : F("OFF "));
    Serial.print(F("sens=")); Serial.print(sensitivity);
    Serial.print(F(" avgAdc=")); Serial.print(avgAdc);
    Serial.print(F(" duty=")); Serial.println(OCR2B);
  }
  oled_show_fan_status();
}

void oled_show_fan_status()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Line 1
  display.setCursor(0, 0);
  display.print(F("Fan: "));
  display.print(fanEnabled, 2);           // 2 decimals; change as you like
  display.print(F("  Sens lvl: "));
  display.print(sensitivity);

  // Line 2
  display.setCursor(0, 16);
  display.print(F("ADC "));
  display.print(avgAdc);

  display.setCursor(60, 16);
  display.print(F("PWM "));
  display.print(duty);


  display.display();
}
