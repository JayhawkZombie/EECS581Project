#include "GameMain.h"
#include "RPGTest.h"
#include <iostream>
#include <map>
#include "ListReader.h"
#include "MainCharacter.h"
GameMain::GameMain()
{
	ListReader list;

	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");

	MonsterTree pyro = MonsterTree();
	pyro.myvec.rbegin();
	pyro.TreeType = 4;


	MonsterType***** MonsterArray = new MonsterType****[6];
	//std::cout << "Size of Monster Array: " << sizeof(MonsterArray << "\n\n");
	MonsterArray[0] = new MonsterType***[6];
	MonsterArray[0][0] = new MonsterType**[5];
	//MonsterArray[0][0][0] would be for eggs, and we're not doing that right now
	MonsterArray[0][0][1] = new MonsterType*[1];
	MonsterArray[0][0][1][0] = myArray[0];
	MonsterArray[0][0][2] = new MonsterType*[3];
	MonsterArray[0][0][2][0] = myArray[1];
	MonsterArray[0][0][2][1] = myArray[2];
	MonsterArray[0][0][2][2] = myArray[3];
	MonsterArray[0][0][3] = new MonsterType*[4];
	MonsterArray[0][0][3][0] = myArray[4];
	MonsterArray[0][0][3][1] = myArray[5];
	MonsterArray[0][0][3][2] = myArray[6];
	MonsterArray[0][0][3][3] = myArray[7];
	MonsterArray[0][0][4] = new MonsterType*[4];
	MonsterArray[0][0][4][0] = myArray[8];
	MonsterArray[0][0][4][1] = myArray[9];
	MonsterArray[0][0][4][2] = myArray[10];
	MonsterArray[0][0][4][3] = myArray[11];
	MonsterArray[0][1] = new MonsterType**[5];
	MonsterArray[0][1][1] = new MonsterType*[1];
	MonsterArray[0][1][1][0] = myArray[12];
	MonsterArray[0][1][2] = new MonsterType*[2];
	MonsterArray[0][1][2][0] = myArray[13];
	MonsterArray[0][1][2][1] = myArray[14];
	MonsterArray[0][1][3] = new MonsterType*[2];
	MonsterArray[0][1][3][0] = myArray[15];
	MonsterArray[0][1][3][1] = myArray[16];
	MonsterArray[0][1][4] = new MonsterType*[2];
	MonsterArray[0][1][4][0] = myArray[17];
	MonsterArray[0][1][4][1] = myArray[18];
	MonsterArray[0][2] = new MonsterType**[5];
	MonsterArray[0][2][1] = new MonsterType*[1];
	MonsterArray[0][2][1][0] = myArray[19];
	MonsterArray[0][2][2] = new MonsterType*[3];
	MonsterArray[0][2][2][0] = myArray[20];
	MonsterArray[0][2][2][1] = myArray[21];
	MonsterArray[0][2][2][2] = myArray[22];
	MonsterArray[0][2][3] = new MonsterType*[3];
	MonsterArray[0][2][3][0] = myArray[23];
	MonsterArray[0][2][3][1] = myArray[24];
	MonsterArray[0][2][3][2] = myArray[25];
	MonsterArray[0][2][4] = new MonsterType*[3];
	MonsterArray[0][2][4][0] = myArray[26];
	MonsterArray[0][2][4][1] = myArray[27];
	MonsterArray[0][2][4][2] = myArray[28];
	MonsterArray[0][3] = new MonsterType**[5];
	MonsterArray[0][3][1] = new MonsterType*[1];
	MonsterArray[0][3][1][0] = myArray[29];
	MonsterArray[0][3][2] = new MonsterType*[2];
	MonsterArray[0][3][2][0] = myArray[30];
	MonsterArray[0][3][2][1] = myArray[31];
	MonsterArray[0][3][3] = new MonsterType*[2];
	MonsterArray[0][3][3][0] = myArray[32];
	MonsterArray[0][3][3][1] = myArray[33];
	MonsterArray[0][3][4] = new MonsterType*[2];
	MonsterArray[0][3][4][0] = myArray[34];
	MonsterArray[0][3][4][1] = myArray[35];
	MonsterArray[0][4] = new MonsterType**[5];
	MonsterArray[0][4][1] = new MonsterType*[1];
	MonsterArray[0][4][1][0] = myArray[36];
	MonsterArray[0][4][2] = new MonsterType*[2];
	MonsterArray[0][4][2][0] = myArray[37];
	MonsterArray[0][4][2][1] = myArray[38];
	MonsterArray[0][4][3] = new MonsterType*[2];
	MonsterArray[0][4][3][0] = myArray[39];
	MonsterArray[0][4][3][1] = myArray[40];
	MonsterArray[0][4][4] = new MonsterType*[2];
	MonsterArray[0][4][4][0] = myArray[41];
	MonsterArray[0][4][4][1] = myArray[42];
	MonsterArray[0][5] = new MonsterType**[5];
	MonsterArray[0][5][1] = new MonsterType*[1];
	MonsterArray[0][5][1][0] = myArray[43];
	MonsterArray[0][5][2] = new MonsterType*[2];
	MonsterArray[0][5][2][0] = myArray[44];
	MonsterArray[0][5][2][1] = myArray[45];
	MonsterArray[0][5][3] = new MonsterType*[2];
	MonsterArray[0][5][3][0] = myArray[46];
	MonsterArray[0][5][3][1] = myArray[47];
	MonsterArray[0][5][4] = new MonsterType*[2];
	MonsterArray[0][5][4][0] = myArray[48];
	MonsterArray[0][5][4][1] = myArray[49];
	MonsterArray[1] = new MonsterType***[6];
	MonsterArray[1][0] = new MonsterType**[5];
	MonsterArray[1][0][1] = new MonsterType*[1];
	MonsterArray[1][0][1][0] = myArray[50];
	MonsterArray[1][0][2] = new MonsterType*[1];
	MonsterArray[1][0][2][0] = myArray[51];
	MonsterArray[1][0][3] = new MonsterType*[1];
	MonsterArray[1][0][3][0] = myArray[52];
	MonsterArray[1][0][4] = new MonsterType*[1];
	MonsterArray[1][0][4][0] = myArray[53];
	MonsterArray[1][1] = new MonsterType**[5];
	MonsterArray[1][1][1] = new MonsterType*[1];
	MonsterArray[1][1][1][0] = myArray[54];
	MonsterArray[1][1][2] = new MonsterType*[3];
	MonsterArray[1][1][2][0] = myArray[55];
	MonsterArray[1][1][2][1] = myArray[56];
	MonsterArray[1][1][2][1] = myArray[57];
	MonsterArray[1][1][3] = new MonsterType*[4];
	MonsterArray[1][1][3][0] = myArray[58];
	MonsterArray[1][1][3][1] = myArray[59];
	MonsterArray[1][1][3][2] = myArray[60];
	MonsterArray[1][1][3][3] = myArray[61];
	MonsterArray[1][1][4] = new MonsterType*[4];
	MonsterArray[1][1][4][0] = myArray[62];
	MonsterArray[1][1][4][1] = myArray[63];
	MonsterArray[1][1][4][2] = myArray[64];
	MonsterArray[1][1][4][3] = myArray[65];
	MonsterArray[1][2] = new MonsterType**[5];
	MonsterArray[1][2][1] = new MonsterType*[1];
	MonsterArray[1][2][1][0] = myArray[66];
	MonsterArray[1][2][2] = new MonsterType*[3];
	MonsterArray[1][2][2][0] = myArray[67];
	MonsterArray[1][2][2][1] = myArray[68];
	MonsterArray[1][2][2][2] = myArray[69];
	MonsterArray[1][2][3] = new MonsterType*[3];
	MonsterArray[1][2][3][0] = myArray[70];
	MonsterArray[1][2][3][1] = myArray[71];
	MonsterArray[1][2][3][2] = myArray[72];
	MonsterArray[1][2][4] = new MonsterType*[3];
	MonsterArray[1][2][4][0] = myArray[73];
	MonsterArray[1][2][4][1] = myArray[74];
	MonsterArray[1][2][4][2] = myArray[75];
	MonsterArray[1][3] = new MonsterType**[5];
	MonsterArray[1][3][1] = new MonsterType*[1];
	MonsterArray[1][3][1][0] = myArray[76];
	MonsterArray[1][3][2] = new MonsterType*[3];
	MonsterArray[1][3][2][0] = myArray[77];
	MonsterArray[1][3][2][1] = myArray[78];
	MonsterArray[1][3][2][2] = myArray[79];
	MonsterArray[1][3][3] = new MonsterType*[3];
	MonsterArray[1][3][3][0] = myArray[80];
	MonsterArray[1][3][3][1] = myArray[81];
	MonsterArray[1][3][3][2] = myArray[82];
	MonsterArray[1][3][4] = new MonsterType*[3];
	MonsterArray[1][3][4][0] = myArray[83];
	MonsterArray[1][3][4][1] = myArray[84];
	MonsterArray[1][3][4][2] = myArray[85];
	MonsterArray[1][4] = new MonsterType**[5];
	MonsterArray[1][4][1] = new MonsterType*[1];
	MonsterArray[1][4][1][0] = myArray[86];
	MonsterArray[1][4][2] = new MonsterType*[3];
	MonsterArray[1][4][2][0] = myArray[87];
	MonsterArray[1][4][2][1] = myArray[88];
	MonsterArray[1][4][2][2] = myArray[89];
	MonsterArray[1][4][3] = new MonsterType*[4];
	MonsterArray[1][4][3][0] = myArray[90];
	MonsterArray[1][4][3][1] = myArray[91];
	MonsterArray[1][4][3][2] = myArray[92];
	MonsterArray[1][4][3][3] = myArray[93];
	MonsterArray[1][4][4] = new MonsterType*[4];
	MonsterArray[1][4][4][0] = myArray[94];
	MonsterArray[1][4][4][1] = myArray[95];
	MonsterArray[1][4][4][2] = myArray[96];
	MonsterArray[1][4][4][3] = myArray[97];
	MonsterArray[1][5] = new MonsterType**[5];
	MonsterArray[1][5][1] = new MonsterType*[1];
	MonsterArray[1][5][1][0] = myArray[98];
	MonsterArray[1][5][2] = new MonsterType*[3];
	MonsterArray[1][5][2][0] = myArray[99];
	MonsterArray[1][5][2][1] = myArray[100];
	MonsterArray[1][5][2][2] = myArray[101];
	MonsterArray[1][5][3] = new MonsterType*[4];
	MonsterArray[1][5][3][0] = myArray[102];
	MonsterArray[1][5][3][1] = myArray[103];
	MonsterArray[1][5][3][2] = myArray[104];
	MonsterArray[1][5][3][3] = myArray[105];
	MonsterArray[1][5][4] = new MonsterType*[4];
	MonsterArray[1][5][4][0] = myArray[106];
	MonsterArray[1][5][4][1] = myArray[107];
	MonsterArray[1][5][4][2] = myArray[108];
	MonsterArray[1][5][4][3] = myArray[109];
	MonsterArray[2] = new MonsterType***[6];
	MonsterArray[2][0] = new MonsterType**[5];
	MonsterArray[2][0][1] = new MonsterType*[1];
	MonsterArray[2][0][1][0] = myArray[110];
	MonsterArray[2][0][2] = new MonsterType*[3];
	MonsterArray[2][0][2][0] = myArray[111];
	MonsterArray[2][0][2][1] = myArray[112];
	MonsterArray[2][0][2][2] = myArray[113];
	MonsterArray[2][0][3] = new MonsterType*[3];
	MonsterArray[2][0][3][0] = myArray[114];
	MonsterArray[2][0][3][1] = myArray[115];
	MonsterArray[2][0][3][2] = myArray[116];
	MonsterArray[2][0][4] = new MonsterType*[3];
	MonsterArray[2][0][4][0] = myArray[117];
	MonsterArray[2][0][4][1] = myArray[118];
	MonsterArray[2][0][4][2] = myArray[119];
	MonsterArray[2][1] = new MonsterType**[5];
	MonsterArray[2][1][1] = new MonsterType*[1];
	MonsterArray[2][1][1][0] = myArray[120];
	MonsterArray[2][1][2] = new MonsterType*[2];
	MonsterArray[2][1][2][0] = myArray[121];
	MonsterArray[2][1][2][1] = myArray[122];
	MonsterArray[2][1][3] = new MonsterType*[2];
	MonsterArray[2][1][3][0] = myArray[123];
	MonsterArray[2][1][3][1] = myArray[124];
	MonsterArray[2][1][4] = new MonsterType*[2];
	MonsterArray[2][1][4][0] = myArray[125];
	MonsterArray[2][1][4][1] = myArray[126];
	MonsterArray[2][2] = new MonsterType**[5];
	MonsterArray[2][2][1] = new MonsterType*[3];
	MonsterArray[2][2][1][0] = myArray[127];
	MonsterArray[2][2][1][1] = myArray[128];
	MonsterArray[2][2][1][2] = myArray[129];
	MonsterArray[2][2][2] = new MonsterType*[4];
	MonsterArray[2][2][2][0] = myArray[130];
	MonsterArray[2][2][2][1] = myArray[131];
	MonsterArray[2][2][2][2] = myArray[132];
	MonsterArray[2][2][2][3] = myArray[133];
	MonsterArray[2][2][3] = new MonsterType*[5];
	MonsterArray[2][2][3][0] = myArray[134];
	MonsterArray[2][2][3][1] = myArray[135];
	MonsterArray[2][2][3][2] = myArray[136];
	MonsterArray[2][2][3][3] = myArray[137];
	MonsterArray[2][2][3][4] = myArray[138];
	MonsterArray[2][2][4] = new MonsterType*[6];
	MonsterArray[2][2][4][0] = myArray[139];
	MonsterArray[2][2][4][1] = myArray[140];
	MonsterArray[2][2][4][2] = myArray[141];
	MonsterArray[2][2][4][3] = myArray[142];
	MonsterArray[2][2][4][4] = myArray[143];
	MonsterArray[2][2][4][5] = myArray[144];
	MonsterArray[2][3] = new MonsterType**[5];
	MonsterArray[2][3][1] = new MonsterType*[1];
	MonsterArray[2][3][1][0] = myArray[145];
	MonsterArray[2][3][2] = new MonsterType*[2];
	MonsterArray[2][3][2][0] = myArray[146];
	MonsterArray[2][3][2][1] = myArray[147];
	MonsterArray[2][3][3] = new MonsterType*[2];
	MonsterArray[2][3][3][0] = myArray[148];
	MonsterArray[2][3][3][1] = myArray[149];
	MonsterArray[2][3][4] = new MonsterType*[2];
	MonsterArray[2][3][4][0] = myArray[150];
	MonsterArray[2][3][4][1] = myArray[151];
	MonsterArray[2][4] = new MonsterType**[5];
	MonsterArray[2][4][1] = new MonsterType*[1];
	MonsterArray[2][4][1][0] = myArray[152];
	MonsterArray[2][4][2] = new MonsterType*[2];
	MonsterArray[2][4][2][0] = myArray[153];
	MonsterArray[2][4][2][1] = myArray[154];
	MonsterArray[2][4][3] = new MonsterType*[2];
	MonsterArray[2][4][3][0] = myArray[155];
	MonsterArray[2][4][3][1] = myArray[156];
	MonsterArray[2][4][4] = new MonsterType*[2];
	MonsterArray[2][4][4][0] = myArray[157];
	MonsterArray[2][4][4][1] = myArray[158];
	MonsterArray[2][5] = new MonsterType**[5];
	MonsterArray[2][5][1] = new MonsterType*[1];
	MonsterArray[2][5][1][0] = myArray[159];
	MonsterArray[2][5][2] = new MonsterType*[1];
	MonsterArray[2][5][2][0] = myArray[160];
	MonsterArray[2][5][3] = new MonsterType*[1];
	MonsterArray[2][5][3][0] = myArray[161];
	MonsterArray[2][5][4] = new MonsterType*[1];
	MonsterArray[2][5][4][0] = myArray[162];
	MonsterArray[3] = new MonsterType***[6];
	MonsterArray[3][0] = new MonsterType**[5];
	MonsterArray[3][0][1] = new MonsterType*[1];
	MonsterArray[3][0][1][0] = myArray[163];
	MonsterArray[3][0][2] = new MonsterType*[3];
	MonsterArray[3][0][2][0] = myArray[164];
	MonsterArray[3][0][2][1] = myArray[165];
	MonsterArray[3][0][2][2] = myArray[166];
	MonsterArray[3][0][3] = new MonsterType*[3];
	MonsterArray[3][0][3][0] = myArray[167];
	MonsterArray[3][0][3][1] = myArray[168];
	MonsterArray[3][0][3][2] = myArray[169];
	MonsterArray[3][0][4] = new MonsterType*[3];
	MonsterArray[3][0][4][0] = myArray[170];
	MonsterArray[3][0][4][1] = myArray[171];
	MonsterArray[3][0][4][2] = myArray[172];
	MonsterArray[3][1] = new MonsterType**[5];
	MonsterArray[3][1][1] = new MonsterType*[1];
	MonsterArray[3][1][1][0] = myArray[173];
	MonsterArray[3][1][2] = new MonsterType*[2];
	MonsterArray[3][1][2][0] = myArray[174];
	MonsterArray[3][1][2][1] = myArray[175];
	MonsterArray[3][1][3] = new MonsterType*[2];
	MonsterArray[3][1][3][0] = myArray[176];
	MonsterArray[3][1][3][1] = myArray[177];
	MonsterArray[3][1][4] = new MonsterType*[2];
	MonsterArray[3][1][4][0] = myArray[178];
	MonsterArray[3][1][4][1] = myArray[179];
	MonsterArray[3][2] = new MonsterType**[5];
	MonsterArray[3][2][1] = new MonsterType*[1];
	MonsterArray[3][2][1][0] = myArray[180];
	MonsterArray[3][2][2] = new MonsterType*[2];
	MonsterArray[3][2][2][0] = myArray[181];
	MonsterArray[3][2][2][1] = myArray[182];
	MonsterArray[3][2][3] = new MonsterType*[2];
	MonsterArray[3][2][3][0] = myArray[183];
	MonsterArray[3][2][3][1] = myArray[184];
	MonsterArray[3][2][4] = new MonsterType*[2];
	MonsterArray[3][2][4][0] = myArray[185];
	MonsterArray[3][2][4][1] = myArray[186];
	MonsterArray[3][3] = new MonsterType**[5];
	MonsterArray[3][3][1] = new MonsterType*[1];
	MonsterArray[3][3][1][0] = myArray[187];
	MonsterArray[3][3][2] = new MonsterType*[3];
	MonsterArray[3][3][2][0] = myArray[188];
	MonsterArray[3][3][2][1] = myArray[189];
	MonsterArray[3][3][2][2] = myArray[190];
	MonsterArray[3][3][3] = new MonsterType*[4];
	MonsterArray[3][3][3][0] = myArray[191];
	MonsterArray[3][3][3][1] = myArray[192];
	MonsterArray[3][3][3][2] = myArray[193];
	MonsterArray[3][3][3][3] = myArray[194];
	MonsterArray[3][3][4] = new MonsterType*[4];
	MonsterArray[3][3][4][0] = myArray[195];
	MonsterArray[3][3][4][1] = myArray[196];
	MonsterArray[3][3][4][2] = myArray[197];
	MonsterArray[3][3][4][3] = myArray[198];
	MonsterArray[3][4] = new MonsterType**[5];
	MonsterArray[3][4][1] = new MonsterType*[1];
	MonsterArray[3][4][1][0] = myArray[199];
	MonsterArray[3][4][2] = new MonsterType*[3];
	MonsterArray[3][4][2][0] = myArray[200];
	MonsterArray[3][4][2][1] = myArray[201];
	MonsterArray[3][4][2][2] = myArray[202];
	MonsterArray[3][4][3] = new MonsterType*[3];
	MonsterArray[3][4][3][0] = myArray[203];
	MonsterArray[3][4][3][1] = myArray[204];
	MonsterArray[3][4][3][2] = myArray[205];
	MonsterArray[3][4][4] = new MonsterType*[3];
	MonsterArray[3][4][4][0] = myArray[206];
	MonsterArray[3][4][4][1] = myArray[207];
	MonsterArray[3][4][4][2] = myArray[208];
	MonsterArray[3][5] = new MonsterType**[5];
	MonsterArray[3][5][1] = new MonsterType*[1];
	MonsterArray[3][5][1][0] = myArray[209];
	MonsterArray[3][5][2] = new MonsterType*[3];
	MonsterArray[3][5][2][0] = myArray[210];
	MonsterArray[3][5][2][1] = myArray[211];
	MonsterArray[3][5][2][2] = myArray[212];
	MonsterArray[3][5][3] = new MonsterType*[3];
	MonsterArray[3][5][3][0] = myArray[213];
	MonsterArray[3][5][3][1] = myArray[214];
	MonsterArray[3][5][3][2] = myArray[215];
	MonsterArray[3][5][4] = new MonsterType*[3];
	MonsterArray[3][5][4][0] = myArray[216];
	MonsterArray[3][5][4][1] = myArray[217];
	MonsterArray[3][5][4][2] = myArray[218];
	MonsterArray[4] = new MonsterType***[6];
	MonsterArray[4][0] = new MonsterType**[5];
	MonsterArray[4][0][1] = new MonsterType*[1];
	MonsterArray[4][0][1][0] = myArray[219];
	MonsterArray[4][0][2] = new MonsterType*[3];
	MonsterArray[4][0][2][0] = myArray[220];
	MonsterArray[4][0][2][1] = myArray[221];
	MonsterArray[4][0][2][2] = myArray[222];
	MonsterArray[4][0][3] = new MonsterType*[3];
	MonsterArray[4][0][3][0] = myArray[223];
	MonsterArray[4][0][3][1] = myArray[224];
	MonsterArray[4][0][3][2] = myArray[225];
	MonsterArray[4][0][4] = new MonsterType*[3];
	MonsterArray[4][0][4][0] = myArray[226];
	MonsterArray[4][0][4][1] = myArray[227];
	MonsterArray[4][0][4][2] = myArray[228];
	MonsterArray[4][1] = new MonsterType**[5];
	MonsterArray[4][1][1] = new MonsterType*[1];
	MonsterArray[4][1][1][0] = myArray[229];
	MonsterArray[4][1][2] = new MonsterType*[2];
	MonsterArray[4][1][2][0] = myArray[230];
	MonsterArray[4][1][2][1] = myArray[231];
	MonsterArray[4][1][3] = new MonsterType*[2];
	MonsterArray[4][1][3][0] = myArray[232];
	MonsterArray[4][1][3][1] = myArray[233];
	MonsterArray[4][1][4] = new MonsterType*[2];
	MonsterArray[4][1][4][0] = myArray[234];
	MonsterArray[4][1][4][1] = myArray[235];
	MonsterArray[4][2] = new MonsterType**[5];
	MonsterArray[4][2][1] = new MonsterType*[1];
	MonsterArray[4][2][1][0] = myArray[236];
	MonsterArray[4][2][2] = new MonsterType*[2];
	MonsterArray[4][2][2][0] = myArray[237];
	MonsterArray[4][2][2][1] = myArray[238];
	MonsterArray[4][2][3] = new MonsterType*[2];
	MonsterArray[4][2][3][0] = myArray[239];
	MonsterArray[4][2][3][1] = myArray[240];
	MonsterArray[4][2][4] = new MonsterType*[2];
	MonsterArray[4][2][4][0] = myArray[241];
	MonsterArray[4][2][4][1] = myArray[242];
	MonsterArray[4][3] = new MonsterType**[5];
	MonsterArray[4][3][1] = new MonsterType*[1];
	MonsterArray[4][3][1][0] = myArray[243];
	MonsterArray[4][3][2] = new MonsterType*[2];
	MonsterArray[4][3][2][0] = myArray[244];
	MonsterArray[4][3][2][1] = myArray[245];
	MonsterArray[4][3][3] = new MonsterType*[2];
	MonsterArray[4][3][3][0] = myArray[246];
	MonsterArray[4][3][3][1] = myArray[247];
	MonsterArray[4][3][4] = new MonsterType*[2];
	MonsterArray[4][3][4][0] = myArray[248];
	MonsterArray[4][3][4][1] = myArray[249];
	MonsterArray[4][4] = new MonsterType**[5];
	MonsterArray[4][4][1] = new MonsterType*[1];
	MonsterArray[4][4][1][0] = myArray[250];
	MonsterArray[4][4][2] = new MonsterType*[3];
	MonsterArray[4][4][2][0] = myArray[251];
	MonsterArray[4][4][2][1] = myArray[252];
	MonsterArray[4][4][2][2] = myArray[253];
	MonsterArray[4][4][3] = new MonsterType*[4];
	MonsterArray[4][4][3][0] = myArray[254];
	MonsterArray[4][4][3][1] = myArray[255];
	MonsterArray[4][4][3][2] = myArray[256];
	MonsterArray[4][4][3][3] = myArray[257];
	MonsterArray[4][4][4] = new MonsterType*[4];
	MonsterArray[4][4][4][0] = myArray[258];
	MonsterArray[4][4][4][1] = myArray[259];
	MonsterArray[4][4][4][2] = myArray[260];
	MonsterArray[4][4][4][3] = myArray[261];
	MonsterArray[4][5] = new MonsterType**[5];
	MonsterArray[4][5][1] = new MonsterType*[1];
	MonsterArray[4][5][1][0] = myArray[262];
	MonsterArray[4][5][2] = new MonsterType*[3];
	MonsterArray[4][5][2][0] = myArray[263];
	MonsterArray[4][5][2][1] = myArray[264];
	MonsterArray[4][5][2][2] = myArray[265];
	MonsterArray[4][5][3] = new MonsterType*[3];
	MonsterArray[4][5][3][0] = myArray[266];
	MonsterArray[4][5][3][1] = myArray[267];
	MonsterArray[4][5][3][2] = myArray[268];
	MonsterArray[4][5][4] = new MonsterType*[3];
	MonsterArray[4][5][4][0] = myArray[269];
	MonsterArray[4][5][4][1] = myArray[270];
	MonsterArray[4][5][4][2] = myArray[271];
	MonsterArray[5] = new MonsterType***[6];
	MonsterArray[5][0] = new MonsterType**[5];
	MonsterArray[5][0][1] = new MonsterType*[1];
	MonsterArray[5][0][1][0] = myArray[272];
	MonsterArray[5][0][2] = new MonsterType*[3];
	MonsterArray[5][0][2][0] = myArray[273];
	MonsterArray[5][0][2][1] = myArray[274];
	MonsterArray[5][0][2][2] = myArray[275];
	MonsterArray[5][0][3] = new MonsterType*[3];
	MonsterArray[5][0][3][0] = myArray[276];
	MonsterArray[5][0][3][1] = myArray[277];
	MonsterArray[5][0][3][2] = myArray[278];
	MonsterArray[5][0][4] = new MonsterType*[3];
	MonsterArray[5][0][4][0] = myArray[279];
	MonsterArray[5][0][4][1] = myArray[280];
	MonsterArray[5][0][4][2] = myArray[281];
	MonsterArray[5][1] = new MonsterType**[5];
	MonsterArray[5][1][1] = new MonsterType*[1];
	MonsterArray[5][1][1][0] = myArray[282];
	MonsterArray[5][1][2] = new MonsterType*[3];
	MonsterArray[5][1][2][0] = myArray[283];
	MonsterArray[5][1][2][1] = myArray[284];
	MonsterArray[5][1][2][2] = myArray[285];
	MonsterArray[5][1][3] = new MonsterType*[3];
	MonsterArray[5][1][3][0] = myArray[286];
	MonsterArray[5][1][3][1] = myArray[287];
	MonsterArray[5][1][3][2] = myArray[288];
	MonsterArray[5][1][4] = new MonsterType*[3];
	MonsterArray[5][1][4][0] = myArray[289];
	MonsterArray[5][1][4][1] = myArray[290];
	MonsterArray[5][1][4][2] = myArray[291];
	MonsterArray[5][2] = new MonsterType**[5];
	MonsterArray[5][2][1] = new MonsterType*[1];
	MonsterArray[5][2][1][0] = myArray[292];
	MonsterArray[5][2][2] = new MonsterType*[2];
	MonsterArray[5][2][2][0] = myArray[293];
	MonsterArray[5][2][2][1] = myArray[294];
	MonsterArray[5][2][3] = new MonsterType*[2];
	MonsterArray[5][2][3][0] = myArray[295];
	MonsterArray[5][2][3][1] = myArray[296];
	MonsterArray[5][2][4] = new MonsterType*[2];
	MonsterArray[5][2][4][0] = myArray[297];
	MonsterArray[5][2][4][1] = myArray[298];
	MonsterArray[5][3] = new MonsterType**[5];
	MonsterArray[5][3][1] = new MonsterType*[1];
	MonsterArray[5][3][1][0] = myArray[299];
	MonsterArray[5][3][2] = new MonsterType*[1];
	MonsterArray[5][3][2][0] = myArray[300];
	MonsterArray[5][3][3] = new MonsterType*[1];
	MonsterArray[5][3][3][0] = myArray[301];
	MonsterArray[5][3][4] = new MonsterType*[1];
	MonsterArray[5][3][4][0] = myArray[302];
	MonsterArray[5][4] = new MonsterType**[5];
	MonsterArray[5][4][1] = new MonsterType*[1];
	MonsterArray[5][4][1][0] = myArray[303];
	MonsterArray[5][4][2] = new MonsterType*[1];
	MonsterArray[5][4][2][0] = myArray[304];
	MonsterArray[5][4][3] = new MonsterType*[1];
	MonsterArray[5][4][3][0] = myArray[305];
	MonsterArray[5][4][4] = new MonsterType*[1];
	MonsterArray[5][4][4][0] = myArray[306];
	MonsterArray[5][5] = new MonsterType**[5];
	MonsterArray[5][5][1] = new MonsterType*[1];
	MonsterArray[5][5][1][0] = myArray[307];
	MonsterArray[5][5][2] = new MonsterType*[3];
	MonsterArray[5][5][2][0] = myArray[308];
	MonsterArray[5][5][2][1] = myArray[309];
	MonsterArray[5][5][2][2] = myArray[310];
	MonsterArray[5][5][3] = new MonsterType*[4];
	MonsterArray[5][5][3][0] = myArray[311];
	MonsterArray[5][5][3][1] = myArray[312];
	MonsterArray[5][5][3][2] = myArray[313];
	MonsterArray[5][5][3][3] = myArray[314];
	MonsterArray[5][5][4] = new MonsterType*[4];
	MonsterArray[5][5][4][0] = myArray[315];
	MonsterArray[5][5][4][1] = myArray[316];
	MonsterArray[5][5][4][2] = myArray[317];
	MonsterArray[5][5][4][3] = myArray[318];







	//m_MonsterMap[0][0].myvec.rbegin();

	//MonsterMap<0><0>=pyro;
}


