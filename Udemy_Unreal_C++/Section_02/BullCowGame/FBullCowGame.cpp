/**/

#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

void FBullCowGame::Reset()
{
	//constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planetory"; // this must be an isogram

	///MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,6}, {6,7}, {7,7}, {8,9}, { 9,9 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;  
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_LowerCase; 
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		EGuessStatus::OK;
	}
}

// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess
	
	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			// if they match then
			if (Guess[i] == MyHiddenWord[j])
			{
				// if they are in the same place
				if (i == j)
				{ 
					BullCowCount.bulls++; // increment the Bull
				}
				else
				{
					BullCowCount.cows++; // increment cows
				}
			}
		}
		
	}
		 
	if (BullCowCount.bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isogram
	if (Word.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen; // set our map
	for (auto Letter : Word)   // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;  //add t he letter to the map as seen
		}
	}
	return true; // for example in case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter
			return false;
	}
	return true;
}
