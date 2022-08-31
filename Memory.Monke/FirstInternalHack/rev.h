#pragma once
#include "stdafx.h"
#include <vector>
#include <Windows.h>
#include "geom.h"

//This code is defining the Padding and offsets from the base pointer 
//For example the base pointer for the ent would be 0x10f4f8 and for the local player it would be 0x10f4f4

//SUPER POG POINTER THAT POINTS TO ALL THE COOL GAMEMODES
enum gameModes
{
	TEAMDEATHMATCH = 0,
	COOPEDIT,
	DEATHMATCH,
	SURVIVOR,
	TEAMSURVIVOR,
	CTF,
	PISTOLFRENZY,
	BOTTEAMDEATHMATCH,
	BOTDEATHMATCH,
	LASTSWISSSTANDING,
	ONESHOTONEKILL,
	TEAMONESHOTONEKILL,
	BOTONESHOTONEKILL,
	HUNTTHEFLAG,
	TEAMKEEPTHEFLAG,
	KEEPTHEFLAG,
	TEAMPF,
	TEAMLSS,
	BOTPISTOLFRENZY,
	BOtlSS,
	BOTTEAMSURVIVOR,
	BOTTEAMONESHOTONEKILL,
	NUM
};

class ent;

//Public class defining the offsets and padding 
class weapon
{
public:
	char pad_0x0000[0x4]; //0x0000
	__int32 ID; //0x0004
	ent* owner; //0x0008
	uintptr_t* guninfo; //0x000C
	int* ammo2; //0x0010
	int* ammo; //0x0014
	int* gunWait;
	int shots;
	int breload;
};

//Another public class defining the offsets and padding 
class ent
{
public:
	DWORD vTable; //0x0
	vec3 head; //0x0004
	char _0x0010[36];
	vec3 pos; //0x0034
	vec3 angle; //0x0040
	char _0x004C[37];
	BYTE bScoping; //0x0071
	char _0x0072[134];
	__int32 health; //0x00F8
	__int32 armor; //0x00FC
	char _0x0100[292];
	BYTE bAttacking; //0x0224
	char name[16]; //0x0225
	char _0x0235[247];
	BYTE team; //0x032C
	char _0x032D[11];
	BYTE state; //0x0338
	char _0x0339[59];
	weapon* weapon; //0x0374
	char _0x0378[520];
};

struct entList
{
	ent* ents[31];
};
