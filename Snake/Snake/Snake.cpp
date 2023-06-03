#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define WIDTH 20
#define HEIGHT 20
#define INIT_SNAKE_SIZE 6
#define SNAKE '0'
#define EMPTY ' '
#define WALL '*'

int snakeX[WIDTH * HEIGHT];
int snakeY[WIDTH * HEIGHT];
int snakeSize = INIT_SNAKE_SIZE;
int direction; // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT

void initializeSnake() {
    for (int i = 0; i < snakeSize; i++) {
        snakeX[i] = WIDTH / 2;
        snakeY[i] = HEIGHT / 2 + i;
    }
}

void draw() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int draw = 0;
            for (int z = 0; z < snakeSize; z++) {
                if (j == snakeX[z] && i == snakeY[z]) {
                    printf("%c", SNAKE);
                    draw = 1;
                }
            }
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("%c", WALL);
                draw = 1;
            }
            if (draw == 0) {
                printf("%c", EMPTY);
            }
        }
        printf("\n");
    }
}

void moveSnake() {
    for (int i = 0; i < snakeSize - 1; i++) {
        snakeX[i] = snakeX[i + 1];
        snakeY[i] = snakeY[i + 1];
    }
    switch (direction) {
    case 0: snakeY[snakeSize - 1]--; break;
    case 1: snakeX[snakeSize - 1]++; break;
    case 2: snakeY[snakeSize - 1]++; break;
    case 3: snakeX[snakeSize - 1]--; break;
    }
}

int isGameOver() { 
    //벽과 부딪히면 게임 종료
    if (snakeX[snakeSize - 1] == 0 || snakeX[snakeSize - 1] == WIDTH - 1 ||
        snakeY[snakeSize - 1] == 0 || snakeY[snakeSize - 1] == HEIGHT - 1)
        return 1;
    return 0;
}

void handleInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': direction = (direction + 3) % 4; break; // 왼쪽으로 회전 
            //방향이 / 0(up)일 때 a누르면 3(left) / 1(right)일 때 0(up) / 2(down)일 때 1(right) / 3(left)일 때 2(down)
        case 'd': direction = (direction + 1) % 4; break; // 오른쪽으로 회전
        case 27: exit(0); // ESC를 누르면 종료
        }
    }
}

int main() {
    initializeSnake();
    while (1) {
        draw();
        handleInput();
        moveSnake();
        if (isGameOver()) break;
        Sleep(100);
    }
    printf("Game Over!\n");
    return 0;
}