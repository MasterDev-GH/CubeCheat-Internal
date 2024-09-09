#pragma once
#include "GameClasses.h"

extern bool isAimbotOn;
// finds the closest enemy to the localPlayer and returns their pointer
Ent* findClosestEnemy();

// Given the pointer of an entity (intended to be closest enemy), this function directs aim to their head.
void Aimbot(Ent* closestEnemy);