#include "CyclesRun.h"

static uint64_t CyclesRun::mls = millis();

CyclesRun::CyclesRun(const cycle _c[]){
  cycleSize = sizeof(_c)/sizeof(cycle);
  cycles = new cyclePrv[cycleSize];
  for(byte i=0;i<cycleSize;i++){
    cycles[i].cycleMls = _c[i].cycleMls;
    if(!_c[i].funcs){
      size_t fs = sizeof(_c[i].funcs)/sizeof(pInvoke);
      cycles[i].funcs = new pInvoke[fs];
      for(byte j=0;j<fs;j++){
        cycles[i].funcs[j] = _c[i].funcs[j];
      }
    }
  }
}

void CyclesRun::addCycle(const uint16_t _mls, const pInvoke _pi[]){
  cyclePrv *cp;
  cp = new cyclePrv[cycleSize+1];

  for(byte i=0;i<cycleSize;i++){
    cp[i].cycleMls = cycles[i].cycleMls;
    if(!cycles[i].funcs){
      size_t fs = sizeof(cycles[i].funcs)/sizeof(pInvoke);
      cp[i].funcs = new pInvoke[fs];
      for(byte j=0;j<fs;j++){
        cp[i].funcs[j] = cycles[i].funcs[j];
      }
      delete [] cycles[i].funcs;
    }
  }
  delete [] cycles;
  
  cp[cycleSize].cycleMls = _mls;
    if(!_pi){
      size_t fs = sizeof(_pi)/sizeof(pInvoke);
      cp[cycleSize].funcs = new pInvoke[fs];
      for(byte j=0;j<fs;j++){
        cp[cycleSize].funcs[j] = _pi[j];
      }
    }
  cycles = cp;
}

void CyclesRun::run(uint64_t _mls){
  if(!_mls) mls=millis();
  else mls = _mls;

  onEveryMls(mls); //invoke overloaded function each loop

  for(byte i=0;i<cycleSize;i++){
    if((mls - cycles[i].mls)>cycles[i].cycleMls){
      cycles[i].mls = mls;
      onEveryCycle(cycles[i].cycleMls,cycles[i].mls); //invoke overloaded function each cycle
      if(!cycles[i].funcs){
        for(byte j=0;j< sizeof(cycles[i].funcs)/sizeof(pInvoke);j++){
          if(cycles[i].funcs[j]) cycles[i].funcs[j](); //invoke each function through initialization
        }  
      }
    }
  }
}

