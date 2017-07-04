/* This is the console executable, that makes use of the BullCow class. 
This acts as the view in a MVC pattern, and is resposbile for all user interaction. 
For game logic see the FBullCowGame class. 
*/

#include <iostream>
#include <string>

#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // intantiate a new game

int main()
{
	bool bplaying = false;
	do
	{
		PrintIntro();
		PlayGame();
		
		bplaying = PlayAgain();
	} while (bplaying);

	return 0;
}

// Everything for running the game
void PlayGame()
{
	BCGame.Reset();
	int32 maxtries = BCGame.GetMaxTries();

	// Loop asking for guesses wheil the game is not won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxtries)
	{
		FText guess = GetValidGuess(); 

		// Submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	
	PrintGameSummary();
	return;
}

bool PlayAgain()
{
	
	std::cout << "Do you want to try again with the same word? (Yes or No) \n";
	FText Response = "";

	bool bplayAgain = false; 
	std::getline(std::cin, Response);

		if (Response[0] == 'y' || Response[0] == 'Y')
		{
			bplayAgain = true;
		}
		else if (Response[0] == 'N' || Response[0] == 'n')
		{
			bplayAgain = false;
		}
		else
		{
			std::cout << "Not a valid option" << std::endl;
		}

		std::cout << std::endl;
	return bplayAgain;
}

// Game introduction
void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a crappy word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram. \n";
	std::cout << std::endl;
	return;
}

// loop until user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText guess = "";

	do
	{
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries() << ". What is your guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuess(guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Word is not an Isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Word is not in lower case.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::Ok); // keep looping until there is a valid guess

	return guess;
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done you win\n";
	}
	else
	{
		std::cout << "You lose, god you are fucking stupid\n";
	}
}
