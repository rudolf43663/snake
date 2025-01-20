#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

const int SIZE_SCREEN_X = 43;
const int SIZE_SCREEN_Y = 43;

vector <vector <int>> snakeElements = {{SIZE_SCREEN_X / 2, SIZE_SCREEN_Y / 2}};

char snakeDirection = 'w';

int score = 0;
int foodX = -1;
int foodY = -1;

//Snake ===========================================================================================================
void snakeUpdate(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if (snakeDirection == 'w') snakeElements.insert(snakeElements.begin(), {snakeHeadX, snakeHeadY + 1});
	if (snakeDirection == 's') snakeElements.insert(snakeElements.begin(), {snakeHeadX, snakeHeadY - 1});
	if (snakeDirection == 'a') snakeElements.insert(snakeElements.begin(), {snakeHeadX - 1, snakeHeadY});
	if (snakeDirection == 'd') snakeElements.insert(snakeElements.begin(), {snakeHeadX + 1, snakeHeadY});
	snakeElements.pop_back();
}

void snakeController(){
	char key;
	while (_kbhit()) {
		key = _getch();
		if (key == 'w') snakeDirection = 'w';
		if (key == 's') snakeDirection = 's';
		if (key == 'a') snakeDirection = 'a';
		if (key == 'd') snakeDirection = 'd';
	}
}

//EventsCheckers ==================================================================================================
bool checkBorders(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if ((snakeHeadX == 0 ) || (snakeHeadX == (SIZE_SCREEN_X - 1))){
		return false;
	}
	if ((snakeHeadY == 0 ) || (snakeHeadY == (SIZE_SCREEN_Y - 1))){
		return false;
	}
	return true;
}

bool isEating(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if ((snakeHeadX == foodX) && (snakeHeadY == foodY)){
		return true;
	}
	snakeElements.insert(snakeElements.begin(), {foodX, foodY});
	return false;
}

bool isSelfCollision(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	for (int index = 1; index < snakeElements.size(); ++index){
		if ((snakeHeadX == snakeElements[index][0])) && (snakeHeadY == snakeElements[index][1])){
			return false;
		}
	}
	return true;
}

//BasicFunctions ==================================================================================================
bool gameEngine(){
	for (int x = 0; x < SIZE_SCREEN_X; ++x){
		for (int y = 0; y < SIZE_SCREEN_Y; ++y){
			checkEvents();
			drawElementOfScreen();
			if (!isEating) snakeUpdate();
		}
	}
}

void showGameOverScreen(){
	cout << "GAME OVER!" << endl;
	cout << "YOUR SCORE: " << score;
}

bool checkEvents(int x, int y){
	if (!checkBorders()){
		return false;
	}
	if (isEating()){
		++score;
	}
	if (!isSelfCollision()){
		return false;
	}
}

bool drawElementOfScreen(int x, int y){
	for (int index = 0; index < snakeElements.size(); ++index){
		currentSnakeElementX = snakeElements[i[0];
		currentSnakeElementY = snakeElements[i][1];
		if ((x == currentSnakeElementX) && (y == currentSnakeElementY)){
			if (index == 0){
				cout << 'H';
			}
			else{
				cout << 'B';
			}
			continue;
		}
		if ((x == foodX) && (y == foodY)){
			cout << '*';
			continue;
		}
		if ((x == 0) && (x == SIZE_SCREEN_X) && (y == 0) && (y == SIZE_SCREEN_Y)){
			cout << '#';
			continue;
		}
		cout << ' ';
	}
}

//Main  ===========================================================================================================
int main(){
	while(true){
		if (!gameEngine()){
			break;
		}
	}
	showGameOverScreen();
	system("pause");
	return 0;
}
