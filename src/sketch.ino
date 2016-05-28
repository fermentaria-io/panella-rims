#include <LiquidCrystal.h>
#include <OneWire.h>

LiquidCrystal lcd(2, 3, 7, 6, 5, 4);
OneWire ds(8);
const int pin_relay = 9;


// Max controllers
float target_temperature = 22.0;


// From http://bildr.org/2011/07/ds18b20-arduino/
float getTemp(OneWire probe){
  byte data[12];
  byte addr[8];

  if ( !probe.search(addr) ||
       OneWire::crc8( addr, 7) != addr[7] ||
       addr[0] != 0x10 && addr[0] != 0x28)
    return -1;

  probe.reset();
  probe.select(addr);
  probe.write(0x44,1);

  byte present = probe.reset();
  probe.select(addr);
  probe.write(0xBE);

  for (int i = 0; i < 9; i++) {
    data[i] = probe.read();
  }
  probe.reset_search();
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB);
  float TemperatureSum = tempRead / 16;
  return TemperatureSum;
}

void setup() {
  pinMode(pin_relay, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("T=XX.XX  A=XX.XX");
}

bool raise_temperature_p(float current, float target){
  return current < target;
}

void adjust_relay(float current_temperature, float target_temperature){
  bool raise = raise_temperature_p(current_temperature, target_temperature);
  if (raise){
    lcd.setCursor(0, 1);
    digitalWrite(pin_relay, HIGH);
    lcd.print("Relay ligado");
  }
  if (!raise){
    lcd.setCursor(0, 1);
    digitalWrite(pin_relay, LOW);
    lcd.print("Relay desligado");
  }
}

void loop() {

  float current_temperature = getTemp(ds);

  adjust_relay(current_temperature, target_temperature);

  lcd.setCursor(2, 0);
  lcd.print(current_temperature);
  lcd.setCursor(11, 0);
  lcd.print(target_temperature);
  delay(100);
}
