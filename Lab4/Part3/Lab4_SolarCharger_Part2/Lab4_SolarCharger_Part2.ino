
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define VIN_BATTERY   A1
#define VIN_SOLAR     A0
#define SWITCH_OUT    7

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const float THRESH_V = 2.5;
const uint16_t THRESH_ADC = (u16)(THRESH_V * 1023) / 5.0;
const float FULL_BATT_CHARGE_VOLTAGE = 4.0;

bool gPoweredBySolar = false;
uint16_t gBatteryIn = 0;
uint16_t gSolarIn = 0;
float gBattVoltage = 0;
float gSolarVoltage = 0;


void setup() {
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

  
  pinMode(VIN_BATTERY, INPUT);
  pinMode(VIN_SOLAR, INPUT);
  pinMode(SWITCH_OUT, OUTPUT);


}

void updateScreen(){

  display.clearDisplay();
  display.setTextSize(1);
  

}

void loop() {
  gSolarIn = analogRead(VIN_SOLAR);
  gBatteryIn = analogRead(VIN_BATTERY);
  gSolarVoltage = (gSolarIn * 5.0) / 1023;
  gBattVoltage = (gBatteryIn * 5.0) / 1023;

  // Powered by battery if battery voltage is greater than 4.8V
  if((gBattVoltage > FULL_BATT_CHARGE_VOLTAGE) || (gBattVoltage > gSolarVoltage)){
    digitalWrite(SWITCH_OUT, LOW);
    gPoweredBySolar = false;

  }else{
    digitalWrite(SWITCH_OUT, HIGH);
    gPoweredBySolar = true;
  }

  Serial.print("Solar voltage: ");
  Serial.print(gSolarVoltage);
  Serial.print("     Battery voltage: ");
  Serial.print(gBattVoltage);
  Serial.print("     Powered by Solar?: ");
  Serial.println(gPoweredBySolar);

  delay(500);
  oled_show_power_status();
}


void oled_show_power_status()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Line 1
  display.setCursor(0, 0);
  display.print(F("Batt V: "));
  display.print(gBattVoltage, 2);           // 2 decimals; change as you like
  display.print(F("  Solar V: "));
  display.print(gSolarVoltage, 2);

  // Line 2
  display.setCursor(0, 16);
  display.print(F("Sol powered? "));
  display.print(gPoweredBySolar);
  display.print(F(";"));

  display.display();
}
