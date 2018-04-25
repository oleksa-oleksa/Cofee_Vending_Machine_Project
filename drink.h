#ifndef DRINK_H
#define DRINK_H

#include "userchoice.h"
#include "opticalsensor.h"
#include "proximitysensor.h"
#include "dc-motor.h"
#include "temperaturesensor.h"
#include "waterheater.h"
#include "flowmeter.h"
#include "brewgroup.h"
#include "milkmaker.h"
#include "rfid_scanner.h"

class Drinktype
{
   private:
      Userchoice drinkSpecs;
      OpticalSensor filllevel[4];
      ProximitySensor cupsensor;
      DC-Motor motor;
      TemperatureSensor temp;
      Waterheater temp;
      Flowmeter flow;
      Brewgroup brew;
      Milkmaker milk;
      RFID_Scanner rfid;
   public:
      Drink();
      ~Drink();
      Drink getinstance(DrinkType type);
      void brewDrink(int extraSugar, int extraMilk);
};

#endif
