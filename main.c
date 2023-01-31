/*******************************************************************************
CCDSTRU_MP.c
Last updated: June 19, 2022
Authors: BACOSA, GABRIEL LUIS B.
         DELA CRUZ, ANGELO RICHTER L.
         OMANG, ELYANA D.G.
         MARISTELA, JOSEPH MIGUEL A.

BS CS-ST S12
MRS. MA. CHRISTINE A. GENDRANO
CCDSTRU TERM 2 A.Y. 2021-2022

Welcome to our game! This machine project was interpreted from the given
specifications which contains the application of the topics discussed in our
CCDSTRU course.

PROGRAM DESCRIPTION: Chesskers is a dual player board game wherein the two
players will compete against each other. This game is similar to a mixture of
chess and checkers, hence the title. The two players will have their respective
pieces placed in coordinates based from our own interpretation. In a 7 rows and
5 columns board, the pieces will only be allowed to move forward or diagonally
with certain limitations which will be applied in the program...

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 7
#define COLUMN 5
#define ALPHA 1
#define BETA 2

/*******************************************************************************
    This structure will be used to store the previous an next moves of a player
*******************************************************************************/
struct nextMove
{
    int curr[2];
    int next[2];
};

typedef struct nextMove playerMove;
typedef int coordinates[2];
typedef char username[20];

/*******************************************************************************
    Purpose: Prints the intro display for the user to pick whether to play or exit
           the game.
    Returns: Does not return anything (void).
*******************************************************************************/
void MainMenu()
{
    printf("    WELCOME TO OUR CHESSKERS!\n");
    printf("----------------------------------\n");
    printf("|                                |\n");
    printf("|      [1] Press 1 to play       |\n");
    printf("|      [2] Press 2 to exit       |\n");
    printf("|                                |\n");
    printf("----------------------------------\n");
}

/*******************************************************************************
    Purpose: This function checks if a piece belongs to Player 1. Otherwise, it
                 returns index and 0.
    Returns: 1 if the piece belongs to Alpha and 0 if it does not
    Pre-condition: The parameters contain valid values.

    @param : Alpha[2] is the array which stores the coordinates of the 5 pieces.
    @param : piece[] is the array which goes over the whole coordinate values,
                 used to compare to the Alpha[2] array.
*******************************************************************************/
int checkAlpha(coordinates Alpha[2], int piece[])
{
    int i; /* Index i allows for looping and determines the index where the specific
            piece can be found inside array Alpha */

    for (i = 0; i < 5; i++)
        if (piece[0] == Alpha[i][0] && Alpha[i][1] == piece[1])
            return i + 1;

    return 0;
}

/*******************************************************************************
    Purpose: This function checks if a piece belongs to Player 1. Otherwise, it
                 returns index and 0.
    Returns: 1 if the piece belongs to Beta and 0 if it does not
    Pre-condition: The parameters contain valid values.

    @param : Beta[2] is the array which stores the coordinates of the 5 pieces.
    @param : piece[] is the array which goes over the whole coordinate values,
                 used to compare to the Beta[2] array
*******************************************************************************/
int checkBeta(coordinates Beta[2], int piece[])
{
    int i; /*Index i is for looping and determines the index where the specific
            piece can be found inside array Beta */

    for (i = 0; i < 5; i++)
        if (piece[0] == Beta[i][0] && Beta[i][1] == piece[1])
            return i + 1;

    return 0;
}

/*******************************************************************************
    Purpose: This function checks if the input coordinate is a free and valid
                 space.
    Returns: 1 if the box/tile where the pieces can be placed is free and valid,
                 returns 0 if not
    Pre-condition: The parameters contain valid values.

    @param : Alpha[2] is the array containing the coordinates of Alpha pieces and
                 is used to call checkAlpha().
    @param : Beta[2] is the array containing the coordinates of Beta pieces and
                 is used to call checkBeta().
    @param : piece[] is used to be able to call both checkAlpha() and checkBeta().
*******************************************************************************/
int checkFree(coordinates Alpha[2], coordinates Beta[2], int piece[])
{
    if (!checkAlpha(Alpha, piece) && !checkBeta(Beta, piece))
        return 1;
    else
        return 0;
}

