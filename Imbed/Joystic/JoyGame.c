<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI 통신 및 조이스틱 설정
#define BASE 100
#define SPI_CHAN 0
#define JOY 18

// 게임 관련 상수
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PADDLE_HEIGHT 4
#define MAX_SCORE 5

// 구조체 정의
typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

// 함수 선언
void initGame(Ball* ball, Paddle* p1, Paddle* p2);
void updateGame(Ball* ball, Paddle* p1, Paddle* p2);
void drawGame(const Ball* ball, const Paddle* p1, const Paddle* p2);
int readJoystick();

int main() {
    Ball ball;
    Paddle p1, p2;
    int score1 = 0, score2 = 0;

    wiringPiSetupGpio();
    mcp3004Setup(BASE, SPI_CHAN);
    pinMode(JOY, INPUT);
    pullUpDnControl(JOY, PUD_UP);

    initGame(&ball, &p1, &p2);

    while (score1 < MAX_SCORE && score2 < MAX_SCORE) {
        updateGame(&ball, &p1, &p2);
        drawGame(&ball, &p1, &p2);

        // 조이스틱 입력 처리
        int joyValue = readJoystick();
        // 패들 이동 로직 구현
        // 예를 들어, 조이스틱이 위로 움직이면 패들을 위로, 아래로 움직이면 패들을 아래로
        if (joyValue > 512) { // 조이스틱이 위로 움직였다고 가정
            p1.y = (p1.y > 0) ? p1.y - 1 : 0; // 패들을 위로 이동
        }
        else if (joyValue < 512) { // 조이스틱이 아래로 움직였다고 가정
            p1.y = (p1.y < SCREEN_HEIGHT - PADDLE_HEIGHT) ? p1.y + 1 : SCREEN_HEIGHT - PADDLE_HEIGHT; // 패들을 아래로 이동
        }
        delay(100);
    }

    printf("Game Over\n");
    return 0;
}

void initGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // 공의 초기 위치와 움직임
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;
    ball->dx = -1; // 공의 초기 수평 이동 방향
    ball->dy = 1;  // 공의 초기 수직 이동 방향

    // 플레이어 1의 패들 초기 위치
    p1->x = 2;
    p1->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p1->height = PADDLE_HEIGHT;

    // 플레이어 2의 패들 초기 위치
    p2->x = SCREEN_WIDTH - 3;
    p2->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p2->height = PADDLE_HEIGHT;
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // 공의 위치 업데이트
    ball->x += ball->dx;
    ball->y += ball->dy;

    // 공이 화면의 상단 또는 하단에 도달하면 방향 전환
    if (ball->y <= 0 || ball->y >= SCREEN_HEIGHT) {
        ball->dy = -ball->dy;
    }

    // 패들과의 충돌 감지
    if ((ball->x == p1->x + 1 && ball->y >= p1->y && ball->y <= p1->y + p1->height) ||
        (ball->x == p2->x - 1 && ball->y >= p2->y && ball->y <= p2->y + p2->height)) {
        ball->dx = -ball->dx; // 방향 전환
    }

    // 점수 계산 및 공의 위치 재설정
    if (ball->x <= 0 || ball->x >= SCREEN_WIDTH) {
        // 여기서 점수 계산 로직 추가

        // 공의 위치 재설정
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
void drawGame(const Ball* ball, const Paddle* p1, const Paddle* p2) {
    system("clear"); // 화면을 지웁니다.
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x == ball->x && y == ball->y) {
                printf("O"); // 공 출력
            }
            else if (x == p1->x && y >= p1->y && y < p1->y + p1->height) {
                printf("|"); // 플레이어 1 패들 출력
            }
            else if (x == p2->x && y >= p2->y && y < p2->y + p2->height) {
                printf("|"); // 플레이어 2 패들 출력
            }
            else {
                printf(" "); // 빈 공간
            }
        }
        printf("\n");
    }
}
int readJoystick() {
    int joyVal = analogRead(BASE + 0); // 조이스틱 값 읽기
    if (joyVal > 800) { // 상한값 설정
        return 1; // 조이스틱이 위로 움직임
    }
    else if (joyVal < 200) { // 하한값 설정
        return -1; // 조이스틱이 아래로 움직임
    }
    return 0; // 중립
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // 기존 로직...

    // 점수 계산 및 공의 위치 재설정
    if (ball->x <= 0) {
        score2++; // 플레이어 2에게 점수 부여
        // 공의 위치 재설정
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
    else if (ball->x >= SCREEN_WIDTH) {
        score1++; // 플레이어 1에게 점수 부여
        // 공의 위치 재설정
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI 통신 및 조이스틱 설정
#define BASE 100
#define SPI_CHAN 0
#define JOY 18

// 게임 관련 상수
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PADDLE_HEIGHT 4
#define MAX_SCORE 5

// 구조체 정의
typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

// 함수 선언
void initGame(Ball* ball, Paddle* p1, Paddle* p2);
void updateGame(Ball* ball, Paddle* p1, Paddle* p2);
void drawGame(const Ball* ball, const Paddle* p1, const Paddle* p2);
int readJoystick();

int main() {
    Ball ball;
    Paddle p1, p2;
    int score1 = 0, score2 = 0;

    wiringPiSetupGpio();
    mcp3004Setup(BASE, SPI_CHAN);
    pinMode(JOY, INPUT);
    pullUpDnControl(JOY, PUD_UP);

    initGame(&ball, &p1, &p2);

    while (score1 < MAX_SCORE && score2 < MAX_SCORE) {
        updateGame(&ball, &p1, &p2);
        drawGame(&ball, &p1, &p2);

        // 조이스틱 입력 처리
        int joyValue = readJoystick();
        // 패들 이동 로직 구현
        // 예를 들어, 조이스틱이 위로 움직이면 패들을 위로, 아래로 움직이면 패들을 아래로
        if (joyValue > 512) { // 조이스틱이 위로 움직였다고 가정
            p1.y = (p1.y > 0) ? p1.y - 1 : 0; // 패들을 위로 이동
        }
        else if (joyValue < 512) { // 조이스틱이 아래로 움직였다고 가정
            p1.y = (p1.y < SCREEN_HEIGHT - PADDLE_HEIGHT) ? p1.y + 1 : SCREEN_HEIGHT - PADDLE_HEIGHT; // 패들을 아래로 이동
        }
        delay(100);
    }

    printf("Game Over\n");
    return 0;
}

void initGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // 공의 초기 위치와 움직임
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;
    ball->dx = -1; // 공의 초기 수평 이동 방향
    ball->dy = 1;  // 공의 초기 수직 이동 방향

    // 플레이어 1의 패들 초기 위치
    p1->x = 2;
    p1->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p1->height = PADDLE_HEIGHT;

    // 플레이어 2의 패들 초기 위치
    p2->x = SCREEN_WIDTH - 3;
    p2->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p2->height = PADDLE_HEIGHT;
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // 공의 위치 업데이트
    ball->x += ball->dx;
    ball->y += ball->dy;

    // 공이 화면의 상단 또는 하단에 도달하면 방향 전환
    if (ball->y <= 0 || ball->y >= SCREEN_HEIGHT) {
        ball->dy = -ball->dy;
    }

    // 패들과의 충돌 감지
    if ((ball->x == p1->x + 1 && ball->y >= p1->y && ball->y <= p1->y + p1->height) ||
        (ball->x == p2->x - 1 && ball->y >= p2->y && ball->y <= p2->y + p2->height)) {
        ball->dx = -ball->dx; // 방향 전환
    }

    // 점수 계산 및 공의 위치 재설정
    if (ball->x <= 0 || ball->x >= SCREEN_WIDTH) {
        // 여기서 점수 계산 로직 추가

        // 공의 위치 재설정
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
void drawGame(const Ball* ball, const Paddle* p1, const Paddle* p2) {
    system("clear"); // 화면을 지웁니다.
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x == ball->x && y == ball->y) {
                printf("O"); // 공 출력
            }
            else if (x == p1->x && y >= p1->y && y < p1->y + p1->height) {
                printf("|"); // 플레이어 1 패들 출력
            }
            else if (x == p2->x && y >= p2->y && y < p2->y + p2->height) {
                printf("|"); // 플레이어 2 패들 출력
            }
            else {
                printf(" "); // 빈 공간
            }
        }
        printf("\n");
    }
}
int readJoystick() {
    int joyVal = analogRead(BASE + 0); // 조이스틱 값 읽기
    if (joyVal > 800) { // 상한값 설정
        return 1; // 조이스틱이 위로 움직임
    }
    else if (joyVal < 200) { // 하한값 설정
        return -1; // 조이스틱이 아래로 움직임
    }
    return 0; // 중립
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // 기존 로직...

    // 점수 계산 및 공의 위치 재설정
    if (ball->x <= 0) {
        score2++; // 플레이어 2에게 점수 부여
        // 공의 위치 재설정
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
    else if (ball->x >= SCREEN_WIDTH) {
        score1++; // 플레이어 1에게 점수 부여
        // 공의 위치 재설정
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
