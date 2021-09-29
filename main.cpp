#include <ddm.h>

DDM o;
bool input[16] = {
  1, 0, 0, 0,
  0, 1, 0, 0,
  0, 0, 1, 0,
  0, 0, 0, 1
};

void setup() {
  Serial.begin(9600);

  for (int i = 24; i < 40; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, input[i - 24] > 0 ? LOW : HIGH);
  }
}

void loop() {
  for (int i = 0; i < 4; i++)
  {
    o.update(44 + i * 2, 45 + i * 2);
    Serial.print("Output ");
    Serial.println(i);
    
    Serial.print("RX: ");
    Serial.print(o.getRXuw());
    Serial.print(" uW | ");
    Serial.print(o.getRXdb());
    Serial.println(" dBm");
    
    Serial.print("Temperature: ");
    Serial.print("o.getTemp()");
    Serial.println(" *C");
    
    Serial.print("Voltage: ");
    Serial.print("o.getVoltage()");
    Serial.println(" V");
    
    Serial.println("- - -");
  }
  
  Serial.println("+---------------+");
  delay(5000);
}
