#include <map>
#include "FBullCowGame.h"

#define TMap std::map;

using FString = std::string;
using int32 = int;

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

bool FBullCowGame::IsGameWon() const 
{ 
	return bGameIsWon; 
}


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}




EGuessStatus FBullCowGame::CheckGuess(FString guess) const
{
	

	if (!IsIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::Ok;
	}
}

// receives a valid guess, increments turn, and returns count. 
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			// if they match
			if (guess[j] == MyHiddenWord[i])
			{
				// incriment bulls if theyre in the same place
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				// incriment cows if they are not
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString guess) const 
{
	// treat 0 and 1 letter words as isograms
	if (guess.length() <= 1) 
	{ 
		return true; 
	}

	std::map<char, bool> LetterSeen;
	for (auto Letter : guess) // for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
		

	return true; // for example where \0 is entered
}

bool FBullCowGame::IsLowercase(FString guess) const
{
	for (auto Letter : guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}
