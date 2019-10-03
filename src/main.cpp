#include<Arduino.h>
#include <Wire.h>

#define VCNL_ADDR 0x60
#define PS_CONF_12 0x03
#define PS_CONF_3 0x04


int read_sensor(char cmd){
  byte status;
  int value = 0;
  Wire.beginTransmission(VCNL_ADDR);
  Wire.write(byte(cmd));
  status = Wire.endTransmission(false);
  // Serial.print("Read Status:");
  // Serial.println(status);
  Wire.requestFrom(VCNL_ADDR,2,true);
  value = Wire.read();
  value |= (Wire.read() << 8);
  // value = valo
  return value;
}


void write_sensor(char cmd, uint16_t info){
  byte status;
  uint8_t L=0,H=0;
  L = info & 0x00FF;
  H = (info >>8) & 0xFF;
  Serial.print("Written:");
  Serial.println(info);
  Wire.beginTransmission(VCNL_ADDR);
  Wire.write(cmd);
  Wire.write(L);
  Wire.write(H);
  status = Wire.endTransmission(true);
  // Serial.print("Write Status:");
  // Serial.println(status);
}


void start_config(){
  // write_sensor(PS_CONF_12, 0x1C02); // no interrupt, duty ratio 1/40, integrationtim 1.5T, PS ON;
  write_sensor(PS_CONF_12, 0x1CC2); // no interrupt, duty ratio 1/320, integration 1.5 T, PS 0N
  write_sensor(PS_CONF_3, 0x0080); // reduce current consumption 1/10, sun light block off;
}


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);
  start_config();
}

void loop() {
  int dist;

  dist = read_sensor(0x08);
  // Serial.print("Dist:");
  Serial.println(dist);
  delay(100);
  
}