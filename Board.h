/*
File Name : Board.h
Copyright � 2018
Original authors : Sanketh Bhat
Written under the supervision of David I.Schwartz, Ph.D., and
supported by a professional development seed grant from the B.Thomas
Golisano College of Computing & Information Sciences
(https ://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.

Description:
Basic Tic Tac Toe AI using a step based method
*/

#ifndef _BOARD_H
#define _BOARD_H

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

#endif _BOARD_H