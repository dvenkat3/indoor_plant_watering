#ifndef _CLASS_LED_H
#define _CLASS_LED_H

//LED is mapped to a physical pin on the board

class LED{
  private:
    byte pin;

  public:
    LED(byte pin) {
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

    void pwm(byte value /*0 to 255*/) {
      //Ensure LED is connected to a PWM supported pin
      analogWrite(pin, value);
    }

    int get_pin_number() {
      return pin;
    }
};

#endif
