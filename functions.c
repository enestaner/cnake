#include "functions.h"

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

