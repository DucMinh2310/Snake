#include "StructAndConst.h"
#include <conio.h>
#include "console.h"

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
		snake.score += 10;
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
