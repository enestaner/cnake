#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define LENGTH 20
#define SNAKE_HEAD 254
#define SNAKE_TAIL 111
#define VOID 32
#define FOOD 42
#define OBSTACLE 221
#define OBSTACLE_TIME 5
#define colorBlue    "\e[1;34m"
#define colorGreen   "\e[1;32m"
#define colorReset   "\e[1;0m"
#define colorYellow  "\e[1;33m"
#define colorRed     "\e[1;31m"
#define colorMagenta "\e[1;35m"
#define colorCyan    "\e[1;36m"

void printer(int *ptr, char type, char difficulty);
void creator(int *ptr);
void sleep(int milli_seconds);
void itemGenerator(int *ptr, char type);
void gameOver(int *ptr, int score, char difficulty);
char entrance();

typedef struct Snake{
    int row;
    int col;
} Sn;