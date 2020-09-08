/*  Your name: Christian Bernier
		Class block: A
		Date: 11/28/17
		Lab: 17
	Title: Lab17_CB.cpp
	Objective: To use a two-dimensional array with the vector class, requiring flexible processing.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
void askForAdvanced(bool &advancedGame);
void initializeGrid(vector<vector<int> > &grid, int &size);
void printBoard(vector<vector<int> > &grid, int &size);
void generateShips(vector<vector<int> > &grid, int shipSize);
void askForFire(int lastFire[2], int &torpedoes, vector<vector<int> > &grid, int &size);
void hitOrMiss(int lastFire[2], vector<vector<int> > &grid, int &hitCount);
void doesWinnerExist(const int &hitCount, const int &torpedoes, int &winner, bool &gameIsRunning, int totalHitsToWin);
void gameSummary(const int &winner,const int &hitCount,const int &torpedoes, const int &totalTorpedoes);

int main() {
	srand(time(0));
	vector<vector<int> > grid(10);
	int lastFire[2], torpedoes=1, hitCount=0, winner=0, totalTorpedoes=25, totalHitsToWin=1,size=1;
	bool gameIsRunning=true, advancedGame=false;
	askForAdvanced(advancedGame);
	if(advancedGame){
	size=10;
	torpedoes=25;
	totalTorpedoes=25;
	grid.resize(size);
	initializeGrid(grid, size);
	generateShips(grid, 5);
	generateShips(grid, 4);
	generateShips(grid, 3);
	generateShips(grid, 3);
	generateShips(grid, 2);
	printBoard(grid, size);
	totalHitsToWin=17;
	}else{
	size=8;
	torpedoes=15;
	totalTorpedoes=15;
	grid.resize(size);
	initializeGrid(grid, size);
	generateShips(grid, 4);
	printBoard(grid, size);
	totalHitsToWin=4;
	}
	do{
	askForFire(lastFire, torpedoes, grid, size);
	hitOrMiss(lastFire, grid, hitCount);
	doesWinnerExist(hitCount, torpedoes, winner, gameIsRunning, totalHitsToWin);
	printBoard(grid, size);
	}while(gameIsRunning);
	gameSummary(winner, hitCount, torpedoes, totalTorpedoes);
	return 0;
}

void askForAdvanced(bool &advancedGame){
	string advancedOp;
	bool understood=false;
	while(understood==false){
	cout<<"Would you like to play the advanced game? ";
	getline(cin,advancedOp);
	if((advancedOp=="y")||(advancedOp=="Y")||(advancedOp=="yes")||(advancedOp=="Yes")||(advancedOp=="true")||(advancedOp=="True")){
		advancedGame=true;
		understood=true;
	} else if((advancedOp=="n")||(advancedOp=="N")||(advancedOp=="no")||(advancedOp=="No")||(advancedOp=="false")||(advancedOp=="False")){
		advancedGame=false;
		understood=true;
	} else{
		understood=false;
	}
	if(understood==false){
		cout<<endl<<"Unable to understand your answer. Please try again."<<endl;
	}
	}
	cout<<endl;
}

void initializeGrid(vector<vector<int> > &grid, int &size){
	for(int i=0;i<grid.size();i++){
		grid[i].resize(size);
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			grid[i][j]=0;
		}
	}
}

void printBoard(vector<vector<int> > &grid, int &size){
	char posType;
	for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				switch(grid[i][j]){
				case 0: posType='.';
					break;
				case 1: posType='.';
					break;
				case 2: posType=' ';
					break;
				case 3: posType='X';
				}
				cout<<posType<<"  ";
			}
			cout<<endl;
		}
}
void generateShips(vector<vector<int> > &grid, int shipSize){
	int maxVal=grid.size()-shipSize;
	bool invalidPos=true, allPosVal=true;
	int direction=(rand()%2)+1;
	vector <bool> positionsValid(shipSize);
	int shipBaseX,shipBaseY;

	do{
	if(direction==1){		//vertical
		shipBaseX=(rand()%grid.size());
		shipBaseY=(rand()%maxVal);
		for(int i=0;i<shipSize;i++){
			if(grid[shipBaseX][shipBaseY+i]==0){
				positionsValid[i]=true;
			}else{
				positionsValid[i]=false;
			}
		}
		for(int i=0;i<positionsValid.size();i++){
			if((allPosVal==true)&&(positionsValid[i]==true)){
				allPosVal=true;

			}else{
				allPosVal=false;
			}
		}
		if(allPosVal){
		for(int i=0;i<shipSize;i++){
			grid[shipBaseX][shipBaseY+i]=1;
		}
		invalidPos=false;
		allPosVal=true;
		}
	} else{					//horizontal
		shipBaseX=(rand()%maxVal);
		shipBaseY=(rand()%grid.size());
		for(int i=0;i<shipSize;i++){
					if(grid[shipBaseX+i][shipBaseY]==0){
						positionsValid[i]=true;
					}else{
						positionsValid[i]=false;
					}
				}
				for(int i=0;i<positionsValid.size();i++){
					if(allPosVal&&positionsValid[i]){
						allPosVal=true;
					}else{
						allPosVal=false;
					}
				}
				if(allPosVal){
				for(int i=0;i<shipSize;i++){
					grid[shipBaseX+i][shipBaseY]=1;
				}
				invalidPos=false;
				}

				allPosVal=true;
		}
	}while(invalidPos);
}

void askForFire(int lastFire[2], int &torpedoes, vector<vector<int> > &grid, int &size){
	bool validPos=false, needMessageDisplayed=true;
	int x,y;
	do{
	cout<<endl<<torpedoes<<" torpedoes remain. Fire where? ";
	cin>>lastFire[0]>>lastFire[1];
	x=lastFire[1]-1;
	y=lastFire[0]-1;

	if((x<size)&&(y<size)){
		if((x>-1)&&(y>-1)){
			if((grid[x][y]==2)||(grid[x][y]==3)){
						cout<<endl<<"You already fired in that spot! Pick another position.";
						validPos=false;
						needMessageDisplayed=false;
				} else{
					validPos=true;
			}
		}
	}
	if((validPos==false)&&needMessageDisplayed){
		cout<<endl<<"Invalid position! Enter your position again.";
	}
	}while(validPos==false);
	torpedoes--;
}

void hitOrMiss(int lastFire[2], vector<vector<int> > &grid, int &hitCount){
	int y=lastFire[0]-1, x=lastFire[1]-1;

	if(grid[x][y]==1){
		cout<<"Hit!";
		grid[x][y]=3;
		hitCount++;
	} else{
		cout<<"Miss!";
		grid[x][y]=2;
	}
	cout<<endl<<endl;
}

void doesWinnerExist(const int &hitCount, const int &torpedoes, int &winner, bool &gameIsRunning, int totalHitsToWin){
	if(hitCount>=totalHitsToWin){
		winner=1;
		gameIsRunning=false;
	} else if(torpedoes==0){
		winner=2;
		gameIsRunning=false;
	} else{
		winner=0;
	}
}

void gameSummary(const int &winner,const int &hitCount,const int &torpedoes, const int &totalTorpedoes){
	if(winner==1){
		cout<<endl<<endl<<"***GAME SUMMARY***"<<endl;
		cout<<"Winner: Player";
		cout<<endl<<"Torpedoes Used: "<<(totalTorpedoes-torpedoes);
		cout<<endl<<endl<<"Thanks for playing Battleship!";
	} else{
		cout<<endl<<endl<<"***GAME SUMMARY***"<<endl;
		cout<<"Winner: Computer";
		cout<<endl<<"Hits: "<<hitCount;
		cout<<endl<<endl<<"Thanks for playing Battleship!";
	}

}
