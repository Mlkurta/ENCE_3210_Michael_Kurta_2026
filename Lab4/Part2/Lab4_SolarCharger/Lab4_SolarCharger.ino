

#define VIN_BATTERY   A1
#define VIN_SOLAR     A2
#define SWITCH_OUT    7


const float THRESH_V = 2.5;
const uint16_t THRESH_ADC = (u16)(THRESH_V * 1023) / 5.0;

bool gPoweredBySolar = false;
uint16_t gBatteryIn = 0;
uint16_t gSolarIn = 0;
float gBattVoltage = 0;
float gSolarVoltage = 0;

void setup() {
  Serial.begin(115200);
  pinMode(VIN_BATTERY, INPUT);
  pinMode(VIN_SOLAR, INPUT);
  pinMode(SWITCH_OUT, OUTPUT);


}

void loop() {
  gSolarIn = analogRead(VIN_SOLAR);
  gBatteryIn = analogRead(VIN_BATTERY);
  gSolarVoltage = (gSolarIn * 5.0) / 1023;
  gBattVoltage = (gBatteryIn * 5.0) / 1023;

  if(gSolarIn > THRESH_ADC){
    digitalWrite(SWITCH_OUT, HIGH);
    gPoweredBySolar = true;

  }else if(gBatteryIn > gSolarIn){
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
}
