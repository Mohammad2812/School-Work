// Group F
// 10/11/2016
// Purpose: Single Player Battleship

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define PAUSE system("pause")
#define CLS system("cls")

void displayMenu();
int getChoice();
void playBattleship(char displayGrid[][12], char actualGrid[][12], static int highScores[], int *scores, int *trackedHits, int *trackedMissiles);
int positionGenerator();
int randGenerator();
int testLocation(char actualGrid[][12], int direction, int shipLength, int row, int col);
void placeShips(char displayGrid[][12], char actualGrid[][12]);
void shootMissile(char displayGrid[][12], char actualGrid[][12], int *missiles, int *hits);
void displayMenu2();
int getChoice2();
int endGame(int missiles, int hits);
int getNumbers(static int highScores[]);
void bubbleSort(int *scores, int i);
char doTheSwitch(int *scores, int i,char switchMade);
void saveGame(char displayGrid[][12], char actualGrid[][12], int *missiles, int *hits);
void resetGrids(char displayGrid[][12], char actualGrid[][12]);
void loadGame(char displayGrid[][12], char actualGrid[][12], int *trackedMissiles, int *trackedHits);

main() {
	int userChoice, i;
	int trackedHits = 0;	// Tracks hits even when you quit the playBattleship function
	int trackedMissiles = 0;	// Tracks missiles even when you quit the playBattleship function
	int *scores;	// Some kind of array
	static int highScores[11];	// Our array with highScores
	scores = getNumbers(highScores);	// Populates "array" and our highScores array right off the bat
	char displayGrid[12][12] = {
		// Play grid
		{ ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' },
		{ '0', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '0' },
		{ '1', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '1' },
		{ '2', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '2' },
		{ '3', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '3' },
		{ '4', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '4' },
		{ '5', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '5' },
		{ '6', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '6' },
		{ '7', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '7' },
		{ '8', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '8' },
		{ '9', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '9' },
		{ ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' }
	};

	char actualGrid[12][12] = {
		// Behind the scenes grid
		{ ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' },
		{ '0', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '0' },
		{ '1', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '1' },
		{ '2', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '2' },
		{ '3', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '3' },
		{ '4', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '4' },
		{ '5', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '5' },
		{ '6', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '6' },
		{ '7', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '7' },
		{ '8', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '8' },
		{ '9', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '9' },
		{ ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' }
	};
	srand(time(NULL));
	placeShips(displayGrid, actualGrid);
	do {
		userChoice = getChoice();
		switch (userChoice) {
		case 1:		// Play Battleship
			playBattleship(displayGrid, actualGrid, highScores, &scores, &trackedHits, &trackedMissiles);
			break;
		case 2:		// Load Game
			loadGame(displayGrid, actualGrid, &trackedMissiles, &trackedHits);
			PAUSE;
			break;
		case 3:		// View Top 10 Scores
			CLS;
			for (i = 1; i < 11; i++)
			{
				printf("%i. %i\n", i, *(scores + 1));	// Printing out each number in our "array" called scores
			}
			PAUSE;
			break;
		case 4:		// Quit
			break;
		default:
			printf("That is not a valid option\n");
			PAUSE;
			break;
		}
	} while (userChoice != 4);

} // End of main


void displayMenu() {
	CLS;
	printf("MAIN MENU\n");
	printf("1. Play Battleship.\n");
	printf("2. Load Game.\n");
	printf("3. View Top 10 Scores.\n");
	printf("4. Quit.\n");
	printf("Enter your choice: ");
} // End of displayMenu

void displayMenu2() {
	printf("1. Shoot Missile.\n");
	printf("2. New Grid.\n");
	printf("3. Save.\n");
	printf("4. Quit.\n");
	printf("Enter your choice: ");
} // End of displayMenu2

int getChoice() {
	int result;
	displayMenu();
	scanf("%i", &result);
	return result;
} // End of getChoice

int getChoice2() {
	int result;
	displayMenu2();
	scanf("%i", &result);
	return result;
} // End of getChoice2

void placeShips(char displayGrid[][12], char actualGrid[][12]) {
	int positionNumber, rowNumber, colNumber, i, j;
	for (i = 1; i < 11; i++) // Resetting Array
	{
		for (j = 1; j < 11; j++)
		{
			if (actualGrid[i][j] != '-')
			{
				actualGrid[i][j] = '-';
			}
		}
	}

	//////////////////////////////////////////////////////
	// Cruiser Ship
	positionNumber = positionGenerator();
	if (positionNumber == 1)    // Down
	{
		 int clear = 1;
		 int cruiser = 2;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, cruiser, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'C';
				actualGrid[rowNumber + 1][colNumber] = 'C';
			}
		} while (clear);
	}
	else if (positionNumber == 2) // Right
	{
		int clear = 1;
		int cruiser = 2;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, cruiser, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'C';
				actualGrid[rowNumber][colNumber + 1] = 'C';
			}
		} while (clear);
	}
	else if (positionNumber == 3) // Up
	{
		int clear = 1;
		int cruiser = 2;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, cruiser, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'C';
				actualGrid[rowNumber - 1][colNumber] = 'C';
			}
		} while (clear);
	}
	else if (positionNumber == 4)	// Left
	{
		int clear = 1;
		int cruiser = 2;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, cruiser, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'C';
				actualGrid[rowNumber][colNumber - 1] = 'C';
			}
		} while (clear);
	}
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	// AirCraft Carrier
	positionNumber = positionGenerator();
	if (positionNumber == 1)    // Down
	{
		int clear = 1;
		int aircraftCarrier = 5;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, aircraftCarrier, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'A';
				actualGrid[rowNumber + 1][colNumber] = 'A';
				actualGrid[rowNumber + 2][colNumber] = 'A';
				actualGrid[rowNumber + 3][colNumber] = 'A';
				actualGrid[rowNumber + 4][colNumber] = 'A';
			}
		} while (clear);
	}
	else if (positionNumber == 2) // Right
	{
		int clear = 1;
		int aircraftCarrier = 5;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, aircraftCarrier, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'A';
				actualGrid[rowNumber][colNumber + 1] = 'A';
				actualGrid[rowNumber][colNumber + 2] = 'A';
				actualGrid[rowNumber][colNumber + 3] = 'A';
				actualGrid[rowNumber][colNumber + 4] = 'A';
			}
		} while (clear);
	}
	else if (positionNumber == 3)	// Up
	{
		int clear = 1;
		int aircraftCarrier = 5;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, aircraftCarrier, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'A';
				actualGrid[rowNumber - 1][colNumber] = 'A';
				actualGrid[rowNumber - 2][colNumber] = 'A';
				actualGrid[rowNumber - 3][colNumber] = 'A';
				actualGrid[rowNumber - 4][colNumber] = 'A';
			}
		} while (clear);
	}
	else if (positionNumber == 4)	// Left
	{
		int clear = 1;
		int aircraftCarrier = 5;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, aircraftCarrier, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'A';
				actualGrid[rowNumber][colNumber - 1] = 'A';
				actualGrid[rowNumber][colNumber - 2] = 'A';
				actualGrid[rowNumber][colNumber - 3] = 'A';
				actualGrid[rowNumber][colNumber - 4] = 'A';
			}
		} while (clear);
	}
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	// Battle Ship
	positionNumber = positionGenerator();
	if (positionNumber == 1)    // Down
	{
		 int clear = 1;
		 int battleship = 4;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, battleship, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'B';
				actualGrid[rowNumber + 1][colNumber] = 'B';
				actualGrid[rowNumber + 2][colNumber] = 'B';
				actualGrid[rowNumber + 3][colNumber] = 'B';
			}
		} while (clear);
	}
	else if (positionNumber == 2) // Right
	{
		 int clear = 1;
		 int battleship = 4;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, battleship, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'B';
				actualGrid[rowNumber][colNumber + 1] = 'B';
				actualGrid[rowNumber][colNumber + 2] = 'B';
				actualGrid[rowNumber][colNumber + 3] = 'B';
			}
		} while (clear);
	}
	else if (positionNumber == 3)	// Up
	{
		int clear = 1;
		int battleship = 4;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, battleship, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'B';
				actualGrid[rowNumber - 1][colNumber] = 'B';
				actualGrid[rowNumber - 2][colNumber] = 'B';
				actualGrid[rowNumber - 3][colNumber] = 'B';
			}
		} while (clear);
	}
	else if (positionNumber == 4)	// Left
	{
		int clear = 1;
		int battleship = 4;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, battleship, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'B';
				actualGrid[rowNumber][colNumber - 1] = 'B';
				actualGrid[rowNumber][colNumber - 2] = 'B';
				actualGrid[rowNumber][colNumber - 3] = 'B';
			}
		} while (clear);
	}
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	// Submarine
	positionNumber = positionGenerator();
	if (positionNumber == 1)	// Down
	{
		int clear = 1;
		int submarine = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, submarine, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'S';
				actualGrid[rowNumber + 1][colNumber] = 'S';
				actualGrid[rowNumber + 2][colNumber] = 'S';
			}
		} while (clear);
	}
	else if (positionNumber == 2) // Right
	{
		int clear = 1;
		int submarine = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, submarine, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'S';
				actualGrid[rowNumber][colNumber + 1] = 'S';
				actualGrid[rowNumber][colNumber + 2] = 'S';
			}
		} while (clear);
	}
	else if (positionNumber == 3)	// Up
	{
		int clear = 1;
		int submarine = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, submarine, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'S';
				actualGrid[rowNumber - 1][colNumber] = 'S';
				actualGrid[rowNumber - 2][colNumber] = 'S';
			}
		} while (clear);
	}
	else if (positionNumber == 4)	// Left
	{
		int clear = 1;
		int submarine = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, submarine, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'S';
				actualGrid[rowNumber][colNumber - 1] = 'S';
				actualGrid[rowNumber][colNumber - 2] = 'S';
			}
		} while (clear);
	}
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	// Destroyer
	positionNumber = positionGenerator();
	if (positionNumber == 1)    // Down
	{
		int clear = 1;
		int destroyer = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, destroyer, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'D';
				actualGrid[rowNumber + 1][colNumber] = 'D';
				actualGrid[rowNumber + 2][colNumber] = 'D';
			}
		} while (clear);
	}
	else if (positionNumber == 2) // Right
	{
		int clear = 1;
		int destroyer = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, destroyer, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'D';
				actualGrid[rowNumber][colNumber + 1] = 'D';
				actualGrid[rowNumber][colNumber + 2] = 'D';
			}
		} while (clear);
	}
	else if (positionNumber == 3)	// Up
	{
		int clear = 1;
		int destroyer = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, destroyer, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'D';
				actualGrid[rowNumber - 1][colNumber] = 'D';
				actualGrid[rowNumber - 2][colNumber] = 'D';
			}
		} while (clear);
	}
	else if (positionNumber == 4)	// Left
	{
		int clear = 1;
		int destroyer = 3;
		do {
			rowNumber = randGenerator();
			colNumber = randGenerator();
			if (testLocation(actualGrid, positionNumber, destroyer, rowNumber, colNumber))
			{
				clear = 0;
				actualGrid[rowNumber][colNumber] = 'D';
				actualGrid[rowNumber][colNumber - 1] = 'D';
				actualGrid[rowNumber][colNumber - 2] = 'D';
			}
		} while (clear);
	}
	//////////////////////////////////////////////////////
} // End of placeShips

