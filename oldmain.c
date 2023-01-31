/**********************************************************************
CCDSTRU_MP.c
Last updated: June 15, 2022
Authors: BACOSA, GABRIEL LUIS B.
         DELA CRUZ, ANGELO RICHTER L.
         OMANG, ELYANA D.G.
         MARISTELA, JOSEPH MIGUEL A.

BS CS-ST S12
MRS. MA. CHRISTINE A. GENDRANO
CCDSTRU TERM 2 A.Y. 2021-2022

<INSERT PROGRAM DESCRIPTION / INTRODUCTION>
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 7
#define COLUMN 5
#define ALPHA 1
#define BETA 2
/**
  int ok, over, aTurn;

  piece Beta = {{1,1}, {1,3}, {1,5}, {2,2}, {4,4}};
  piece Alpha = {{6,2}, {6,4}, {7,1}, {7,3}, {7,5}};

  playerMove nMove;

  char play;
  user playerAlpha, playerBeta;

playername;
playerpiece[2][5];



**/
struct nextMove
{
    int prev[2];
    int next[2];
};


typedef struct nextMove playerMove;
typedef int coordinates[2];
typedef char username[20];

void MainMenu()
{
    printf("    WELCOME TO OUR BOARD GAME!\n\n");
    printf("----------------------------------\n");
    printf("|                                |\n");
    printf("|      [1] Press 1 to play       |\n");
    printf("|      [2] Press 2 to exit       |\n");
    printf("|                                |\n");
    printf("----------------------------------\n");
}

/* This function checks if a piece belongs to Player 1. Otherwise, it returns index and 0. */
int
checkAlpha(coordinates Alpha[2], int piece[])
{
    int i;/* i is for looping and determines the index where the specific piece
	         can be found inside array Alpha */

    for (i = 0; i < 5; i++)
    {
        if(piece[0] == Alpha[i][0] && Alpha[i][1] == piece[1])
        {
            return i + 1;
        }
    }
    return 0;
}

int
checkBeta(coordinates Beta[2], int piece[])
{
    int i;/* i is for looping and determines the index where the specific piece
	         can be found inside array Beta */

    for(i = 0; i < 5; i++)
    {
        if(piece[0] == Beta[i][0] && Beta[i][1] == piece[1])
        {
            return i + 1;
        }
    }
    return 0;
}

