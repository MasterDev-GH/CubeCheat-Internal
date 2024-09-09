#pragma once

extern bool isAimbotOn;
// finds the closest enemy to the localPlayer and returns their playerNumber
int findClosestEnemy();

// Given the playerNumber of an entity (intended to be closest enemy), this function directs aim to their head.
void Aimbot(int closestEnemy);