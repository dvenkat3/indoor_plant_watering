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

unsigned long last_log_mills;

void setup() {
  //initialize variables
  last_log_mills = 0;
  sr_data = SHIFT_REG_INIT_STATE;

  //Check all LEDs are working
  //OFF
  water_level_led.off();
  first_plant.moist_level_led->off();
  alovera.moist_level_led->off();
  anthu.moist_level_led->off();
  leafy.moist_level_led->off();
  
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());
  bitWrite(sr_data, ANTHU_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, LEAFY_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, alovera.pump->get_state());
  sr1.latch_data();
  
  delay(1000);

  //ON
  water_level_led.on();
  first_plant.moist_level_led->on();
  alovera.moist_level_led->on();
  anthu.moist_level_led->on();
  leafy.moist_level_led->on();
  
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());
  bitWrite(sr_data, ANTHU_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, LEAFY_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, alovera.pump->get_state());
  sr1.write_msb_first(sr_data, SHIFT_REG_NUM_BYTES);
  sr1.latch_data();  
  
  delay(1000);

  //OFF
  water_level_led.off();
  first_plant.moist_level_led->off();
  alovera.moist_level_led->off();
  anthu.moist_level_led->off();
  leafy.moist_level_led->off();
  
  bitWrite(sr_data, FIRST_PLANT_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, FIRST_PLANT_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, ALOVERA_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, ALOVERA_PUMP, alovera.pump->get_state());
  bitWrite(sr_data, ANTHU_MOIST_LED, first_plant.moist_level_led->get_state());
  bitWrite(sr_data, ANTHU_PUMP, first_plant.pump->get_state());
  bitWrite(sr_data, LEAFY_MOIST_LED, alovera.moist_level_led->get_state());
  bitWrite(sr_data, LEAFY_PUMP, alovera.pump->get_state());
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
  } else {
    water_level_led.off();
  }
  /*Water level tracking and indication end*/

  /*plant watering begin*/
  if(water_level > WATER_LEVEL_LWM){
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
  }
  first_plant.update_moisture_led();
  alovera.update_moisture_led();
  anthu.update_moisture_led();
  leafy.update_moisture_led();
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
      Serial.print("raw_sensor_data = ");
      Serial.print(first_plant.get_mosture_level_raw_value());
      Serial.print(" converted moisture % = ");
      Serial.print(first_plant.get_moisture_level());
      Serial.print(" continue_watering_till_hwm = ");
      Serial.print(first_plant.continue_watering_till_hwm);
      Serial.println("");
    } else if(incoming_cmd == "p1_mwt"){
      first_plant.set_manual_watering_trigger();
    }
    
    else if(incoming_cmd == "alo_d"){
      alovera.watering_data();
    } else if(incoming_cmd == "alo_c"){
      alovera.config_data();
    } else if(incoming_cmd == "alo_ms"){
      Serial.print("raw_sensor_data = ");
      Serial.print(alovera.get_mosture_level_raw_value());
      Serial.print(" converted moisture % = ");
      Serial.print(alovera.get_moisture_level());
      Serial.print(" continue_watering_till_hwm = ");
      Serial.print(alovera.continue_watering_till_hwm);
      Serial.println("");
    } else if(incoming_cmd == "alo_mwt"){
      alovera.set_manual_watering_trigger();
    }
    
    else if(incoming_cmd == "ant_d"){
      anthu.watering_data();
    } else if(incoming_cmd == "ant_c"){
      anthu.config_data();
    } else if(incoming_cmd == "ant_ms"){
      Serial.print("raw_sensor_data = ");
      Serial.print(anthu.get_mosture_level_raw_value());
      Serial.print(" converted moisture % = ");
      Serial.print(anthu.get_moisture_level());
      Serial.print(" continue_watering_till_hwm = ");
      Serial.print(anthu.continue_watering_till_hwm);
      Serial.println("");
    } else if(incoming_cmd == "ant_mwt"){
      anthu.set_manual_watering_trigger();
    }
    
    else if(incoming_cmd == "lef_d"){
      leafy.watering_data();
    } else if(incoming_cmd == "lef_c"){
      leafy.config_data();
    } else if(incoming_cmd == "lef_ms"){
      Serial.print("raw_sensor_data = ");
      Serial.print(leafy.get_mosture_level_raw_value());
      Serial.print(" converted moisture % = ");
      Serial.print(leafy.get_moisture_level());
      Serial.print(" continue_watering_till_hwm = ");
      Serial.print(leafy.continue_watering_till_hwm);
      Serial.println("");
    } else if(incoming_cmd == "lef_mwt"){
      leafy.set_manual_watering_trigger();
    }
    
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
  
  sr1.write_msb_first(sr_data, SHIFT_REG_NUM_BYTES);
  sr1.latch_data();
  /*Send data to shift register end*/
  
  
}
