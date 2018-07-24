#pragma once
#include <vector>

//simple struct to hole a location in the grid
struct pair {

	int x;
	int y;

	pair(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

std::vector<pair> corners = {pair(0,0),pair(2,0),pair(0,2), pair(2,2) };
std::vector<pair> sides = { pair(1,0),pair(0,1),pair(2,1),pair(1,2) };
int playerNumber;

int indX = 0;
int indY = 0;
int solvedX=0;
int solvedY=0;	
int turncount;
//Checks if a row/column/diagonal has 2 of the same units on it.
//Parameters are the board data, the AI player number and a boolean if the method is used to check for a fork or not.
 int CheckDouble(int u[3][3], int pNum, bool checkFork=false)
{
	int doubleCount=0;
	int pCount=0;
	

	//Rows
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (u[i][j] == pNum)
				pCount++;
			else if (u[i][j] == 0)
			{
				indX = i;
				indY = j;
			}
			else
				pCount--;

		}
		if (pCount == 2)
		{
			if (!checkFork)
				return 1;
			else
				doubleCount++;
		}

		pCount=0;
	}

	//Columns
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (u[j][i] == pNum)
				pCount++;
			else if (u[j][i] == 0)
			{
				indX = j;
				indY = i;
			}
			else
				pCount--;
		}
		if (pCount == 2)
		{
			if (!checkFork)
				return 1;
			else
				doubleCount++;
		}

		pCount = 0;
	}

	//Diagonals
	for (int i = 0; i < 3; i +=2 )
	{			
	
		if (u[i][0] == pNum)
			pCount++;
		else if (u[i][0] == 0)
		{
			indX = i;
			indY = 0;
		}
		else
			pCount--;

		if (u[1][1] == pNum)
			pCount++;
		else if (u[1][1] == 0)
		{
			indX = 1;
			indY = 1;
		}
		else
			pCount--;

		if (u[2-i][2] == pNum)
			pCount++;
		else if (u[2 - i][2] == 0)
		{
			indX = 2 - i;
			indY = 2;
		}
		else
			pCount--;
		

		if (pCount == 2)
		{
			if (!checkFork)
				return 1;
			else
				doubleCount++;
		}

		pCount = 0;
	}

	
	return doubleCount;
}

//Checks if a row/column/diagonal has 2 of the same units on it.
//Parameters are the board data, the AI player number and a boolean if the method is to be called inside of it or not
bool CheckFork(int u[3][3], int pNum, bool parent=true)
{
	int uCopy[3][3];
	int doubleCheck = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			uCopy[i][j] = u[i][j];
		}
	}
	bool check=false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (uCopy[i][j] == 0)
			{
				uCopy[i][j] = pNum;

				//Semi-recursive functionality here to "predict" future forks
				//Only called once per unit and only if each player has already played at least one turn
				if (parent && turncount>2)
				{
					
					check = CheckFork(uCopy, pNum, false);
					if (check)
						return true;
				}
				else
				{			
					doubleCheck = CheckDouble(uCopy, pNum, true);
					if (doubleCheck >= 2)
					{
						indX = i;
						indY = j;
						return true;
					}
				}

				uCopy[i][j] = 0;
			}
		}
	}
	return false;
}


//Checks if a win is possible
bool Win(int u[3][3])
{
	return(CheckDouble(u, playerNumber, false)==1);
}

//Checks if a block to an opponents possible win exists
bool Block(int u[3][3])
{
	if (playerNumber == 1 )
		return(CheckDouble(u, 2) == 1);
	else if (playerNumber == 2)
		return(CheckDouble(u, 1) == 1);

	return false;
}

//Checks if a fork is available
bool Fork(int u[3][3])
{
	return CheckFork(u, playerNumber);

	
}

//Tries to block an opponents fork
bool BlockFork(int u[3][3])
{
	if (playerNumber == 1)
		return CheckFork(u, 2);
	else if (playerNumber == 2)
		return CheckFork(u, 1);
}

//Checks if the center unit is empty
bool Center(int u[3][3])
{
	indX = 1;
	indY = 1;
	if (u[1][1] == 0)
	{
		return true; 
	}
	return false;
}

//Plays in the opposite corner of the other player if possible
bool OppCorner(int u[3][3])
{
	for (int i = 0; i < 4; i++)
	{
		indX = corners[i].x;
		indY= corners[i].y;
		if (u[indX][indY] != 0 && u[indX][indY] != playerNumber)
		{
			//0/0 - 2/2  2/0 - 0/2 :Index locations
			if (i == 0)
			{
				if (u[2][2] == 0)
				{
					indX = 2;
					indY = 2;

					return true;
				}
			}
			else if (i == 1)
			{
				if (u[0][2] == 0)
				{
					indX = 0;
					indY = 2;

					return true;
				}
			}
			else if (i == 2)
			{
				if (u[2][0] == 0)
				{
					indX = 2;
					indY = 0;

					return true;
				}
			}
			else if (i == 3)
			{
				if (u[0][0] == 0)
				{
					indX = 0;
					indY = 0;

					return true;
				}
			}
			
		}
	}
	return false;
}

//Checks if there is an empty corner 
bool EmptyCorner(int u[3][3])
{
	for (int i = 0; i < 4; i++)
	{
		indX = corners[i].x;
		indY = corners[i].y;
		if (u[indX][indY] == 0)
		{
			return true;
		}
	}
	return false;
}

//Checks if a side unit is empty 
bool EmptySide(int u[3][3])
{
	for (int i = 0; i < 4; i++)
	{
		indX = sides[i].x;
		indY = sides[i].y;
		if (u[indX][indY] == 0)
		{
			return true;
		}
	}
	return false;
}

//The Solved Game Strategy for tic tac toe is the following series of turns, taking first possible one:
//Make 3 in a row
//Block an opponenet from getting 3 in a row
//Create a fork leading to 2 possible 3 in a rows next turn
//Block your opponenets fork
//Get the center 
//Get corner opposite to a corner taken by your opponent
//Get an empty corner
//Get an empty side
//This leads to a win or stalemate 100% of the time and make it impossible to lose
 void PlayTurn(int u[3][3], int pNum)
{
	 playerNumber = pNum;
	if (!Win(u))
		if (!Block(u))
			if (!Fork(u))
				if (!BlockFork(u))
					if (!Center(u))
						if (!OppCorner(u))					
							if (!EmptyCorner(u))
									EmptySide(u);

	solvedX = indX;
	solvedY = indY;

	

}