// Exisiting file implemented for project by Oleksandra Baga
#include "flowmeter.h"

Flowmeter::Flowmeter()
{
    sensorType = FLOW;
    sensorState = UNDEFINED;
    recipeAmountOfLiquid = 0;
    hasPreparedDrink = false;
}


Flowmeter::~Flowmeter() {

}

int Flowmeter::getRecipeAmountOfLiquid() const {
    return recipeAmountOfLiquid;
}

void Flowmeter::setRecipeAmountOfLiquid(UserChoice *activeUserChoice) {
    recipeAmountOfLiquid = activeUserChoice->getHotWaterAmount();
}

bool Flowmeter::mainFlowmeterRoutine() {
    for (int i = 0; i < recipeAmountOfLiquid; i++) {
        // we will do here some simulation
    }

    // All is OK, drink is ready
    recipeAmountOfLiquid = 0;
    hasPreparedDrink = true;

    return hasPreparedDrink;
}

bool Flowmeter::getHasPreparedDrink() const {
    qDebug() << "FLOWMETER: A drink just have been prepared: " << hasPreparedDrink;
    return hasPreparedDrink;
}

void Flowmeter::setHasPreparedDrink(bool flag) {
    hasPreparedDrink = flag;
}