/* This function checks if the input coordinate is a free and valid space. It returns 1 if yes and if otherwise, returns 0 */
int
checkFree(coordinates Alpha[2], coordinates Beta[2], int piece[])
{
    if(!checkAlpha(Alpha,piece) && !checkBeta(Beta,piece))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void
displayBoard(coordinates piecesAlpha[2], coordinates piecesBeta[2])
{
    int i, j;/* i and j are used for loops and also represent the x and y coordinates of the grid */
    int x[2];/* array x represents a proxy piece or space */

    printf("   ");
    for(i = 1; i <= COLUMN; i++) {
        printf(" %d ",i);
    }

    printf("\n");

    for(i = 0; i <= ROW - 1; i++)
        for(j = 0; j <= COLUMN - 1; j++)
        {
            j++; i++;
            x[0] = i; x[1] = j;

            if(j==1)
                printf(" %d ",i);

            if(checkAlpha(piecesAlpha,x))
                printf("[A]");

            if(checkBeta(piecesBeta,x))
                printf("[B]");

            if(checkFree(piecesAlpha,piecesBeta,x))
                printf("[ ]");

            if(j==5)
                printf("\n");

            j--; i--;
        }
    printf("\n");
}

int piecesCount(coordinates pieces[2])
{
    int i;
    int count = 0;

    for(i = 0; i < 5; i++)
        if(pieces[i][0] > 0 && pieces[i][1] > 0)
            count++;


    return count;
}

int ifEndAlpha (coordinates piecesAlpha[2]) {
    int i;
    int count = 0;

    for(i = 0; i < 5; i++) {
        if (piecesAlpha[i][0] == 1) {
            count++;
            if (count == piecesCount(piecesAlpha)) {
                return 1;
            }
        }
    }

    return 0;
}


int ifEndBeta (coordinates piecesBeta[2]) {
    int i;
    int count = 0;

    for(i = 0; i < 5; i++) {
        if (piecesBeta[i][0] == 7) {
            count++;
            if (count == piecesCount(piecesBeta)) {
                return 1;
            }
        }
    }

    return 0;
}

void gameLoop ()
{
    int ok, over, aTurn, winner;

    //coordinates piecesAlpha[5] = {{2,6}, {4,6}, {1,7}, {3,7}, {5,7}};
    //coordinates piecesBeta[5] = {{1,1}, {3,1}, {5,1}, {2,2}, {4,2}};


    //BEFORE COORIDNATES:
    coordinates piecesAlpha[5] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {7,5}};
    coordinates piecesBeta[5] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};


    username playerAlpha, playerBeta;
    int indexAlpha, indexBeta;


    playerMove nMove;




    do
    {


        if (over != 1) {
            displayBoard(piecesAlpha, piecesBeta);
            printf("Please enter a username for player 1: ");
            scanf("%s", playerAlpha);

            while (strlen(playerAlpha) > 19)
            {
                printf("Username too long\n");
                printf("Please enter a username for player 1: ");
                scanf("%s", playerAlpha);
            }

            printf("Please enter a username for player 2: ");
            scanf("%s", playerBeta);

            while (strlen(playerBeta) > 19 || strcmp(playerAlpha,playerBeta) == 0)
            {
                if(strcmp(playerAlpha,playerBeta) == 0)
                {
                    printf("\nUsername is already in use");
                }
                else
                {
                    printf("\nUsername too long");
                }
                printf("\nPlease enter a username for player 2: ");
                scanf("%s", playerBeta);
            }

            printf("\nWelcome to the world of -blank-, %s and %s!\n", playerAlpha, playerBeta);
            printf("The rules of this game is simple.\n\t> Player %s gets A pieces.\n\t> Player %s gets B pieces.\n", playerAlpha, playerBeta);
            printf("\t>Two of you will play inside a 7x5 grid wherein you can only move FORWARD and DIAGONALLY.\n");
            printf("Good luck!");

            over = 0;
            ok = 0;
            aTurn = 1;

            while(over == 0)
            {
                printf("When inputting to make a move, please follow the correct format\n");
                printf("<X coordinate><space><Y coordinate>");
                printf("For example, to move a piece to (3,1), Enter: 3 1\n\n");
                displayBoard(piecesAlpha, piecesBeta);

                if(aTurn)
                {
                    do {
                        printf("Player %s (A) Turn, move piece: ", playerAlpha);
                        scanf("%d%d", &nMove.prev[0], &nMove.prev[1]);
                        if (!checkAlpha(piecesAlpha, nMove.prev)) {
                            printf("There's no such piece. \n \n");
                        }
                    } while (!checkAlpha(piecesAlpha, nMove.prev));

                    printf("to space: ");
                    scanf("%d%d", &nMove.next[0], &nMove.next[1]);

                    while(!ok)
                    {
                        if (checkAlpha(piecesAlpha,nMove.prev) &&
                            nMove.next[0] == nMove.prev[0]-1 &&
                            (nMove.next[1] == nMove.prev[1]+1 ||
                             nMove.prev[1] == nMove.next[1]+1 ||
                             nMove.prev[1] == nMove.next[1]) &&
                            !checkAlpha(piecesAlpha,nMove.next))
                        {
                            printf("%d \n",checkAlpha(piecesAlpha,nMove.prev) - 1);
                            indexAlpha = checkAlpha(piecesAlpha,nMove.prev)-1;
                            ok = !ok;
                        }
                        else
                        {
                            printf("Invalid move, please try again\n");
                            printf("Move piece: ");
                            scanf("%d%d", &nMove.prev[0], &nMove.prev[1]);
                            printf("to space: ");
                            scanf("%d%d", &nMove.next[0], &nMove.next[1]);
                        }
                    }
                }
                else
                {
                    do {
                        printf("Player %s (B) Turn, move piece: ", playerBeta);
                        scanf("%d%d", &nMove.prev[0], &nMove.prev[1]);
                        if (!checkBeta(piecesBeta, nMove.prev)) {
                            printf("There's no such piece. \n \n");
                        }
                    } while (!checkBeta(piecesBeta, nMove.prev));

                    printf("to space: ");
                    scanf("%d%d", &nMove.next[0], &nMove.next[1]);

                    while(!ok)
                    {
                        if (checkBeta(piecesBeta,nMove.prev) &&
                            nMove.next[0] == nMove.prev[0]+1 &&
                            (nMove.next[1] == nMove.prev[1]+1 ||
                             nMove.prev[1] == nMove.next[1]+1 ||
                             nMove.prev[1] == nMove.next[1]) &&
                            !checkBeta(piecesBeta,nMove.next))
                        {
                            printf("%d \n",checkBeta(piecesBeta,nMove.prev) - 1);
                            indexBeta = checkBeta(piecesBeta,nMove.prev)-1;
                            ok = !ok;
                        }
                        else
                        {
                            printf("Invalid move, please try again\n");
                            printf("Move piece: ");
                            scanf("%d%d", &nMove.prev[0], &nMove.prev[1]);
                            printf("to space: ");
                            scanf("%d%d", &nMove.next[0], &nMove.next[1]);
                        }
                    }
                }

                if(ok)
                {
                    if(aTurn)
                    {
                        /* checks if the chosen space to move is only an empty space */
                        if(checkFree(piecesAlpha, piecesBeta, nMove.next))
                        {
                            piecesAlpha[indexAlpha][1] = nMove.next[1];
                            piecesAlpha[indexAlpha][0] = nMove.next[0];
                            aTurn = !aTurn;
                            ok = !ok;
                        }    /* or if the chosen space to move is where an enemy piece is located */
                        else if((indexBeta = checkBeta(piecesBeta, nMove.next)-1) > -1)
                        {
                            piecesAlpha[indexAlpha][1] = nMove.next[1];
                            piecesAlpha[indexAlpha][0] = nMove.next[0];
                            piecesBeta[indexBeta][1] = -1;
                            piecesBeta[indexBeta][0] = -1;
                            aTurn = !aTurn;
                            ok = !ok;
                        }
                    }
                    else
                    {
                        /* checks if the chosen space to move is only an empty space */
                        if(checkFree(piecesAlpha, piecesBeta, nMove.next))
                        {
                            piecesBeta[indexBeta][1] = nMove.next[1];
                            piecesBeta[indexBeta][0] = nMove.next[0];
                            aTurn = !aTurn;
                            ok = !ok;
                        }    /* or if the chosen space to move is where an enemy piece is located */
                        else if((indexAlpha = checkAlpha(piecesAlpha, nMove.next)-1) > -1)
                        {
                            piecesBeta[indexBeta][1] = nMove.next[1];
                            piecesBeta[indexBeta][0] = nMove.next[0];
                            piecesAlpha[indexAlpha][1] = -1;
                            piecesAlpha[indexAlpha][0] = -1;
                            aTurn = !aTurn;
                            ok = !ok;
                        }
                    }
                }
                if(piecesCount(piecesAlpha) == 0 || ifEndBeta(piecesBeta) == 1)
                {
                    over = 1;
                    winner = BETA;
                }
                else if(piecesCount(piecesBeta) == 0 || ifEndAlpha(piecesAlpha) == 1)
                {
                    over = 1;
                    winner = ALPHA;
                }
            }
            if(winner == ALPHA)
                printf("Player %s wins!!\n", playerAlpha);
            else if(winner == BETA)
                printf("Player %s wins!!\n", playerBeta);
        }
    } while (over != 1);
}
int main()
{
    char cAskPlayAgain;
    int nPlayAgain;

    do
    {
        system("cls");
        MainMenu();
        scanf("%c", &cAskPlayAgain);
        getchar();

        //displayBoard(1);

        while (cAskPlayAgain != '1' && cAskPlayAgain != '2')
        {
            if (cAskPlayAgain != '\n')
                printf("Invalid input. Please try again:\n");
            scanf("%c", &cAskPlayAgain);
        }

        if(cAskPlayAgain == '2')
        {
            nPlayAgain = 0;
        }
        else
            gameLoop();

        if(cAskPlayAgain == '1')
        {
            printf("\nWould you like to play again?\n[1] Yes \t [2] No\n");
            scanf("%c", &cAskPlayAgain);

            while (cAskPlayAgain != '1' && cAskPlayAgain != '2')
            {
                if (cAskPlayAgain != '\n')
                    printf("Invalid input. Please try again:\n");
                scanf("%c", &cAskPlayAgain);
            }

            if (cAskPlayAgain == '1')
            {
                nPlayAgain = 1;
            }
            else if (cAskPlayAgain == '2')
            {
                nPlayAgain = 0;
            }
        }

    } while (nPlayAgain == 1);

    return 0;
}