GameMain::~GameMain()
{
}

std::map<int, std::map<int, std::string>> GameMain::SubElementNames()
{
	std::map<int,
		std::map<int, std::string>> SubElementNames;
	SubElementNames[0][0] = "Pyro";
	SubElementNames[0][1] = "Lava";
	SubElementNames[0][2] = "Dinosaur";
	SubElementNames[0][3] = "Phoenix";
	SubElementNames[0][4] = "Justice";
	SubElementNames[0][5] = "Vengence";
	SubElementNames[1][0] = "Steam";
	SubElementNames[1][1] = "Aqua";
	SubElementNames[1][2] = "Amphibious";
	SubElementNames[1][3] = "Weather";
	SubElementNames[1][4] = "Ice";
	SubElementNames[1][5] = "Deep";
	SubElementNames[2][0] = "Fairy";
	SubElementNames[2][1] = "Swamp";
	SubElementNames[2][2] = "Tera";
	SubElementNames[2][3] = "Pegasus";
	SubElementNames[2][4] = "Compassion";
	SubElementNames[2][5] = "Rotten";
	SubElementNames[3][0] = "Sands";
	SubElementNames[3][1] = "SeaBreeze";
	SubElementNames[3][2] = "Birds";
	SubElementNames[3][3] = "Aero";
	SubElementNames[3][4] = "Cocka";
	SubElementNames[3][5] = "NightWing";
	SubElementNames[4][0] = "Solar";
	SubElementNames[4][1] = "Lunar";
	SubElementNames[4][2] = "Guardian";
	SubElementNames[4][3] = "Holy";
	SubElementNames[4][4] = "Light";
	SubElementNames[4][5] = "Redemption";
	SubElementNames[5][0] = "Demonic";
	SubElementNames[5][1] = "Poison";
	SubElementNames[5][2] = "Undead";
	SubElementNames[5][3] = "Storm";
	SubElementNames[5][4] = "Betrayer";
	SubElementNames[5][5] = "Umbral";
	return SubElementNames;
}



