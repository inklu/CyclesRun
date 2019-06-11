#include <CyclesRun.h>

class MyCyclesRun:public CyclesRun{
  protected:
    void onEveryMls(uint64_t mls=0);
    void onEveryCycle(const uint16_t cycleMls, const uint64_t mls=0);
};

void MyCyclesRun::onEveryMls(uint64_t mls){
  Serial.print("X");
}

void MyCyclesRun::onEveryCycle(const uint16_t cycleMls, const uint64_t mls){
  switch(cycleMls){
    case 1000:
      Serial.println("1000");
      break;
    case 2500:
      Serial.println("2500");
      break;
    case 4500:
      Serial.println("4500");
      break;
    case 5000:
      //do something
      break;
  }
}

MyCyclesRun cr;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //no definitions of the array of functions are needed
  
  //define cycles of invocations with array of functions
  cr.addCycle(1000);
  cr.addCycle(2500);
  cr.addCycle(4500);
  cr.addCycle(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  cr.run();
}