void playBattleship(char displayGrid[][12], char actualGrid[][12], static int highScores[], int *scores, int *trackedHits, int *trackedMissiles) {
	int i, j;
	int userChoice;
	int hits = *trackedHits;
	int missiles = *trackedMissiles;
	CLS;
	do {
		for (i = 0; i < 12; i++) // Printing out the game grid
		{
			for (j = 0; j < 12; j++)
			{
				printf("%c ", displayGrid[i][j]);
			}
			printf("\n");
		}

		for (i = 0; i < 12; i++) // Testing grid
		{
			for (j = 0; j < 12; j++)
			{
				printf("%c ", actualGrid[i][j]);
			}
			printf("\n");
		}

		printf("\n");
		printf("MISSILES LAUNCHED: %i\n", missiles);
		userChoice = getChoice2();
		switch (userChoice) {
		case 1: // Shoot
			shootMissile(displayGrid, actualGrid, &missiles, &hits);
			if (endGame(missiles, hits) == 1)
			{
				*(scores + 10) = missiles;
				CLS;
				printf("%i is the 11th spot.\n", *(scores+10));	// test
				printf("YOU WON BY FIRING %i MISSILES!\n", missiles);	
				bubbleSort(*(scores), i);
				printf("%i is the first value in the array.\n", *(scores));	// testing the sort
				PAUSE;
				resetGrids(displayGrid, actualGrid);
				userChoice = 4;	// Exits the submenu and goes to the main menu
				placeShips(displayGrid, actualGrid);
				break;
			}
			PAUSE;
			CLS;
			break;
		case 2: // New Grid
			missiles = 0;
			hits = 0;
			resetGrids(displayGrid, actualGrid);
			placeShips(displayGrid, actualGrid);
			CLS;
			break;
		case 3: // Save
			saveGame(displayGrid, actualGrid, &missiles, &hits);
			break;
		case 4: // Quit
			*trackedMissiles = missiles;	// When you quit it saves the missiles you've fired
			*trackedHits = hits;	// When you quit it saves the hits you've obtained
			break;
		default:
			printf("That is not a valid option\n");
			break;
		}
	} while (userChoice != 4);
} // End of playBattleship

