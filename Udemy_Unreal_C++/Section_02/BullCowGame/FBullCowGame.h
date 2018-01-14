/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/



#pragma once
#include <string>

// to make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};


enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase

};

class FBullCowGame
{
public:

	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);  // counts bulls and cows and increases try # assuming valid guess
	

private:
	//See constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};