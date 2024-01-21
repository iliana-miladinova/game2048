// game2048.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/**
*
* Solution to course project # <номер на вариант>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Iliana Stefanova Miladinova
* @idnumber 6MI0600326
* @compiler VC
*
* <file with the game code>
*
*/


#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <fstream>

const int MAX_SIZE = 10;
const int MAX_SIZE_NICKNAME = 100;
const int MAX_LEADERBORD_PLAYERS = 5;
const int finalNumber = 2048;


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
		for (int col = size - 2; col >= 0; col--)
		{
			if (board[row][col] == 0 || board[row][col] == board[row][col+1])
			{
				return false;
			}
		}
	}

	for (int row = 0; row < size; row++)
	{
		for (int col = 1; col < size; col++)
		{
			if (board[row][col] == 0 || board[row][col] == board[row][col-1])
			{
				return false;
			}
		}
	}

	for (int col = 0; col < size; col++)
	{
		for (int row = size - 2; row >= 0; row--)
		{
			if (board[row][col] == 0 || board[row][col] == board[row+1][col])
			{
				return false;
			}
		}
	}

	for (int col = 0; col < size; col++)
	{
		for (int row = 1; row < size; row++)
		{
			if (board[row][col] == 0 || board[row][col] == board[row-1][col])
			{
				return false;
			}
		}
	}
	return true;
}

bool hasWon(int board[][MAX_SIZE], int size)
{
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (board[row][col] == finalNumber)
			{
				return true;  
			}
		}
	}
	return false; 
}

int min(int num1, int num2)
{
	if (num1>num2)
	{
		return num2;
	}
	return num1;
}

void myStrcpy(char* dest, const char* source)
{
	if (!source || !dest)
	{
		return;
	}

	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}

void generateLeaderboardFileName(int size, char* leaderboardName) 
{
	switch (size) 
	{
	case 4:
		myStrcpy(leaderboardName, "Leaderboard 4x4.txt");
		break;
	case 5:
		myStrcpy(leaderboardName, "Leaderboard 5x5.txt");
		break;
	case 6:
		myStrcpy(leaderboardName, "Leaderboard 6x6.txt");
		break;
	case 7:
		myStrcpy(leaderboardName, "Leaderboard 7x7.txt");
		break;
	case 8:
		myStrcpy(leaderboardName, "Leaderboard 8x8.txt");
		break;
	case 9:
		myStrcpy(leaderboardName, "Leaderboard 9x9.txt");
		break;
	case 10:
		myStrcpy(leaderboardName, "Leaderboard 10x10.txt");
		break;
	default:
		std::cout << "Invalid board size." << std::endl;
		leaderboardName[0] = '\0';
		break;
	}
}

void updateLeaderboard(int score, const char* nickname, int size) 
{
	char leaderboardName[100];
	generateLeaderboardFileName(size, leaderboardName);
	std::ofstream leaderboardFile(leaderboardName, std::ofstream::app);

	if (leaderboardFile.is_open()) 
	{
		leaderboardFile << nickname << " " << score << std::endl;
		leaderboardFile.close();
	}
	else 
	{
		std::cout << "Error." << std::endl;
	}
}

void showLeaderboard(int size) 
{
	char leaderboardName[100];
	generateLeaderboardFileName(size, leaderboardName);
	std::ifstream leaderboardFile(leaderboardName);

	if (leaderboardFile.is_open())
	{
		char names[MAX_LEADERBORD_PLAYERS][100];
		int scores[MAX_LEADERBORD_PLAYERS];       
		int players = 0;
		while (leaderboardFile >> names[players] >> scores[players]) 
		{
			players++;
		}
		leaderboardFile.close();

		for (int i = 0; i < players - 1; i++) 
		{
			int maxIndex = i;
			for (int j = i + 1; j < players; j++) 
			{
				if (scores[j] > scores[maxIndex]) 
				{
					maxIndex = j;
				}
			}
			int tempScore = scores[maxIndex];
			scores[maxIndex] = scores[i];
			scores[i] = tempScore;
			char tempName[100];
			myStrcpy(tempName, names[maxIndex]);
			myStrcpy(names[maxIndex], names[i]);
			myStrcpy(names[i], tempName);
		}

		int displayPlayers = min(players, MAX_LEADERBORD_PLAYERS);
		std::cout << "Leaderboard " << size << "x" << size << ":" << std::endl;
		for (int i = 0; i < displayPlayers; i++)
		{
			std::cout << names[i] << " - " << scores[i] << std::endl;
		}
	}
	else 
	{
		std::cout << "Error." << std::endl;
	}
}

void showMenu(int& choice)
{
	std::cout << "1. Start game" << std::endl;
	std::cout << "2. Leaderboard" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cin >> choice;
}

void startGame()
{
	std::cout << "Input your Nickname: ";
	char nickname[MAX_SIZE_NICKNAME];
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

		while (!isGameOver(board, size) && !hasWon(board, size))
		{
			score = getScore(board, size);
			printBoard(board, size);
			std::cout << "Score: " << score << std::endl;

			char move;
			std::cout << "Input your move (w/a/s/d): ";
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
		if (hasWon(board, size))
		{
			std::cout << "You won! Your final score is: " << score << std::endl;
		}
		else
		{
			std::cout << "Game over! Your final score is: " << score << std::endl;
		}
		updateLeaderboard(score, nickname, size);
	}
	else
	{
		std::cout << "Incorrect input" << std::endl;
	}
}

int main()
{
	int choice;

	do
	{
		showMenu(choice);
		
		switch (choice)
		{
		case 1: 
			startGame();
			break;
		case 2: 
			std::cout << "Input board size between 4 and 10: ";
			int leaderboardSize;
			std::cin >> leaderboardSize;
			if (leaderboardSize >= 4 && leaderboardSize <= 10)
			{
				showLeaderboard(leaderboardSize);
			}
			else
			{
				std::cout << "Invalid input";
			}
			break;
		case 3:
			std::cout << "End Game!" << std::endl;
			break;
		default:
			break;
		}
	} while (choice != 3);
}



