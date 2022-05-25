# Chess-Program
Chess Game with Player vs AI mode (Team Project)
Author: Kunal Paode

Intro:
Hello! This is a repository for a chess program that I wrote along side 4 other students for EECS22L at UCI for a C programming class. We had 4 weeks in total to complete the assignement, and during each week we had to submit 1 submission in the given order: User Manual(1), Software Specification (2), Alpha Version(3), Final Version(4). Our chess program has a functional GUI built in GTK 2.0, and so it runs only on linux.

My Contributions: soley built Board.c/Board.h, and helped with the actual implementation (but did not plan the sudo-code for the minimax algorithm) for aiZach.c/aiZach.h

Board.c/Board.h Description: Defines crucial functions that are used by gui.c/chess.c/aiZach.c
such as SmartMovePiece(), which moves a piece if it is found to be legal, and returns an errorcode if the move was found to be illegal. This function relies itself relies upon many other functions within Board.c, such as Rules() which determines if a move is legal, and BoardUpkeep() which ensures that certain variables are updated in relation to castling and en-passanting. 
