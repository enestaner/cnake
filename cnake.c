#include "functions.h"

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
