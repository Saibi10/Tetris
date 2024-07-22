/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

 //---Piece Starts to Fall When Game Starts---//

 /*
 Muhammad Sohaib
 22I-0879
 Section K
 PF-Project
 */

#include <cstdlib>
#include <iostream>

void fallingPiece(float& timer, float& delay, int& colorNum, int& delta_x, bool& checkGameOver, int& clearedRows)
{

	if (timer > delay)
	{
		int n;

		for (int i = 0; i < 4; i++)
		{
			point_2[i][0] = point_1[i][0];
			point_2[i][1] = point_1[i][1];
			point_1[i][1] += 1; // How much units downward
		}
		if (!anamoly())
		{

			for (int i = 0; i < 4; i++)
				gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;

			colorNum = (1 + (rand() % 7));

			if (clearedRows < 2)
			{
				n = rand() % 4;
			}
			else
			{
				n = rand() % 7;
			}

			for (int i = 0; i < 4; i++)
			{
				point_1[i][0] = BLOCKS[n][i] % 2;
				point_1[i][1] = BLOCKS[n][i] / 2;
			}
			delta_x = 0;

			for (int i = 0; i < 4; i++)
			{
				if (point_2[i][1] == point_1[i][1])
				{
					checkGameOver = true; // Here I am checking if the gameIsOver or not...
				}
			}
		}
		timer = 0;
	}
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
/*

void resetVals(float& delay, int& delta_x, bool rotate)
{
	delay = 0.3;
	rotate = 0;
}

*/

// The following Function is for moving the block towards Right...

void moveR(bool& rightMove, int& delta_x)
{
	int rightCount = 0;

	for (int i = 0; i < 4; i++)
	{
		if (point_1[i][1] == 0)
		{
			rightCount++; // This loop is specific for straight Block...
		}
	}

	if (rightCount == 4)
	{
		if (delta_x < 11)
		{
			if (rightMove == true) // Checking if rightKey is Pressed or not...
			{
				for (int i = 0; i < 4; i++)
				{
					point_1[i][1] += 1;
					point_1[i][0] += 1;
				}
				delta_x++;
			}
		}
		rightMove = false;
	}
	else
	{
		if (delta_x < 8)
		{
			if (rightMove == true)
			{
				for (int i = 0; i < 4; i++)
				{
					point_1[i][1] += 1;
					point_1[i][0] += 1;
				}
				delta_x++;
			}
		}
		rightMove = false;
	}
}

// This function is for moving the Block towards Left...

void moveL(bool& leftMove, int& delta_x)
{
	if (delta_x > 0)
	{
		if (leftMove == true) // Checking if left key is pressed or not...
		{
			for (int i = 0; i < 4; i++)
			{
				point_1[i][1] -= 1;
				point_1[i][0] -= 1;
			}
			delta_x--;
		}
	}
	leftMove = false;
}

void doRotation(bool& rotate)
{
	if (rotate)
	{

		for (int i = 0; i < 4; i++)
		{
			int valueOnX = point_1[i][1] - point_1[1][1];
			int valueOnY = point_1[i][0] - point_1[1][0];
			point_1[i][0] = point_1[1][0] - valueOnX;
			point_1[i][1] = point_1[1][1] - valueOnY;
		}
	}
}

// This Function is clearing rows and also transfering rows...

void clearFullRow(int& scores, int& bars, int& clearedRows)
{

	int noBlocks = 0;

	for (int i = 1; i <= 5; i++)
	{
		for (int i = 19; i >= 0; i--) // Going for every row
		{
			for (int j = 0; j < 10; j++)
			{
				if (gameGrid[i][j] > 0)
				{
					noBlocks++; // Checking all the blocks in column
				}
			}
			if (noBlocks == 10)
			{
				bars += 1;
			}
			if (noBlocks == 10)
			{
				for (int m = 0; m < 10; m++)
				{
					gameGrid[i][m] = 0; // Clearing the row...
				}
			}
			if (noBlocks == 10)
			{
				for (int m = 0; m < 10; m++)
				{
					gameGrid[i][m] = gameGrid[i - 1][m]; // Transfering the row...
				}
			}
			if (noBlocks == 10)
			{
				clearedRows++;
				for (int m = i; m > 0; m--)
				{
					for (int n = 0; n < 10; n++)
					{
						gameGrid[m][n] = gameGrid[m - 1][n];
					}
				}
				// Here I add scores...
				scores += 10;
				if (clearedRows == 2)
				{
					scores += 20;
				}
				if (clearedRows == 3)
				{
					scores += 50;
				}
				if (clearedRows > 3)
				{
					scores += 90;
				}
			}
			noBlocks = 0;
		}
	}
}

// Making a Probability of falling a BOMB...

void bombFallingProb(bool& makeBomb, int& colorNumOfBomb)
{
	int probabilityBOMB;
	srand(time(0));

	probabilityBOMB = rand() % 15;

	if (probabilityBOMB == 5) // Bomb only fall if 5 is random number...
	{
		makeBomb = true;
		colorNumOfBomb = rand() % 7;
	}
}

// This is a same funciton as of pieces but this is for bombs, bomb will fall down.

void fallingBoom(float& timerOfBomb, float& delayOfBomb, bool& makeBomb, int& colorNumOfBomb, int& scores)
{

	if (timerOfBomb > delayOfBomb)
	{
		if (make_anamoly_bombs())
		{
			timerOfBomb = 0;
			for (int i = 0; i < 4; i++)
			{
				boom_2[i][0] = boom_1[i][0];
				boom_2[i][1] = boom_1[i][1];
				boom_1[i][1] += 1;
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				gameGrid[boom_2[i][1]][boom_2[i][0]] = colorNumOfBomb;
				// Checking if bomb is of same color...
				if (gameGrid[boom_2[i][1]][boom_2[i][0]] == gameGrid[boom_2[i][1] + 1][boom_2[i][0]])
				{
					for (int i = 0; i < 20; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							gameGrid[i][j] = 0; // Clearing whole Grid...
						}
					}
					scores += 25;
					for (int i = 0; i < 4; i++)
					{
						boom_2[i][0] = 0;
						boom_2[i][1] = 0;
					}
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						// Else...Clearing some Blocks around...
						gameGrid[boom_2[i][1] + 1][boom_2[i][0]] = 0;
						gameGrid[boom_2[i][1]][boom_2[i][0] + 1] = 0;
						gameGrid[boom_2[i][1]][boom_2[i][0]] = 0;
						gameGrid[boom_2[i][0] + 1][boom_2[i][0] + 1] = 0;
					}
					scores += 5;
					gameGrid[boom_2[i][1]][boom_2[i][0]] = 0;
					makeBomb = false;
				}
			}
		}
	}
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