int positionGenerator() {	// Function that determines if the ship will go up, down, left, or right
	int i = 0;
	int positionNumber;
	// 1 = down, 2 = right, 3 = up, 4 = left 
	while (i < 1)
	{
		positionNumber = rand() % 4 + 1;
		i++;
	}
	// End of while
	i = 0;
	return positionNumber;
} // End of randomNumberGenerator

int randGenerator() {	// Our random number generator for placing the ships
	int randNumber;
	randNumber = rand() % 10;
	randNumber = randNumber + 1;
	return randNumber;
} // End of randGenerator

void shootMissile(char displayGrid[][12], char actualGrid[][12], int *missiles, int *hits) {	// Function that shoots the missile
	int x, y;
	printf("Enter X Coordinate: ");
	scanf(" %i", &x);

	printf("Enter Y Coordinate: ");
	scanf(" %i", &y);
	printf("You shot at: (%i,%i)\n", x, y);

	if (actualGrid[y + 1][x + 1] == 'C')	// Checks if spot has a C
	{
		actualGrid[y + 1][x + 1] = 'H';
		displayGrid[y + 1][x + 1] = 'C';
		(*hits)++;
		(*missiles)++;
	}
	else if (actualGrid[y + 1][x + 1] == 'B')	// Checks if spot has a B
	{
		actualGrid[y + 1][x + 1] = 'H';
		displayGrid[y + 1][x + 1] = 'B';
		(*hits)++;
		(*missiles)++;
	}
	else if (actualGrid[y + 1][x + 1] == 'D')	// Checks if spot has a D
	{
		actualGrid[y + 1][x + 1] = 'H';
		displayGrid[y + 1][x + 1] = 'D';
		(*hits)++;
		(*missiles)++;
	}
	else if (actualGrid[y + 1][x + 1] == 'A')	// Checks if spot has an A
	{
		actualGrid[y + 1][x + 1] = 'H';
		displayGrid[y + 1][x + 1] = 'A';
		(*hits)++;
		(*missiles)++;
	}
	else if (actualGrid[y + 1][x + 1] == 'S')	// Checks if spot has an S
	{
		actualGrid[y + 1][x + 1] = 'H';
		displayGrid[y + 1][x + 1] = 'S';
		(*hits)++;
		(*missiles)++;
	}
	else if (displayGrid[y + 1][x + 1] != '-')	// Checks if it was somewhere you already shot
	{
		printf("You have already shot at that location\n");
	}
	else  // Checks if it was a miss
	{
		actualGrid[y + 1][x + 1] = 'M';
		displayGrid[y + 1][x + 1] = 'M';
		(*missiles)++;
	}
} // End of shootMissile