/*******************************************************************************
    Purpose: This function checks displays/prints the board with the Alpha & Beta
                 pieces and is updated each move.
    Returns: does not return anything (void)
    Pre-condition: The parameters contain valid values.

    @param : Alpha[2] is the array containing the coordinates of Alpha pieces and
                 is used to call checkAlpha().
    @param : Beta[2] is the array containing the coordinates of Beta pieces and
                     is used to call checkBeta().
*******************************************************************************/
void displayBoard(coordinates piecesAlpha[2], coordinates piecesBeta[2])
{
    int i, j; /* Indices i and j are used for loops and also represent the
                 x and y coordinates of the grid respectively. */
    int x[2]; // Array x acts an alternate piece or space.

    printf("   ");
    for (i = 1; i <= COLUMN; i++)
        printf(" %d ", i);

    printf("\n");

    for (i = 0; i <= ROW - 1; i++)
        for (j = 0; j <= COLUMN - 1; j++)
        {
            j++;
            i++;
            x[0] = i;
            x[1] = j;

            if (j == 1)
                printf(" %d ", i);

            if (checkAlpha(piecesAlpha, x))
                printf("[A]");

            if (checkBeta(piecesBeta, x))
                printf("[B]");

            if (checkFree(piecesAlpha, piecesBeta, x)) {
                if ((x[0] % 2) == (x[1] % 2))
                {
                    printf("[X]");
                }
                else
                {
                    printf("[ ]");
                }
            }


            if (j == 5)
                printf("\n");

            j--;
            i--;
        }
    printf("\n");
}

/*******************************************************************************
    Purpose: This function checks the number of pieces the player has.
    Returns: the number of pieces the player has
    Pre-condition: The parameters contain valid values.

    @param : pieces[2] is the player's pieces (Alpha or Beta) present in the
                 board.
*******************************************************************************/
int piecesCount(coordinates pieces[2])
{
    int i;         // index for looping
    int count = 0; // counter variable

    for (i = 0; i < 5; i++)
        if (pieces[i][0] > 0 && pieces[i][1] > 0)
            count++;

    return count; // number of a player's pieces present in the board
}

/*******************************************************************************
    Purpose: This function checks if all remaining pieces of the Alpha reach the
                 end of the board, which is row.
    Returns: 1 if all remaining Alpha pieces reached the end of the board, 0 if
           not
    Pre-condition: The parameters contain valid values.

    @param : Alpha[2] is the array containing the coordinates of Alpha pieces and
                 is used to call piecesCount().
*******************************************************************************/
int ifEndAlpha(coordinates piecesAlpha[2])
{
    int i;         // index for looping
    int count = 0; // counter variable

    for (i = 0; i < 5; i++)
    {
        if (piecesAlpha[i][0] == 1)
        {
            count++;
            if (count == piecesCount(piecesAlpha))
            {
                return 1; // all pieces reached the opposite end
            }
        }
    }

    return 0; // not all pieces reached the opposite end
}

/*******************************************************************************
    Purpose: This function checks if all remaining pieces of the Beta reach the
                 end of the board, which is row.
    Returns: 1 if all remaining Beta pieces reached the end of the board, 0 if
                 not.
    Pre-condition: The parameters contain valid values.

    @param : Beta[2] is the array containing the coordinates of Beta pieces and
                 is used to call piecesCount().
*******************************************************************************/
int ifEndBeta(coordinates piecesBeta[2])
{
    int i;         // index for looping
    int count = 0; // counter variable

    for (i = 0; i < 5; i++)
    {
        if (piecesBeta[i][0] == 7)
        {
            count++;
            if (count == piecesCount(piecesBeta))
            {
                return 1; // all pieces reached the opposite end
            }
        }
    }

    return 0; // not all pieces reached the opposite end
}

