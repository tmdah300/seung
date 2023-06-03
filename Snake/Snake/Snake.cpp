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
    for (int i = 0; i < snakeSize; i++) { //뱀의 사이즈만큼 반복하여 뱀의 한 부분(0)마다의 좌표를 저장한다.
        snakeX[i] = WIDTH / 2;
        snakeY[i] = HEIGHT / 2 + i;
        //snakeX[i]는 뱀의 X좌표를 저장하는 배열 
        //snakeY[i]는 뱀의 Y좌표를 저장하는 배열
        //뱀의 초기 위치를 맵의 중앙으로 초기화
    }
}

void draw() {
    system("cls"); //화면을 지우고 생성하고를 반복
    for (int i = 0; i < HEIGHT; i++) { //열
        for (int j = 0; j < WIDTH; j++) { //행
            int draw = 0; //1일때 그림, 0일때는 그리지 않음
            for (int z = 0; z < snakeSize; z++) {
                if (j == snakeX[z] && i == snakeY[z]) { //뱀의 현재 위치 == 반복문 중의 i(열) j(행)의 값 일때 뱀(0)을 그림
                    printf("%c", SNAKE);
                    draw = 1;
                }
            }
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) { //가장자리 부분에는 벽(*)을 그림
                printf("%c", WALL);
                draw = 1;
            }
            if (draw == 0) { // 나머지 부분엔 " " (공백)을 그림
                printf("%c", EMPTY);
            }
        }
        printf("\n"); //행을 다 그렸으면 줄바꿈
    }
}

void moveSnake() {
    for (int i = 0; i < snakeSize - 1; i++) { //뱀의 각 부분의 위치를 이동시킴 
        //첫번째 부분(0)은 공백부분으로, 두번째 부분은 첫번째 있던 부분으로...
        snakeX[i] = snakeX[i + 1];
        snakeY[i] = snakeY[i + 1];
    }
    switch (direction) {
    case 0: snakeY[snakeSize - 1]--; break;
    case 1: snakeX[snakeSize - 1]++; break;
    case 2: snakeY[snakeSize - 1]++; break;
    case 3: snakeX[snakeSize - 1]--; break;

        // direction 값에 따라 뱀의 이동방향 결정됨
        //0은 위, 1은 오른쪽, 2는 아래, 3은 왼쪽
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
        case 'a': direction = (direction + 3) % 4; break; // 왼쪽으로 90도 회전 
            //방향이 / 0(up)일 때 a누르면 3(left) / 1(right)일 때 0(up) / 2(down)일 때 1(right) / 3(left)일 때 2(down)
        case 'd': direction = (direction + 1) % 4; break; // 오른쪽으로 90도 회전
        case 27: exit(0); // ESC를 누르면 종료
        }
    }
}

int main() {
    initializeSnake(); // 뱀의 위치를 초기화 함
    while (1) {
        draw(); //그리고
        handleInput(); //방향 입력받고
        moveSnake(); // 이동하고
        if (isGameOver()) break;
        Sleep(100); //이 반복문을 sleep안에 있는 시간 마다 반복
    }
    printf("Game Over!\n");
    return 0;
}