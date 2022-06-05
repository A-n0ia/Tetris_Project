#include "Headers.h"


//Allows to know the value of a cell of the array passed in parameter
char read_case(char array[LINE][COLUMN],int line,int column){
    char res;
    res=array[line][column];
    return res;
}

/*After selecting the orientation and the column of a piece, add_in_case allows to place the piece in the right place of the array by calculating the collisions,
or by returning the end of the game if there is not enough room*/

int add_in_case(Piece piece_array[7][4], int nb,int orientation, int column,Scoring player, char color_table[LINE][COLUMN]){
    int blocked=0,O[4]={0},P[4]={0},top=LINE,count,res=0,C,L,augm=-1,end=CTE0;
    char cell;

    //Calculates the number of empty spaces in a part so as not to count them in collisions
    for(int p=0;p<piece_array[nb][orientation].width;p++){
            for(int q=piece_array[nb][orientation].height-1;q>=CTE0;q--){
                if(piece_array[nb][orientation].form[q][p]=='@'){
                    P[p]=piece_array[nb][orientation].height-1-q;
                    break;
                }
            }
    }
    /*Calculates the number of empty spaces it has between the top of the board and the previously placed pieces
    before comparing with the number of empty spaces needed to place the selected piece*/
    for(int i=0;i<piece_array[nb][orientation].width;i++){
        top=LINE;
        while((blocked==CTE0) && (top>0)){
            top--;
            cell=read_case(color_table, top, column+i);
            if(cell!=' '){
                blocked=CTE1;
                O[i]=top+CTE1;
            }

            O[i]-=P[i];
            if(O[i]<CTE0){
            O[i]=CTE0;
            }
            
            if((LINE-O[i])<piece_array[nb][orientation].height){
                end=CTE1;
                return end;
            }
        }
        blocked=CTE0;
    }
    
    if(end!=CTE1){
    
        for(int j=0;j<4;j++){
            count=O[j];
            if(count>res){
                res=count;
            }
        }

        /*Allows to place in color_table the number of the part selected at the right height.
        (The number will then be replaced by an @ of the color of the correct part during the display)*/
        
        for(int k=piece_array[nb][orientation].height-CTE1; k>=CTE0; k--){
            augm++;       
            for(int h=0;h<piece_array[nb][orientation].width;h++){
                L=res+augm;
                C=column+h;
                if(piece_array[nb][orientation].form[k][h]!=' '){
                    color_table[L][C]=nb;
                }
            }
        }
        return 0;
    }
    
}

//del_line allows to delete a line passed as a parameter and to move all the lines above it down one notch
void del_line(char color_table[LINE][COLUMN],int lines){
        for(int w=lines;w<LINE;w++){
            for(int c=0;c<COLUMN;c++){
                if(w==CTE9){
                    color_table[w][c]=' ';
                }
                else{
                    color_table[w][c]=color_table[w+1][c];
                } 
            }
        }
}

/*line_complete watches when a row of the table is completed using Readcase, beeps (with printf("\a")),
counts the number of rows deleted at the same time and returns this counter to the add_score function*/
int line_complete(char color_table[LINE][COLUMN],Scoring player){
    char verif_line;
    int bin=CTE0,count=CTE0;
    for(int i=0;i<LINE;i++){
        bin=CTE0;
        for(int j=0;j<COLUMN;j++){
            verif_line=read_case(color_table,i,j);
            if(verif_line!=' '){
                bin+=CTE1;
            }
        }
        if(bin==CTE10){
            printf("\a");
            del_line(color_table,i);
            count++;
            i--;
        }
    }
    return count;
    
}

//Adds a number of points to the player's score depending on the number of lines deleted at the same time
int add_score(int count_lines,Scoring player){
    player.score+=CTE10;
    if(count_lines==CTE1){
        player.score+= CTE40;
    }
    else if(count_lines==CTE2){
        player.score+=CTE100;
    }
    else if(count_lines==CTE3){
        printf("WoW, 3 lignes d'un coup, pas mal !\n");
        player.score+= CTE300;
    }
    else if(count_lines==CTE4){
        printf("Incroyable ! 4 lignes d'un coup, quel coup de génie ! Vous faites maintenant partie de l'ELITE de Tetris !\n");
        player.score+= CTE1200;
    }
    return player.score;
}


unsigned long getTimeMicrosec(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (1000000*tv.tv_sec)+tv.tv_usec;
}

//Checks that the selected column is valid, i.e. that the part does not protrude from the table on the right
int vertical_size(Piece piece_array[7][4],int piece, int orientation,int column){
    int width,diff;
    width=COLUMN-column;
    diff=piece_array[piece][orientation].width-width;
    if(piece_array[piece][orientation].width>width){
        printf("Impossible car la piece sort de %d case(s) de la grille...\n",diff);
        return 0;
    }
    else{
        return 1;
    }
}

//Returns the letter passed in parameter (for the column) in uppercase
int verifMaj(char car){
    if(car>96){
        car=car-32;
    }
    return car;
}

/*Allows the player to select the orientation and the column where he wishes to place his piece, calculates the player's response time using the getTimeMicrosec function, 
compares this time to the time available according to the difficulty chosen by the player and calls the function add_in_case with parameters chosen by the player
(even if it leads to a bad move), or calls add_in_case with parameters chosen randomly if the player took too long to answer
(which may result in a better move than the one thought by the player...)*/

