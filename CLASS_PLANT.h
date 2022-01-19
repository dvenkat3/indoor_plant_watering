#ifndef _CLASS_PLANT_H
#define _CLASS_PLANT_H

#define NUM_EEPROM_BYTES_PER_LOG 3
#define MOIST_SEN_MAX 550
#define MOIST_SEN_MIN 350


class PLANT{
  public:
    VIRTUAL_PIN* moist_level_led;
    ANALOG_IN_SEN* moist_level_sen;
    int moist_level_lwm, moist_level_hwm;
    boolean started_watering;
    VIRTUAL_PIN* pump;
    unsigned long pump_on_duration;
    unsigned long pump_on_mills;
    unsigned long soil_soak_duration;
    boolean continue_watering_till_hwm;
    int eeprom_addr_begin, eeprom_addr_end;
    int eeprom_addr_current; int log_number;
    byte num_pump_on;
    boolean manual_watering_trigger;

    PLANT(byte moist_level_led_pin, 
          byte moist_level_sen_pin, MUX_BASE* mux, byte uc_in_pin, int moist_level_lwm, int moist_level_hwm,
          byte pump_pin, unsigned long pump_on_duration, unsigned long soil_soak_duration,
          int eeprom_addr_begin, int eeprom_addr_end) {
      this->moist_level_led = new VIRTUAL_PIN(moist_level_led_pin);
      this->moist_level_sen = new ANALOG_IN_SEN(moist_level_sen_pin, MOIST_SEN_MIN/*min_val*/, MOIST_SEN_MAX/*max_val*/, mux, uc_in_pin);
      this->moist_level_lwm = moist_level_lwm;
      this->moist_level_hwm = moist_level_hwm;
      this->pump = new VIRTUAL_PIN(pump_pin, 1/*active_low*/);
      this->pump_on_duration = pump_on_duration;
      this->soil_soak_duration = soil_soak_duration;
      this->eeprom_addr_begin = eeprom_addr_begin;
      this->eeprom_addr_end = eeprom_addr_end;
      init();
    }

    void init(){
      //put any init code
      pump_on_mills = 0;
      eeprom_addr_current = eeprom_addr_begin;
      num_pump_on = 0;
      log_number = 0;
      started_watering = 0;
      manual_watering_trigger = 0;
    }

    int get_moisture_level(){
      int moist_level_raw = get_mosture_level_raw_value();
      //Prevent having negative numbers
      if(moist_level_raw > MOIST_SEN_MAX){
        return 0; //0% moisture
      } else if(moist_level_raw < MOIST_SEN_MIN) {
        return 100; //100% moisutre
      } else {
        return moist_level_sen->map_reading_to_percent_reverse();
      }
    }

    int get_mosture_level_raw_value(){
      return moist_level_sen->get_reading();
    }

    void update_moisture_led(){
      int moist_level = get_moisture_level();
      //indicate moisture level on LED
      if(moist_level > moist_level_lwm){
        moist_level_led->on();
      } else {
        moist_level_led->off();
      }
      //Serial.print(" moi pin = ");
      //Serial.print(moist_level_sen->get_pin_number());
      //Serial.print(" moi level = ");
      //Serial.print(moist_level);
    }

