
enum RemoteButton {
    CH_MINUS = 0x45,
	  CH = 0x46,
	  CH_Add = 0x47,
	  PREV = 0x44,
	  PLAY = 0x43,
	  NUM_200 = 0xd,
	  NEXT = 0x40,
	  NUM_100 = 0x19,
	  Minus = 0x7,
	  Add = 0x15,
	  EQ = 0x9,
	  NUM0 = 0x16,
	  NUM1 = 0xc,
	  NUM2 = 0x18,
	  NUM3 = 0x5e,
	  NUM4 = 0x8,
	  NUM5 = 0x1c,
	  NUM6 = 0x5a,
	  NUM7 = 0x42,
	  NUM8 = 0x52,
	  NUM9 = 0x4A
}

/**
 * IR remote
 */
//% icon="\uf110" weight=5 color=#2699BF
namespace IR {

  /**
  * initialization
  */
  //% blockId=ir_init
  //% blockGap=20 weight=90
  //% block="connect ir receiver to %pin"
  //% shim=IR::init
  export function init(pin: Pins): void {
    return
  }

  /**
  * button pushed.
  */
  //% blockId=ir_received_event
  //% blockGap=20 weight=70
  //% block="on |%btn| button pressed"
  //% shim=IR::onPressEvent
  export function onPressEvent(btn: RemoteButton, body:Action): void {
    return
  }


}
