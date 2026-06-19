#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfos
{
    short RoundNumber = 1;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName = "";
};

short RandomNumber(short From, short To) {
    int RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}

struct stGameResults
{
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName;
};

string Tabs(short TabsNumber)
{
    string T = "";
    for (short i = 1; i <= TabsNumber; i++)
        T += "\t";
    return T;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) + "_________________________________________________________________________________\n\n";
    cout << Tabs(2) + "                           +++ G a m e O v e r +++\n";
    cout << Tabs(2) + "_________________________________________________________________________________\n\n";
}

void MakeTheColorOnScreen(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::Draw:
        system("color 60");
        break;
    }
}

string ChoiceName(short ChoiceNumber)
{
    string ArrayOfCoices[3] = { "Stone", "Paper", "Scissor" };
    return ArrayOfCoices[ChoiceNumber - 1];
}

string WinnerName(enWinner RoundWinner)
{
    string Winner[3] = { "Player", "Computer", "No One" };
    return Winner[RoundWinner - 1];
}

void PrintRoundResults(stRoundInfos RoundInfos)
{
    cout << "\n____________ Round [" << RoundInfos.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfos.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfos.ComputerChoice) << endl;
    cout << "Round Winner : [" << RoundInfos.WinnerName << "]\n";
    cout << "___________________________________\n" << endl;
    MakeTheColorOnScreen(RoundInfos.RoundWinner);
}

enGameChoice ReadPlayerChoice()
{
    short PlayerChoice = 1;
    do {

        cout << "\n Your Choice ? [1]:Stone , [2]:Paper , [3]:Scissor .\n";
        cin >> PlayerChoice;

    } while (PlayerChoice < 1 || PlayerChoice > 3);

    return (enGameChoice)PlayerChoice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfos RoundInfos)
{
    if (RoundInfos.ComputerChoice == RoundInfos.PlayerChoice)
        return enWinner::Draw;

    switch (RoundInfos.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfos.ComputerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;
    case enGameChoice::Paper:
        if (RoundInfos.ComputerChoice == enGameChoice::Scissor)
            return enWinner::Computer;
        break;
    case enGameChoice::Scissor:
        if (RoundInfos.ComputerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }
    return enWinner::Player;
}

enWinner WhoWonTheGame(short PlayerWonTimes, short ComputerWonTimes)
{
    if (PlayerWonTimes > ComputerWonTimes)
        return enWinner::Player;
    else if (ComputerWonTimes > PlayerWonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

void RestartGame()
{
    system("cls");
    system("color 07");
}

short ReadHowManyRounds()
{
    short HowManyRounds = 1;
    do
    {
        cout << "\n Enter how many Rounds you want to play ? The Number should be in Range (1 -- 10) !\n";
        cin >> HowManyRounds;
    } while (HowManyRounds < 1 || HowManyRounds > 10);
    return HowManyRounds;
}

stGameResults FillGameResults(short HowManyRounds, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.PlayerWonTimes = PlayerWonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWonTimes, ComputerWonTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfos RoundInfos;
    short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\n Round [" << GameRound << "] Begin :\n";
        RoundInfos.RoundNumber = GameRound;
        RoundInfos.PlayerChoice = ReadPlayerChoice();
        RoundInfos.ComputerChoice = GetComputerChoice();
        RoundInfos.RoundWinner = WhoWonTheRound(RoundInfos);
        RoundInfos.WinnerName = WinnerName(RoundInfos.RoundWinner);

        if (RoundInfos.RoundWinner == enWinner::Player)
            PlayerWonTimes++;
        else if (RoundInfos.RoundWinner == enWinner::Computer)
            ComputerWonTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfos);
    }
    return FillGameResults(HowManyRounds, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << "\n";
    cout << Tabs(2) + "______________________________[ Game Results ]___________________________________\n\n";
    cout << Tabs(2) + " Player Won times : " << GameResults.PlayerWonTimes << "\n";
    cout << Tabs(2) + " Computer Won times : " << GameResults.ComputerWonTimes << "\n";
    cout << Tabs(2) + " Draw times : " << GameResults.DrawTimes << "\n";
    cout << Tabs(2) + " Game Winner : " << GameResults.WinnerName << "\n\n";
    cout << Tabs(2) + "_________________________________________________________________________________\n";
}

void StartGame()
{
    char PlayAgain = 'y';
    do
    {
        if (PlayAgain == 'n' || PlayAgain == 'N') break;
        RestartGame();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout << "\n Do you want to play again ?"
            << " YES : press 'y' !"
            << " NO : press 'n' !\n";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
    system("color 1F");
    cout << "\n";
}

int main()
{
    //Seeds the random Number Generator in C++ , call only once .
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}