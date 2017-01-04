// Mohammad Hussain
//Game Simulater


#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define PAUSE system ("pause");
#define CLS system ("cls");


// Protoype functions 
void displayMenu();
int getChoice();
void battle(struct PLAYER* Mohammad);
void displayResults(struct PLAYER* Mohammad);
void buySomething(struct PLAYER* Mohammad);
void displayHighscores(float highScores[], int numGames);
void readHighscoresBin(int* numGame, float p[]);
void writeHighscoresBin(int numGame, float p[]);

// Structs 
typedef struct {
	char Name[20];
	int lives;
	float money;
	int strength;
	int wins;
	int loss;
	int winStreak;
	int winCounter;
	int lossCounter;
	int lossStreak;
	float maxMoney;

}PLAYER;


main() {
	///////////////  VARIABLES ///////////////
	float highScores[10];
	int userChoice;
	int wins = 0;
	int loss = 0;
	int numGame = 0;
	int i;
	srand(time(NULL));

	//////////SETTING STUCT VALUES //////////

	PLAYER Mohammad;
	Mohammad.lives = 4;
	Mohammad.money = 0;
	Mohammad.strength = 0;
	Mohammad.wins = 0;
	Mohammad.loss = 0;
	Mohammad.winStreak = 0;
	Mohammad.lossStreak = 0;
	Mohammad.lossCounter = 0;
	Mohammad.winCounter = 0;
	Mohammad.maxMoney = 0;

	/////////////////////////////////////////////////

	readHighscoresBin(&numGame, highScores);// function to read the highscores in

	do {
		CLS;
		if (Mohammad.lives == 0) {
			printf("******************\n");
			printf("*  GAME OVER     * \n");
			printf("******************\n");
			printf("\n");
			numGame++;// incrementing the game counter 
			float insert = Mohammad.maxMoney;
			for (i = 0; i < 10; i++) {
				if (insert >= highScores[i]) {
					float temp;
					temp = highScores[i];
					highScores[i] = insert;
					insert = temp;
				}// end if for sorting the array
			}
			PAUSE;
			// resetting the values in struct
			Mohammad.lives = 4;
			Mohammad.money = 0;
			Mohammad.strength = 0;
			Mohammad.wins = 0;
			Mohammad.loss = 0;
			Mohammad.winStreak = 0;
			Mohammad.lossStreak = 0;
			Mohammad.lossCounter = 0;
			Mohammad.winCounter = 0;
			Mohammad.maxMoney = 0;

		}// end if
		printf("===============================================================\n");
		printf("Lives [%i] Strength [%i] , Money[ %.2f] ,Money accumilated [%.2f]\n", Mohammad.lives, Mohammad.strength,
			Mohammad.money, Mohammad.maxMoney);
		printf("===============================================================\n");
		userChoice = getChoice();
		switch (userChoice) {

		case 1:// Battle
			battle(&Mohammad);
			break;

		case 2:// Buy something
			buySomething(&Mohammad);
			break;

		case 3:// Display result of battles 
			displayResults(&Mohammad);
			break;

		case 4:// display the top 10 previous high scores
			displayHighscores(highScores, numGame);
			break;

		case 5:// quit 
			break;

		default:
			printf("Please enter a valid option\n");
			PAUSE;
			break;
		}// end switch 

	} while (userChoice != 5);
	writeHighscoresBin(numGame, highScores);


	//writeFile(highScores);

}// end of main 

void displayMenu() {
	printf("1.Battle\n");
	printf("2.Buy something\n");
	printf("3.Display the result of all battles\n");
	printf("4.Display top 10 previous high scores\n");
	printf("5.Quit\n");
	printf(" Enter your Choice:");

}// end of display menu 

int getChoice() {
	int result;
	displayMenu();
	scanf("%i", &result);
	return result;
}// end get choice 

