// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to BC game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // magic word , REMOVE it!
    PrintLine(TEXT("Press TAB to continue"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    FString HiddenWord = TEXT("Cake"); // move outside this function

    if (Input == "") {
        return;
    }

    if (Input == HiddenWord) {
        PrintLine(TEXT("You have Won!"));
    }
    else {
        PrintLine(TEXT("You have Lose!"));
    }
}