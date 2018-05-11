#include<conio.h>
#include"console.h"
#include<ctime>
#include<string>
#include<cstdlib>
#include"StructAndConst.h"
#include<mmsystem.h>
#include<Windows.h>
#include<iostream>
#include<fstream>

using namespace std;
int score;
// Khởi tạo con rắn và đồ ăn
void initialize(Snake &snake, Food &food) {
	PlaySound(TEXT("Runnin.wav"), NULL, SND_ASYNC);
	snake.length = 1;
	snake.seg[0].x = 0;
	snake.seg[0].y = 0;
	snake.dir = RIGHT;

	food.coor.x = 20;
	food.coor.y = 20;
	// khởi tạo buffer
	for (int i = 0; i < boardH; i++)
	{
		for (int j = 0; j < boardW; j++)
		{
			buffer[i][j].character = ' ';
			buffer[i][j].color = 7;
		}
	}
}
// hàm tùy chỉnh độ khó của game ( tốc độ di chuyển )
// độ khó tương ứng với điểm của người chơi
void chooseLevel(int &level) {
	clrscr();
	switch (level)
	{
	case 1: {
		level = 1000;
		score = 10;
		break;
	}
	case 2: {
		level = 800;
		score = 20;
		break;
	}
	case 3: {
		level = 700;
		score = 30;
		break;
	}
	case 4: {
		level = 600;
		score = 40;
		break;
	}
	case 5: {
		level = 500;
		score = 50;
		break;
	}
	case 6: {
		level = 300;
		score = 60;
		break;
	}
	case 7: {
		level = 100;
		score = 70;
		break;
	}
	case 8: {
		level = 50;
		score = 80;
		break;
	}
	case 9: {
		level = 1;
		score = 90;
		break;
	}
	default:
		break;
	}
}
// vẽ màn hình chào mừng người chơi
void drawScreen1(){
	PlaySound(TEXT("gao.wav"), NULL, SND_ASYNC);
	char nameGame[10][50] = {
		" OOOO    O   O     OOO     O   O    OOOOO",
		"O        O   O    O   O    O  O     O", 
		"O        OO  O    O   O    O O      O",
		"OOOO     O O O    OOOOO    OO       OOOO", 
		"    O    O  OO    O   O    O O      O", 
		"    O    O   O    O   O    O  O     O", 
		"OOOO     O   O    O   O    O   O    OOOOO",	
		"                                         ",
		"                                         "
	};
	TextColor(5);
	for (int i = 0; i < 10; i++) {
		gotoXY(40, 10 + i);
		cout << nameGame[i];
		Sleep(200);
	}
	char welcomePlayers[3][30] = {
		""
		"    Welcome to snake game",
		"  Are you ready play game Y/N"
	};
	for (int i = 0; i < 3; i++) {
		gotoXY(45, 20 + i);
		cout << welcomePlayers[i];
		Sleep(200);
	}
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == 'y' || key == 'Y') {
				break;
			}
			else if (key == 'n' || key == 'N') {
				cout << "Sure, hope you enjoy listening music\n";
			}
		}
	}
	clrscr();
}
// vẽ màn hình để hướng dẫn người chơi
void drawScreen2() {
	char guide[5][66] = {
		"press W,A,S,D or arrow keys to move",
		"you will die if you bite into wall or yourself",
		"good luck!, hope you enjoy playing game",
		"press enter to play game"
	};
	for (int i = 0; i < 4; i++) {
		gotoXY(40, 10 + i);
		cout << guide[i];
		Sleep(200);
	}
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == 13) break;
		}
	}
	clrscr();
}
// hàm hiển thị game
void display(Snake snake, Food food) {	
	for (int i = 0; i < boardH; i++) {
		drawACell(i, boardW, 179, ColorCode_Grey); // vẽ tường bao
	}
	drawACell(food.coor.y, food.coor.x, 'O', ColorCode_Green);// vẽ đồ ăn
	drawACell(snake.seg[0].y, snake.seg[0].x, 'O', ColorCode_Red);// vẽ đầu con rắn
	for (int i = 1; i < snake.length; i++) {
		drawACell(snake.seg[i].y, snake.seg[i].x, 'o', ColorCode_Yellow);// vẽ thân con rắn
	}
	// từ buffer in ra màn hình
	gotoXY(0, 0);
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j <= boardW; j++) {
			TextColor(buffer[i][j].color);
			putchar(buffer[i][j].character);
			buffer[i][j].character = ' ';
		}
		if (i < boardH - 1) {
			cout << endl;
		}
	}
	TextColor(ColorCode_Blue);
	gotoXY(boardW + 5, boardH / 2 - 10);
	cout << "Score = " << snake.score;
	// tạo điểm cao cho game
	ifstream file("best.txt");
	int bestScore;
	file >> bestScore;
	file.close();
	if (bestScore < snake.score)
	{
		ofstream file("best.txt");
		file << snake.score;
		bestScore = snake.score;
		file.close();
	}
	gotoXY(boardW + 5, boardH / 2 - 9);
	cout << "Best Score = " << bestScore;
	// thông tin cá nhân tác giả
	gotoXY(boardW + 5, boardH / 2 +3 );
	TextColor(6);
	cout << "Creater: LE DUC MINH";
	gotoXY(boardW + 5, boardH / 2 +4);
	cout << "Class: K62IE3";
}
// điều khiển rắn
void control(Snake &snake) {
	for (int i = snake.length - 1; i > 0; i--) {
		snake.seg[i] = snake.seg[i - 1];
	}
	// thiết lập hướng di chuyển
	if (_kbhit()) {
		int key;
		key = _getch();
		if (key == 'A' || key == 'a') snake.dir = LEFT;
		else if (key == 'S' || key == 's') snake.dir = DOWN;
		else if (key == 'D' || key == 'd') snake.dir = RIGHT;
		else if (key == 'W' || key == 'w') snake.dir = UP;
		else if (GetAsyncKeyState(VK_LEFT)) snake.dir = LEFT;
		else if (GetAsyncKeyState(VK_RIGHT)) snake.dir = RIGHT;
		else if (GetAsyncKeyState(VK_DOWN)) snake.dir = DOWN;
		else if (GetAsyncKeyState(VK_UP)) snake.dir = UP;
	}
	if (snake.dir == LEFT) snake.seg[0].x--;
	else if (snake.dir == RIGHT) snake.seg[0].x++;
	else if (snake.dir == UP) snake.seg[0].y--;
	else if (snake.dir == DOWN) snake.seg[0].y++;
}
// sử lý thua game, thắng game, tăng điểm,...
Resuit Logic(Snake &snake, Food &food) {
	//rắn ăn được mồi và dài thêm 1 đốt
	if (snake.seg[0].x == food.coor.x && snake.seg[0].y == food.coor.y) {
		for (int i = snake.length; i > 0; i--) {
			snake.seg[i] = snake.seg[i - 1];
		}
		snake.length++;
		snake.score += score;
		// rắn dài ra và tiếp tục di chuyển
		if (snake.dir == LEFT) snake.seg[0].x--;
		else if (snake.dir == RIGHT) snake.seg[0].x++;
		else if (snake.dir == UP) snake.seg[0].y--;
		else if (snake.dir == DOWN) snake.seg[0].y++;
		// random đồ ăn ở 1 vị trí bất kì
		food.coor.x = rand() % boardW;
		food.coor.y = rand() % boardH;
	}
	// sử lí thua game nếu chạm tường
	if (snake.seg[0].x < 0 || snake.seg[0].x >= boardW || snake.seg[0].y < 0 || snake.seg[0].y >= boardH) {
		return LOST;
	}
	// sử lý thua game nếu cắn vào thân
	for (int i = 1; i < snake.length; i++) {
		if (snake.seg[0].x == snake.seg[i].x && snake.seg[0].y == snake.seg[i].y) {
			return LOST;
		}
	}
}
// vẽ màn hình sau khi chết
void drawLastScreen() {
	clrscr();
	TextColor(ColorCode_DarkRed);
	char lose[12][80] = {
		"00      00   0000    00    00     00000    00   000000  00000",
		" 00    00   00  00   00    00     00  00   00   00      00  00",
		"  00  00   00    00  00    00     00   00  00   00      00   00",
		"   0000    00    00  00    00     00   00  00   000000  00   00",
		"    00      00  00    00  00      00   00  00   00      00   00",
		"    00       0000      0000       000000   00   000000  000000",
		"                                                       ",
		"                                                       ",
		"                  TO EXIT PRESS ENTER"
	};
	for (int i = 0; i < 12; i++) {
		gotoXY(30, 10 + i);
		cout << lose[i];
		Sleep(200);
	}
	PlaySound(TEXT("rap.wav"), NULL, SND_ASYNC);

}

int main() {
	int level;
	srand((unsigned int)time(NULL));
	Snake snake;
	Food food;
	Resuit resuit;
	ShowCur(false); // ẩn con trỏ
	drawScreen1();  // vẽ màn hình lần 1
	drawScreen2();  // vẽ màn hình lần 2
	initialize(snake, food); // khởi tạo con rắn
	gotoXY(45, boardH/2); // chỉnh vị trí chọn độ khó
	TextColor(ColorCode_Green);
	cout << "Please choose level(1-9): ";
	cin >> level;
	chooseLevel(level);
	while (1) {
		display(snake, food); 
		control(snake);
		resuit = Logic(snake, food);
		if (resuit == LOST) {
			drawLastScreen();
			while (_getch() != 13);
			break;
		}
		Sleep(level);
	}	
	return 0;
}