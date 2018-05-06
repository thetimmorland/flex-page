/*
 * flex-page.c
 *
 * Created: 2018-04-25 3:14:45 PM
 * Author : Tim
 */ 

#define F_CPU 16000000
#define F_UPDATE 60

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "include/matrix.h"

uint8_t paddle1_x = 0;
uint8_t paddle1_y = 0;
uint8_t paddle1_len = 3;

uint8_t paddle2_x = 0;
uint8_t paddle2_y = 7;
uint8_t paddle2_len = 3;

float ball_x = 4;
float ball_y = 4;

float ball_v_x = 1;
float ball_v_y = 1;

void reset_game(void) {
	paddle1_x = 0;
	paddle1_y = 0;
	
	paddle2_x = 0;
	paddle2_y = 7;
	
	ball_x = 4;
	ball_y = 4;
	
	ball_v_x = 1;
	ball_v_y = 1;
}

void draw_game(void) {
	
	// clear old instances of ball and paddles
	clr_matrix();
	
	rect_matrix(ball_x, ball_y, 1, 1); // draw ball
	
	// draw paddles
	rect_matrix(paddle1_x, paddle1_y, 1, paddle1_len);
	rect_matrix(paddle2_x, paddle2_y, 1, paddle2_len);
}

int main (void)
{
	init_matrix();
	sei();
	
	reset_game();
	
	for(;;) {
		draw_game();
		_delay_ms(1000/F_UPDATE);
	}
}
