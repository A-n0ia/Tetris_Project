#include "Headers.h"

int main(){
//------------------------------------------------------------------------- The Beginning of a Legend -------------------------------------------------------------------------
    int nb,next_nb,end=CTE0,count,lg_pseudo,game=CTE1;
    char color_table[LINE][COLUMN],pseudo1[50],ask_game[50];
    Scoring player;
    Variables variables;
    Piece piece_array[7][4];
    Scoring scoreboard[10];
    
    //Opening of all top players ranking files
    
    FILE* highscores =NULL;
    highscores=fopen("../src/highscores","rb+");
    if(highscores==NULL){
        printf("Erreur ouverture fichier 1\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }
    fread(scoreboard,sizeof(player),10,highscores);
    rewind(highscores);

    FILE* highscores_Easy =NULL;
    highscores_Easy=fopen("../src/highscores_Easy","rb+");
    if(highscores_Easy==NULL){
        printf("Erreur ouverture fichier 2\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }

    FILE* highscores_Medium =NULL;
    highscores_Medium=fopen("../src/highscores_Medium","rb+");
    if(highscores_Medium==NULL){
        printf("Erreur ouverture fichier 3\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }

    FILE* highscores_Hard =NULL;
    highscores_Hard=fopen("../src/highscores_Hard","rb+");
    if(highscores_Hard==NULL){
        printf("Erreur ouverture fichier 4\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }

    FILE* highscores_Chinese_Mode =NULL;
    highscores_Chinese_Mode=fopen("../src/highscores_Chinese_Mode","rb+");
    if(highscores_Chinese_Mode==NULL){
        printf("Erreur ouverture fichier 5\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }

    FILE* highscores_classic =NULL;
    highscores_classic=fopen("../src/highscores_classic","rb+");
    if(highscores_classic==NULL){
        printf("Erreur ouverture fichier 6\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }
    srand(time(NULL));
    //Filling of piece_array by Tetriminos
    piece_generator(piece_array);

    //Start of the loop that allows the game to be restarted once lost
    while(game==CTE1){
        player.level=0;
        player.score=0;
        variables.accel=0;
        variables.end=0;
        //Calling up the menu function as long as a game or a difficulty level has not been selected
        do{
            variables=menu(scoreboard,player,variables,highscores_Chinese_Mode,highscores_Hard,highscores_Medium,highscores_Easy,highscores_classic,highscores);   
        }while(variables.bestscores==CTE1);

        player.difficulty=variables.lvl;
        //Reading the scoreboard corresponding to the difficulty chosen by the player
        if(variables.lvl==CTE0){
            fread(scoreboard,sizeof(player),10,highscores_classic);
        }
        else if(variables.lvl==CTE1){
            fread(scoreboard,sizeof(player),10,highscores_Easy);
        }
        else if(variables.lvl==CTE2){
            fread(scoreboard,sizeof(player),10,highscores_Medium);
        }
        else if(variables.lvl==CTE3){
            fread(scoreboard,sizeof(player),10,highscores_Hard);
        }
        else if(variables.lvl==CTE4){
            fread(scoreboard,sizeof(player),10,highscores_Chinese_Mode);
        }
        clscr();
        //Generation of the number of the current and the next piece
        nb=alea();
        next_nb=alea();
        //Initialization of color_table and display of the game grid
        init(color_table);
        Tab2D(color_table,piece_array,player,next_nb);
        
        //Start of the loop allowing to play a turn as long as the game is not finished
        while(variables.end==CTE0){
            piece_display(piece_array,nb);
            variables=scan(color_table,piece_array,nb,player,variables);
            if(variables.end!=CTE1){
                count=line_complete(color_table,player);
                player.score=add_score(count,player);
                player.level+=CTE1;
                clscr();
                nb=next_nb;
                next_nb=alea();
                Tab2D(color_table,piece_array,player,next_nb);
            }
            printf("\n\nVous avez mis %d secondes à jouer, le timer est a %d secondes\n\n",variables.time/SEC1,variables.time_available/SEC1);
        }
        printf("OMG !!!\nYou \e[1m\e[31mLOSE\e[0m you \e[1m\e[31mLOSER\e[0m !!!!\n");
        printf("Au fait, quelle est votre pseudo ?\t\e[3m\e[1m(Attention : Pseudo limité à 14 caractères)\e[0m\n");
        scanf(" %[^\n]",pseudo1);
        for(int i=0;i<CTE13;i++){
            player.pseudo[i]=pseudo1[i];
        }
        printf("\e[32m%s\e[0m ? Sérieusement ? Mon pauvre...\n\n",player.pseudo);
        //Checking the player's score against the worst score in the ranking
        if(player.score>scoreboard[9].score){
            scoreboard[9]=player;
        }
        else{
            printf("HAHAHA ! Vous êtes si nul que vous ne pouvez même pas entrer deans le tableau des MEILLEURS scores du même niveau de difficulté !\n");
        }
        tri_insertion(scoreboard);
        
        //Rewrite the new classification in the file corresponding to the selected level
        if(variables.lvl==CTE0){
            rewind(highscores_classic);
            fwrite(scoreboard,sizeof(player),10,highscores_classic);
        }
        else if(variables.lvl==CTE1){
            rewind(highscores_Easy);
            fwrite(scoreboard,sizeof(player),10,highscores_Easy);
        }
        else if(variables.lvl==CTE2){
            rewind(highscores_Medium);
            fwrite(scoreboard,sizeof(player),10,highscores_Medium);
        }
        else if(variables.lvl==CTE3){
            rewind(highscores_Hard);
            fwrite(scoreboard,sizeof(player),10,highscores_Hard);
        }
        else if(variables.lvl==CTE4){
            rewind(highscores_Chinese_Mode);
            fwrite(scoreboard,sizeof(player),10,highscores_Chinese_Mode);
        }

        //Displaying the new ranking
        for(int i=0;i<CTE10;i++){
            lg_pseudo= strlen(scoreboard[i].pseudo);
            if(lg_pseudo<CTE8){
                printf("%s\t\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
            }
            else{
                printf("%s\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
            }
        }
        
        //Reading of the table of ELITES regrouping the best scores of all the difficulties
        rewind(highscores);
        fread(scoreboard,sizeof(player),10,highscores);
        if(player.score>scoreboard[9].score){
            scoreboard[9]=player;
            tri_insertion(scoreboard);
            printf("\nFélicitation !\nVous venez d'entrer dans le tableau des ELITES, regroupant les meilleurs scores de toutes les difficultés confondus\n");
            rewind(highscores);
            fwrite(scoreboard,sizeof(player),10,highscores);

            /*If the player is good enough to enter this ranking, rewrite and display the new ranking,
            indicating for each player the difficulty in which this one has played*/
            for(int i=0;i<CTE10;i++){
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

        do{
            printf("\n\nVotre partie est terminé\nSouhaité vous recommencer une partie ?\n\t\e[3mTapez 1 pour OUI, J'ADORE CE JEU ! et 0 pour non...\e[0m\n");
            scanf("%s",ask_game);
        }while(ask_game[0]!='0' && ask_game[0]!='1');
        game=ask_game[0]-CTE48;
    }
    fclose(highscores);
    fclose(highscores_classic);
    fclose(highscores_Easy);
    fclose(highscores_Medium);
    fclose(highscores_Hard);
    fclose(highscores_Chinese_Mode);
    return 0;
//--------------------------------------------------------------------------- End of the Programme ---------------------------------------------------------------------------
}