/*******************************************************************************
    Purpose: This function runs the whole game where the player inputs and moves
                 in the board.
    Returns: does not return anything (void)
*******************************************************************************/
void gameLoop()
{
    int ok;     // determines if player's move is valid
    int over;   // determines whether the game is over or not
    int aTurn;  // determines which player's turn to move
    int winner; // concludes the winner of the game

    // initial coordinates of Alpha and Beta pieces
    coordinates piecesAlpha[5] = {{6, 2}, {6, 4}, {7, 1}, {7, 3}, {7, 5}};
    coordinates piecesBeta[5] = {{1, 1}, {1, 3}, {1, 5}, {2, 2}, {2, 4}};

    username playerAlpha, playerBeta; // username to call the two players
    int indexAlpha, indexBeta;        /* indices of Alpha and Beta to where it is used
                                                                       when moving a piece */

    playerMove nMove; /* struct variable containing the current position of the
                                             piece and the next position of the piece */

    do
    {
        if (over != 1)
        {
            printf("Please enter a username for player 1: ");
            scanf("%s", playerAlpha);

            while (strlen(playerAlpha) > 19)
            {
                printf("Username is too long.\n");
                printf("Please enter a username for player 1: ");
                scanf("%s", playerAlpha);
            }

            printf("Please enter a username for player 2: ");
            scanf("%s", playerBeta);

            while (strlen(playerBeta) > 19 || strcmp(playerAlpha, playerBeta) == 0)
            {
                if (strcmp(playerAlpha, playerBeta) == 0)
                {
                    printf("\nUsername is already in use.");
                }
                else
                {
                    printf("\nUsername is too long.");
                }
                printf("\nPlease enter a username for player 2: ");
                scanf("%s", playerBeta);
            }

            printf("\nWelcome, %s and %s!\n", playerAlpha, playerBeta);
            printf("RULES OF THE GAME:\n\t> Player %s gets A pieces.\n\t", playerAlpha);
            printf("> Player %s gets B pieces.\n\t", playerBeta);
            printf("> In this 7x5 grid, you can only move FORWARD and DIAGONALLY.\n\t");
            printf("> To win, either eat all your opponent's pieces or reach the \n\t");
            printf("  opposite side of the board with all your remaining pieces.\n\t");
            printf("> You can not eat an opponent's piece on a white tile. \n\t");
            printf("Good luck and have fun!\n\n");

            // on-screen instructions
            printf("When inputting to make a move, please follow the correct format:\n\t");
            printf("<BOARD ROW><space><BOARD COLUMN>\n");
            printf("BOARD ROW are the numbers on the LEFT side of the board while the\n");
            printf("BOARD COLUMN are the numbers at the TOP of the board.\n\n");
            printf("EXAMPLE: To move piece B located on (1,3) to (2,3), type '1 3' for\n");
            printf("piece location then press enter. Type '2 3' for destination then\n");
            printf("press enter again to finish your move.\n\n");

            over = 0;
            ok = 0;
            aTurn = 1;

            while (over == 0)
            {
                printf("\n\n");
                displayBoard(piecesAlpha, piecesBeta);

                if (aTurn) {
                    do {
                        printf("Player %s (A) Turn, move piece: ", playerAlpha);
                        scanf("%d%d", &nMove.curr[0], &nMove.curr[1]);

                        if (!checkAlpha(piecesAlpha, nMove.curr))
                            printf("You have no such piece.\n\n");

                        if (nMove.curr[0] == 1)
                            printf("Sorry, you cannot move this piece.\n\n");

                    } while (!checkAlpha(piecesAlpha, nMove.curr) || nMove.curr[0] == 1);


                    printf("to space: ");
                    scanf("%d%d", &nMove.next[0], &nMove.next[1]);

                    while (!ok) {
                        if (checkAlpha(piecesAlpha, nMove.curr) && nMove.next[0] == nMove.curr[0] - 1 &&
                            (nMove.next[1] == nMove.curr[1] + 1 || nMove.curr[1] == nMove.next[1] + 1 ||
                             nMove.curr[1] == nMove.next[1]) && !checkAlpha(piecesAlpha, nMove.next) &&
                            !(checkBeta(piecesBeta, nMove.next) && ((nMove.next[0] % 2) != (nMove.next[1] % 2))) &&
                            !(nMove.next[0] > 7 || nMove.next[1] > 5 || (nMove.next[0] < 1 || nMove.next[1] < 1))) {
                            indexAlpha = checkAlpha(piecesAlpha, nMove.curr) - 1;
                            ok = !ok;
                        } else {
                            printf("Invalid move, please try again \n \n");
                            do {
                                printf("Player %s (A) Turn, move piece: ", playerAlpha);
                                scanf("%d%d", &nMove.curr[0], &nMove.curr[1]);

                                if (!checkAlpha(piecesAlpha, nMove.curr))
                                    printf("You have no such piece.\n\n");
                                else if (nMove.curr[0] == 1)
                                    printf("Sorry, you cannot move this piece.\n\n");

                            } while (!checkAlpha(piecesAlpha, nMove.curr) || nMove.curr[0] == 1);


                            printf("to space: ");
                            scanf("%d%d", &nMove.next[0], &nMove.next[1]);

                            if (nMove.next[0] > 7 || nMove.next[1] > 5 || (nMove.next[0] < 1 || nMove.next[1] < 1))
                                printf("Invalid space.\n\n");
                        }
                    }
                }
                else
                {
                    do
                    {
                        printf("Player %s (B) Turn, move piece: ", playerBeta);
                        scanf("%d%d", &nMove.curr[0], &nMove.curr[1]);

                        if (!checkBeta(piecesBeta, nMove.curr))
                            printf("You have no such piece.\n\n");
                        else if (nMove.curr[0] == 7)
                            printf("Sorry, you cannot move this piece.");

                    } while (!checkBeta(piecesBeta, nMove.curr) || nMove.curr[0] == 7);

                    do
                    {
                        printf("to space: ");
                        scanf("%d%d", &nMove.next[0], &nMove.next[1]);

                        if (nMove.next[0] > 7 || nMove.next[1] > 5 || (nMove.next[0] < 1 || nMove.next[1] < 1))
                            printf("Invalid space.\n\n");

                    } while ((nMove.next[0] > 7 || nMove.next[1] > 5) || (nMove.next[0] < 1 || nMove.next[1] < 1));

                    while (!ok)
                    {
                        if (checkBeta(piecesBeta, nMove.curr) &&
                            nMove.next[0] == nMove.curr[0] + 1 &&
                            (nMove.next[1] == nMove.curr[1] + 1 ||
                             nMove.curr[1] == nMove.next[1] + 1 ||
                             nMove.curr[1] == nMove.next[1]) &&
                            !checkBeta(piecesBeta, nMove.next) &&
                            !(checkAlpha(piecesAlpha, nMove.next) && ((nMove.next[0] % 2) != (nMove.next[1] % 2))) &&
                            !(nMove.next[0] > 7 || nMove.next[1] > 5 || (nMove.next[0] < 1 || nMove.next[1] < 1)))
                        {
                            indexBeta = checkBeta(piecesBeta, nMove.curr) - 1;
                            ok = !ok;
                        }
                        else
                        {
                            printf("Invalid move, please try again \n \n");
                            do
                            {
                                printf("Player %s (B) Turn, move piece: ", playerBeta);
                                scanf("%d%d", &nMove.curr[0], &nMove.curr[1]);

                                if (!checkBeta(piecesBeta, nMove.curr))
                                    printf("You have no such piece.\n\n");
                                else if (nMove.curr[0] == 7)
                                    printf("Sorry, you cannot move this piece.");

                            } while (!checkBeta(piecesBeta, nMove.curr) || nMove.curr[0] == 7);

                            printf("to space: ");
                            scanf("%d%d", &nMove.next[0], &nMove.next[1]);

                        }
                    }
                }

                if (ok)
                {
                    if (aTurn)
                    {
                        /* checks if the chosen space to move is only an empty space */
                        if (checkFree(piecesAlpha, piecesBeta, nMove.next))
                        {
                            piecesAlpha[indexAlpha][1] = nMove.next[1];
                            piecesAlpha[indexAlpha][0] = nMove.next[0];
                            aTurn = !aTurn;
                            ok = !ok;
                        } /* or if the chosen space to move is where an enemy piece is located */
                        else if ((indexBeta = checkBeta(piecesBeta, nMove.next) - 1) > -1)
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
                        if (checkFree(piecesAlpha, piecesBeta, nMove.next))
                        {
                            piecesBeta[indexBeta][1] = nMove.next[1];
                            piecesBeta[indexBeta][0] = nMove.next[0];
                            aTurn = !aTurn;
                            ok = !ok;
                        } /* or if the chosen space to move is where an enemy piece is located */
                        else if ((indexAlpha = checkAlpha(piecesAlpha, nMove.next) - 1) > -1)
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
                if (piecesCount(piecesAlpha) == 0 || ifEndBeta(piecesBeta) == 1)
                {
                    over = 1;
                    winner = BETA;
                }
                else if (piecesCount(piecesBeta) == 0 || ifEndAlpha(piecesAlpha) == 1)
                {
                    over = 1;
                    winner = ALPHA;
                }
            }
            if (winner == ALPHA)
                printf("Player %s wins!!\n", playerAlpha);
            else if (winner == BETA)
                printf("Player %s wins!!\n", playerBeta);
            displayBoard(piecesAlpha, piecesBeta);
        }
    } while (over != 1);
}

/* This is the main function */

int main()
{
    char cAskPlayAgain; // variable to be able to store the value if user wants to play/play again
    int nPlayAgain;     // initialized as 1 or 0 depending if the user wants to play again or not

    do
    {
        system("cls");
        MainMenu();
        scanf("%c", &cAskPlayAgain);
        getchar();

        while (cAskPlayAgain != '1' && cAskPlayAgain != '2')
        {
            if (cAskPlayAgain != '\n')
                printf("Invalid input. Please try again:\n");
            scanf("%c", &cAskPlayAgain);
        }

        if (cAskPlayAgain == '2')
        {
            nPlayAgain = 0;
        }
        else
            gameLoop();

        if (cAskPlayAgain == '1')
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