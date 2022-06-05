#include "Headers.h"

void clscr(){
    printf("\033[H\033[2J");
}

//------------------------------------------------------------------------------ View in Terminal -----------------------------------------------------------------------------

//Displays colored pieces in the game grid, along with the player's current level and score on the right, with the next piece coming just below
void disptab(char color_table[LINE][COLUMN],Piece piece_array[7][4],Scoring player,int next_nb){
    int k=0,h;
    h=piece_array[next_nb][0].height;
    char cell;
    //Read each box of color_table, and for each part number, display an @ of the color of the corresponding Tetrimino
    for(int i=LINE-1; i>=0; i--){
        printf("\t\t");
        for(int j=0; j<COLUMN; j++){
            cell=read_case(color_table,i,j);
            if(cell==CTE0){
                printf("|\e[36m@\e[0m");
            }
            else if(cell==CTE1){
                printf("|\e[33m@\e[0m");
            }
            else if(cell==CTE2){
                printf("|\e[32m@\e[0m");
            }
            else if(cell==CTE3){
                printf("|\e[31m@\e[0m");
            }
            else if(cell==CTE4){
                printf("|\e[37m@\e[0m");
            }
            else if(cell==CTE5){
                printf("|\e[34m@\e[0m");
            }
            else if(cell==CTE6){
                printf("|\e[35m@\e[0m");
            }
            else{
                printf("| ");
            }
        }
        //Displays the player's current level at the eighth line of the game grid
        if(i==CTE8){
            printf("|\t\tLevel : %d\n",player.level);
        }
        //Displays the player's current score on the eighth line of the game grid
        else if(i==CTE6){
            printf("|\t\tScore : %d\n",player.score);
        }
        //Displays the next piece in color!
        else if(i<CTE4){
            printf("|");
            if(i==CTE4){
                printf("\t\tPièce suivante :");
            }
            else if((i<=CTE2) && (k<h)){
                printf("\t\t\t\e[%dm%s\e[0m",piece_array[next_nb][0].color,piece_array[next_nb][0].form[k]);
                k++;
            }
            printf("\n");
        }
        else{
            printf("|\n");
        }
    }
}

//initialize all color_table boxes with spaces
void init(char color_table[LINE][COLUMN]){
    for(int i=0;i<LINE;i++){
        for(int j=0;j<COLUMN;j++){
            color_table[i][j]=' ';
        }
    }
}

//Displays the letters corresponding to the columns (A B C ...) then calls the disptab function
void Tab2D(char color_table[LINE][COLUMN],Piece piece_array[7][4],Scoring player,int next_nb){
    int k,ch;
    printf("\t\t");
    for(k=0;k<COLUMN;k++){
        ch=CTE65+k;
        printf(" %c",ch);
    }
    printf("\n");
    disptab(color_table,piece_array,player,next_nb);
    printf("\n");
}

//Displays the different orientations of a piece passed as a parameter (and in colors!)
void piece_display(Piece piece_array[7][4],int nb){
    for(int j=0;j<CTE4;j++){
        for(int i=0;i<piece_array[nb][j].height;i++){
            if(i==CTE0){
                printf("%d :",j+1);
            }
            printf("\t\e[%dm%s\e[0m",piece_array[nb][j].color,piece_array[nb][j].form[i]);
            printf("\n");
        }
        printf("\n");
    }
}

/*Asks the player the level of difficulty he want, then asks him if he want to activate the progressive acceleration of the descent of the pieces
(except for the classic mode for which this option is always activated)*/
Variables difficulty_level(Variables variables){
    char lvl_ask[25];
    do{
        printf("\n0\t\e[34mClassic\e[0m\n1\t\e[32mEasy\e[0m\n2\t\e[33mMedium\e[0m\n3\t\e[31mHard\e[0m\n4\t\e[30m\e[41mCHINESE MODE\e[0m\n\n");
        scanf("%s",lvl_ask);
    }while(lvl_ask[0]!='0' && lvl_ask[0]!='1' && lvl_ask[0]!='2' && lvl_ask[0]!='3' && lvl_ask[0]!='4');
    variables.lvl=lvl_ask[0]-CTE48;
    if(variables.lvl!=CTE0){
        do{
            printf("\nVoulez-vous activé l'accélération de la descente des pièces ? \n1 :\t\e[34mOui\e[0m \n0 :\t\e[31mNon\e[0m\n\n");
            scanf("%s",lvl_ask);
        }while(lvl_ask[0]!='0' && lvl_ask[0]!='1');
        if(lvl_ask[0]=='1'){
            variables.accel=CTE1;
        }
    }
    else{
        variables.accel=CTE1;
    }
    
    return variables;
}

