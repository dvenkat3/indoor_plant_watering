#ifndef _CLASS_ANALOG_IN_SEN_H
#define _CLASS_ANALOG_IN_SEN_H

#include "CLASS_MUX_BASE.h"

class ANALOG_IN_SEN{
  private:
    byte pin;
    int min_val, max_val;
    MUX_BASE* mux; int uc_in_pin;

  public:
    ANALOG_IN_SEN(byte pin, int min_val=0, int max_val=ANALOG_IN_MAX, MUX_BASE* mux=NULL, byte uc_in_pin=A0) {
      this->pin = pin;
      this->min_val = min_val;
      this->max_val = max_val;
      this->mux = mux;
      this->uc_in_pin = uc_in_pin;
      init();
    }

    void init(){
      //put any init code
    }

    int get_reading() {
      if(mux != NULL){
        mux->set_select_lines(pin);
        return analogRead(uc_in_pin);
      } else {
        return analogRead(pin);
      }
    }

    int map_reading_to_percent() {
      return map(get_reading()/*value*/, min_val/*fromLow*/, max_val/*fromMax*/, 0/*toLow*/, 100/*toMax*/);
    }

    int map_reading_to_percent_reverse() {
      return map(get_reading(), min_val/*fromLow*/, max_val/*fromMax*/, 100/*toLow*/, 0/*toMax*/);
    }

    int get_pin_number() {
      return pin;
    }

    int get_uc_in_pin() {
      return uc_in_pin;
    }
};

#endif
