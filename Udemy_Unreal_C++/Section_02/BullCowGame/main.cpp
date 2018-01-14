/* ##########################################################################
   # This is the console executable, that makes use of BullCow class        #
   # This act as the view in a MVC pattern, and is responsible for all user #
   # interactions. For game logic see FBullCowGame class.                   #
   ##########################################################################
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

//function prototypes as outside a class
void  PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //Instantiate a new game, which re-use across plays

// the entry point for our application
int main() 
{
	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0;
}

//Introduce the game
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram that I am thinking of ? \n";
	std::cout << std::endl;
	return;
}

// plays a sinlge game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FString Guess = "";
		Guess = GetValidGuess(); 

		
		// submit guess valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.bulls;
		std::cout << " Cows = " << BullCowCount.cows << std::endl;
	}

	PrintGameSummary();

	
}

// Loop continually untill user gives valid guess
FString GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FString Guess = "";
	do
	{
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << " : Enter your guess: ";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assuming guess is valid
			return Guess;
		}
		
	}
	while (Status != EGuessStatus::OK); // Keep looping until we get no errors
	
	//return Guess;
}

//Ask player to play again
bool AskToPlayAgain()
{
	std::cout << "Do you wanat to play again with the same hidden word (y/n)?";
	FString Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nWelldone! You Won!\n\n";
		//AskToPlayAgain();
	}
	else
	{
		std::cout << "\nBetter luck next time!\n\n";
		//AskToPlayAgain();

	}
}