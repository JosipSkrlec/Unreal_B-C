// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	// = 0 nas stiti od un inicijalizacije jer na pocetku ne moze biti drugacije nego 0!!
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;

	//void GetValidWords();
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	// ako stravimo int32& (da je referenca) a ne const tada znaci da ce oni biti output od te metode!!!
	// next with return aprameters (2 i 3)
	//FBullCowCount GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const; // const na kraju znaci da nece promjenti nista od navedenog (isisogram gameover....)
	FBullCowCount GetBullCows(const FString& Guess) const;

	// Your declarations go below!
	// member variables
private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> WordsFromTxtFile;
	TArray<FString> Isograms;
	//TArray<FString> ValidWords;
};