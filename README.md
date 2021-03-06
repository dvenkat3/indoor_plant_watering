# indoor_plant_watering

Hardware components needed
  1. Arduino Uno
  2. Mini water pumps
  3. Soil moisture sensor
  4. Water level sensor
  5. Relay module
  6. Analog/Digital multiplexer - CD74HC4067
  7. Shift Register - SN74HC595N

For the full schematic and how to go about building, read through:
https://create.arduino.cc/projecthub/dhruvaV/indoor-plant-watering-9ae3c4?ref=user&ref_id=476029&offset=0
    
How to compile:
  1. After downloading the repository, move only the folders to path <YOUR PC PATH>/Arduino/libraries/
  2. Move files, CLASS_PLANT.h, plantWatering_config.h and Plant_Watering_project.ino, to path <YYOUR PC PATH>/Arduino/<YOUR PROJECT NAME>
  3. Open Plant_Watering_project.ino and hit the compile button and your all good to program the controller

For more additions and changes, read through file MORE_INFO.docx. Has info on what to do for the following
  1. Adding a new plant
  2. Using a different relay board
  3. Using a different moisture sensor
  4. Calibrating the moisutre sensor
