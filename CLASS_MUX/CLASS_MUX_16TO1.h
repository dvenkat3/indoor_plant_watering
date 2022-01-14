#ifndef _CLASS_MUX_16TO1_H
#define _CLASS_MUX_16TO1_H

class MUX_16to1 : public MUX_BASE {
  public:
    byte pin_s0, pin_s1, pin_s2, pin_s3;

    MUX_16to1(byte pin_s0, byte pin_s1, byte pin_s2, byte pin_s3){
      this->pin_s0 = pin_s0;
      this->pin_s1 = pin_s1;
      this->pin_s2 = pin_s2;
      this->pin_s3 = pin_s3;
      init();
    }

    void init(){
      pinMode(pin_s0, OUTPUT);
      pinMode(pin_s1, OUTPUT);
      pinMode(pin_s2, OUTPUT);
      pinMode(pin_s3, OUTPUT);
    }

    void set_select_lines(int value){
      //Serial.print("MUX_16to1::set_select_lines: Setting value=");
      //Serial.println(value);
      digitalWrite(pin_s0, bitRead(value,0));
      digitalWrite(pin_s1, bitRead(value,1));
      digitalWrite(pin_s2, bitRead(value,2));
      digitalWrite(pin_s3, bitRead(value,3));
    }
};

#endif
