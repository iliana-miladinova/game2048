// game2048.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>

const int MAX_SIZE = 10;

void swap(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
int generateRandomNumbers()
{
	int randomNum = rand() % 2;
	if (randomNum == 0)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}
void generateNewNumber(int board[][MAX_SIZE], int size)
{
	int countEmpty = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == 0)
			{
				countEmpty++;
			}
		}
	}
	if (countEmpty > 0)
	{
		int position = rand() % countEmpty + 1;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (board[i][j] == 0)
				{
					position--;
					if (position == 0)
					{
						board[i][j] = generateRandomNumbers();
						return;
					}
				}
			}
		}
	}
}
void printBoard(int board[][MAX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == 0)
			{
				std::cout << std::setw(6) << 0;
			}
			else
			{
				std::cout << std::setw(6) << board[i][j];
			}
		}
		std::cout << std::endl;
	}
}

void moveUp(int board[][MAX_SIZE], int size)
{
	for (int col = 0; col < size; col++)
	{
		int curRow = 0;
		for (int row = 1; row < size; row++)
		{
			if (board[row][col] != 0)
			{
				if (board[curRow][col] == 0)
				{
					swap(board[curRow][col], board[row][col]);
				}
				else if (board[curRow][col] == board[row][col])
				{
					board[curRow][col] *= 2;
					board[row][col] = 0;
					curRow++;
				}
				else
				{
					curRow++;
					swap(board[curRow][col], board[row][col]);
				}
			}
		}
	}
}

void moveDown(int board[][MAX_SIZE], int size)
{
	for (int col = 0; col < size; col++)
	{
		int curRow = size - 1;
		for (int row = size - 2; row >= 0; row--)
		{

			if (board[row][col] != 0)
			{
				if (board[curRow][col] == 0)
				{
					swap(board[curRow][col], board[row][col]);
				}
				else if (board[curRow][col] == board[row][col])
				{
					board[curRow][col] *= 2;
					board[row][col] = 0;
					curRow--;
				}
				else
				{
					curRow--;
					swap(board[curRow][col], board[row][col]);
				}
			}
		}
	}
}

void moveLeft(int board[][MAX_SIZE], int size)
{
	for (int row = 0; row < size; row++)
	{
		int curCol = 0;
		for (int col = 1; col < size; col++)
		{
			if (board[row][col] != 0)
			{
				if (board[row][curCol] == 0)
				{
					swap(board[row][curCol], board[row][col]);
				}
				else if (board[row][curCol] == board[row][col])
				{
					board[row][curCol] *= 2;
					board[row][col] = 0;
					curCol++;
				}
				else
				{
					curCol++;
					swap(board[row][curCol], board[row][col]);
				}
			}
		}
	}
}
void moveRight(int board[][MAX_SIZE], int size)
{
	for (int row = 0; row < size; row++)
	{
		int curCol = size - 1;
		for (int col = size - 2; col >= 0; col--)
		{
			if (board[row][col] != 0)
			{
				if (board[row][curCol] == 0)
				{
					swap(board[row][curCol], board[row][col]);
				}
				else if (board[row][curCol] == board[row][col])
				{
					board[row][curCol] *= 2;
					board[row][col] = 0;
					curCol--;
				}
				else
				{
					curCol--;
					swap(board[row][curCol], board[row][col]);
				}
			}
		}
	}
}

unsigned getScore(int board[][MAX_SIZE], int size)
{
	unsigned score = 0;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			score += board[row][col];
		}
	}
	return score;
}

bool isGameOver(int board[][MAX_SIZE], int size)
{
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (board[row][col] == 0)
			{
				return false;  
			}
		}
	}
	for (int row = 0; row < size; row++)
	{
		for (int col = 1; col < size; col++)
		{
			if (board[row][col] == 0 || board[row][col] == board[row][col - 1])
			{
				return false; 
			}
		}
	}
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size - 1; col++)
		{
			if (board[row][col] == 0 || board[row][col] == board[row][col + 1])
			{
				return false;
			}
		}
	}
	for (int row = 1; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (board[row][col] == 0 || board[row][col] == board[row - 1][col])
			{
				return false;
			}
		}
	}
	for (int row = 0; row < size - 1; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (board[row][col] == 0 || board[row][col] == board[row + 1][col])
			{
				return false;
			}
		}
	}

	return true;
}

void startGame()
{
	std::cout << "Input your Nickname: ";
	char nickname[100];
	std::cin >> nickname;

	std::cout << "Input size of the board(between 4 and 10): ";
	int size;
	std::cin >> size;



	if (size >= 4 && size <= 10)
	{
		int board[MAX_SIZE][MAX_SIZE] = {0};
		int score = 0;

		int sizeBoard = rand() % size;
		int sizeBoard2 = rand() % size;
		board[sizeBoard][sizeBoard] = generateRandomNumbers();
		board[sizeBoard2][sizeBoard2] = generateRandomNumbers();
		while (!isGameOver(board, size))
		{
			score = getScore(board, size);
			printBoard(board, size);
			std::cout << "Score: " << score << std::endl;
			char move;
			std::cout << "Enter your move (w/a/s/d): ";
			std::cin >> move;
			switch (move) {
			case 'w':
				moveUp(board, size);
				generateNewNumber(board, size);
				break;
			case 's':
				moveDown(board, size);
				generateNewNumber(board, size);
				break;
			case 'a':
				moveLeft(board, size);
				generateNewNumber(board, size);
				break;
			case 'd':
				moveRight(board, size);
				generateNewNumber(board, size);
				break;
			default:
				std::cout << "Invalid move. Please try again." << std::endl;
			}
		}
		std::cout << "Game over! Your final score is: " << score << std::endl;
	}
	else
	{
		std::cout << "Incorrect input" << std::endl;
	}
}
int main()
{
	int choice;

	std::cout << "1. Start game" << std::endl;
	std::cout << "2. Leaderboard" << std::endl;
	std::cout << "3. Quit" << std::endl;

	std::cin >> choice;
	do
	{
		switch (choice)
		{
		case 1: startGame();
			break;
		case 2:
			break;
		case 3:
			std::cout << "End Game!" << std::endl;
			break;
		default:
			break;
		}
	} while (choice != 3);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
