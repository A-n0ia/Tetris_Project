#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#define COLUMN 10
#define LINE 10
#define NB_PIECE 7
#define MAX_PIECE_HEIGHT 4
#define SCANF 75
#define TIME_EASY 16000000
#define TIME_MEDIUM 12000000
#define TIME_HARD 7000000
#define CHINESE_MODE 3000000
#define TIME_CLASSIC 15000000
#define SEC5 5000000
#define SEC2 200000
#define SEC1 1000000
#define CTE0 0
#define CTE1 1
#define CTE2 2
#define CTE3 3
#define CTE4 4
#define CTE5 5
#define CTE6 6
#define CTE7 7
#define CTE8 8
#define CTE9 9
#define CTE10 10
#define CTE13 13
#define CTE17 17
#define CTE48 48
#define CTE49 49
#define CTE40 40
#define CTE65 65
#define CTE100 100
#define CTE300 300
#define CTE1200 1200


//Do I really need to comment out this part of my code? I do not think so

typedef struct{
    int height;
    int width;
    int color;
    char *form[MAX_PIECE_HEIGHT];
}Piece;

typedef struct{
    int level;
    int score;
    char pseudo[14];
    int difficulty;
}Scoring;

typedef struct{
    int end;
    int time;
    int time_available;
    int accel;
    int lvl;
    int bestscores;
}Variables;

void disptab(char tab_color[LINE][COLUMN],Piece piece_array[7][4],Scoring player,int next_nb);
void init(char tab_color[LINE][COLUMN]);
void Tab2D(char tab_color[LINE][COLUMN],Piece piece_array[7][4],Scoring player,int next_nb);
char read_case(char tab[LINE][COLUMN],int line,int column);
void clscr();
unsigned long getTimeMicroec();
void piece_generator(Piece piece_array[7][4 ]);
int add_in_case(Piece piece_array[7][4], int nb,int orientation, int column,Scoring player, char tab_color[LINE][COLUMN]);
void del_line(char tab_color[LINE][COLUMN],int lines);
int line_complete(char tab_color[LINE][COLUMN],Scoring player);
int add_score(int compt_lines,Scoring player);
void piece_display(Piece piece_array[7][4],int nb);
int vertical_size(Piece piece_array[7][4],int piece, int orientation,int column);
int verifMaj(char car);
Variables scan(char tab_color[LINE][COLUMN],Piece piece_array[7][4],int nb,Scoring player,Variables variables);
int alea();
void tri_insertion(Scoring tab[10]);
Variables difficulty_level(Variables variables);
void bestscores(Scoring tabscore[10],Scoring player,Variables variables,FILE* highscores_Chinese_Mode,FILE* highscores_Hard,FILE* highscores_Medium,FILE* highscores_Easy,FILE* highscores_Classic,FILE* highscores);
Variables menu(Scoring tabscore[10],Scoring player,Variables variables,FILE* highscores_Chinese_Mode,FILE* highscores_Hard,FILE* highscores_Medium,FILE* highscores_Easy,FILE* highscores_Classic,FILE* highscores);