#ifndef _plantWatering_pin_config_H
#define _plantWatering_pin_config_H

//This to note. 
//Ensure SOAK time is not same across multiple plants (Minimum of 1min apart).
//  Multiple pumps turning on at the same time will take power away from the arduino and cause shitty behaviour


//Water reservoir
#define WATER_LEVEL_SEN 0
#define WATER_LEVEL_SEN_UC_IN A0
#define WATER_LEVEL_LED 9
#define WATER_LEVEL_LWM 55

//First plant (1) ------------------ 
#define FIRST_PLANT_MOIST_LED 0
#define FIRST_PLANT_PUMP 1
#define FIRST_PLANT_MOIST_LEVEL_SEN 2
#define FIRST_PLANT_MOIST_LEVEL_SEN_UC_IN A0
#define FIRST_PLANT_EEPROM_ADDR_BEGIN 0
#define FIRST_PLANT_EEPROM_ADDR_END 90

#define FIRST_PLANT_MOIST_LEVEL_LWM 15
#define FIRST_PLANT_MOIST_LEVEL_HWM 80
#define FIRST_PLANT_PUMP_ON_DURATION_MS 2000 //3s in ms 
#define FIRST_PLANT_SOIL_SOAK_DURATION_MS 300000 //5min in ms

//Alovera (2) ------------------ 
#define ALOVERA_MOIST_LED 2
#define ALOVERA_PUMP 3
#define ALOVERA_MOIST_LEVEL_SEN 3
#define ALOVERA_MOIST_LEVEL_SEN_UC_IN A0
#define ALOVERA_EEPROM_ADDR_BEGIN 91
#define ALOVERA_EEPROM_ADDR_END 181

#define ALOVERA_MOIST_LEVEL_LWM 10
#define ALOVERA_MOIST_LEVEL_HWM 65
#define ALOVERA_PUMP_ON_DURATION_MS 2000 //2s in ms 
#define ALOVERA_SOIL_SOAK_DURATION_MS 360000 //6min in ms

//Anthurium (3) ------------------
#define ANTHU_MOIST_LED 4
#define ANTHU_PUMP 5
#define ANTHU_MOIST_LEVEL_SEN 4
#define ANTHU_MOIST_LEVEL_SEN_UC_IN A0
#define ANTHU_EEPROM_ADDR_BEGIN 182
#define ANTHU_EEPROM_ADDR_END 272

#define ANTHU_MOIST_LEVEL_LWM 25
#define ANTHU_MOIST_LEVEL_HWM 95
#define ANTHU_PUMP_ON_DURATION_MS 3000 //3s in ms 
#define ANTHU_SOIL_SOAK_DURATION_MS 480000 //8min in ms

//LEAFY (4) ------------------
#define LEAFY_MOIST_LED 6
#define LEAFY_PUMP 7
#define LEAFY_MOIST_LEVEL_SEN 5
#define LEAFY_MOIST_LEVEL_SEN_UC_IN A0
#define LEAFY_EEPROM_ADDR_BEGIN 273
#define LEAFY_EEPROM_ADDR_END 363

#define LEAFY_MOIST_LEVEL_LWM 15
#define LEAFY_MOIST_LEVEL_HWM 70
#define LEAFY_PUMP_ON_DURATION_MS 2000 //2s in ms 
#define LEAFY_SOIL_SOAK_DURATION_MS 420000 //7min in ms

//shift register
#define SHIFT_REG_CLK 11
#define SHIFT_REG_LATCH 12
#define SHIFT_REG_DATA 13              
#define SHIFT_REG_NUM_BYTES 1
#define SHIFT_REG_INIT_STATE 0b10101010 //LED off and PUMP relay off

//MUX
#define MUX_S0 7
#define MUX_S1 6
#define MUX_S2 5
#define MUX_S3 4

#define LOG_DATA_FREQUENCY 43200000 //every 12hr in ms

#endif