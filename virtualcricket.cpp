#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

class Player{
	public:
		string name;
		int id;
		int ballsPlayed;
		int ballsBowled;
		int runsGiven;
		int runsScored;
		int wicketsTaken;
		Player(){
			ballsPlayed=0;
			ballsBowled=0;
			runsGiven=0;
			runsScored=0;
			wicketsTaken=0;
		}
};
class Team{
	public:
		string teamName;
		int totalRunsScored;
		int wicketsLost;
		int totalBallsBowled;
		vector<Player>players;
		Team(){
			totalRunsScored=0;
			wicketsLost=0;
			totalBallsBowled=0;
		}
};
class Game{
	public:
		int playersPerTeam;
		int maxBalls;
		int totalPlayers;
		string players[11];
		bool isFirstInnings;
		Team teamA ,teamB;
		Team *bowlingTeam, *battingTeam;
		Player *batsman, *bowler;
		void greetUser(){
			cout<<"\t\t\t|***************************|\n";
			cout<<"\t\t\t|---------------------------|\n";
	    	cout<<"\t\t\t|                           |\n";
			cout<<"\t\t\t|     ->*  WELCOME  *<-     |\n";
			cout<<"\t\t\t|                           |\n";
			cout<<"\t\t\t|---------------------------|\n";
			cout<<"\t\t\t|***************************|\n";
			cout<<"\n\n\n";
			cout<<"\t\t\t|---------------------------------------------|\n";
			cout<<"\t\t\t|          ->->* Instructions *<-<-           |\n";
			cout<<"\t\t\t|---------------------------------------------|\n";
		    cout<<"\t\t\t|                                             |\n";
			cout<<"\t\t\t|1) Create 2 teams(team-A & team-B 4 players) |\n";
			cout<<"\t\t\t|   each from the given pool of 11 players.   |\n";
			cout<<"\t\t\t|2) Lead the toss & decide the choice of play.|\n";
			cout<<"\t\t\t|3) Each inning will be of four balls.        |\n";
			cout<<"\t\t\t|---------------------------------------------|\n";
			cout<<"\t\t\t|*********************************************|\n";
		}
		void showAllPlayers(){
			cout<<"\t\t\t|-----------------------------------|\n";
			cout<<"\t\t\t|          Pool Of Players          |\n";
			cout<<"\t\t\t|-----------------------------------|\n";
			cout<<"\n\n";
			for(int i=0;i<totalPlayers;i++){
				cout<<"\t\t\t\t[" <<i<< "]" <<players[i]<<endl;
			}
		}
		int takeIntegerInput(){
			int n;
			while(!(cin>>n)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout<<"Invalid input! Please try again with valid input: ";
			}
			return n;
		}
		void selectPlayers(){
			cout<<endl;
			cout<<"\t\t\t|------------------------------------------|\n";
			cout<<"\t\t\t|          Create Team-A & Team-B          |\n";
			cout<<"\t\t\t|------------------------------------------|\n";
			for(int i=0;i<playersPerTeam;i++){
				//Select for team-A.
				teamASelection:
				cout<<"\t\t\t\nSelect Player "<<i+1<<" Of Team-A: ";
				int playerIndexTeamA = takeIntegerInput();
				if(playerIndexTeamA<0 || playerIndexTeamA>10){
					cout<<"\n Please select from the given players\n";
					goto teamASelection;
				}else if(!validateSelectedPlayer(playerIndexTeamA)){
					cout<<"\nPlayer has been already selected! Please select another player\n";
					   goto teamASelection;
				}
				else{
					Player teamAPlayer;
					teamAPlayer.id = playerIndexTeamA;
					teamAPlayer.name = players[playerIndexTeamA];
					teamA.players.push_back(teamAPlayer);	
				}
				
				//Select for team-B.
				teamBSelection:
				cout<<"\t\t\t\nSelect Player "<<i+1<<" Of Team-B: ";
				int playerIndexTeamB = takeIntegerInput();
					if(playerIndexTeamB<0 || playerIndexTeamB>10){
					cout<<"\n Please select from the given players\n";
					goto teamBSelection;
				}else if(!validateSelectedPlayer(playerIndexTeamB)){
					cout<<"\nPlayer has been already selected! Please select another player\n";
					goto teamBSelection;
				}
				else{
					Player teamBPlayer;
					teamBPlayer.id = playerIndexTeamB;
					teamBPlayer.name = players[playerIndexTeamB];
					teamB.players.push_back(teamBPlayer);
				}
				
			}
		}
		bool validateSelectedPlayer(int index){
			int n;
			vector<Player>players;
			players=teamA.players;
			n=players.size();
			for(int i=0;i<n;i++){
				if(players[i].id==index)
				return false;
			}
			players=teamB.players;
			n=players.size();
			for(int i=0;i<n;i++){
				if(players[i].id==index)
				return false;
			}
			return true;
		}
		void showTeamPlayers(){
			vector<Player>teamAPlayers = teamA.players;
			vector<Player>teamBPlayers = teamB.players;
			cout<<"\n\n";
			cout<<"|----------------------|\t\t|----------------------|\n";
			cout<<"|========Team-A========|\t\t|========Team-B========|\n";
			cout<<"|----------------------|\t\t|----------------------|\n";
			for(int i=0;i<playersPerTeam;i++){
				cout<<"|\t"<<teamAPlayers[i].name<<"\t |"<<"\t\t"<<"|\t"<<teamBPlayers[i].name<<"\t |\n";
			}
			cout<<"|----------------------|\t\t|----------------------|\n\n";
		}
		void toss(){
			cout<<endl;
			cout<<"\t\t\t|------------------------------------------|\n";
			cout<<"\t\t\t|                Let's Toss                |\n";
			cout<<"\t\t\t|------------------------------------------|\n";
			cout<<"\n \t\t\tTossing the coin.....\n\n";
			srand(time(NULL));
			int randomValue = rand()%2;
			switch(randomValue){
				case 0:
					cout<<"\t\t\tTeam-A WON THE TOSS\n\n";
					tossChoice(teamA);
					break;
				case 1:
					cout<<"\t\t\tTeam-B WON THE TOSS\n\n";
					tossChoice(teamB);
					break;	
			}
		}
		void tossChoice(Team tossWinnerTeam){
			cout<<"Enter ! to bat or 2 to bowl first\n";
			cout<<"1.Bat\n";
			cout<<"2.Bowl\n";
			int tossInput = takeIntegerInput();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch(tossInput){
				case 1:
					cout<<endl<<tossWinnerTeam.teamName<<" won the toss & elected to bat first.\n";
					if(tossWinnerTeam.teamName.compare("Team-A")==0){
						battingTeam = &teamA;
						bowlingTeam = &teamB;
					}
					else{
						battingTeam = &teamB;
						bowlingTeam = &teamA;
					}
					break;
				case 2:
					cout<<endl<<tossWinnerTeam.teamName<<" won the toss & elected to bowl first.\n";
					if(tossWinnerTeam.teamName.compare("Team-A")==0){
						bowlingTeam = &teamA;
						battingTeam = &teamB;
					}
					else{
						bowlingTeam = &teamB;
						battingTeam = &teamA;
					}
					break;
				default:
					cout<<"\nInvalid input please try again";
					tossChoice(tossWinnerTeam);
			}
		}
		void startFirstInnings(){
			cout<<"\n\t\t||| FIRST INNINGS STARTS |||\n";
			isFirstInnings = true;
			initializePlayers();
		}
		void initializePlayers(){
			batsman = &battingTeam->players[0];
			bowler  = &bowlingTeam->players[0];
			cout<<battingTeam->teamName<<" - "<<batsman->name<<" is batting\n";
			cout<<bowlingTeam->teamName<<" - "<<bowler->name<<" is bowling\n\n"; 
		}
		void playInning(){
			for(int i=0;i<maxBalls;i++){
				cout<<"Press enter to bowl....";
				getchar();
				cout<<"Bowling....\n";
				bat();
				if(!validateInningsScore()){
					break;
				}
			}
		}
		void bat(){
			srand(time(NULL));
			int runsScored = rand() % 7;
			// To update batting team & batsman score.
			batsman->runsScored=batsman->runsScored+runsScored;
			battingTeam->totalRunsScored=battingTeam->totalRunsScored+runsScored;
			batsman->ballsPlayed=batsman->ballsPlayed+1;
			// To update bowling team & bowler score.
			bowler->ballsBowled=bowler->ballsBowled+1;
			bowlingTeam->totalBallsBowled=bowlingTeam->totalBallsBowled+1;
			bowler->runsGiven=bowler->runsGiven+runsScored;
			if(runsScored!=0){
				cout<<"\n"<<bowler->name<<" to "<<batsman->name<<" "<<runsScored<<" runs!\n";
				showGameScorecard();
			}
			else{
				cout<<"\n"<<bowler->name<<" to "<<batsman->name<<" OUT!\n";
				battingTeam->wicketsLost=battingTeam->wicketsLost+1;
				bowler->wicketsTaken=bowler->wicketsTaken+1;
				showGameScorecard();
				
				int nextPlayerIndex = battingTeam->wicketsLost;
				batsman = &battingTeam->players[nextPlayerIndex];
			}
		}
		bool validateInningsScore(){
			if(isFirstInnings){
			if(battingTeam->wicketsLost==playersPerTeam||bowlingTeam->totalBallsBowled==maxBalls){
				cout<<"\t\t ||| FIRST INNINGS END |||\n\n";
				cout<<battingTeam->teamName<<" "<<battingTeam->totalRunsScored<<"-"<<battingTeam->wicketsLost<<" ("<<bowlingTeam->totalBallsBowled<<") \n";
				cout<<bowlingTeam->teamName<<" needs "<<battingTeam->totalRunsScored+1<<" runs to win the match\n\n";
				return false;
			}
			}else{
				if(battingTeam->wicketsLost==playersPerTeam||bowlingTeam->totalBallsBowled==maxBalls){
				
					 if(battingTeam->totalRunsScored>bowlingTeam->totalRunsScored){
						cout<<battingTeam->teamName<<" WON THE Match\n\n";
				}
					else if(bowlingTeam->totalRunsScored>battingTeam->totalRunsScored){
						cout<<bowlingTeam->teamName<<" WON THE MATCH\n\n";
				}
					else{
						cout<<"Match TIE !\n\n";
				}
			}
			
			}
			return true;
		}
		void showGameScorecard(){
			cout<<"---------------------------------------------------------------------\n\n";
			cout<<"\t"<<battingTeam->teamName<<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost<<" ("<<bowlingTeam->totalBallsBowled<<")  | "<<batsman->name<<" "<<batsman->runsScored<<" ("<<batsman->ballsPlayed<<") \t"<<bowler->name<<" "<<bowler->ballsBowled<<" - "<<bowler->runsGiven<<" - "<<bowler->wicketsTaken<<" \t\n";
			cout<<"---------------------------------------------------------------------\n\n";
		}
		void startSecondInnings(){
			cout<<"\n\n\t\t ||| SECOND INNINGS STARST |||\n\n";
			Team temp = *battingTeam;
			*battingTeam = *bowlingTeam;
			*bowlingTeam = temp;
			isFirstInnings = false;
			initializePlayers();
		}
		void matchSummary(){
			cout<<" ||| MATCH ENDS |||\n\n";
			cout<<battingTeam->teamName<<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost<<" ("<<bowlingTeam->totalBallsBowled<<") \n";
			cout<<"==============================================|\n";
			cout<<"|  Player\t\t Batting\t Bowling |\n";
			cout<<"|---------------------------------------------|\n";
			cout<<"|  "<<batsman->name<<"\t\t"<<batsman->runsScored<<" ("<<batsman->ballsPlayed<<") \t\t"<<batsman->ballsBowled<<"-"<<batsman->runsGiven<<"-"<<batsman->wicketsTaken<<"|\n";
		}
			Game(){
			isFirstInnings=false;
			teamA.teamName="Team-A";
			teamB.teamName="Team-B";
			playersPerTeam=4;
			maxBalls=6;
			totalPlayers=11;
			players[0]="Virat";
			players[1]="Rohit";
			players[2]="Dhawan";
			players[3]="Kl-Rahul";
			players[4]="Jadeja";
			players[5]="Dhoni";
			players[6]="Pant";
			players[7]="Hardik";
			players[8]="Bumrah";
			players[9]="Ishan";
			players[10]="Kartik";
			
		}
		
};
int main(){
	Game game;
	game.greetUser();
	cout<<"\nPress Enter To Continue:";
	getchar();
	game.showAllPlayers();
	cout<<"\nPress Enter To Continue:";
	getchar();
	game.selectPlayers();
	game.showTeamPlayers();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"\nPress Enter To Continue:";
	getchar();
	game.toss();
	game.startFirstInnings();
	game.playInning();
	game.startSecondInnings();
	game.playInning();
	game.matchSummary();
}