std::map<int, std::map<int, std::string>> GameMain::Symbols()
{
	std::map<int,
		std::map<int, std::string>> SymbolLocations;
	SymbolLocations[0][0] = "Game/ContentFiles/UIStuff/Symbols/PyroSymbol.png";
	SymbolLocations[0][1] = "Game/ContentFiles/UIStuff/Symbols/LavaSymbol.png";
	SymbolLocations[0][2] = "Game/ContentFiles/UIStuff/Symbols/DinoSymbol.png";
	SymbolLocations[0][3] = "Game/ContentFiles/UIStuff/Symbols/PhoenixSymbol.png";
	SymbolLocations[0][4] = "Game/ContentFiles/UIStuff/Symbols/JusticeSymbol.png";
	SymbolLocations[0][5] = "Game/ContentFiles/UIStuff/Symbols/VengenceSymbol.png";
	SymbolLocations[1][0] = "Game/ContentFiles/UIStuff/Symbols/SteamSymbol.png";
	SymbolLocations[1][1] = "Game/ContentFiles/UIStuff/Symbols/AquaSymbol.png";
	SymbolLocations[1][2] = "Game/ContentFiles/UIStuff/Symbols/AmphibiousSymbol.png";
	SymbolLocations[1][3] = "Game/ContentFiles/UIStuff/Symbols/WeatherSymbol.png";
	SymbolLocations[1][4] = "Game/ContentFiles/UIStuff/Symbols/IceSymbol.png";
	SymbolLocations[1][5] = "Game/ContentFiles/UIStuff/Symbols/DeepSymbol.png";
	SymbolLocations[2][0] = "Game/ContentFiles/UIStuff/Symbols/FeySymbol.png";
	SymbolLocations[2][1] = "Game/ContentFiles/UIStuff/Symbols/SwampSymbol.png";
	SymbolLocations[2][2] = "Game/ContentFiles/UIStuff/Symbols/TeraSymbol.png";
	SymbolLocations[2][3] = "Game/ContentFiles/UIStuff/Symbols/PegasusSymbol.png";
	SymbolLocations[2][4] = "Game/ContentFiles/UIStuff/Symbols/CompassionSymbol.png";
	SymbolLocations[2][5] = "Game/ContentFiles/UIStuff/Symbols/RottenSymbol.png";
	SymbolLocations[3][0] = "Game/ContentFiles/UIStuff/Symbols/SandSymbol.png";
	SymbolLocations[3][1] = "Game/ContentFiles/UIStuff/Symbols/SeaBreeze.png";
	SymbolLocations[3][2] = "Game/ContentFiles/UIStuff/Symbols/BirdSymbol.png";
	SymbolLocations[3][3] = "Game/ContentFiles/UIStuff/Symbols/AeroSymbol.png";
	SymbolLocations[3][4] = "Game/ContentFiles/UIStuff/Symbols/CockaSymbol.png";
	SymbolLocations[3][5] = "Game/ContentFiles/UIStuff/Symbols/NightWingSymbol.png";
	SymbolLocations[4][0] = "Game/ContentFiles/UIStuff/Symbols/SolarSymbol.png";
	SymbolLocations[4][1] = "Game/ContentFiles/UIStuff/Symbols/LunarSymbol.png";
	SymbolLocations[4][2] = "Game/ContentFiles/UIStuff/Symbols/GuardianSymbol.png";
	SymbolLocations[4][3] = "Game/ContentFiles/UIStuff/Symbols/AngelSymbol.png";
	SymbolLocations[4][4] = "Game/ContentFiles/UIStuff/Symbols/LightSymbol.png";
	SymbolLocations[4][5] = "Game/ContentFiles/UIStuff/Symbols/RedemptionSymbol.png";
	SymbolLocations[5][0] = "Game/ContentFiles/UIStuff/Symbols/DemonSymbol.png";
	SymbolLocations[5][1] = "Game/ContentFiles/UIStuff/Symbols/PoisonSymbol.png";
	SymbolLocations[5][2] = "Game/ContentFiles/UIStuff/Symbols/UndeadSymbol.png";
	SymbolLocations[5][3] = "Game/ContentFiles/UIStuff/Symbols/StormSymbol.png";
	SymbolLocations[5][4] = "Game/ContentFiles/UIStuff/Symbols/BetrayerSymbol.png";
	SymbolLocations[5][5] = "Game/ContentFiles/UIStuff/Symbols/UmbralSymbol.png";
	return SymbolLocations;
}