Variables scan(char color_table[LINE][COLUMN],Piece piece_array[7][4],int nb,Scoring player,Variables variables){
    char answer_s[100];
    int answer,col,place=CTE0,tmp_total,born=CTE1,end,calc;
    unsigned long tmp1,tmp2;
    tmp1=getTimeMicrosec();
    while(born==CTE1){
        born=CTE0;
        do{
            printf("\nQuelle orientation choisissez-vous ?");
            scanf("%s",answer_s);
        }while(answer_s[0]!='1' && answer_s[0]!='2' && answer_s[0]!='3' && answer_s[0]!='4');
        answer=answer_s[0]-CTE49;
        if(piece_array[nb][answer].height==CTE0){
            printf("Cette orientation n'existe pas, veuillez en prendre une autre\n");
            born=CTE1;
        }
    }

    while(place==CTE0){
        do{
        printf("Dans quelle colonne voulez-vous mettre votre piece \n\t(En partant du premier caractere à gauche) ?\n");
        scanf("%s",answer_s);
        tmp2=getTimeMicrosec();
        answer_s[0];
        col=verifMaj(answer_s[0]);
        col=col-'A';
        }while(col>CTE9 || col<CTE0);
        place=vertical_size(piece_array,nb,answer,col);
    }

    variables.time=tmp2-tmp1;
    printf("Vous avez mis %d secondes pour placer votre pièce\n",variables.time/SEC1);
    
    //compares the time to the time available according to the difficulty chosen by the player and calls the function add_in_case
    if(variables.lvl==CTE0){
        
        /*Look at the following comment, at line 227 - 228.
        For this difficulty, the progressive acceleration of the descent of the pieces is always selected.*/
        variables.time_available=TIME_CLASSIC-(player.level*SEC2);
        if(variables.time_available<CHINESE_MODE){
            //prevent the available time from dropping below the base time for Chinese_Mode (fixed at 3 seconds by the devs)
            variables.time_available=CHINESE_MODE;
        }
        if(variables.time<variables.time_available){
        variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
        }
        else{
            do{
                answer=rand()%CTE4;
            }while(piece_array[nb][answer].height==CTE0);
            col=rand()%CTE7;
            printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
            variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
        }
    }
    
    else if(variables.lvl==CTE1){
        /*If the player has chosen the progressive acceleration of the descent of the pieces (variables.accel==1), 
        recalculate the maximum time available for a turn by subtracting from the base time approximately 1 second every 5 turns.*/
        if(variables.accel==CTE1){
            variables.time_available=TIME_EASY-(player.level*SEC2);
            if(variables.time_available<TIME_HARD){
                //prevent the available time from dropping below the base time for Hard mode (fixed at 7 seconds by the devs)
                variables.time_available=TIME_HARD;
            }
            if(variables.time<variables.time_available){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }
        else{
            variables.time_available=TIME_EASY;
            if(variables.time<TIME_EASY){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }        
    }

    else if(variables.lvl==CTE2){
        //See previous comment at line 227 - 228
        if(variables.accel==CTE1){
            variables.time_available=TIME_MEDIUM-(player.level*SEC2);
            if(variables.time_available<SEC5){
                //prevent the available time from dropping below the 5SEC constante (fixed at 5 seconds by the devs)
                variables.time_available=SEC5;
            }
            if(variables.time<variables.time_available){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }
        else{
            variables.time_available=TIME_MEDIUM;
            if(variables.time<TIME_MEDIUM){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }        
    }

    else if(variables.lvl==CTE3){
        //See previous comment at line 227 - 228
        if(variables.accel==CTE1){
            variables.time_available=TIME_HARD-(player.level*SEC2);
            if(variables.time_available<CHINESE_MODE){
                //prevent the available time from dropping below the base time for Chinese_Mode (fixed at 3 seconds by the devs)
                variables.time_available=CHINESE_MODE;
            }
            if(variables.time<variables.time_available){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                printf("Temps ecoulé !\n");
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }
        else{
            variables.time_available=TIME_HARD;
            if(variables.time<TIME_HARD){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %d\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }        
    }

    else if(variables.lvl==CTE4){
        //See previous comment at line 227 - 228
        if(variables.accel==CTE1){
            variables.time_available=CHINESE_MODE-(player.level*SEC2);
            if(variables.time_available<SEC1){
                //prevent the available time from dropping below the 1SEC constante (fixed at 1 seconds by the devs)
                variables.time_available=SEC1;
            }
            if(variables.time<variables.time_available){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                printf("Temps ecoulé ! La pièce a été placé aléatoirement... Soyez plus rapide !\n");
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %c\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }
        else{
            variables.time_available=CHINESE_MODE;
            if(variables.time<CHINESE_MODE){
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
            else{
                printf("Temps ecoulé ! La pièce a été placé aléatoirement... Soyez plus rapide !\n");
                do{
                    answer=rand()%CTE4;
                }while(piece_array[nb][answer].height==CTE0);
                col=rand()%CTE7;
                printf("La pièce d'orientation %d a été placé colonne %c\n",answer+CTE1,col+CTE17);
                variables.end=add_in_case(piece_array,nb,answer,col,player,color_table);
            }
        }        
    }
    
    return variables;
}


//Returns a random number between 0 and 6
int alea(){
    int nb;
    nb=rand()%CTE7;
    return nb;
}

//Sorts an array passed as a parameter
void tri_insertion(Scoring array[10]){
    int decalage,tmp_bis;
    Scoring tmp;
    for(int i=CTE0;i<CTE10;i++){
        tmp_bis=array[i].score;
        tmp=array[i];
        decalage=i-CTE1;
        while(decalage>=CTE0 && array[decalage].score<tmp_bis){
            array[decalage+CTE1]=array[decalage];
            decalage=decalage-CTE1;
        }
        array[decalage+CTE1]=tmp;
    }
}