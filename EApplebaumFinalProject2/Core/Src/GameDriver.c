/*
 * GameDriver.c
 *
 *  Created on: Nov 19, 2024
 *      Author: Ted Applebaum
 */
#include "GameDriver.h"
#include <math.h>

uint8_t tetrominoes[7][4][4] = {

    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

uint8_t board[BOARD_HEIGHT][BOARD_WIDTH];
uint8_t current_tetromino[4][4];
uint8_t current_x, current_y;
uint8_t current_rotation;
uint8_t current_type;
uint16_t singles=0;
uint16_t doubles=0;
uint16_t tetris=0;

static RNG_HandleTypeDef HRNG;

void Display_Start_Screen() {
	current_type = 0;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 0;
    current_y = 0;

    place_tetromino();

	current_type = 1;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 3;
    current_y = 0;

    place_tetromino();

	current_type = 2;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 7;
    current_y = 0;

    place_tetromino();

	current_type = 3;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 0;
    current_y = 4;

    place_tetromino();

	current_type = 4;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 4;
    current_y = 4;

    place_tetromino();
	current_type = 5;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 0;
    current_y = 8;

    place_tetromino();

	current_type = 6;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = 4;
    current_y = 8;

    place_tetromino();
}

void initialize_game() {
    Game_RNG_Init();
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[y][x] = 0;
        }
    }
    spawn_tetromino();
    Timer2_Reset();
    Timer2_Start();
}

void draw_block(uint8_t x, uint8_t y, uint16_t color) {
	for(int temp_x = x*LCD_PIXEL_WIDTH/BOARD_WIDTH; temp_x < (x+1)*LCD_PIXEL_WIDTH/BOARD_WIDTH; temp_x++){
		for(int temp_y = y*LCD_PIXEL_HEIGHT/BOARD_HEIGHT; temp_y < (y+1)*LCD_PIXEL_HEIGHT/BOARD_HEIGHT; temp_y++){
			LCD_Draw_Pixel(temp_x,temp_y,color);
		}
	}


}


void draw_board() {

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x]) {
            	draw_block(x,y,LCD_COLOR_WHITE);
            } else {
            	draw_block(x,y,LCD_COLOR_BLACK);
            }
        }
    }

    for (uint8_t y = 0; y < 4; y++) {
    	for (uint8_t x = 0; x<4; x++) {
    		if(current_tetromino[y][x]) {
    			draw_block(x+current_x,(y+current_y),LCD_COLOR_WHITE);
    		}
    	}
    }
}


void spawn_tetromino() {
	current_type = HAL_RNG_GetRandomNumber(&HRNG)%7;
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = BOARD_WIDTH / 2 - 2;
    current_y = 0;
}


void rotate_tetromino() {
    int temp[4][4];
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            temp[y][x] = current_tetromino[3 - x][y];
        }
    }

    switch(current_rotation) {
    case 0:
    	current_x--;
    	current_x--;
    	break;
    case 1:
    	current_y--;
    	current_y--;
    	break;
    case 2:
    	current_x++;
    	current_x++;
    	break;
    case 3:
        current_y++;
        current_y++;
        break;
    }

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = temp[y][x];
        }
    }

    if (check_collision(current_x, current_y)) {
        switch(current_rotation) {
        case 0:
        	current_x++;
        	current_x++;
        	break;
        case 1:
        	current_y++;
        	current_y++;
        	break;
        case 2:
        	current_x--;
        	current_x--;
        	break;
        case 3:
            current_y--;
            current_y--;
            break;

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                current_tetromino[y][x] = tetrominoes[current_type][y][x];

                }
            }
        }
    }
    else {
    	current_rotation = (current_rotation+1)%4;
    }


}


int check_collision(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (current_tetromino[i][j]) {
                int board_x = x + j;
                int board_y = y + i;
                if (board_x < 0 || board_x >= BOARD_WIDTH || board_y >= BOARD_HEIGHT || (board_y >= 0 && board[board_y][board_x])) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


void move_down() {
    if (!check_collision(current_x, current_y + 1)) {
        current_y++;
    } else {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (current_tetromino[i][j]) {
                    board[current_y + i][current_x + j] = 1;
                }
            }
        }
        clear_lines();
        if(current_y==0) {
        	game_over();
        }
        else {
        spawn_tetromino();
        }
    }
}


void drop_tetromino() {
    while (!check_collision(current_x, current_y + 1)) {
        current_y++;
    }
}

void move_left() {
    if (!check_collision(current_x - 1, current_y)) {
        current_x--;
    }
}