MonsterType*** GameMain::returnTree(int primary, int secondary)
{
	return MonsterArray[primary][secondary];
}

int GameMain::run()
{

	std::map<int, std::map<int, std::string>> myMap;
	myMap = GameMain::Symbols();
	std::map<int, std::map<int, std::string>> namesMap;
	namesMap = GameMain::SubElementNames();



	std::cout << "ITS WORKING!\n";
	RPGTest::runTests(true);
	MainCharacter* mchar = new MainCharacter();
	ListReader list;
	list.readConversation("Game/ContentFiles/Conversation/ConvoJohnWakeUp.txt",*(mchar));
	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	std::cout << "Myarray's length " << sizeof(myArray) << "\n";
	
	//std::map<int, std::map<int, std::string>> SymbolHolder = Symbols();

	/*
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			std::cout << Symbols()[i][j] << "\n";
			std::cout << SubElementNames()[i][j] << "\n";
		}
	}
	*/

	//for (int i = 0; i < sizeof(myArray); i++)
	/*
	for(int i=0; i<319; i++)
	{
		std::cout << "Index:            " << i << "\n";
		std::cout << "Name:             " << myArray[i]->getName() << "\n";
		std::cout << "Description:      " << myArray[i]->getDescription() << "\n";
		std::cout << "PrimaryElement:   " << myArray[i]->getPrimary() << "\n";
		std::cout << "SecondaryElement: " << myArray[i]->getSecondary() << "\n";
		std::cout << "EvolutionStage:   " << myArray[i]->getEvolutionStage() << "\n";
		std::cout << "EvolutionType:    " << myArray[i]->getEvolutionType() << "\n";
		std::cout << "Texture:          " << myArray[i]->getTexture() << "\n";
//		std::cout << "PhysicalEvolution:" << myArray[i]->getPhysicalEvolution() << "\n";
//		std::cout << "BalancedEvolution:" << myArray[i]->getBalancedEvolution() << "\n";
//		std::cout << "MagicalEvolution: " << myArray[i]->getMagicalEvolution() << "\n";

		std::cout << "\n\n";
	}
	*/


	//std::cout << "\n\n\n Lets try this: " << MonsterArray[0][0][1][0]->getName() << "\n";

	/*
	* int reply;
	* reply = list.readConversation(...);
	*/
	list.menu();
	delete mchar;
	return 0;
}

void GameMain::TickUpdate(const double &Delta)
{

}

void GameMain::Render(std::shared_ptr<sf::RenderTexture> Target)
{

}

/*
MonsterType***** GameMain::generate4dArray()
{



	return MonsterArray;
}
*/
/*
void GameMain::Init(std::shared_ptr<Engine::Level> GameLevel)
{
  Level = GameLevel;
  LoadLevel();
}

void GameMain::LoadLevel()
{
  

void GameMain::printAssetStatus()
{

}

*/