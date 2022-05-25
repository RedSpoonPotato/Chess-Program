#ifndef _GUI_H
#define _GUI_H


#define MAX_MSGLEN  400 
#define SQUARE_SIZE 50  
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (14*SQUARE_SIZE + 2*BOARD_BORDER)
#define WINDOW_HEIGHT (10*SQUARE_SIZE + 2*BOARD_BORDER)
#define UNDO_BTN_WIDTH 50
#define UNDO_BTN_HEIGHT 30
#define OPTION_BTN_WIDTH 50
#define OPTION_BTN_HEIGHT 30
#define SETTING_BTN_WIDTH 100
#define SETTING_BTN_HEIGHT 10

enum GRID
{
	BLACK = 0,
	WHITE = 1,
	KING
};

#endif
