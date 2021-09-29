#include "ddm.h"
#include <SoftWire.h>
#include <AsyncDelay.h>
#include <math.h>

const byte EEPROM_ID = 0x51;
SoftWire sw(SDA, SCL);
byte ddm_memory[256];
char swTxBuffer[16];
char swRxBuffer[16];

float DDM::getRXdbm()
{
  return 10 * log10((float)(ddm_memory[104]<<8 |
  ddm_memory[105]) * 0.0001);
}

float DDM::getTXdbm()
{
  return 10 * log10((float)(ddm_memory[102]<<8 |
  ddm_memory[103]) * 0.0001);
}

float DDM::getRXuw()
{
  return (ddm_memory[104]<<8 | ddm_memory[105]) * 0.1;
}

float DDM::getTXuw()
{
  return (ddm_memory[102]<<8 | ddm_memory[103]) * 0.1;
}

float DDM::getTemp()
{
  return ddm_memory[96] + (float)ddm_memory[97] / 256;
}

float DDM::getVoltage()
{
  return (ddm_memory[98]<<8 | ddm_memory[99]) * 0.0001;
}

float DDM::getTXcurrent()
{
  return (ddm_memory[100]<<8 |
  ddm_memory[101]) * 0.000002;
}

void DDM::dumpAll()
{
  for (int i = 0; i < 256; i++)
  {
    Serial.print("ddm_memory[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(ddm_memory[i], BIN);
  }
}

void DDM::update()
{
  for (int i = 0; i < 256; i++) ddm_memory[i] = read(i);
}

void DDM::update(uint8_t sda, uint8_t scl)
{
  sw.setSda(sda);
  sw.setScl(scl);
  for (int i = 0; i < 256; i++) ddm_memory[i] = read(i);
}

uint8_t DDM::read(unsigned int address)
{
  byte data;
  sw.setTxBuffer(swTxBuffer, sizeof(swTxBuffer));
  sw.setRxBuffer(swRxBuffer, sizeof(swRxBuffer));
  sw.begin();
  sw.beginTransmission(EEPROM_ID);
  sw.write(address);
  sw.endTransmission();
  sw.requestFrom(EEPROM_ID,(byte)1);
  while (sw.available() == 0);
  data = sw.read();
   
  return data;
}
