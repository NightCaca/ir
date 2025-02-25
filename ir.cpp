#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;
typedef vector<Action> vA;

enum class RemoteButton {
    //% block="CHMinus"
    CHMinus = 0x45,
    //% block="CH"
    CH = 0x46,
    //% block="CHPlus"
    CHPlus = 0x47,
    //% block="PREV"
    PREV = 0x44,
    //% block="NEXT"
    NEXT = 0x40,
    //% block="PLAYORPAUSE"
    PLAYORPAUSE = 0x43,
    //% block="VOLMinus"
    VOLMinus = 0x07,
    //% block="VOLPlus"
    VOLPlus = 0x15,
    //% block="EQ"
    EQ = 0x09,
    //% block="ONEHUNDREDPLUS"
    ONEHUNDREDPLUS = 0x19,
    //% block="TWOHUNDREDPLUS"
    TWOHUNDREDPLUS = 0x0D,
    //% block="NUM0"
    NUM0 = 0x16,
    //% block="NUM1"
    NUM1 = 0x0C,
    //% block="NUM2"
    NUM2 = 0x18,
    //% block="NUM3"
    NUM3 = 0x5E,
    //% block="NUM4"
    NUM4 = 0x08,
    //% block="NUM5"
    NUM5 = 0x1C,
    //% block="NUM6"
    NUM6 = 0x5A,
    //% block="NUM7"
    NUM7 = 0x42,
    //% block="NUM8"
    NUM8 = 0x52,
    //% block="NUM9"
    NUM9 = 0x4A,
};

enum class Pins{
    P0=  3,
    P1=  2,
    P2=  1,
    P3=  4,
    P4=  5,
    P5=  17,
    P6=  12,
    P7=  11,
    P8=  18,
    P9=  10,
    P10= 6,
    P11= 26,
    P12= 20,
    P13= 23,
    P14= 22,
    P15= 21,
    P16= 16,
    P19= 0,
    P20= 30
};

namespace IR {
  map<RemoteButton, vA> actions;
  map<RemoteButton, uint32_t> lastact;
  Timer tsb;
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;

  void cA(vA runner){for(int i=0;i<runner.size();i++){runAction0(runner[i]);} }

  void onReceivable(){
    int x = rx->getData(&fmt, buf, 32 * 8);
    if(actions.find((RemoteButton)buf[2]) == actions.end()) return;
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
    cA(actions[(RemoteButton)buf[2]]);
  }


  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){
        uBit.sleep(50);
      }
      onReceivable();
    }
  }

  //%
  void init(Pins pin){
    rx = new ReceiverIR((PinName)pin);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }

  //%
  void onPressEvent(RemoteButton btn, Action body) {
    actions[btn].push_back(body);
  }

}