int testLocation(char actualGrid[][12], int direction, int shipLength, int row, int col)	// Checks location to see if ship fits
{
	int counter;
	int valid = 0;
	for (counter = 0; counter < shipLength; counter++)
	{
		switch (direction) {
		case 1: // Down
			if (row + shipLength > 10)
			{
				valid = 0;
				return valid;
			}
			if (actualGrid[row + counter][col] == '-')	// Checking if max length of ship fits down
			{
				valid = 1;
			}
			else
			{
				valid = 0;
				return valid;
			}
			break;
		case 2: // Right
			if (col + shipLength > 10)
			{
				valid = 0;
				return valid;
			}
			if (actualGrid[row][col + counter] == '-')	// Checking if max length of ship fits to the right
			{
				valid = 1;
			}
			else
			{
				valid = 0;
				return valid;
			}
			break;
		case 3:	// Up
			if (row - shipLength > 10)
			{
				valid = 0;
				return valid;
			}
			if (actualGrid[row - counter][col] == '-')	// Checking if max length of ship fits up
			{
				valid = 1;
			}
			else
			{
				valid = 0;
				return valid;
			}
			break;
		case 4:	// Left
			if (col - shipLength > 10)
			{
				valid = 0;
				return valid;
			}
			if (actualGrid[row][col - counter] == '-')	// Checking if max length of ship fits to left
			{
				valid = 1;
			}
			else
			{
				valid = 0;
				return valid;
			}
			break;
		}
	}
	return valid;
} // End of testLocation

