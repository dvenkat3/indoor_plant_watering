#ifndef _CLASS_SHIFT_REG_H
#define _CLASS_SHIFT_REG_H

class SHIFT_REG{
  private:
    byte latch_pin;
    byte clock_pin;
    byte data_pin;

  public:
    SHIFT_REG(byte clock_pin, byte latch_pin, byte data_pin) {
      this->latch_pin = latch_pin;
      this->clock_pin = clock_pin;
      this->data_pin = data_pin;
      init();
    }

    void init(){
      //put any init code
      pinMode(latch_pin, OUTPUT);
      pinMode(clock_pin, OUTPUT);
      pinMode(data_pin, OUTPUT);
    }

    void write_msb_first(int data, int num_bytes){
      unlatch_data();
      for(int num = (num_bytes - 1); num >= 0; --num){
        shiftOut(data_pin, clock_pin, MSBFIRST, (data >> (num*8)));
      }
    }

    void latch_data(){
      digitalWrite(latch_pin, HIGH);
    }

    void unlatch_data(){
      digitalWrite(latch_pin, LOW);
    }

};

#endif
