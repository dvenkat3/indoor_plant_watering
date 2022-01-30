#include <EEPROM.h>

#include <arduinoUno_config.h>
#include <CLASS_VIRTUAL_PIN.h>
#include <CLASS_RELAY.h>
#include <CLASS_MUX_BASE.h>
#include <CLASS_MUX_16TO1.h>
#include <CLASS_LED.h>
#include <CLASS_ANALOG_IN_SEN.h>
#include <CLASS_SHIFT_REG.h>

#include "plantWatering_config.h"
#include "CLASS_PLANT.h"


MUX_16to1 A0_in (MUX_S0, MUX_S1, MUX_S2, MUX_S3);

SHIFT_REG sr1 (SHIFT_REG_CLK, SHIFT_REG_LATCH, SHIFT_REG_DATA);
int sr_data;

ANALOG_IN_SEN water_level_sen (WATER_LEVEL_SEN, 0, ANALOG_IN_MAX, &A0_in, WATER_LEVEL_SEN_UC_IN);
LED water_level_led (WATER_LEVEL_LED);

PLANT first_plant (FIRST_PLANT_MOIST_LED, 
                   FIRST_PLANT_MOIST_LEVEL_SEN, &A0_in, FIRST_PLANT_MOIST_LEVEL_SEN_UC_IN, FIRST_PLANT_MOIST_LEVEL_LWM, FIRST_PLANT_MOIST_LEVEL_HWM,
                   FIRST_PLANT_PUMP, FIRST_PLANT_PUMP_ON_DURATION_MS, FIRST_PLANT_SOIL_SOAK_DURATION_MS,
                   FIRST_PLANT_EEPROM_ADDR_BEGIN, FIRST_PLANT_EEPROM_ADDR_END);

PLANT alovera (ALOVERA_MOIST_LED, 
               ALOVERA_MOIST_LEVEL_SEN, &A0_in, ALOVERA_MOIST_LEVEL_SEN_UC_IN, ALOVERA_MOIST_LEVEL_LWM, ALOVERA_MOIST_LEVEL_HWM,
               ALOVERA_PUMP, ALOVERA_PUMP_ON_DURATION_MS, ALOVERA_SOIL_SOAK_DURATION_MS,
               ALOVERA_EEPROM_ADDR_BEGIN, ALOVERA_EEPROM_ADDR_END);

PLANT anthu (ANTHU_MOIST_LED, 
             ANTHU_MOIST_LEVEL_SEN, &A0_in, ANTHU_MOIST_LEVEL_SEN_UC_IN, ANTHU_MOIST_LEVEL_LWM, ANTHU_MOIST_LEVEL_HWM,
             ANTHU_PUMP, ANTHU_PUMP_ON_DURATION_MS, ANTHU_SOIL_SOAK_DURATION_MS,
             ANTHU_EEPROM_ADDR_BEGIN, ANTHU_EEPROM_ADDR_END);

PLANT leafy (LEAFY_MOIST_LED, 
             LEAFY_MOIST_LEVEL_SEN, &A0_in, LEAFY_MOIST_LEVEL_SEN_UC_IN, LEAFY_MOIST_LEVEL_LWM, LEAFY_MOIST_LEVEL_HWM,
             LEAFY_PUMP, LEAFY_PUMP_ON_DURATION_MS, LEAFY_SOIL_SOAK_DURATION_MS,
             LEAFY_EEPROM_ADDR_BEGIN, LEAFY_EEPROM_ADDR_END);

//ADDING A NEW PLANT
/*
PLANT new_plant (NEW_PLANT_MOIST_LED, 
                 NEW_PLANT_MOIST_LEVEL_SEN, &A0_in, NEW_PLANT_MOIST_LEVEL_SEN_UC_IN, NEW_PLANT_MOIST_LEVEL_LWM, NEW_PLANT_MOIST_LEVEL_HWM,
                 NEW_PLANT_PUMP, NEW_PLANT_PUMP_ON_DURATION_MS, NEW_PLANT_SOIL_SOAK_DURATION_MS,
                 NEW_PLANT_EEPROM_ADDR_BEGIN, NEW_PLANT_EEPROM_ADDR_END);
*/

unsigned long last_log_mills;
boolean watering_enabled;
unsigned long debug_count;

