#pragma once
#include "rev.h"
#include "glDraw.h"
#include "gltext.h"

//Credits to @Rake <-- Really smart dude 
//This is to scale the esp and it is universal so u can use this shiz basically anywhere >:)
const int VIRTUAL_SCREEN_WIDTH = 800;
const int GAME_UNIT_MAGIC = 400;

//Player Stuff For the esp 
const float PLAYER_HEIGHT = 5.25f;
const float PLAYER_WIDTH = 2.0f;
const float EYE_HEIGHT = 4.5f;
const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;

const int ESP_FONT_HEIGHT = 15;
const int ESP_FONT_WIDTH = 9;

class ESP
{
public:
	//I reversed theses offsets 
	//THEY ARE IN MY NOTE BOOK!
	int* gameMode = (int*)(0x50F49C);
	int* numOfPlayers = (int*)(0x50f500);
	float* matrix = (float*)(0x501AE8);
	ent* localPlayer = *(ent**)0x50F4F4;
	entList* entlist = *(entList**)0x50F4F8;

	//I would not use this but i have to due to it being OpenGL
	int viewport[4];

	//These will be used to get the right colour for the ent 
	//Also to check the ent/players team and if it 
	bool IsTeamGame();
	bool IsEnemy(ent* e);
	bool IsValidEnt(ent* ent);

	//I mean this is drawing the boxes (O_o)
	void DrawESPBox(ent* p, vec3 screen, GL::Font& font);
	void Draw(GL::Font& font);
};














//       .-'^'-.
//      '/"'"^"\'
//     :( *   * ):
//     ::)  ,| (::
//     '(       )'          _.
//      '\ --- /'          / /
//    .-'       '-.      .__D
//  ,"      |      \    / : (=|
// :   Y    |    \  \  /  : (=|
// |   |o__/ \__o:   \/  " \ \
// |   |          \     '   "-.
// |    `.    ___ \:._.'
//  ".__  "-" __ \ \
//   .|''---''------|               _
//   / -.          _""-.--.        C )
//  '    '/.___.--'        '._    : |
// |     --_   ^"--...__      ''-.' |
// |        ''---.o)    ""._        |
//  ^'--.._      |o)        '`-..._.|
//         '--.._|o)
//               'O)
 





