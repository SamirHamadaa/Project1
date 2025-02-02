#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enGameChoice { Stone = 1 , Paper = 2 , Scissors = 3 };
enum enWinner { Player1 = 1 , Computer = 2 , Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;

};
struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes =0;
    short DrawTimes = 0;
    enWinner  GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{

    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;

}

string WinnerName(enWinner Winner)
{

    string arrWinnerName[3] = { "Player1","Computer","Draw" };
    return arrWinnerName[Winner - 1];

}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{

    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }

    return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{

    string arrGameChoice[3] = { "Stone","Paper","Scissors" };
    return arrGameChoice[Choice - 1];

}

void SetWinnerScreenColor(enWinner Winner)
{

    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F");
        break;
    }

}

void PrintRoundResults(stRoundInfo RoundInfo)
{

    cout << "\n--------Round [" << RoundInfo.RoundNumber << "]--------\n\n";
    cout << "Player1 Choice : " << ChoiceName(RoundInfo.PlayerChoice) << "\n";
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
    cout << "Round Winner : [" << RoundInfo.WinnerName << "]\n";
    cout << "-----------------------------------------------------------\n\n";


    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerTimes, short ComputerTimes)
{

    if (PlayerTimes > ComputerTimes)
        return enWinner::Player1;
    else if (ComputerTimes > PlayerTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;

}

stGameResults FillGameResults(int GameRound, short Player1WinTimes, 
    short ComputerWinTimes, short DrawTimes)
{

    stGameResults GameResults;

    GameResults.GameRounds = GameRound;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

enGameChoice ReadPlayer1Choice()
{

    short Choice = 1;

    do
    {

        cout << "\n Your choice : [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;


    } while (Choice < 1 || Choice > 3);


    return (enGameChoice)Choice;
}

enGameChoice GetcomputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short HowManyRound)
{

    stRoundInfo RoundInfo;

    short Player1WinTimes = 0, ComputerwinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begines :\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetcomputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);


        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerwinTimes++;
        else
            DrawTimes++;


        PrintRoundResults(RoundInfo);
    }


    return FillGameResults(HowManyRound, Player1WinTimes,
        ComputerwinTimes, DrawTimes);


}

string Tabs(short Numberoftabs)
{
    string t = "";

    for (short i = 1; i < Numberoftabs; i++)
    {
        t = t + "\t";
        cout << t;
    }

    return t;
}

void ShowGameOverScreen()
{

   cout << Tabs(2) <<"__________________________________________________________\n\n";
   cout << Tabs(2) <<"                   +++ G a m e O v e r +++ \n";
   cout << Tabs(2) <<"__________________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{

   cout << Tabs(2) << "_____________________ [Game Results]_____________________\n\n";
   cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
   cout << Tabs(2) << "Player1 won times : " << GameResults.Player1WinTimes << endl;
   cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
   cout << Tabs(2) << "Draw times : " << GameResults.DrawTimes << endl;
   cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl;
   cout << Tabs(2) << "___________________________________________________________\n";
    
    
    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {

        cout << "How Many Rounds 1 To 10 ?\n";
        cin >> GameRounds;

    } while (GameRounds < 1 || GameRounds>10);

    return GameRounds;
}

void ResetScreen()
{

    system("cls");
    system("color 0F");

}

void StartGame()
{

    char playAgain = 'Y';

      
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << "\n" << Tabs(3) << "Do You Want To Play Again ? Y/N?";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');



}

int main()
{

    srand((unsigned)time(NULL));

    StartGame();





    return 0;
}
