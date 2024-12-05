/*
 * GameDriver.c
 *
 *  Created on: Nov 19, 2024
 *      Author: Ted Applebaum
 */
#include "GameDriver.h"
// Initialize game settings
void initialize_game() {
    score = 0;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[y][x] = 0;
        }
    }
    spawn_tetromino();
}

void draw_block(uint8_t x, uint8_t y, uint16_t color) {
	for(int temp_x = x*LCD_PIXEL_WIDTH/BOARD_WIDTH; temp_x < (x+1)*LCD_PIXEL_WIDTH/BOARD_WIDTH; temp_x++){
		for(int temp_y = y*LCD_PIXEL_HEIGHT/BOARD_HEIGHT; temp_y < (y+1)*LCD_PIXEL_HEIGHT/BOARD_HEIGHT; temp_y++){
			LCD_Draw_Pixel(temp_x,temp_y,color);
		}
	}


}

// Draw the game board and current score
void draw_board() {
//clear
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x]) {
            	draw_block(x,y,LCD_COLOR_WHITE);
            } else {
            	draw_block(x,y,LCD_COLOR_BLACK);
            }
        }
    }


}

// Spawn a new tetromino at the top
void spawn_tetromino() {
    current_type = HAL_RNG_GetRandomNumber(&HRNG) % 7; // Choose random tetromino
    current_rotation = 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = tetrominoes[current_type][y][x];
        }
    }

    current_x = BOARD_WIDTH / 2 - 2;
    current_y = 0;
}

// Rotate the current tetromino
void rotate_tetromino() {
    int temp[4][4];
    // Rotate the tetromino 90 degrees
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            temp[y][x] = current_tetromino[3 - x][y];
        }
    }

    // Check if rotated position is valid
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            current_tetromino[y][x] = temp[y][x];
        }
    }

    if (check_collision(current_x, current_y)) {
        // If collision occurs, revert the rotation
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                current_tetromino[y][x] = tetrominoes[current_type][y][x];
            }
        }
    }
}

// Check if the current tetromino collides with the board or other blocks
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

// Move the tetromino down by one row
void move_down() {
    if (!check_collision(current_x, current_y + 1)) {
        current_y++;
    } else {
        // Place the tetromino on the board
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (current_tetromino[i][j]) {
                    board[current_y + i][current_x + j] = 1;
                }
            }
        }

        // Clear full lines
        clear_lines();

        // Spawn a new tetromino
        spawn_tetromino();
    }
}

// Drop the tetromino to the bottom
void drop_tetromino() {
    while (!check_collision(current_x, current_y + 1)) {
        current_y++;
    }
}

// Move the tetromino left by one unit
void move_left() {
    if (!check_collision(current_x - 1, current_y)) {
        current_x--;
    }
}

// Move the tetromino right by one unit
void move_right() {
    if (!check_collision(current_x + 1, current_y)) {
        current_x++;
    }
}

// Clear any full lines
void clear_lines() {
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int full = 1;
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x] == 0) {
                full = 0;
                break;
            }
        }

        if (full) {
            // Shift all rows above down
            for (int i = y; i > 0; i--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    board[i][x] = board[i - 1][x];
                }
            }
            // Clear the top row
            for (int x = 0; x < BOARD_WIDTH; x++) {
                board[0][x] = 0;
            }
            score += 100; // Increase score for clearing a line
            y++; // Recheck the same row after shift
        }
    }
}

// Game over
void game_over() {

}



