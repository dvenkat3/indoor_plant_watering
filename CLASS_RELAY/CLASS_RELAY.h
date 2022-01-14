#ifndef _CLASS_RELAY_H
#define _CLASS_RELAY_H

class RELAY{
  private:
    byte pin;

  public:
    RELAY(byte pin) {
      this->pin = pin;
      init();
    }

    void init(){
      pinMode(pin, OUTPUT);
    }

    void on() {
      digitalWrite(pin, HIGH);
    }

    void off() {
      digitalWrite(pin, LOW);
    }

    void toggle() {
      boolean current_state = digitalRead(pin);
      digitalWrite(pin, !current_state);
    }

    bool is_on() {
      return (digitalRead(pin) == 1);
    }

    bool is_off() {
      return (digitalRead(pin) == 0);
    }

    int get_pin_number() {
      return pin;
    }

};

#endif
