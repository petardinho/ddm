#ifndef ddm_h
#define ddm_h

#include <Arduino.h>

class DDM
{
  public:
    float getRXdbm();
    float getTXdbm();
    float getRXuw();
    float getTXuw();
    float getTemp();
    float getVoltage();
    float getTXcurrent();
    void dumpAll();
    void update(uint8_t sda, uint8_t scl);
    void update();

  private:
    uint8_t read(unsigned int address);
};

#endif
