/* ai.c file */
#include "aiZach.h"
#include "stdlib.h"
#include "stdio.h"
#include <time.h>

int boardEvaluation(Board* board) {
    int kingValue         = 40;
    int queenValue        =  9;
    int rookValue         =  5;
    int bishopKnightValue =  3;
    int pawnValue         =  1;

    int whiteTotal = 0, blackTotal = 0;
    int file, rank;

    for (rank = one; rank <= eight; rank++) {
        for (file = a; file <= h; file++) {
            if (board->grid[file][rank].color == white) {
                if (board->grid[file][rank].type == king) {
                    whiteTotal += kingValue;
                }
                else if (board->grid[file][rank].type == queen) {
                    whiteTotal += queenValue;
                }
                else if (board->grid[file][rank].type == rook) {
                    whiteTotal += rookValue;
                }
                else if (board->grid[file][rank].type == bishop || board->grid[file][rank].type == knight) {
                    whiteTotal += bishopKnightValue;
                }
                else if (board->grid[file][rank].type == pawn) {
                    whiteTotal += pawnValue;
                }
            }
            else if (board->grid[file][rank].color == black) {
                if (board->grid[file][rank].type == king) {
                    blackTotal += kingValue;
                }
                else if (board->grid[file][rank].type == queen) {
                    blackTotal += queenValue;
                }
                else if (board->grid[file][rank].type == rook) {
                    blackTotal += rookValue;
                }
                else if (board->grid[file][rank].type == bishop || board->grid[file][rank].type == knight) {
                    blackTotal += bishopKnightValue;
                }
                else if (board->grid[file][rank].type == pawn) {
                    blackTotal += pawnValue;
                }
            }
        }
    }
    return (whiteTotal - blackTotal);
}

BoardList createBoardList(Board* board, Color teamColor) {
    BoardList listOfBoards;

    MoveList iMoves = GetAllMoves(teamColor, board);
    listOfBoards.size = iMoves.size;
    listOfBoards.list = malloc(iMoves.size * sizeof(Board));
    for (int i = 0; i < listOfBoards.size; i++) {
        listOfBoards.list[i] = CloneBoardV2(board);
        SmartMovePiece(iMoves.list[i].iPos, iMoves.list[i].fPos, listOfBoards.list + i, queen);
    }
    free(iMoves.list);
    return listOfBoards;
}

int minimax(Board* board, int depth, Color teamColor) {
    int i = 0;
    int minEval, maxEval;
    static int eval; 

    BoardList listOfBoards = createBoardList(board, teamColor);
    if (depth == 0 || CheckForCheckMate(LocateKing(teamColor, board), board)) {
        free(listOfBoards.list);
        return boardEvaluation(board);
    }

    if (teamColor == white) {
        maxEval = -1000000;
        for (i = 0; i < listOfBoards.size; i++) {
            eval = minimax(listOfBoards.list+i, depth - 1, black);
            maxEval = (maxEval > eval) ? maxEval : eval;
        }
        free(listOfBoards.list);
        return maxEval;
    }
    else {
        minEval = 1000000;
        for (i = 0; i < listOfBoards.size; i++) {
            eval = minimax(listOfBoards.list+i, depth - 1, white);
            minEval = (minEval < eval) ? minEval : eval;
            free(listOfBoards.list);
            return minEval;
        }
    }
}



MinimaxBoardList createMinimaxBoardList(Board* board, int depth, Color teamColor) {
    MoveList iMoves;
    Color oppositeColor;
    iMoves = GetAllMoves(teamColor, board);
    listOfMinimaxBoards.size = iMoves.size;

    //randomizing moves
    srand(time(NULL));
    int rand1, rand2, temp;
    int *arry = malloc(sizeof(int) * listOfMinimaxBoards.size);
    for (int i = 0; i < listOfMinimaxBoards.size; i++) {
        arry[i] = i;
    }
    for (int i = 0; i < 200; i++)
    {
        rand1 = rand() % listOfMinimaxBoards.size;
        rand2 = rand() % listOfMinimaxBoards.size;
        temp = arry[rand1];
        arry[rand1] = arry[rand2];
        arry[rand2] = temp;
    }
    // arry is now a randomized list of ints all with unique values between 0 and list.size - 1

    listOfMinimaxBoards.list = malloc(iMoves.size * sizeof(MinimaxBoard));
    for (int i = 0; i < listOfMinimaxBoards.size; i++) {
        listOfMinimaxBoards.list[i].board = CloneBoard(board);
        listOfMinimaxBoards.list[i].move = iMoves.list[arry[i]];
        SmartMovePiece(iMoves.list[arry[i]].iPos, iMoves.list[arry[i]].fPos, listOfMinimaxBoards.list[i].board, queen);
        if (teamColor == white) { oppositeColor = black; }
        else if (teamColor == black) { oppositeColor = white; }
        listOfMinimaxBoards.list[i].minimaxScore = minimax(listOfMinimaxBoards.list[i].board, depth - 1, oppositeColor);
    }

    free(arry);
    free(iMoves.list);
    return listOfMinimaxBoards;
}

/* updated function for creatingBestAIMove */
Move createBestMove(Board *board, int depth, Color teamColor) {
    int i, maxMinimaxScore;
    MinimaxBoardList minimaxBoardList;
    Move finalMove;     
    Move bestMove;

    minimaxBoardList = createMinimaxBoardList(board, depth, teamColor);

    /* find max/min for white/black */
    if (teamColor == white) {
        maxMinimaxScore = -1000000;
        for (i = 0; i < minimaxBoardList.size; i++) {
            if (maxMinimaxScore < minimaxBoardList.list[i].minimaxScore) {
                maxMinimaxScore = minimaxBoardList.list[i].minimaxScore;
                bestMove = minimaxBoardList.list[i].move;
            }
        }
    }
    else if (teamColor == black) {
        maxMinimaxScore = 1000000;
        for (i = 0; i < minimaxBoardList.size; i++) {
            if (maxMinimaxScore > minimaxBoardList.list[i].minimaxScore) {
                maxMinimaxScore = minimaxBoardList.list[i].minimaxScore;
                bestMove = minimaxBoardList.list[i].move;
            }
        }
    }

    finalMove = bestMove;
    for (i = 0; i < minimaxBoardList.size; i++) {
        free(minimaxBoardList.list[i].board);
    }
    free(minimaxBoardList.list);
    return finalMove;
}
