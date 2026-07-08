#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

int Max_Rounds=10;

enum enGameChoice{Stone= 1,Paper= 2,Scissors= 3};

enum enWinner{Player1= 1,Computer= 2,Draw= 3};

struct stRoundInfo
{
	short RoundNumber= 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName="";
	
};

struct stGameResults
{
short GameRounds= 0;
short Player1WinTimes= 0;
short ComputerWinTimes= 0;
short DrawTimes= 0;
enWinner GameWinner;
string WinnerName="";
	
};

int ReadNumberOfGameRounds(string Message)
{
	short GameRound=1;
	do{
	cout<<Message<<endl;
	cin>>GameRound;
	}while(GameRound<1 || GameRound>Max_Rounds);
return GameRound;	
}

string Tabs(short NumberOfTabs)
{
	string t=" ";
	for(int counter=1;counter<=NumberOfTabs;counter++){
		t = t + "\t";
	}
	return t;
}

int RandomNumber(int from,int to)
{
	int RandNum=rand()%(to-from+1)+ from;
	return RandNum;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) 
{ 
  if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice) 
  return enWinner::Draw; 
  switch (RoundInfo.Player1Choice) {
  case enGameChoice::Stone:
  return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1; 
  case enGameChoice::Paper: 
  return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
  case enGameChoice::Scissors:
   return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1; 
} 
return enWinner::Draw;
}

enWinner WhoWonTheGame(short Player1WinTimes,short ComputerWinTimes)
{
	if(Player1WinTimes>ComputerWinTimes)
	return enWinner::Player1;
	else if(Player1WinTimes<ComputerWinTimes)
	return enWinner::Computer;
	else 
	return 
	enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
	 string arrGameChoices[3]={"Stone","Paper","Scissors"};
	 return arrGameChoices[Choice-1];
}

string FnWinnerName(enWinner Winner)
{
	 string arrWinnerName[3]={"Player1","Computer","No Winner(Draw)"};
	 return arrWinnerName[Winner-1];
}

enGameChoice ReadPlayer1Choice()
{
	short Choice;
	do{
		cout<<"Your Choice :\n [1]: Stone\n [2]: Paper\n [3]: Scissor\n";
		cin>>Choice;
	}while(Choice<1||Choice>3);
	return (enGameChoice)Choice;
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch(Winner){
		case enWinner::Player1:
		system("color 2F");
		break;
		case enWinner::Computer:
		system("color 4F");
		cout<<"\a";
		break;
		default:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout<<"\n________________ Round["<<RoundInfo.RoundNumber<<"]_________________\n\n";
	cout<<"Player1 Choice: "<<ChoiceName(RoundInfo.Player1Choice)<<endl;
	cout<<"Computer Choice: "<<ChoiceName(RoundInfo.ComputerChoice)<<endl;
	cout<<"Round Winner: ["<<RoundInfo.WinnerName<<"]\n";
	cout<<"_________________________________________________________________\n";
	SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults FillGameRuslts(int GameRounds,short Player1WinTimes,short ComputerWinTimes,short DrawTimes)
{
	stGameResults GameResults;
	GameResults.GameRounds=GameRounds;
	GameResults.Player1WinTimes=Player1WinTimes;
	GameResults.ComputerWinTimes=ComputerWinTimes;
	GameResults.DrawTimes=DrawTimes;
	GameResults.GameWinner=WhoWonTheGame(Player1WinTimes,ComputerWinTimes);
	GameResults.WinnerName=FnWinnerName(GameResults.GameWinner);
	return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes=0,ComputerWinTimes=0,DrawTimes=0;
	for(short GameRound=1;GameRound<=HowManyRounds;GameRound++){
		cout<<"\nRound ["<<GameRound<<"] begins:\n";
		RoundInfo.RoundNumber=GameRound;
		RoundInfo.Player1Choice=ReadPlayer1Choice();
		RoundInfo.ComputerChoice=GetComputerChoice();
		RoundInfo.Winner=WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName=FnWinnerName(RoundInfo.Winner);
		 
		if(RoundInfo.Winner==enWinner::Player1)
		Player1WinTimes++;
		else if(RoundInfo.Winner==enWinner::Computer)
		ComputerWinTimes++;
		else
		DrawTimes++;
		
		PrintRoundResults(RoundInfo);	
		
}
return FillGameRuslts(HowManyRounds,Player1WinTimes,ComputerWinTimes,DrawTimes);
	
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void ShowGameOverScreen()
{
cout<<Tabs(2)<<"---------------------------------------------------------------------------------\n\n";
cout<<Tabs(2)<<"                           ++++++ G a m e  O v e r++++++              \n";
cout<<Tabs(2)<<"---------------------------------------------------------------------------------\n\n";		
}
void ShowFinalGameRuslt(stGameResults GameRuslts)
{
     cout<<Tabs(2) <<"======================[ GAME RESULTS ]=====================\n\n";
     cout<<Tabs(2) <<"Game Rounds: "<<GameRuslts.GameRounds<<endl;
     cout<<Tabs(2) <<"Player1 Won Times: "<<GameRuslts.Player1WinTimes<<"\n";
     cout<<Tabs(2) <<"Computer Won Times: "<<GameRuslts.ComputerWinTimes<<"\n";
     cout<<Tabs(2) <<"Draw Timer: "<<GameRuslts.DrawTimes<<"\n";
     cout<<Tabs(2) <<"Final Winner: "<<GameRuslts.GameWinner<endl;
     cout<<Tabs(2) <<"===========================================================\n\n";
     SetWinnerScreenColor(GameRuslts.GameWinner);	
}
void StartGame()
{
	
	char PlayAgain='Y';
	do{
		ResetScreen();
		stGameResults GameRuslts=PlayGame(ReadNumberOfGameRounds("Enter The Number Of Rounds You Want To Play: "));
		ShowGameOverScreen();
		
		ShowFinalGameRuslt(GameRuslts);
		cout<<endl<<Tabs(3)<< "Do you want to play again ?(Y/N): ";
		cin>>PlayAgain;
		
	}while(PlayAgain=='Y'||PlayAgain=='y');
}

int main(){
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
	
}
