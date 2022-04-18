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
                    if(*(ptr + row * LENGTH + col) == SMALL_FOOD || *(ptr + row * LENGTH + col) == BIG_FOOD){
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
                    if(*(ptr + row * LENGTH + col) == SMALL_FOOD || *(ptr + row * LENGTH + col) == BIG_FOOD){
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
                    if(*(ptr + row * LENGTH + col) == SMALL_FOOD || *(ptr + row * LENGTH + col) == BIG_FOOD){
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
                    if(*(ptr + row * LENGTH + col) == SMALL_FOOD || *(ptr + row * LENGTH + col) == BIG_FOOD){
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

    int random, chance;

    while(1){
        random = rand() % (LENGTH * LENGTH);
        chance = rand() % 100 + 1;

        if(*(ptr + random) != SNAKE_TAIL && *(ptr + random) != SNAKE_HEAD && *(ptr + random) != OBSTACLE){
            if(type == 'f'){
                if(chance < 90){
                    *(ptr + random) = SMALL_FOOD;
                }
                else{
                    *(ptr + random) = BIG_FOOD;
                }
                break;
            }
            else if(type == 'o' && *(ptr + random) != SMALL_FOOD && *(ptr + random) != BIG_FOOD){
                *(ptr + random) = OBSTACLE;
                break;
            }
        }
    }
}

void gameOver(int *ptr, int score, char difficulty){
   
    printf(colorRed "\n\t    ----GAME OVER----\n\n" colorReset);
    printer(ptr, 'f', difficulty);
    printf(colorYellow "\n\t\tFINAL SCORE: %d\n\n" colorReset, score);
    
    if(difficulty == 'h'){
        sleep(1500);
        system("cls");
        recordTable(score);
        getch();
    }
    else{
        getch();
        getch();
    }
}

char entrance(){
    
    char diff;

    printf(colorYellow " -Welcome to CNAKE game\n" colorReset);
    sleep(600);
    printf(colorBlue " -To move use W,A,S,D\n" colorReset);
    sleep(600);
    printf(colorGreen " -To resume or quit press Q\n" colorGreen);
    sleep(600);
    printf(colorMagenta " -Evertime snake eats food, becomes faster\n" colorReset);
    sleep(600);
    printf(colorYellow " -Normal food +1, Big food +5 increases score\n" colorReset);
    sleep(600);
    printf(colorBlue " -There is special leaderboard for hard mode\n" colorReset);
    sleep(600);
    printf(colorGreen " -Snake dies when (1) touchs itself, (2) touchs the walls, (3) touchs the random obstacles which each %d seconds summoning\n" colorReset, OBSTACLE_TIME);
    sleep(600);
    printf(colorMagenta " -Easy mode have (1)\n" colorReset);
    sleep(600);
    printf(colorYellow " -Medium mode have (1), (2)\n" colorReset);
    sleep(600);
    printf(colorBlue " -Hard mode have (1), (2), (3)\n" colorReset);
    sleep(600);
    printf(colorGreen " -Select the difficulty E - M - H: " colorReset);
    scanf("%c", &diff);
    printf(colorMagenta " -NOTE: If you have trouble with food summons just restart the game\n" colorReset);
    sleep(1000);
    printf(colorYellow "\n\t\tHAVE FUN :)\n" colorReset);
    sleep(1000);

    switch(diff){
        case 'e':
        case 'E':
            diff = 'e';
            break;

        case 'M':
        case 'k':
            diff = 'k';
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

void recordTable(int score){

    int *record, old_record, temp, i, j, k, l;
    char *record_name, temp_name[20], name[20];
    FILE *file;

    record = (int*)malloc(sizeof(int) * 5);
    record_name = (char*)malloc(sizeof(char) * 100);
    file = fopen("cnake_record_table.txt", "r+");

    for(i = 0; i < 100; i++){
        *(record_name + i) = ' ';
    }

    if(file == NULL){
        fclose(file);
        file = fopen("cnake_record_table.txt", "w+");

        fprintf(file, "\t\tNAME\t\tSCORE\n");
        for(i = 1; i < 6; i++){
            fprintf(file, "%d\t%10s\t\t%5d\n", i, "NONE", 0);
        }
    }
    rewind(file);
    fgets(name, 100, file);
    for(i = 0; i < 5; i++){
        fscanf(file ,"%d\t%s\t\t%d\n", &temp, &temp_name, (record + i));
 
        for(j = 20 * i, k = 0; temp_name[k] != '\0'; j++, k++){
            *(record_name + j) = temp_name[k];
        }
        *(record_name + j) = '\0';
    }

    for(i = 0; i < 5; i++){
        if(score > *(record + i)){
            
            printf(colorBlue "\n\nCONGRATULATIONS YOU ARE PLACED %d. ON SCOREBOARD\n" colorReset, i+1);
            printf(colorGreen "PLEASE ENTER YOUR NAME: " colorReset);
            scanf("%s", &name);

            temp = score;

            for(l = i; l < 5; l++){
                old_record = *(record + l);
                *(record + l) = temp;
                temp = old_record;

                for(j = 20 * l, k = 0; *(record_name + j) != '\0'; j++, k++){
                    temp_name[k] = *(record_name + j);
                }
                temp_name[k] = '\0';

                for(j = 20 * l, k = 0; name[k] != '\0'; j++, k++){
                    *(record_name + j) = name[k];
                }
                *(record_name + j) = '\0';

                for(k = 0; temp_name[k] != '\0'; k++){
                    name[k] = temp_name[k];
                }
                name[k] = '\0';
            }
            i = 5;
        }
    }
    printf(colorYellow "\tLEADERBOARD (for hard mode)\n\n" colorReset);
    printf("\n\t\tNAME\t\tSCORE\n\n");
    rewind(file);
    fprintf(file, "\t\tNAME\t\tSCORE\n");

    for(i = 0; i < 5; i++){

        for(j = 20 * i, k = 0; *(record_name + j) != '\0'; j++, k++){
            temp_name[k] = *(record_name + j);
        }
        temp_name[k] = '\0';
        fprintf(file, "%d\t%10s\t\t%5d\n", i + 1, temp_name, *(record + i));
        printf("%d\t%10s\t\t%5d\n", i + 1, temp_name, *(record + i));
    }

    fclose(file);
    free(record);
    free(record_name);
}