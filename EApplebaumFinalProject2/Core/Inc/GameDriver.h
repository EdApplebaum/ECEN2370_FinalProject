/*
 * GameDriver.h
 *
 *  Created on: Nov 19, 2024
 *      Author: 14408
 */

#ifndef INC_GAMEDRIVER_H_
#define INC_GAMEDRIVER_H_

#include "LCD_Driver.h"
#include "Timer_Driver.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10
#define MOVE_RIGHT 0x1
#define MOVE_LEFT 0x2


// Function declarations
void initialize_game();
void Game_RNG_Init();
void draw_block(uint8_t x, uint8_t y, uint16_t color);

void draw_board();
void Display_Start_Screen();
void rotate_tetromino();
int check_collision(int x, int y);
void move_left();
void move_right();
void move_down();
void drop_tetromino();
void clear_lines();
void game_over();
void spawn_tetromino();
void place_tetromino();



#endif /* INC_GAMEDRIVER_H_ */
