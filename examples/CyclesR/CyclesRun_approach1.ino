#include <CyclesRun.h>

void f1(){
  Serial.println("f1");
}

void f2(){
  Serial.println("f2");
}

void f3(){
  Serial.println("f3");
}

void f4(){
  Serial.println("f4");
}

/*CyclesRun::cycle cyc[] = {{1000,{f1}},
                          {2000,{f2}}};*/

//CyclesRun cr = new CyclesRun{1000, { f1 }};
/*              {2500,{f2}},
              {4500,{f4,f3}} });*/

CyclesRun cr;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //define array of functions to be invoked each cycle
  CyclesRun::pInvoke pi1000[]={f1,f2},
                     pi2500[]={f2,f3},
                     pi4500[]={f4},
                     pi5000[]={};
  
  //define cycles of invocations with array of functions
  cr.addCycle(1000,pi1000);
  cr.addCycle(2500,pi2500);
  cr.addCycle(4500,pi4500);
  cr.addCycle(5000,pi5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  cr.run();
}
