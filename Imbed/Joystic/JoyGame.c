<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI ��� �� ���̽�ƽ ����
#define BASE 100
#define SPI_CHAN 0
#define JOY 18

// ���� ���� ���
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PADDLE_HEIGHT 4
#define MAX_SCORE 5

// ����ü ����
typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

// �Լ� ����
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

        // ���̽�ƽ �Է� ó��
        int joyValue = readJoystick();
        // �е� �̵� ���� ����
        // ���� ���, ���̽�ƽ�� ���� �����̸� �е��� ����, �Ʒ��� �����̸� �е��� �Ʒ���
        if (joyValue > 512) { // ���̽�ƽ�� ���� �������ٰ� ����
            p1.y = (p1.y > 0) ? p1.y - 1 : 0; // �е��� ���� �̵�
        }
        else if (joyValue < 512) { // ���̽�ƽ�� �Ʒ��� �������ٰ� ����
            p1.y = (p1.y < SCREEN_HEIGHT - PADDLE_HEIGHT) ? p1.y + 1 : SCREEN_HEIGHT - PADDLE_HEIGHT; // �е��� �Ʒ��� �̵�
        }
        delay(100);
    }

    printf("Game Over\n");
    return 0;
}

void initGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // ���� �ʱ� ��ġ�� ������
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;
    ball->dx = -1; // ���� �ʱ� ���� �̵� ����
    ball->dy = 1;  // ���� �ʱ� ���� �̵� ����

    // �÷��̾� 1�� �е� �ʱ� ��ġ
    p1->x = 2;
    p1->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p1->height = PADDLE_HEIGHT;

    // �÷��̾� 2�� �е� �ʱ� ��ġ
    p2->x = SCREEN_WIDTH - 3;
    p2->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p2->height = PADDLE_HEIGHT;
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // ���� ��ġ ������Ʈ
    ball->x += ball->dx;
    ball->y += ball->dy;

    // ���� ȭ���� ��� �Ǵ� �ϴܿ� �����ϸ� ���� ��ȯ
    if (ball->y <= 0 || ball->y >= SCREEN_HEIGHT) {
        ball->dy = -ball->dy;
    }

    // �е���� �浹 ����
    if ((ball->x == p1->x + 1 && ball->y >= p1->y && ball->y <= p1->y + p1->height) ||
        (ball->x == p2->x - 1 && ball->y >= p2->y && ball->y <= p2->y + p2->height)) {
        ball->dx = -ball->dx; // ���� ��ȯ
    }

    // ���� ��� �� ���� ��ġ �缳��
    if (ball->x <= 0 || ball->x >= SCREEN_WIDTH) {
        // ���⼭ ���� ��� ���� �߰�

        // ���� ��ġ �缳��
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
void drawGame(const Ball* ball, const Paddle* p1, const Paddle* p2) {
    system("clear"); // ȭ���� ����ϴ�.
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x == ball->x && y == ball->y) {
                printf("O"); // �� ���
            }
            else if (x == p1->x && y >= p1->y && y < p1->y + p1->height) {
                printf("|"); // �÷��̾� 1 �е� ���
            }
            else if (x == p2->x && y >= p2->y && y < p2->y + p2->height) {
                printf("|"); // �÷��̾� 2 �е� ���
            }
            else {
                printf(" "); // �� ����
            }
        }
        printf("\n");
    }
}
int readJoystick() {
    int joyVal = analogRead(BASE + 0); // ���̽�ƽ �� �б�
    if (joyVal > 800) { // ���Ѱ� ����
        return 1; // ���̽�ƽ�� ���� ������
    }
    else if (joyVal < 200) { // ���Ѱ� ����
        return -1; // ���̽�ƽ�� �Ʒ��� ������
    }
    return 0; // �߸�
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // ���� ����...

    // ���� ��� �� ���� ��ġ �缳��
    if (ball->x <= 0) {
        score2++; // �÷��̾� 2���� ���� �ο�
        // ���� ��ġ �缳��
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
    else if (ball->x >= SCREEN_WIDTH) {
        score1++; // �÷��̾� 1���� ���� �ο�
        // ���� ��ġ �缳��
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

// SPI ��� �� ���̽�ƽ ����
#define BASE 100
#define SPI_CHAN 0
#define JOY 18

// ���� ���� ���
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PADDLE_HEIGHT 4
#define MAX_SCORE 5

// ����ü ����
typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

// �Լ� ����
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

        // ���̽�ƽ �Է� ó��
        int joyValue = readJoystick();
        // �е� �̵� ���� ����
        // ���� ���, ���̽�ƽ�� ���� �����̸� �е��� ����, �Ʒ��� �����̸� �е��� �Ʒ���
        if (joyValue > 512) { // ���̽�ƽ�� ���� �������ٰ� ����
            p1.y = (p1.y > 0) ? p1.y - 1 : 0; // �е��� ���� �̵�
        }
        else if (joyValue < 512) { // ���̽�ƽ�� �Ʒ��� �������ٰ� ����
            p1.y = (p1.y < SCREEN_HEIGHT - PADDLE_HEIGHT) ? p1.y + 1 : SCREEN_HEIGHT - PADDLE_HEIGHT; // �е��� �Ʒ��� �̵�
        }
        delay(100);
    }

    printf("Game Over\n");
    return 0;
}

void initGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // ���� �ʱ� ��ġ�� ������
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;
    ball->dx = -1; // ���� �ʱ� ���� �̵� ����
    ball->dy = 1;  // ���� �ʱ� ���� �̵� ����

    // �÷��̾� 1�� �е� �ʱ� ��ġ
    p1->x = 2;
    p1->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p1->height = PADDLE_HEIGHT;

    // �÷��̾� 2�� �е� �ʱ� ��ġ
    p2->x = SCREEN_WIDTH - 3;
    p2->y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    p2->height = PADDLE_HEIGHT;
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // ���� ��ġ ������Ʈ
    ball->x += ball->dx;
    ball->y += ball->dy;

    // ���� ȭ���� ��� �Ǵ� �ϴܿ� �����ϸ� ���� ��ȯ
    if (ball->y <= 0 || ball->y >= SCREEN_HEIGHT) {
        ball->dy = -ball->dy;
    }

    // �е���� �浹 ����
    if ((ball->x == p1->x + 1 && ball->y >= p1->y && ball->y <= p1->y + p1->height) ||
        (ball->x == p2->x - 1 && ball->y >= p2->y && ball->y <= p2->y + p2->height)) {
        ball->dx = -ball->dx; // ���� ��ȯ
    }

    // ���� ��� �� ���� ��ġ �缳��
    if (ball->x <= 0 || ball->x >= SCREEN_WIDTH) {
        // ���⼭ ���� ��� ���� �߰�

        // ���� ��ġ �缳��
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
void drawGame(const Ball* ball, const Paddle* p1, const Paddle* p2) {
    system("clear"); // ȭ���� ����ϴ�.
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x == ball->x && y == ball->y) {
                printf("O"); // �� ���
            }
            else if (x == p1->x && y >= p1->y && y < p1->y + p1->height) {
                printf("|"); // �÷��̾� 1 �е� ���
            }
            else if (x == p2->x && y >= p2->y && y < p2->y + p2->height) {
                printf("|"); // �÷��̾� 2 �е� ���
            }
            else {
                printf(" "); // �� ����
            }
        }
        printf("\n");
    }
}
int readJoystick() {
    int joyVal = analogRead(BASE + 0); // ���̽�ƽ �� �б�
    if (joyVal > 800) { // ���Ѱ� ����
        return 1; // ���̽�ƽ�� ���� ������
    }
    else if (joyVal < 200) { // ���Ѱ� ����
        return -1; // ���̽�ƽ�� �Ʒ��� ������
    }
    return 0; // �߸�
}
void updateGame(Ball* ball, Paddle* p1, Paddle* p2) {
    // ���� ����...

    // ���� ��� �� ���� ��ġ �缳��
    if (ball->x <= 0) {
        score2++; // �÷��̾� 2���� ���� �ο�
        // ���� ��ġ �缳��
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
    else if (ball->x >= SCREEN_WIDTH) {
        score1++; // �÷��̾� 1���� ���� �ο�
        // ���� ��ġ �缳��
        ball->x = SCREEN_WIDTH / 2;
        ball->y = SCREEN_HEIGHT / 2;
    }
}
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
