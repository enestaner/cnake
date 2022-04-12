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

int main(){

    int i, *row, *col, game, *table, score = 1, timer, speed, temp_row, temp_col, temp_snake_row, temp_snake_col, direction_s_row = 0, direction_s_col = 0, direction_d_row = 0, direction_d_col = 0, direction_w_row = 0, direction_w_col = 0, direction_a_row = 0, direction_a_col = 0;
    char active_direction = '!', negative_direction = '!', choice, isStart = 'n', difficulty;
    Sn *snake;

    system("cls");
    difficulty = entrance();

    snake = (Sn*) malloc(sizeof(Sn) * LENGTH * LENGTH);
    table = (int*) malloc(sizeof(int) * LENGTH * LENGTH);

    if(snake == NULL || table == NULL){
        printf("Memory allocation failed");
        return -1;
    }

    temp_row = LENGTH / 2 - 1;
    temp_col = LENGTH / 2 - 1;
    row = &temp_row;
    col = &temp_col;
    snake->col = temp_row;
    snake->row = temp_col;
    srand(time(NULL));
    creator(table);
    itemGenerator(table, 'f');

    for(timer = 0, speed = 150, game = 1; game != 0;  direction_s_row++, direction_d_col++, direction_w_row--, direction_a_col--, timer += speed){

        system("cls");

        if(difficulty == 'e'){
            switch(*(row)){
                case -1:
                    *(row) = LENGTH - 1;
                    break;
                
                case LENGTH:
                    *(row) = 0;
                    break;
            }

            switch(*(col)){
                case -1:
                    *(col) = LENGTH - 1;
                    break;

                case LENGTH:
                    *(col) = 0;
                    break;
            }
        }
        else if(difficulty == 'h'){
            if(timer >= OBSTACLE_TIME * 1000){
                itemGenerator(table, 'o');
                timer = 0;
                printf(colorMagenta "\n\tNEW OBSTACLE SUMMONED\n\n" colorReset);
            }
            else{
                printf(colorMagenta "\n\t%d SECONDS LATER NEW OBSTACLE WILL SUMMON\n\n" colorReset, OBSTACLE_TIME - timer / 1000);
            }
        }
        
        if(*(table + (*(row) * LENGTH) + *(col)) == FOOD){
            speed >= 60 ? speed -= 3 : 0;
            score++;
            itemGenerator(table, 'f');
        }
        else if(*(table + (*(row) * LENGTH) + *(col)) == OBSTACLE || *(table + (*(row) * LENGTH) + *(col)) == SNAKE_TAIL){
            gameOver(table, score, difficulty);
            break;
        }
        else if(*(row) == -1 || *(row) == LENGTH || *(col) == -1 || *(col) == LENGTH){
            gameOver(table, score, difficulty);
            break;
        }

        for(i = 0; i < score; i++){
            temp_snake_row = (snake + i + 1)->row;
            temp_snake_col = (snake + i + 1)->col;
            (snake + i + 1)->row = snake->row;
            (snake + i + 1)->col = snake->col;
            snake->row = temp_snake_row;
            snake->col = temp_snake_col;
        }
        snake->row = *(row);
        snake->col = *(col);

        *(table + ((snake)->row * LENGTH) + (snake)->col) = SNAKE_HEAD;
        for(i = 1; i < score;  i++){
            *(table + ((snake + i)->row * LENGTH) + (snake + i)->col) = SNAKE_TAIL;
        }
        isStart == 'y' ? *(table + (temp_snake_row * LENGTH) + temp_snake_col) = VOID : 0;

        printf(colorYellow "\t\tSCORE: %d\n" colorReset, score - 1);
        printer(table, 'n', difficulty);
        sleep(speed);

        if(kbhit()){
            choice = getch();
            isStart = 'y';

            if(choice == active_direction || choice == negative_direction){
                continue;
            }
            temp_row = *(row);
            temp_col = *(col);

            switch(choice){
                case 'd':
                case 'D':
                    row = &direction_d_row;
                    col = &direction_d_col;
                    *(row) = temp_row;
                    *(col) = temp_col;
                    active_direction = 'd';
                    negative_direction = 'a';
                    break;

                case 's':
                case 'S':
                    row = &direction_s_row;
                    col = &direction_s_col;
                    *(row) = temp_row;
                    *(col) = temp_col;
                    active_direction = 's';
                    negative_direction = 'w';
                    break;

                case 'w':
                case 'W':
                    row = &direction_w_row;
                    col = &direction_w_col;
                    *(row) = temp_row;
                    *(col) = temp_col;
                    active_direction = 'w';
                    negative_direction = 's';
                    break;

                case 'a':
                case 'A':
                    row = &direction_a_row;
                    col = &direction_a_col;
                    *(row) = temp_row;
                    *(col) = temp_col;
                    active_direction = 'a';
                    negative_direction = 'd';
                    break;

                case 'q':
                case 'Q':
                    printf("\nDo you really want to quit Y / N: ");
                    scanf("%c", &choice);
                    
                    if(choice == 'y' || choice == 'Y'){
                        game = 0;
                    }
                    break;
            }
        }
    }
    free(snake);
    free(table);
    return 0;
}

void creator(int *ptr){

    int row, col;

    for(row = 0; row < LENGTH; row++){
        for(col = 0; col < LENGTH; col++){
            *(ptr + row * LENGTH + col) = VOID;
        }
    }
}

