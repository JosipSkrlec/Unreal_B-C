// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // LECTURE 69. citanje iz TXT file-a
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordsFromTxtFile, *WordListPath);

    // stavljamo rijeci unutra kako bi izbjegli pisanje dugog istog koda kasnije !!!
    Isograms = GetValidWords(WordsFromHeader);

    SetupGame();
}


void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming The Player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    //HiddenWord = TEXT("cakes");
    //HiddenWord = GetValidWords(WordsFromHeader)[FMath::RandRange(0, GetValidWords(WordsFromHeader).Num() - 1)];
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompt Player For Guess
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);// Debug Line 
    //PrintLine(TEXT("The number in list is : %i."), GetValidWords(WordsFromHeader).Num() - 1);
    //GetValidWords();

    // const TCHAR HW[] = TEXT("plums");
    // PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]); // print "c"
    // PrintLine(TEXT("The 4th character of HW is: %c"), HW[3]); // prints "m"
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining."), Lives);
        return;
    }

    // Check If Isogram
    if (!IsIsogram(Guess))
    {
        /* code */
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Remove Life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    // ovdje vidimo da smo deklarirali 2 varijable ali ih nismo inicijalizirali
    // to nam je znak da ce one biti out parametri od metode!!!
    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("Yout have %i Bulls and %i Cows"), Bulls, Cows);

    // Show the player Bulls and Cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    // int32 Index = 0;
    // int32 Comparison = Index + 1;

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index+1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
    //for (int32 Index = 0, Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    //{
    //    if (Word[Index] == Word[Comparison])
    //    {
    //        return false;
    //    }
    //}

    return true;

    // For each letter. 
    // Start at element [0].
    // Compare against the next letter.
    // Until we reach [Word.Len() -1].
    // if any are the same return false.   
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    // if the index guess is same as index hidden, bullcount++
    // if not a bull was it a cow if yes CawCount++
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount++;
            }
        }
    }
}


//void UBullCowCartridge::GetValidWords()
//{
//    PrintLine(TEXT("The number of possible words is: %i."), WordsFromHeader.Num());
//
//    for (int32 i = 0; i != 10; i++)
//    {
//        //if (WordsFromHeader[i].Len() >= 4 && WordsFromHeader[i].Len() <= 8)
//        if (WordsFromHeader[i].Len() == 5 && IsIsogram(WordsFromHeader[i]))
//        {
//            ValidWords.Emplace(WordsFromHeader[i]);
//            //PrintLine(TEXT("word on place %i is %s"), i, *WordsFromHeader[i]);
//        }
//    }
//
//    for (int32 i = 0; i < ValidWords.Num(); i++)
//    {
//        PrintLine(TEXT("word is %s"), *ValidWords[i]);
//    }
//}