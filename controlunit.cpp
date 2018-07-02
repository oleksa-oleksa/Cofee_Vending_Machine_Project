// Implemented by Oleksandra Baga
#include "controlunit.h"

ControlUnit::ControlUnit()
{
    activeUserChoice = NULL;
}

void ControlUnit::linkUserChoice(UserChoice *activeUserChoice)
{
    qDebug() << "CONTROL_UNIT: UserChoice linked";
    this->activeUserChoice = activeUserChoice;
}
void ControlUnit::connectRFID(RFID_Scanner *sensor)
{
    cardScanner = sensor;
}
void ControlUnit::connectOptical(OpticalSensor *sensor)
{
    opticalSensor = sensor;
}
void ControlUnit::connectPressure(PressureSensor *sensor)
{
    pressureSensor = sensor;
}
void ControlUnit::connectTemperatur(TemperaturSensor *sensor)
{
    temperatureSensor = sensor;
}

void ControlUnit::connectBrightnessSensor(BrightnessSensor *sensor)
{
    brightSensor = sensor;
}
void ControlUnit::connectFlow(Flowmeter *sensor)
{
    flow = sensor;
}

void ControlUnit::connectLCD(LCD_Display *actuator)
{
    display = actuator;
}
void ControlUnit::connectMotor(DC_Motor *actuator[], int numOfActuators)
{
  for(int i = 0; i < numOfActuators; i++) {
      motor[i] = actuator[i];
  }
}

void ControlUnit::connectHeater(Waterheater *actuator)
{
    heater = actuator;
}
void ControlUnit::connectMilkMaker(Milkmaker *actuator)
{
    milkMaker = actuator;
}

void ControlUnit::connectBrewGroup(Brewgroup *actuator)
{
    brew = actuator;
}


bool ControlUnit::checkIngredients()
{

}

bool ControlUnit::checkStartConditions()
{
    // get Optical Sensor Measurements
    if (opticalSensor->getOpticalFlowSensorsMeasurements() == NO_CUP) {
        qDebug() << "Place your cup first!";
        return false;
    }
    else if (opticalSensor->getOpticalFlowSensorsMeasurements() == FULL_CUP) {
        qDebug() << "Take your cup with prepared drink before order a new one! :)";
        return false;
    }

    else if (opticalSensor->getOpticalFlowSensorsMeasurements() == EMPTY_CUP) {
        // PASSED
        qDebug() << "Cup is OK, liquid can flow!";
    }

    // check if drink is preselected
    if (activeUserChoice->getSelectedDrink() == NO_DRINK) {
        qDebug() << "Select drink first!";
        return false;
    }

    // check if card is still in the card holder
    if (cardScanner->isValidCardInside() != VALID_CARD_INSIDE)
    {
        qDebug() << "Card missed, please return your card back!";
        return false;
    }

    // if it is possible to get here, the payment process could start
    if (activeUserChoice->payDrink())
    {
        qDebug() << "We can start prepare drink! Yahoo!";
        qDebug() << "You can purchase next drink after this one will be prepared!";
        return true;
    }
    else
    {
        qDebug() << "Payment error!";
        qDebug() << "Take your card!";
        return false;
    }
}

void ControlUnit::maintenanceRoutine()
{
    checkIngredients();

// Set sensor and actuator states OK if UNDEFINED

    if (cardScanner->getSensorState() == UNDEFINED)
        cardScanner->setSensorState(OK);

    if (flow->getSensorState() == UNDEFINED)
        flow->setSensorState(OK);

    if (opticalSensor->getSensorState() == UNDEFINED)
        opticalSensor->setSensorState(OK);

    if (pressureSensor->getSensorState() == UNDEFINED)
        pressureSensor->setSensorState(OK);

    if (temperatureSensor->getSensorState() == UNDEFINED)
        temperatureSensor->setSensorState(OK);

    if (brightSensor->getSensorState() == UNDEFINED)
        brightSensor->setSensorState(OK);

    if (display->getActuatorState() == UNDEFINED)
        display->setActuatorState(OK);

//    for (int i = 0; i < AMOUNT_OF_MOTORS; i++)
//    {
//        if (motor[i]->getActuatorState() == UNDEFINED)
//            motor[i]->setActuatorState(OK);
//    }

    if (heater->getActuatorState() == UNDEFINED)
        heater->setActuatorState(OK);

    if (brew->getActuatorState() == UNDEFINED)
        brew->setActuatorState(OK);

    if (milkMaker->getActuatorState() == UNDEFINED)
        milkMaker->setActuatorState(OK);

    qDebug() << "CONTROL_UNIT: Checking Sensors and Actuatots done. State is OK.";
}
