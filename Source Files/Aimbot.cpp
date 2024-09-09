#include "pch.h"
#include "Globals.h"
#include "GameClasses.h"

bool isAimbotOn = false;
// finds the closest enemy to the localPlayer and returns their playerNumber
int findClosestEnemy() {
	// A default error condition
	int closestEnemyPlayerNumber = 0; 

	float smallestDistanceFromPlayer = 99999.0f;
	Ent *me = (Ent*)(*(pStartOfEntityList - 1));
	for (int i = 1; i < currentPlayerCount; i++) {
		Ent *currentEnt = *(Ent**)(*pStartOfEntityList + (i * 4));

		// get relative positions from player
		float relX = currentEnt->FeetX - me->FeetX;
		float relY = currentEnt->FeetY - me->FeetY;
		float relZ = currentEnt->FeetZ - me->FeetZ;

		float distanceFromPlayer = sqrt(relX * relX + relY * relY + relZ * relZ);

		if (distanceFromPlayer < smallestDistanceFromPlayer && currentEnt->TeamNum != me->TeamNum && !currentEnt->isDead) {
			smallestDistanceFromPlayer = distanceFromPlayer;
			closestEnemyPlayerNumber = currentEnt->playerNumber;
		}
	}

	return closestEnemyPlayerNumber;
}

// Given the playerNumber of an entity (intended to be closest enemy), this function directs aim to their head.
void Aimbot(int closestEnemy) {
	if (closestEnemy == 0) {
		return;
	}
	// Due to the way that the entitylist stores entity pointers (ascending playerNumber order except for localPLayer), we don't need to create a for loop to
	// match the playerNumber to the correct enemy
	Ent *enemyToAimAt = *(Ent**)(*pStartOfEntityList + (closestEnemy * 4));
	Ent *me = (Ent*)(*(pStartOfEntityList - 1));

	float relX = enemyToAimAt->FeetX - me->FeetX;
	float relY = enemyToAimAt->FeetY - me->FeetY;
	// it shouldn't matter if we use headCoords or feetCoords as long as both of them are the same type.
	float relZ = enemyToAimAt->zCoord - me->zCoord;

	float newPitch = atanf(relZ / sqrt(relY * relY + relX * relX));
	// The x and y axis is swapped and the y axis sign is inverted, hence the changes to this formula.
	float newYaw = atan2f(relX, -relY);

	me->Pitch = newPitch * ((float)180 / (float)std::numbers::pi);
	me->Yaw = newYaw * ((float)180 / (float)std::numbers::pi);
}