#include "Headers.h"

/*This procedure is used to initialize all the Tetriminos that will be used in the game, 
listing their height, width, color and their different shapes depending on their orientation.*/

void piece_generator(Piece piece_array[7][4]){
    
    //Tetrimino I (2 orientation)
    piece_array[0][0].height= 1;
    piece_array[0][0].width=4;
    piece_array[0][0].color=36;
    piece_array[0][0].form[0]="@@@@";
    piece_array[0][1].height=4;
    piece_array[0][1].width=1;
    piece_array[0][1].color=36;
    piece_array[0][1].form[0]="@";
    piece_array[0][1].form[1]="@";
    piece_array[0][1].form[2]="@";
    piece_array[0][1].form[3]="@";
    piece_array[0][2].height=0;
    piece_array[0][2].width=0;
    piece_array[0][3].height=0;
    piece_array[0][3].width=0;
    
    //Tetrimino O (1 orientation)
    piece_array[1][0].height=2;
    piece_array[1][0].width=2;
    piece_array[1][0].color=33;
    piece_array[1][0].form[0]="@@";
    piece_array[1][0].form[1]="@@";
    piece_array[1][1].height=0;
    piece_array[1][1].width=0;
    piece_array[1][2].height=0;
    piece_array[1][2].width=0;
    piece_array[1][3].height=0;
    piece_array[1][3].width=0;
    
    //Tetrimino S (2 orientation)
    piece_array[2][0].height=2;
    piece_array[2][0].width=3;
    piece_array[2][0].color=32;
    piece_array[2][0].form[0]=" @@";
    piece_array[2][0].form[1]="@@ ";
    piece_array[2][1].height=3;
    piece_array[2][1].width=2;
    piece_array[2][1].color=32;
    piece_array[2][1].form[0]="@ ";
    piece_array[2][1].form[1]="@@";
    piece_array[2][1].form[2]=" @";
    piece_array[2][2].height=0;
    piece_array[2][2].width=0;
    piece_array[2][3].height=0;
    piece_array[2][3].width=0;
    
    //Tetrimino Z (2 orientation)
    piece_array[3][0].height=2;
    piece_array[3][0].width=3;
    piece_array[3][0].color=31;
    piece_array[3][0].form[0]="@@ ";
    piece_array[3][0].form[1]=" @@";
    piece_array[3][1].height=3;
    piece_array[3][1].width=2;
    piece_array[3][1].color=31;
    piece_array[3][1].form[0]=" @";
    piece_array[3][1].form[1]="@@";
    piece_array[3][1].form[2]="@ ";
    piece_array[3][2].height=0;
    piece_array[3][2].width=0;
    piece_array[3][3].height=0;
    piece_array[3][2].width=0;
    
    //Tetrimino L (4 orientation)
    piece_array[4][0].height=3;
    piece_array[4][0].width=2;
    piece_array[4][0].color=37;
    piece_array[4][0].form[0]="@ ";
    piece_array[4][0].form[1]="@ ";
    piece_array[4][0].form[2]="@@";
    piece_array[4][1].height=2;
    piece_array[4][1].width=3;
    piece_array[4][1].color=37;
    piece_array[4][1].form[0]="  @";
    piece_array[4][1].form[1]="@@@";
    piece_array[4][2].height=3;
    piece_array[4][2].width=2;
    piece_array[4][2].color=37;
    piece_array[4][2].form[0]="@@";
    piece_array[4][2].form[1]=" @";
    piece_array[4][2].form[2]=" @";
    piece_array[4][3].height=2;
    piece_array[4][3].width=3;
    piece_array[4][3].color=37;
    piece_array[4][3].form[0]="@@@";
    piece_array[4][3].form[1]="@  ";
    
    //Tetrimino J (4 orientation)
    piece_array[5][0].height=3;
    piece_array[5][0].width=2;
    piece_array[5][0].color=34;
    piece_array[5][0].form[0]=" @";
    piece_array[5][0].form[1]=" @";
    piece_array[5][0].form[2]="@@";
    piece_array[5][1].height=2;
    piece_array[5][1].width=3;
    piece_array[5][1].color=34;
    piece_array[5][1].form[0]="@  ";
    piece_array[5][1].form[1]="@@@";
    piece_array[5][2].height=3;
    piece_array[5][2].width=2;
    piece_array[5][2].color=34;
    piece_array[5][2].form[0]="@@";
    piece_array[5][2].form[1]="@ ";
    piece_array[5][2].form[2]="@ ";
    piece_array[5][3].height=2;
    piece_array[5][3].width=3;
    piece_array[5][3].color=34;
    piece_array[5][3].form[0]="@@@";
    piece_array[5][3].form[1]="  @";
    
    //Tetrimino T (4 orientation)
    piece_array[6][0].height=2;
    piece_array[6][0].width=3;
    piece_array[6][0].color=35;
    piece_array[6][0].form[0]="@@@";
    piece_array[6][0].form[1]=" @ ";
    piece_array[6][1].height=3;
    piece_array[6][1].width=2;
    piece_array[6][1].color=35;
    piece_array[6][1].form[0]=" @";
    piece_array[6][1].form[1]="@@";
    piece_array[6][1].form[2]=" @";
    piece_array[6][2].height=2;
    piece_array[6][2].width=3;
    piece_array[6][2].color=35;
    piece_array[6][2].form[0]=" @ ";
    piece_array[6][2].form[1]="@@@";
    piece_array[6][3].height=3;
    piece_array[6][3].width=2;
    piece_array[6][3].color=35;
    piece_array[6][3].form[0]="@ ";
    piece_array[6][3].form[1]="@@";
    piece_array[6][3].form[2]="@ ";
}