void move_right() {
    if (!check_collision(current_x + 1, current_y)) {
        current_x++;
    }
}

void clear_lines() {
	uint8_t LinesCleared=0;
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int full = 1;
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x] == 0) {
                full = 0;
                break;
            }
        }

        if (full) {
            for (int i = y; i > 0; i--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    board[i][x] = board[i - 1][x];
                }
            }
            for (int x = 0; x < BOARD_WIDTH; x++) {
                board[0][x] = 0;
            }
            y++;
            LinesCleared++;
        }
    }
    if(LinesCleared){
    	if(LinesCleared%2) {
    		LinesCleared--;
    		singles++;
    	}

    	while(LinesCleared>=4) {
    		LinesCleared -= 4;
    		tetris++;
    	}
    	if(LinesCleared) {
    		doubles++;
    	}
    }

}

void place_tetromino() {
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if (current_tetromino[i][j]) {
                uint8_t x = current_x + j;
                uint8_t y = current_y + i;
                if (y >= 0) {
                    board[y][x] = 1;
                }
            }
        }
    }
    clear_lines();
}

void game_over() {
	LCD_Clear(0, LCD_COLOR_RED);
	Timer2_Stop();
	int Time_Played = (int) GetGameTime();

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

	LCD_DisplayChar(60,40,'T');
	LCD_DisplayChar(70,40,'I');
	LCD_DisplayChar(80,40,'M');
	LCD_DisplayChar(95,40,'E');
	LCD_DisplayChar(105,40,' ');
	LCD_DisplayChar(115,40,'P');
	LCD_DisplayChar(130,40,'L');
	LCD_DisplayChar(145,40,'A');
	LCD_DisplayChar(160,40,'Y');
	LCD_DisplayChar(175,40,'E');
	LCD_DisplayChar(190,40,'D');
	LCD_DisplayChar(205,40,':');

	LCD_DisplayChar(60,80,'S');
	LCD_DisplayChar(70,80,'I');
	LCD_DisplayChar(82,80,'N');
	LCD_DisplayChar(96,80,'G');
	LCD_DisplayChar(110,80,'L');
	LCD_DisplayChar(123,80,'E');
	LCD_DisplayChar(136,80,'S');
	LCD_DisplayChar(147,80,':');

	LCD_DisplayChar(60,120,'D');
	LCD_DisplayChar(75,120,'O');
	LCD_DisplayChar(90,120,'U');
	LCD_DisplayChar(105,120,'B');
	LCD_DisplayChar(120,120,'L');
	LCD_DisplayChar(135,120,'E');
	LCD_DisplayChar(150,120,'S');
	LCD_DisplayChar(160,120,':');

	LCD_DisplayChar(60,160,'T');
	LCD_DisplayChar(75,160,'E');
	LCD_DisplayChar(90,160,'T');
	LCD_DisplayChar(105,160,'R');
	LCD_DisplayChar(115,160,'I');
	LCD_DisplayChar(125,160,'S');
	LCD_DisplayChar(135,160,':');


	char time_string[10];
	sprintf(time_string, "%d", Time_Played);

	for(int i=0; i < 10; i++) {
		if(time_string[i]>=0x30 && time_string[i]<=0x39) LCD_DisplayChar(90 + 12*i,60,time_string[i]);
	}

	LCD_DisplayChar(210 ,60,'s');

	for(int i=0; i < 10; i++) {
		time_string[i]='\0';
	}

	sprintf(time_string, "%d", singles);

	for(int i=0; i < 10; i++) {
		if(time_string[i]>=0x30 && time_string[i]<=0x39) LCD_DisplayChar(90 + 12*i,100,time_string[i]);
	}

	for(int i=0; i < 10; i++) {
		time_string[i]='\0';
	}

	sprintf(time_string, "%d", doubles);

	for(int i=0; i < 10; i++) {
		if(time_string[i]>=0x30 && time_string[i]<=0x39) LCD_DisplayChar(90 + 12*i,140,time_string[i]);
	}

	for(int i=0; i < 10; i++) {
		time_string[i]='\0';
	}

	sprintf(time_string, "%d", tetris);

	for(int i=0; i < 10; i++) {
		if(time_string[i]>=0x30 && time_string[i]<=0x39) LCD_DisplayChar(90 + 12*i,180,time_string[i]);
	}

	while(1);
}

void Game_RNG_Init() {
	HRNG.Instance = RNG;
	__HAL_RCC_RNG_CLK_ENABLE();
	HAL_RNG_Init(&HRNG);
}

