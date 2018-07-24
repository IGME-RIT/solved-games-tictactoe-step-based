#pragma once

#include "GameObject.h"




class Board {

	int AIturn = 2;
	int units[3][3];

	enum State
	{
		 end, player1, player2
	}state;

	int CheckWin();


public:
	Model *empty;
	Model *modelX;
	Model *modelO;
	GameObject * tiles[3][3];
	Board(Model* eM, Model* xM, Model* oM, int aturn);

	void UnitSelected(glm::vec3 pos);
	void UpdateBoard(int x, int y);
};