//Asks the player for the ranking of the best he wants to see, then displays the one requested
void bestscores(Scoring scoreboard[10],Scoring player,Variables variables,FILE* highscores_Chinese_Mode,FILE* highscores_Hard,FILE* highscores_Medium,FILE* highscores_Easy,FILE* highscores_Classic,FILE* highscores){
    int score,lg_pseudo;
    char score_ask[25],enter;
    do{
        printf("\nQuel classement souhaitez-vous voir ?\n\n0\t\e[35mCelui des ELITES\e[0m\n1\t\e[34mCelui du mode Classic\e[0m\n2\t\e[32mCelui du mode Easy\e[0m\n3\t\e[33mCelui du mode Medium\e[0m\n4\t\e[31mCelui du mode Hard\e[0m\n5\t\e[30m\e[41mCelui du CHINESE MODE\e[0m\n\n");
        scanf("%s",score_ask);
    }while(score_ask[0]!='0' && score_ask[0]!='1' && score_ask[0]!='2' && score_ask[0]!='3' && score_ask[0]!='4' && score_ask[0]!='5');
    score=score_ask[0]-CTE48;

    //This large package of code displays the best players in the ELITE ranking by also displaying the difficulty in color in which they have played

    if(score==CTE0){
        rewind(highscores);
        fread(scoreboard,sizeof(player),10,highscores);
        rewind(highscores);
        for(int i=CTE0;i<CTE10;i++){
            if(scoreboard[i].difficulty==CTE0){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("%s\t\tlevel : %d\tscore : %d\tdifficulty :  \e[34mClassic\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("%s\tlevel : %d\tscore : %d\tdifficulty :  \e[34mClassic\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }

            else if(scoreboard[i].difficulty==CTE1){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("%s\t\tlevel : %d\tscore : %d\tdifficulty :  \e[32mEasy\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("%s\tlevel : %d\tscore : %d\tdifficulty :  \e[32mEasy\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
            
            else if(scoreboard[i].difficulty==CTE2){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("%s\t\tlevel : %d\tscore : %d\tdifficulty :  \e[33mMedium\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("%s\tlevel : %d\tscore : %d\tdifficulty :  \e[33mMedium\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
            
            else if(scoreboard[i].difficulty==CTE3){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("%s\t\tlevel : %d\tscore : %d\tdifficulty :  \e[31mHard\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("%s\tlevel : %d\tscore : %d\tdifficulty :  \e[31mHard\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
            
            else if(scoreboard[i].difficulty==CTE4){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("%s\t\tlevel : %d\tscore : %d\tdifficulty :  \e[41mChinese Mode\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("%s\tlevel : %d\tscore : %d\tdifficulty :  \e[41mChinese Mode\e[0m\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
                
            else{
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("%s\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("%s\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
        }
    }

    //Phew, we can finally move on to the ranking of the other difficulties (it will be much shorter this time, don't worry)

    else if(score==CTE1){
        rewind(highscores_Classic);
        fread(scoreboard,sizeof(player),10,highscores_Classic);
        rewind(highscores_Classic);
        for(int i=0;i<CTE10;i++){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("\e[34m%s\e[0m\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("\e[34m%s\e[0m\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
    }
    else if(score==CTE2){
        rewind(highscores_Easy);
        fread(scoreboard,sizeof(player),10,highscores_Easy);
        rewind(highscores_Easy);
        for(int i=0;i<CTE10;i++){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("\e[32m%s\e[0m\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("\e[32m%s\e[0m\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
    }
    else if(score==CTE3){
        rewind(highscores_Medium);
        fread(scoreboard,sizeof(player),10,highscores_Medium);
        rewind(highscores_Medium);
        for(int i=0;i<CTE10;i++){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("\e[33m%s\e[0m\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("\e[33m%s\e[0ms\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
    }
    else if(score==CTE4){
        rewind(highscores_Hard);
        fread(scoreboard,sizeof(player),10,highscores_Hard);
        rewind(highscores_Hard);
        for(int i=0;i<CTE10;i++){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<8){
                    printf("\e[31m%s\e[0m\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("\e[31m%s\e[0m\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
    }
    else if(score==CTE5){
        rewind(highscores_Chinese_Mode);
        fread(scoreboard,sizeof(player),10,highscores_Chinese_Mode);
        rewind(highscores_Chinese_Mode);
        for(int i=0;i<CTE10;i++){
                lg_pseudo= strlen(scoreboard[i].pseudo);
                if(lg_pseudo<CTE8){
                    printf("\e[30m\e[41m%s\e[0m\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
                else{
                    printf("\e[30m\e[41m%s\e[0m\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
                }
            }
    }
    printf("\n\n\t\e[3mAppuyer sur Entrer pour revenir au menu\e[0m\n");
    getchar();
    while( enter !='\n' ){
        enter=getchar();
    }
}


/*Displays a BEAUTIFUL menu leaving 4 options to the player: Play (in Classic difficulty by default), 
Change the difficulty level by calling the difficulty_level procedure, See the best rankings by calling the bestscores function, or Quit the program*/

Variables menu(Scoring scoreboard[10],Scoring player,Variables variables,FILE* highscores_Chinese_Mode,FILE* highscores_Hard,FILE* highscores_Medium,FILE* highscores_Easy,FILE* highscores_Classic,FILE* highscores){
    int tmp;
    char ask[50];
    variables.lvl=0;
    variables.accel=CTE1;
    variables.bestscores=0;
    clscr();
    printf("\t\e[31m\e[1m .----------------. \e[34m .----------------. \e[33m .----------------. \e[32m .----------------. \e[36m .----------------. \e[35m .----------------. \n\
\t\e[31m| .--------------. |\e[34m| .--------------. |\e[33m| .--------------. |\e[32m| .--------------. |\e[36m| .--------------. |\e[35m| .--------------. |\n\
\t\e[31m| |  _________   | |\e[34m| |  _________   | |\e[33m| |  _________   | |\e[32m| |  _______     | |\e[36m| |     _____    | |\e[35m| |    _______   | |\n\
\t\e[31m| | |  _   _  |  | |\e[34m| | |_   ___  |  | |\e[33m| | |  _   _  |  | |\e[32m| | |_   __ \\    | |\e[36m| |    |_   _|   | |\e[35m| |   /  ___  |  | |\n\
\t\e[31m| | |_/ | | \\_|  | |\e[34m| |   | |_  \\_|  | |\e[33m| | |_/ | | \\_|  | |\e[32m| |   | |__) |   | |\e[36m| |      | |     | |\e[35m| |  |  (__ \\_|  | |\n\
\t\e[31m| |     | |      | |\e[34m| |   |  _|  _   | |\e[33m| |     | |      | |\e[32m| |   |  __ /    | |\e[36m| |      | |     | |\e[35m| |   '.___`-.   | |\n\
\t\e[31m| |    _| |_     | |\e[34m| |  _| |___/ |  | |\e[33m| |    _| |_     | |\e[32m| |  _| |  \\ \\_  | |\e[36m| |     _| |_    | |\e[35m| |  |`\\____) |  | |\n\
\t\e[31m| |   |_____|    | |\e[34m| | |_________|  | |\e[33m| |   |_____|    | |\e[32m| | |____| |___| | |\e[36m| |    |_____|   | |\e[35m| |  |_______.'  | |\n\
\t\e[31m| |              | |\e[34m| |              | |\e[33m| |              | |\e[32m| |              | |\e[36m| |              | |\e[35m| |              | |\n\
\t\e[31m| '--------------' |\e[34m| '--------------' |\e[33m| '--------------' |\e[32m| '--------------' |\e[36m| '--------------' |\e[35m| '--------------' |\n\
\t\e[31m '----------------' \e[34m '----------------' \e[33m '----------------' \e[32m '----------------' \e[36m '----------------' \e[35m '----------------'\e[0m ");
    do{
        printf("\n\n\n1\t\e[36mClassic Game\e[0m \n2\t\e[35mChange difficultie level\e[0m \n3\t\e[32mHigh Scores\e[0m \n4\t\e[31mLeave\e[0m\n\n");
        scanf("%s",ask);
    }while(ask[0]!='1' && ask[0]!='2' && ask[0]!='3' && ask[0]!='4');
    tmp=ask[0]-CTE48;
    if(tmp==CTE2){
        variables=difficulty_level(variables);
    }
    else if(tmp==CTE3){
        variables.bestscores=CTE1;
        bestscores(scoreboard,player,variables,highscores_Chinese_Mode,highscores_Hard,highscores_Medium,highscores_Easy,highscores_Classic,highscores);
    }
    else if(tmp==CTE4){
        exit(0);
    }
    return variables;
}
