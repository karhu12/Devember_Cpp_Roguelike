#pragma once

#include "state.h"

void wColorOn(WINDOW *win, int foreground, int background);
void wColorOff(WINDOW *win, int foreground, int background);
void initializeColors();
int randomNumber(int minValue, int maxValue);
bool checkForEncounter();
