#include <CyclesRun.h>

class MyCyclesRun:public CyclesRun{
  protected:
    void onEveryMls(unsigned long mls=0);
    void onEveryCycle(const uint16_t cycleMls, const unsigned long mls=0);
};

void MyCyclesRun::onEveryMls(unsigned long mls){
  //Serial.print("X");
}

void MyCyclesRun::onEveryCycle(const uint16_t cycleMls, const unsigned long mls){
  switch(cycleMls){
    case 1000:
      Serial.print("1000 ");
      Serial.println(mls);
      break;
    case 2500:
      Serial.print("2500 ");
      Serial.println(mls);
      break;
    case 4500:
      Serial.print("4500 ");
      Serial.println(mls);
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
  
  //define cycles of invocations without array of functions
  cr.addCycle(1000);
  cr.addCycle(2500);
  cr.addCycle(4500);
  cr.addCycle(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  cr.run();
}