void printer(int *ptr, char type, char difficulty){

    int row, col;
 
    if(difficulty == 'e'){

        printf(colorCyan "%c" colorReset, 218);                                      //top left corner
        for(row = 0; row < 2 * LENGTH; row++){
            printf(colorCyan "%c" colorReset, 196);                                  //top edge
        }
        printf(colorCyan "%c\n" colorReset, 191);                                    //top right corner

        for(row = 0; row < LENGTH; row++){
            printf(colorCyan "%c" colorReset, 179);                                  // left edge

            if(type == 'n'){
                for(col = 0; col < LENGTH; col++){
                    if(*(ptr + row * LENGTH + col) == FOOD){
                        printf(colorYellow "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else if(*(ptr + row * LENGTH + col) == OBSTACLE){
                        printf(colorMagenta "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else{
                        printf(colorGreen "%c " colorReset, *(ptr + row * LENGTH + col));     //table elements
                    }
                }
            }
            else if(type == 'f'){
                for(col = 0; col < LENGTH; col++){
                    if(*(ptr + row * LENGTH + col) == FOOD){
                        printf(colorYellow "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else if(*(ptr + row * LENGTH + col) == OBSTACLE){
                        printf(colorMagenta "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else{
                        printf(colorRed "%c " colorReset, *(ptr + row * LENGTH + col));     //table elements
                    }
                }
            }
            
            printf(colorCyan "%c" colorReset, 179);                                  //right edge
            printf("\n");
        }
        
        printf(colorCyan "%c" colorReset, 192);                                      //bottom left corner
        for(row = 0; row < 2 * LENGTH; row++){
            printf(colorCyan "%c" colorReset, 196);                                  //bottom edge
        }
        printf(colorCyan "%c\n" colorReset, 217);                                    //bottom right corner
    }
    else{

        printf(colorBlue "%c" colorReset, 218);                                      //top left corner
        for(row = 0; row < 2 * LENGTH; row++){
            printf(colorBlue "%c" colorReset, 196);                                  //top edge
        }
        printf(colorBlue "%c\n" colorReset, 191);                                    //top right corner

        for(row = 0; row < LENGTH; row++){
            printf(colorBlue "%c" colorReset, 179);                                  // left edge

            if(type == 'n'){
                for(col = 0; col < LENGTH; col++){
                    if(*(ptr + row * LENGTH + col) == FOOD){
                        printf(colorYellow "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else if(*(ptr + row * LENGTH + col) == OBSTACLE){
                        printf(colorMagenta "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else{
                        printf(colorGreen "%c " colorReset, *(ptr + row * LENGTH + col));     //table elements
                    }
                }
            }
            else if(type == 'f'){
                for(col = 0; col < LENGTH; col++){
                    if(*(ptr + row * LENGTH + col) == FOOD){
                        printf(colorYellow "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else if(*(ptr + row * LENGTH + col) == OBSTACLE){
                        printf(colorMagenta "%c " colorReset, *(ptr + row * LENGTH + col));
                    }
                    else{
                        printf(colorRed "%c " colorReset, *(ptr + row * LENGTH + col));     //table elements
                    }
                }
            }

            printf(colorBlue "%c" colorReset, 179);                                  //right edge
            printf("\n");
        }
        
        printf(colorBlue "%c" colorReset, 192);                                      //bottom left corner
        for(row = 0; row < 2 * LENGTH; row++){
            printf(colorBlue "%c" colorReset, 196);                                  //bottom edge
        }
        printf(colorBlue "%c\n" colorReset, 217);                                    //bottom right corner
    }
    
}

void sleep(int milli_seconds){
    
    clock_t initial_time = clock();

    while(clock() < milli_seconds + initial_time);

}

void itemGenerator(int *ptr, char type){

    int random;

    while(1){
        random = rand() % (LENGTH * LENGTH);

        if(*(ptr + random) != SNAKE_TAIL && *(ptr + random) != SNAKE_HEAD && *(ptr + random) != OBSTACLE){
            if(type == 'f'){
                *(ptr + random) = FOOD;
                break;
            }
            else if(type == 'o' && *(ptr + random) != FOOD){
                *(ptr + random) = OBSTACLE;
                break;
            }
        }
    }
}

void gameOver(int *ptr, int score, char difficulty){
   
    printf(colorRed "\n\t    ----GAME OVER----\n\n" colorReset);
    printer(ptr, 'f', difficulty);
    printf(colorYellow "\n\t\tFINAL SCORE: %d\n\n" colorReset, score - 1);
    getch();
    getch();
}

char entrance(){
    
    char diff;

    printf(colorYellow " -Welcome to CNAKE game\n" colorReset);
    sleep(700);
    printf(colorBlue " -To move use W,A,S,D\n" colorReset);
    sleep(700);
    printf(colorGreen " -To resume or quit press Q\n" colorGreen);
    sleep(700);
    printf(colorMagenta " -Evertime snake eats food, becomes faster\n" colorReset);
    sleep(700);
    printf(colorYellow " -Snake dies when (1) touchs itself, (2) touchs the walls, (3) touchs the random obstacles which each %d seconds summoning\n" colorReset, OBSTACLE_TIME);
    sleep(700);
    printf(colorBlue " -Easy mode have (1)\n" colorReset);
    sleep(700);
    printf(colorGreen " -Medium mode have (1), (2)\n" colorReset);
    sleep(700);
    printf(colorMagenta " -Hard mode have (1), (2), (3)\n" colorReset);
    sleep(700);
    printf(colorYellow " -Select the difficulty E - M - H: " colorReset);
    scanf("%c", &diff);
    printf(colorBlue " -NOTE: If you have trouble with food summons just restart the game\n" colorReset);
    sleep(1000);
    printf(colorGreen "\n\t\tHAVE FUN :)\n" colorReset);
    sleep(1000);

    switch(diff){
        case 'e':
        case 'E':
            diff = 'e';
            break;

        case 'M':
        case 'm':
            diff = 'm';
            break;

        case 'H':
        case 'h':
            diff = 'h';
            break;

        default:
            diff = 'e';
            break;
    }
    return diff;
}

