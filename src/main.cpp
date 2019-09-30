#include <Arduino.h>
#include <Wire.h>


#define I2C_addr 0x60
#define PS_CONF1_2 0x03

int status;

int read_sensor(){
  int data;
  char addr; 
  addr = I2C_addr >> 1;
  Wire.beginTransmission(addr);
  Wire.write(byte(0x08));
  // Wire.write(byte(0x08));
  // Wire.beginTransmission(addr);

  // Serial.print("Read_Status:");
  // Serial.println(status);
  
  // Wire.requestFrom(addr,2, true);
  //status = Wire.endTransmission(true);
  // data = Wire.read();
  // data <<= 8;
  // data |= Wire.read();

  return data; 
}

void write_sensor(int cmd, int info){
  uint8_t H=0,L=0;

  Wire.beginTransmission(I2C_addr);
  Wire.write(byte(cmd));
  H = info & 0xFF00;
  H >>=8;
  L = info & 0x00FF;
  Wire.write(byte(L));
  Wire.write(byte(H));
  Serial.println(byte(H) +byte(L));
  status = Wire.endTransmission(true);
  Serial.print("Write_Status:");
  Serial.println(status);

}

void config_sensor(){

}
void setup() {
  Wire.begin();
  Serial.begin(115200);

  // put your setup code here, to run once:
}

void loop() {
  int val;
  // write_sensor(PS_CONF1_2, 0x3C46);

  val = read_sensor();
  // Serial.println(val);
  delay(5000);
  // put your main code here, to run repeatedly:
}