void battle(PLAYER* Mohammad) {
	int randomNumber;
	int i = 0;

	while (i < 1) // Random number generator
	{
		randomNumber = rand() % 100 + 1;
		i++;
	} //end of while

	if (Mohammad->strength >= 30) {
		randomNumber = randomNumber - 30;
	}
	else
	{
		randomNumber = randomNumber - Mohammad->strength;
	}

	if (randomNumber <= 50) {
		printf("****************\n");
		printf("*  YOU WON!    *\n");
		printf("****************\n");
		PAUSE;
		Mohammad->wins++;
		Mohammad->lossCounter = 0;
		Mohammad->winCounter++;
		if (Mohammad->winCounter > Mohammad->winStreak) {
			Mohammad->winStreak = Mohammad->winCounter;
		}
		Mohammad->money = Mohammad->money + 50;
		Mohammad->maxMoney = Mohammad->maxMoney + 50;
		Mohammad->strength = Mohammad->strength + 5;
	}
	else if (randomNumber >= 51 && randomNumber <= 100) {
		printf("****************\n");
		printf("*  YOU LOST!  *\n");
		printf("****************\n");
		PAUSE;
		Mohammad->loss++;
		Mohammad->winCounter = 0;
		Mohammad->lossCounter++;
		if (Mohammad->lossCounter > Mohammad->lossStreak) {
			Mohammad->lossStreak = Mohammad->lossCounter;
		}
		Mohammad->lives = Mohammad->lives - 1;
		if (Mohammad->strength == 0) {
			Mohammad->strength = 0;
		}
		else {
			Mohammad->strength = Mohammad->strength - 5;
		}
	}// end of loss calcualtions

}// end battle 

void displayResults(PLAYER* Mohammad) {

	printf("Number of wins %i\n", Mohammad->wins);
	printf("Number of losses %i\n", Mohammad->loss);
	printf("Longest winning streak %i\n", Mohammad->winStreak);
	printf("Longest Loss streak %i\n", Mohammad->lossStreak);
	PAUSE;

}// end of display Result 

void buySomething(PLAYER* Mohammad) {
	int Userchoice;
	do {
		CLS;
		printf("===============================================================\n");
		printf("Lives [%i] Strength [%i] Money [%.2f]  Money accumilated [%.2f]\n", Mohammad->lives, Mohammad->strength,
			Mohammad->money, Mohammad->maxMoney);
		printf("===============================================================\n");
		printf("\n");
		printf(" STORE \n");
		printf("1.Buy strength: [Price $50 ]\n");
		printf("2.Buy lives [Price $100 ]\n");
		printf("3.Main Menu\n");
		printf("What is your choice:");
		scanf("%i", &Userchoice);

		if (Userchoice == 1) {
			if (Mohammad->money < 50) {
				printf("Insufficient Funds\n ");
			}
			else {
				Mohammad->money = Mohammad->money - 50;
				Mohammad->strength = Mohammad->strength + 5;
				printf(" You succesfully added 5 strenght point\n");
			}
			PAUSE;
		}// end if 
		if (Userchoice == 2) {
			if (Mohammad->money < 100) {
				printf("Insufficient Funds\n");
			}
			else {
				Mohammad->money = Mohammad->money - 100;
				Mohammad->lives = Mohammad->lives + 1;
				printf(" You succesfully added 1 life\n");
			}
			PAUSE;

		}// end if 
	} while (Userchoice != 3);

}// end of buy something function 



void displayHighscores(float highScores[], int numGames) {
	int i;
	printf("\n");
	printf("TOP SCORES (HIGHEST MONEY EARNED)\n");
	for (i = 0; i < numGames; i++) {
		printf("%.2f\n", highScores[i]);
	}
	PAUSE;
}// end of displayHighScores function 

void writeHighscoresBin(int numGame, float p[])
{
	FILE* payPtr;
	payPtr = fopen("highScores.bin", "wb");
	if (payPtr == NULL)
	{
		CLS;
		printf("\n\n\tERROR WRITING THE FILE\n\t");
		PAUSE;
	}
	fwrite(&numGame, sizeof(int), 1, payPtr);
	fwrite(p, sizeof(float), numGame, payPtr);


	fclose(payPtr);
	return;
}// end of  write high scores function 

void readHighscoresBin(int* numGame, float p[])
{
	FILE* payPtr;
	payPtr = fopen("highScores.bin", "rb");
	if (payPtr == NULL)
	{
		CLS;
		printf("\n\t********************"
			"\n\t* Cannot connect to file *"
			"\n\t********************\n\n\t");
		PAUSE;
		return;
	}
	fread(numGame, sizeof(int), 1, payPtr);
	fread(p, sizeof(float), *numGame, payPtr);
	fclose(payPtr);
	return;
}// end of read high scores 
