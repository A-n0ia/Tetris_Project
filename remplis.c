#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#define CTE10 10

/*This small program allows you to reset a file's classification to zero 
(if it has started to bug for some obscure reason or the file's data has been "accidentally" deleted)
        Look below to find out how to do it.
*/

typedef struct{
    int level;
    int score;
    char pseudo[14];
    int difficulty;
}Scoring;


void tri_insertion(Scoring array[10]){
    int decalage,tmp_bis;
    Scoring tmp;
    for(int i=0;i<CTE10;i++){
        tmp_bis=array[i].score;
        tmp=array[i];
        decalage=i-1;
        while(decalage>=0 && array[decalage].score<tmp_bis){
            array[decalage+1]=array[decalage];
            decalage=decalage-1;
        }
        array[decalage+1]=tmp;
    }
}

int main(){
    Scoring player;
    Scoring scoreboard[10];
    player.level=0;
    player.score=0;
    player.difficulty=-1;
    srand(time(NULL));
    FILE* highscores =NULL;

    /*In fopen("highscores","rb+"), replace highscore with the name of the desired file ("highscore","highscore_Easy",...) 
    making sure that it is in the same file as this program.
    By executing this program, type the nickname which will become the default nickname (unknown for example)*/

    highscores=fopen("highscores","rb+");
    if(highscores==NULL){
        printf("Erreur ouverture fichier\nError %d : %s\n",errno,strerror(errno));
        exit(1);
    }
    scanf("%s",player.pseudo);

    for(int i=0;i<CTE10;i++){
        scoreboard[i] = player;
        scoreboard[i].score=0;
    }
    

    tri_insertion(scoreboard);
    
    fwrite(scoreboard,sizeof(player),10,highscores);
    rewind(highscores);
    fread(scoreboard,sizeof(player),10,highscores);
    for(int i=0;i<CTE10;i++){
        printf("%s\tlevel : %d\tscore : %d\n",scoreboard[i].pseudo,scoreboard[i].level,scoreboard[i].score);
    }
    fclose(highscores);
    return 0;
}