#ifndef _CLASS_VIRTUAL_PIN_H
#define _CLASS_VIRTUAL_PIN_H

//LED is NOT mapped to a physical pin on the board. Use it for LED virtual state to be retrieved later
//Use case - LED is connected to 74HC595 (shift Register)

class VIRTUAL_PIN{
  private:
    boolean state;
    byte bit_pos;
    boolean active_low;

  public:
    VIRTUAL_PIN(byte bit_pos, boolean active_low = 0) {
      this->bit_pos = bit_pos;
      this->active_low = active_low;
      init();
    }

    void init(){
      if(active_low){
        state = 1; 
      } else {
        state = 0;
      }
    }

    void on() {
      if(active_low){
        state = 0; 
      } else {
        state = 1;
      }
    }

    boolean is_on() {
      if(active_low){
        return state == 0;
      } else {
        return state == 1;
      }
    }

    void off() {
      if(active_low){
        state = 1; 
      } else {
        state = 0;
      }        
    }

    boolean is_off() {
      if(active_low){
        return state == 1; 
      } else {
        return state == 0;
      } 
    }

    byte get_bit_pos() {
      return bit_pos;
    }

    boolean get_state() {
      return state;
    }
};

#endif
