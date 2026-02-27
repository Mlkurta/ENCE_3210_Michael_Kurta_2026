#include <Arduino.h>
#include <stdint.h>

static const uint16_t N_BITS = 14;
static const float VREF = 3.0f;
static const float LSB = VREF / (1UL << N_BITS);

uint16_t sar14_convert(float vin, float vref, uint8_t *decisions /* size 14 or nullptr */)
{
  // Clamp Vin to [0, Vref]
  if (vin < 0.0f) vin = 0.0f;
  if (vin > vref) vin = vref;

  uint16_t code = 0;

  // MSB -> LSB
  for (int b = (int)N_BITS - 1; b >= 0; --b) {
    uint16_t trial = (uint16_t)(code | (1U << b));

    // Ideal DAC value for the trial code: Vdac = trial * Vref / 2^N
    float vdac = ((float)trial * vref) / (float)(1UL << N_BITS);

    if (vin >= vdac) {
      code = trial;
      if (decisions) decisions[N_BITS - 1 - b] = 1; // store MSB-first decision
    } else {
      if (decisions) decisions[N_BITS - 1 - b] = 0;
    }
  }

  return code;
}

void print_bits14(uint16_t code)
{
  for (int b = (int)N_BITS - 1; b >= 0; --b) {
    Serial.print((code & (1U << b)) ? '1' : '0');
  }
}

void print_hex4(uint16_t code)
{
  // Print as 0xXXXX with leading zeros
  Serial.print(F("0x"));
  if (code < 0x1000) Serial.print('0');
  if (code < 0x0100) Serial.print('0');
  if (code < 0x0010) Serial.print('0');
  Serial.print(code, HEX);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial) { /* Uno usually doesn’t need this, but it’s harmless */ }

  Serial.println(F("14-bit SAR ADC software simulation (Arduino Uno)"));
  Serial.print(F("Vref = ")); Serial.print(VREF, 6); Serial.println(F(" V"));
  Serial.print(F("LSB  = ")); Serial.print(LSB, 12); Serial.println(F(" V"));
  Serial.println();

  const float tests[] = {0.42f, 0.83f, 1.65f, 2.752f};
  const uint8_t ntests = sizeof(tests) / sizeof(tests[0]);

  for (uint8_t i = 0; i < ntests; ++i) {
    float vin = tests[i];
    uint8_t decisions[14] = {0};

    uint16_t code = sar14_convert(vin, VREF, decisions);

    float vq = (float)code * LSB;
    float err = vin - vq;

    Serial.print(F("Vin = ")); Serial.print(vin, 6); Serial.println(F(" V"));
    Serial.print(F("  Code (dec) = ")); Serial.println(code);

    Serial.print(F("  Code (hex) = "));
    print_hex4(code);
    Serial.println();

    Serial.print(F("  Code (bin) = "));
    print_bits14(code);
    Serial.println();

    Serial.print(F("  Vquantized = ")); Serial.print(vq, 12); Serial.println(F(" V"));
    Serial.print(F("  Error      = ")); Serial.print(err, 12); Serial.println(F(" V"));
    Serial.println();
  }
}

void loop()
{
  // Nothing to do repeatedly.
}