#ifndef CYCLESRUN_H
#define CYCLESRUN_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

//// CyclesRun
class CyclesRun{
  public:
    typedef void (*pInvoke)(); //type description of the pointer to void func()
    struct cycle { 
      uint16_t cycleMls;
      pInvoke *funcs;//=nullptr;
    };
    CyclesRun(){};
    CyclesRun(const cycle _c[]);
    void addCycle(const uint16_t _mls, const pInvoke _pi[]=nullptr);
    void run(uint64_t _mls=0);
    void start(){ isRun=true; };
    void pause(){ isRun=false; };
  protected:
    virtual void onEveryMls(uint64_t mls=0){};
    virtual void onEveryCycle(const uint16_t cycleMls, const uint64_t mls=0){};
  private:
    struct cyclePrv:cycle {
      uint16_t mls;
    } *cycles;// = nullptr;
    size_t cycleSize;
    static uint64_t mls;
    bool isRun=false;
};

#endif