void setup() {
 
  //initialize variables
  last_log_mills = 0;
  sr_data = SHIFT_REG_INIT_STATE;
  watering_enabled = 0;
  debug_count = 0;

  //Check all LEDs are working
  //OFF
  water_level_led.off();
  first_plant.moist_level_led->off();
  alovera.moist_level_led->off();
  anthu.moist_level_led->off();
  leafy.moist_level_led->off();
  //ADDING A NEW PLANT
  //new_plant.moist_level_led->off();
  
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());
  bitWrite(sr_data, ANTHU_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, LEAFY_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, alovera.pump->get_state());
  //ADDING A NEW PLANT
  /*
  //bitWrite(sr_data, NEW_PLANT_MOIST_LED, new_plant.moist_level_led->get_state());
  //bitWrite(sr_data, NEW_PLANT_PUMP, new_plant.pump->get_state());
  */
  sr1.latch_data();
  
  delay(1000);

  //ON
  water_level_led.on();
  first_plant.moist_level_led->on();
  alovera.moist_level_led->on();
  anthu.moist_level_led->on();
  leafy.moist_level_led->on();
  //ADDING A NEW PLANT
  /*
  new_plant.moist_level_led->on();
  */
  
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());
  bitWrite(sr_data, ANTHU_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, LEAFY_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, alovera.pump->get_state());
  //ADDING A NEW PLANT
  /*
   * bitWrite(sr_data, NEW_PLANT_MOIST_LED, new_plant.moist_level_led->get_state());
   * bitWrite(sr_data, NEW_PLANT_PUMP, new_plant.pump->get_state());
  */
  sr1.write_msb_first(sr_data, SHIFT_REG_NUM_BYTES);
  sr1.latch_data();  
  
  delay(1000);

  //OFF
  water_level_led.off();
  first_plant.moist_level_led->off();
  alovera.moist_level_led->off();
  anthu.moist_level_led->off();
  leafy.moist_level_led->off();
  //ADDING A NEW PLANT
  /*
   * new_plant.moist_level_led->off();
   */
  
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());
  bitWrite(sr_data, ANTHU_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, LEAFY_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, alovera.pump->get_state());
  //ADDING A NEW PLANT
  /*
   * bitWrite(sr_data, NEW_PLANT_MOIST_LED, new_plant.moist_level_led->get_state());
   * bitWrite(sr_data, NEW_PLANT_PUMP, new_plant.pump->get_state());
   */
  sr1.write_msb_first(sr_data, SHIFT_REG_NUM_BYTES);
  sr1.latch_data();
  
  delay(1000);

  //setup serial for debug
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*Water level tracking and indication begin*/
  int water_level = water_level_sen.get_reading();
  //Serial.println(water_level);
  if(water_level <= WATER_LEVEL_LWM){ //Toggle LED if water level falls below LWM
    water_level_led.on();
    delay(50);
    water_level_led.off();
    delay(50);
  } else if(!watering_enabled){
    water_level_led.on();
  } else {
    water_level_led.off();
  }
  /*Water level tracking and indication end*/

  /*plant watering begin*/
  //This is an optimization to ensure only one relay & pump is ON at any given time. 
  //Plans that need water will get them sequentially
  if((water_level > WATER_LEVEL_LWM) & watering_enabled){
    if(first_plant.pump->is_on()) {
      first_plant.perform_watering_task();
    } 
    else if(alovera.pump->is_on()) {
      alovera.perform_watering_task();
    } 
    else if(anthu.pump->is_on()) {
      anthu.perform_watering_task();
    } 
    else if(leafy.pump->is_on()) {
      leafy.perform_watering_task();
    }
    //ADDING A NEW PLANT
    /*
    else if(new_plant.pump->is_on()){
       new_plant.perform_watering_task();
    }
    */
    else {
      if(first_plant.perform_watering_task()){
        Serial.println("Watering first_plant");
      }
      else if(alovera.perform_watering_task()){
        Serial.println("Watering alovera");
      }
      else if(anthu.perform_watering_task()){
        Serial.println("Watering anthu");
      }
      else if(leafy.perform_watering_task()){
        Serial.println("Watering leafy");
      }
      //ADDING A NEW PLANT
      /*
      else if(new_plant.perform_watering_task()){
        Serial.println("Watering new_plant");
      }
      */
    }
  }
  
  //Serial.print("debug_count");
  //Serial.println(debug_count++);
  first_plant.update_moisture_led();
  //Serial.print("alovera ");
  alovera.update_moisture_led();
  //Serial.print("anthu ");
  anthu.update_moisture_led();
  //Serial.print("leafy ");
  leafy.update_moisture_led();
  //ADDING A NEW PLANT
  /*
  new_plant.update_moisture_led();
  */
  //Serial.println("");
  /*plant watering end*/

  /*Serial cmd processing begin*/
  if(Serial.available() > 0){
    String incoming_cmd = Serial.readString();
    incoming_cmd.trim();
    Serial.print("processing cmd .... ");
    Serial.println(incoming_cmd);
    if(incoming_cmd == "cm"){
      Serial.println(millis());
    } else if(incoming_cmd == "wl"){
      Serial.print("water level = ");
      Serial.println(water_level_sen.get_reading());
    } else if(incoming_cmd == "wat_d"){
      watering_enabled = 0;
      Serial.print("Setting watering_enabled = ");
      Serial.println(watering_enabled);      
    } else if(incoming_cmd == "wat_e"){
      watering_enabled = 1;
      Serial.print("Setting watering_enabled = ");
      Serial.println(watering_enabled);      
    } else if(incoming_cmd == "help"){
      Serial.println("wl - water level");
      Serial.println("cm - currnet millis");
      Serial.println("<plant>_d   - plant data stored in EEPROM data");
      Serial.println("<plant>_c   - plant pin and other config data");
      Serial.println("<plant>_ms  - plant moisture and state data");
      Serial.println("<plant>_mwt - manual watering trigger");
      Serial.println("<plant>     - p1, alo, ant, lef");
    }
    
    else if(incoming_cmd == "p1_d"){
      first_plant.watering_data();
    } else if(incoming_cmd == "p1_c"){
      first_plant.config_data();
    } else if(incoming_cmd == "p1_ms"){
      first_plant.moisture_data();
    } else if(incoming_cmd == "p1_mwt"){
      first_plant.set_manual_watering_trigger();
    }
    
    else if(incoming_cmd == "alo_d"){
      alovera.watering_data();
    } else if(incoming_cmd == "alo_c"){
      alovera.config_data();
    } else if(incoming_cmd == "alo_ms"){
      alovera.moisture_data();
    } else if(incoming_cmd == "alo_mwt"){
      alovera.set_manual_watering_trigger();
    }
    
    else if(incoming_cmd == "ant_d"){
      anthu.watering_data();
    } else if(incoming_cmd == "ant_c"){
      anthu.config_data();
    } else if(incoming_cmd == "ant_ms"){
      anthu.moisture_data();
    } else if(incoming_cmd == "ant_mwt"){
      anthu.set_manual_watering_trigger();
    }
    
    else if(incoming_cmd == "lef_d"){
      leafy.watering_data();
    } else if(incoming_cmd == "lef_c"){
      leafy.config_data();
    } else if(incoming_cmd == "lef_ms"){
      anthu.moisture_data();
    } else if(incoming_cmd == "lef_mwt"){
      leafy.set_manual_watering_trigger();
    }

    //ADDING A NEW PLANT
    /*
    else if(incoming_cmd == "np_d"){
      new_plant.watering_data();
    } else if(incoming_cmd == "np_c"){
      new_plant.config_data();
    } else if(incoming_cmd == "np_ms"){
      anthu.moisture_data();
    } else if(incoming_cmd == "np_mwt"){
      new_plant.set_manual_watering_trigger();
    }    
    */
    
    Serial.println(); 
  }
  /*Serial cmd processing end*/

  /*data loggin begin*/
  if((millis() - last_log_mills) > LOG_DATA_FREQUENCY){
    Serial.println("DEBUG: logging data .... ");
    first_plant.log_data();
    alovera.log_data();
    anthu.log_data();
    leafy.log_data();
    //ADDING A NEW PLANT
    /*
    new_plant.log_data();
    */
    last_log_mills = millis();
  }

  //Reset pump_on_mills if mills overflows during last_log_mills duration
  if(last_log_mills > millis()){
    last_log_mills = 0;
  }
  /*data loggin end*/

  /*Send data to shift register begin*/
  sr_data = SHIFT_REG_INIT_STATE;
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());

  bitWrite(sr_data, ANTHU_MOIST_LED, anthu.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, anthu.pump->get_state());

  bitWrite(sr_data, LEAFY_MOIST_LED, leafy.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, leafy.pump->get_state());

  //ADDING A NEW PLANT
  /*
  bitWrite(sr_data, NEW_PLANT_MOIST_LED, new_plant.moist_level_led->get_state());
  bitWrite(sr_data, NEW_PLANT_PUMP, new_plant.pump->get_state());
  */
  
  sr1.write_msb_first(sr_data, SHIFT_REG_NUM_BYTES);
  sr1.latch_data();
  /*Send data to shift register end*/
  
  
}