    boolean perform_watering_task(){
      
      int moist_level = get_moisture_level();

      //check if soild soak time is done
      boolean soil_soak_time_done = (millis() - pump_on_mills) > soil_soak_duration;
      boolean moist_level_below_lwm = moist_level < moist_level_lwm;
      boolean moist_level_above_hwm = moist_level > moist_level_hwm;
      continue_watering_till_hwm = started_watering & !(pump->is_off() & soil_soak_time_done & moist_level_above_hwm); //Avoid reading bad or sudden burts of high moisture sensor data

      //water the plant
      if(pump->is_off() & ((soil_soak_time_done & (moist_level_below_lwm || continue_watering_till_hwm))
                            | manual_watering_trigger)){
        manual_watering_trigger = 0;
        started_watering = 1;
        pump->on();
        pump_on_mills = millis();
        ++num_pump_on;
        Serial.print(pump->get_bit_pos());
        Serial.println(" is PUMP_ON");
      }

      if(started_watering & moist_level_above_hwm){
        started_watering = 0; //end watering
      }

      //turn-off water pump after set duration
      unsigned long current_mills = millis();
      if(pump->is_on() & ((current_mills - pump_on_mills) > pump_on_duration)){
        Serial.print(pump->get_bit_pos());
        Serial.println(" is PUMP_OFF");
        pump->off();
      }

      //Reset pump_on_mills if mills overflows during pump_on time
      if(pump_on_mills > millis()){
        pump_on_mills = 0;
      }

      return pump->is_on();
      /*
      Serial.print("moist_level = ");
      Serial.print(moist_level);
      Serial.print(" soil_soak_time_done = ");
      Serial.print(soil_soak_time_done);
      Serial.print(" moist_level_below_lwm = ");
      Serial.print(moist_level_below_lwm);
      Serial.print(" continue_watering_till_hwm = ");
      Serial.print(continue_watering_till_hwm);
      Serial.print(" started_watering = ");
      Serial.print(started_watering);
      Serial.print(" moist_level_above_hwm = ");
      Serial.println(moist_level_above_hwm);
      */
    }

    void set_manual_watering_trigger(){
      manual_watering_trigger = 1;
    }

    void log_data(){
      //log moisture and number of time pump was on
      int moist_level = moist_level_sen->get_reading();
      EEPROM.update(eeprom_addr_current++, log_number++);
      EEPROM.update(eeprom_addr_current++, num_pump_on);
      EEPROM.update(eeprom_addr_current++, moist_level/4);

      //reset necessary variable
      num_pump_on = 0;
      if(eeprom_addr_current == eeprom_addr_end){
        eeprom_addr_current = eeprom_addr_begin;
      }
      if(log_number >= 255){
        log_number = 0;
      }
    }

    void watering_data(){
      for(int eeprom_read_loc = eeprom_addr_begin; eeprom_read_loc < eeprom_addr_end; eeprom_read_loc+=NUM_EEPROM_BYTES_PER_LOG){
        Serial.print("LOG NUMBER -> ");
        Serial.print(EEPROM.read(eeprom_read_loc));
        Serial.print(" : num pump on = ");
        Serial.print(EEPROM.read(eeprom_read_loc + 1));         
        Serial.print(", moist level = ");
        Serial.println(EEPROM.read(eeprom_read_loc + 2));
      }
    }

    void config_data(){
      Serial.println("Plant_1");
      
      Serial.print("MOIST LED BIT POS = ");
      Serial.println(moist_level_led->get_bit_pos());
      
      Serial.print("PUMP RELAY BIT POS = ");
      Serial.println(pump->get_bit_pos());

      Serial.print("MOIST LEVEL SEN MUX IN PIN = ");
      Serial.println(moist_level_sen->get_pin_number());

      Serial.print("MOIST LEVEL SEN UC IN PIN = ");
      Serial.println(moist_level_sen->get_uc_in_pin());

      Serial.print("SET EEPROM BEGIN ADDR = ");
      Serial.println(eeprom_addr_begin); 
              
      Serial.print("SET EEPROM END ADDR = ");
      Serial.println(eeprom_addr_end);
      
      Serial.print("SET MOIST LEVEL LWM = ");
      Serial.println(moist_level_lwm);
      
      Serial.print("SET MOIST LEVEL HWM = ");
      Serial.println(moist_level_hwm);

      Serial.print("SET PUMP ON DURATION = ");
      Serial.println(pump_on_duration);
      
      Serial.print("SET SOIL SOAK DURATION = ");
      Serial.println(soil_soak_duration);
    }

};

#endif
