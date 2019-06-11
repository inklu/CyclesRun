#include "CyclesRun.h"

static unsigned long CyclesRun::mls = millis();

CyclesRun::CyclesRun(const cycle _c[]){
  cycleSize = sizeof(_c)/sizeof(cycle);
  cycles = new cyclePrv[cycleSize];
  for(byte i=0;i<cycleSize;i++){
    cycles[i].cycleMls = _c[i].cycleMls;
    if(_c[i].funcs){
      size_t fs = sizeof(_c[i].funcs)/sizeof(pInvoke);
      cycles[i].funcs = new pInvoke[fs];
      for(byte j=0;j<fs;j++){
        cycles[i].funcs[j] = _c[i].funcs[j];
      }
    }
  }
}

void CyclesRun::addCycle(const uint16_t _mls, const pInvoke *_pi, const byte _pi_size){
  cyclePrv *cp;
  cp = new cyclePrv[cycleSize+1];

  for(byte i=0;i<cycleSize;i++){
    cp[i].cycleMls = cycles[i].cycleMls;
    byte fSize = cp[i].cycleFuncSize = cycles[i].cycleFuncSize;
    if(cycles[i].funcs){
      //size_t fs = sizeof(cycles[i].funcs)/sizeof(pInvoke);
      cp[i].funcs = new pInvoke[fSize];
      for(byte j=0;j<fSize;j++){
        cp[i].funcs[j] = cycles[i].funcs[j];
/*        Serial.print(i);
        Serial.print(" ");
        Serial.println(j);*/
      }
      delete [] cycles[i].funcs;
    }
  }
  if(cycles) delete [] cycles;
  
  cp[cycleSize].cycleMls = _mls;
    if(_pi){
      //size_t fs = sizeof(_pi)/sizeof(pInvoke);
      cp[cycleSize].cycleFuncSize = _pi_size;
/*      Serial.print(sizeof(_pi));
      Serial.print(" ");
      Serial.print(sizeof(pInvoke));
      Serial.print(" ");
      Serial.println(fs);*/
      cp[cycleSize].funcs = new pInvoke[_pi_size];
      for(byte j=0;j<_pi_size;j++){
        cp[cycleSize].funcs[j] = _pi[j];
      }
    }
  cycles = cp;
  cycleSize += 1;
}

void CyclesRun::run(unsigned long _mls){
  if(!_mls) mls=millis();
  else mls = _mls;

  onEveryMls(mls); //invoke overloaded function each loop

  for(byte i=0;i<cycleSize;i++){
    if((mls - cycles[i].mls)>cycles[i].cycleMls){
      cycles[i].mls = mls;
      onEveryCycle(cycles[i].cycleMls,cycles[i].mls); //invoke overloaded function each cycle
      if(cycles[i].funcs){
        for(byte j=0;j<cycles[i].cycleFuncSize;j++){
          if(cycles[i].funcs[j]) cycles[i].funcs[j](); //invoke each function through initialization
        }  
      }
    }
  }
}