int endGame(int missiles, int hits)
{
	if (hits == 1)
		// If all ship letters are hit
	{
		// Line where you save missiles to high scores file
		return 1;
	}
	return 0;
} // End of endGame

int getNumbers(static int highScores[])
{
	FILE *fp;
	char buff[100];

	fp = fopen("highscores.txt", "r");
	if (fp == NULL) {	// Error check for file
		printf("Cannot write to file. Program exiting.\n");
		PAUSE;
		exit(-1);
	}
	int i;
	fscanf(fp, "%s", buff);	// Grabbing first string in file until space is found
	for (i = 0; i < 11; i++)
	{
		fscanf(fp, "%s", buff);	// Grabbing string until space is found in text file

		highScores[i] = atoi(buff);	// atoi converts "buff" into an int (buff is holding "9999")
	}
	fclose(fp);
	return highScores;
}	// End of getNumbers

void bubbleSort(int *scores, int i) {
	int bottom, temp;
	char switchMade;

	bottom = 10;
	do {
		switchMade = 'N';
		for (i = 0; i < bottom; i++){
			if (*(scores + i) > *(scores + i + 1))
				switchMade = doTheSwitch(*(scores), i, switchMade);
			}// end for 
		bottom--;
	} while (switchMade == 'Y');
	PAUSE;
}// end of bubble sort 

char doTheSwitch(int *scores, int i, char switchMade) {
	char result = 'Y';
	int temp;
	temp = *(scores + i);
	*(scores + i) = *(scores + i + 1);
	*(scores + i + 1) = temp;
	return result;
}// end of doTheSwitch 

void saveGame(char displayGrid[][12], char actualGrid[][12], int *missiles, int *hits)	// Saves current game into a text file
{
	FILE *fp;
	int i, j;
	
	fp = fopen("savedgame.txt", "w");
	if (fp == NULL) {	// Error check for file
		printf("Cannot write to file. Program exiting.\n");
		PAUSE;
		exit(-1);
	}

	for (i = 0; i < 12; i++) // Printing actualGrid array to a text file
	{
		for (j = 0; j < 12; j++)
		{
			fprintf(fp, "%c", actualGrid[i][j]);
		}
		fprintf(fp, "\n");
	}

	fprintf(fp, "\n");

	for (i = 0; i < 12; i++) // Printing actualGrid array to a text file
	{
		for (j = 0; j < 12; j++)
		{
			fprintf(fp, "%c", displayGrid[i][j]);
		}
		fprintf(fp, "\n");
	}
	
	fprintf(fp, "\nMissiles: %i", *missiles);
	fprintf(fp, "\nHits: %i", *hits);

	fclose(fp);
}	// End of saveGame

void resetGrids(char displayGrid[][12], char actualGrid[][12])	// Resets both grids
{
	int i, j;
	for (i = 1; i < 11; i++) // Resetting Display Array
	{
		for (j = 1; j < 11; j++)
		{
			if (displayGrid[i][j] != '-')
			{
				displayGrid[i][j] = '-';
			}
		}
	}

	for (i = 1; i < 11; i++) // Resetting Actual Array
	{
		for (j = 1; j < 11; j++)
		{
			if (actualGrid[i][j] != '-')
			{
				actualGrid[i][j] = '-';
			}
		}
	}
}	// End of resetGrids

void loadGame(char displayGrid[][12], char actualGrid[][12], int *trackedMissiles, int *trackedHits)
{
	FILE *loadGame;
	char c;
	int i, j;
	loadGame = fopen("savedgame.txt", "w");
	if (loadGame == NULL) {	// Error check for file
		printf("Cannot write to file. Program exiting.\n");
		PAUSE;
		exit(-1);
	}
	
	for (i = 0; i < 12; i++) // Printing text file saved game into the array
	{
		for (j = 0; j < 12; j++)
		{
			c = fgetc(loadGame);
		}
		fgetc(loadGame);
	}

	fclose(loadGame);

}	// End of loadGame