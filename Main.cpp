#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int SIZE_SCREEN_X = 27;
const int SIZE_SCREEN_Y = 27;

vector <vector <int> > snakeElements = {{SIZE_SCREEN_X / 2, SIZE_SCREEN_Y / 2}};

char snakeDirection = 'w';

int score = 0;
int foodX = -1;
int foodY = -1;

void snakeUpdate();
void snakeController();
bool isBorderCollision();
bool isEating();
bool isSelfCollision();
bool gameEngine();
void showGameOverScreen();
bool checkEvents();
bool drawElementOfScreen(int x, int y);
void createFood();

//Snake ===========================================================================================================
void snakeUpdate(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if (snakeDirection == 'w') {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX, snakeHeadY - 1});
	}
	if (snakeDirection == 's') {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX, snakeHeadY + 1});
	}
	if (snakeDirection == 'a') {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX - 1, snakeHeadY});
	}
	if (snakeDirection == 'd') {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX + 1, snakeHeadY});
	}
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
bool isBorderCollision(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if ((snakeHeadX <= 0 ) || (snakeHeadX >= (SIZE_SCREEN_X - 1))){
		return true;
	}
	if ((snakeHeadY <= 0 ) || (snakeHeadY >= (SIZE_SCREEN_Y - 1))){
		return true;
	}
	return false;
}
bool eatingPrediction(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if ((snakeDirection == 'w') && (snakeHeadX == foodX) && (snakeHeadY - 1 == foodY)) {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX, snakeHeadY - 1});
		return true;
	}
	if ((snakeDirection == 's') && (snakeHeadX == foodX) && (snakeHeadY + 1 == foodY)) {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX, snakeHeadY + 1});
		return true;
	}
	if ((snakeDirection == 'a') && (snakeHeadY == foodY) && (snakeHeadX - 1 == foodX)) {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX - 1, snakeHeadY});
		return true;
	}
	if ((snakeDirection == 'd') && (snakeHeadY == foodY) && (snakeHeadX + 1 == foodX)) {
		snakeElements.insert(snakeElements.begin(), {snakeHeadX + 1, snakeHeadY});
		return true;
	}
	return false;
}
bool isEating(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	if ((snakeHeadX == foodX) && (snakeHeadY == foodY)){
		createFood();
		return true;
	}
	return false;
}

bool isSelfCollision(){
	int snakeHeadX = snakeElements[0][0];
	int snakeHeadY = snakeElements[0][1];
	for (int index = 1; index < snakeElements.size(); ++index){
		if ((snakeHeadX == snakeElements[index][0]) && (snakeHeadY == snakeElements[index][1])){
			return true;
		}
	}
	return false;
}

//BasicFunctions ==================================================================================================
bool gameEngine(){
	for (int y = 0; y < SIZE_SCREEN_Y; ++y){
		for (int x = 0; x < SIZE_SCREEN_X; ++x){
			drawElementOfScreen(x, y);
		}
	}
	Sleep(200);
	system("cls");
	snakeController();

	if (!eatingPrediction()) {
		snakeUpdate();
	}
	if (!checkEvents()){
		return false;
	}
	return true;
}

void showGameOverScreen(){
	cout << "GAME OVER!" << endl;
	cout << "YOUR SCORE: " << score << endl;
}

bool checkEvents(){
	if (isBorderCollision()){
		return false;
	}
	if (isEating()){
		++score;
	}
	if (isSelfCollision()){
		return false;
	}
	return true;
}

bool drawElementOfScreen(int x, int y){
	bool event = false;
	for (int index = 0; index < snakeElements.size(); ++index){
		int currentSnakeElementX = snakeElements[index][0];
		int currentSnakeElementY = snakeElements[index][1];
		if ((x == currentSnakeElementX) && (y == currentSnakeElementY)){
			if (index == 0){
				cout << '@';
				event = true;
			}
			else{
				cout << 'O';
				event = true;
			}
		}
	}
	if ((x == foodX) && (y == foodY)){
		cout << '*';
		event = true;
	}
	if ((x == 0) || (x == SIZE_SCREEN_X - 1) || (y == 0) || (y == SIZE_SCREEN_Y - 1)){
		cout << '#';
		event = true;
		if ((x == SIZE_SCREEN_X - 1) && (y != SIZE_SCREEN_Y - 1)){
			cout << endl;
		}
	}
	if (!event){
		cout << ' ';
	}

}
void createFood(){
	foodX = 2 + rand() % (SIZE_SCREEN_X - 3);
	foodY = 2 + rand() % (SIZE_SCREEN_Y - 3);
}
//Main  ===========================================================================================================
int main(){
	srand(time(0));
	createFood();
	while(true){
		if (!gameEngine()){
			break;
		}
	}
	showGameOverScreen();
	system("pause");
	return 0;
}
