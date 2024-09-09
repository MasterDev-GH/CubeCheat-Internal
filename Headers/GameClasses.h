#pragma once
#include <cstdint>

class Ent {
public:
	char pad_0000[4]; //0x0000
	float xCoord; //0x0004
	float yCoord; //0x0008
	float zCoord; //0x000C
	char pad_0010[24]; //0x0010
	float FeetX; //0x0028
	float FeetY; //0x002C
	float FeetZ; //0x0030
	float Yaw; //0x0034
	float Pitch; //0x0038
	char pad_003C[176]; //0x003C
	int32_t health; //0x00EC
	char pad_00F0[212]; //0x00F0
	int32_t playerNumber; //0x01C4
	char pad_01C8[61]; //0x01C8
	char N000009E4[16]; //0x0205
	char pad_0215[247]; //0x0215
	int32_t TeamNum; //0x030C
	char pad_0310[8]; //0x0310
	bool isDead; //0x0318
}; //Size: 0x0319