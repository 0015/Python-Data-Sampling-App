#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#define I2C_SDA 21
#define I2C_SCL 22

TwoWire I2CMPU = TwoWire(0);
Adafruit_MPU6050 mpu;
TFT_eSPI tft = TFT_eSPI();

void setup(){
  Serial.begin(115200);
  displayInit();

  I2CMPU.begin(I2C_SDA, I2C_SCL);

  if (!mpu.begin(104, &I2CMPU, 0x68)) {
    printString("No MPU6050 detected", TFT_BLACK, TFT_YELLOW);
    while (1) {
      delay(10);
    }
  }

  delay(100);   

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);

  printString("READING...", TFT_BLACK, TFT_DARKGREEN);
  delay(100);
}

void loop(){

  delay(7); // To make sampling rate around 100hz

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print(g.gyro.x);
  Serial.print(", ");
  Serial.print(g.gyro.y);
  Serial.print(", ");
  Serial.print(g.gyro.z);
  Serial.print(", ");

  Serial.print(a.acceleration.x);
  Serial.print(", ");
  Serial.print(a.acceleration.y);
  Serial.print(", ");
  Serial.println(a.acceleration.z);
}

void displayInit(){
  tft.begin();
  tft.setRotation(1);
  tft.setTextColor(TFT_WHITE,TFT_BLACK); 
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.setTextFont(4);
  tft.setTextDatum(MC_DATUM);
}

void printString(String text, uint16_t textColor, uint16_t bgColor){
  tft.fillScreen(bgColor);
  tft.setTextColor(textColor, bgColor);
  tft.drawCentreString(text, tft.width()/2, tft.height()/2, 4);
}