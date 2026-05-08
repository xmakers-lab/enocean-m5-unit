#include <M5Stack.h>
#include <SoftwareSerial.h>

SoftwareSerial enoceanSerial(22, 21);

void setup() {
  M5.begin(true, false, true, false);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("EnOcean receive");

  Serial.begin(115200);
  Serial.println("EnOcean receive basic example");

  enoceanSerial.begin(57600);
}

void loop() {
  bool received = false;

  while (enoceanSerial.available()) {
    uint8_t data = enoceanSerial.read();

    if (!received) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.setTextSize(3);
      M5.Lcd.setTextColor(WHITE);
      received = true;
    }

    Serial.print("0x");
    if (data < 16) Serial.print("0");
    Serial.print(data, HEX);
    Serial.print(" ");

    if (data < 16) M5.Lcd.print("0");
    M5.Lcd.print(data, HEX);
    M5.Lcd.print(" ");
  }

  if (received) {
    Serial.println();
  }

  delay(100);
}
