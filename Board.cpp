#include "Board.h"
#include "Solver.h"

//Checks if there is 3 in a row anywhere on the board
int Board::CheckWin()
{
	bool win = false;
	int check = 0;
	
	//Checking rows
	for (int i = 0; i < 3; i++)
	{
		check = units[i][0];

		win = true;
		for (int j = 1; j < 3; j++)
		{
			if (units[i][j] != check)
				win = false;
		}

		if (win == true && units[0][i] != 0)
			return check;
	}


	//Checking columns
	for (int i = 0; i < 3; i++)
	{
		check = units[0][i];
		win = true;
		for (int j = 0; j < 3; j++)
		{
			if (units[j][i] != check)
				win = false;
		}

		if (win == true && units[0][i]!=0)
			return check;
	}
	//Checking diagonals
	
	for (int i = 0; i < 3; i+=2)
	{
		if (units[i][0] != 0)
		{
			if (units[i][0] == units[1][1] && units[i][0] == units[2-i][2])
				return units[i][0];
		}
	}

	return 0;
}

//Finds the unit at the given position
void Board::UnitSelected(glm::vec3 pos)
{
	int x=-1, y;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (pos == tiles[i][j]->Position())
			{
				x = i;
				y = j;
				break;
			}
			
		}
		if (x != -1)
			break;
	}

	if (units[x][y] != 0)
		return;

	UpdateBoard(x, y);

}


//updates game board based on the game state and unit selected
void Board::UpdateBoard(int x, int y)
{
	int check = 0;
	turncount++;

	//Updates board data and switches states
	if (state == player1)
	{
		units[x][y] = 1;
		tiles[x][y]->setModel(modelX);	

		state = player2;
	}
	else if (state == player2)
	{
		units[x][y] = 2;
		tiles[x][y]->setModel(modelO);

		state = player1;
	}

	//Checking for game end
	check = CheckWin();

	if (turncount == 9 || check != 0)
	{
		state = end;
		if (check == 0)
			std::cout << "It's a Tie!";
		else
			std::cout << "Player " << check << " Wins!";
	}
	//If the next turn is by the AI play it 
	else
	{
		if (state == AIturn)
		{
			PlayTurn(units, AIturn);
			UpdateBoard(solvedX, solvedY);
		}
	}

}

//Constructor that takes the models for the board units
Board::Board(Model* eM, Model* xM, Model* oM, int aturn)
{
	state = player1;
	empty = eM;
	modelX = xM;	
	modelO = oM;

	AIturn = aturn;
	float x = -1 + 1 / 3.0f;
	float y = 1 - 1 / 3.0f;

	//Initializing board
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			units[i][j] = 0;
			tiles[i][j] = new GameObject(empty);
			tiles[i][j]->Position(glm::vec3(x,y,0));
			tiles[i][j]->setRotation(glm::vec3(0, 0, 3.14f/4));
			x += 2 / 3.0f;
		}
		x = -1 + 1 / 3.0f;
		y -= 2 / 3.0f;
	}

	//Make the AI play the first turn if it's player number 1
	if (AIturn == 1)
	{
		PlayTurn(units, 1);
		UpdateBoard(solvedX, solvedY);
	}
}
