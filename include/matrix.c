/*
 * pov.c
 *
 * Created: 2018-04-26 9:00:57 AM
 *  Author: Tim
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t povCount;
uint8_t matrix[8];

void init_matrix (void) {
	TCCR0B = (1<<CS01); // clk/64
	TIMSK0 = (1<<TOIE0); // TIM1_OVF interupt enable
	
	DDRB = 0xFF;
	DDRD = 0xFF;
}

void clr_matrix (void) {
	for (uint8_t i = 0; i < 8; i++) {
		matrix[i] = 0;
	}
}

void rect_matrix (uint8_t x_pos, uint8_t y_pos, uint8_t width, uint8_t height) {
	
	uint8_t line;
	
	for (uint8_t i = 0; i < height; i++) {
		for (uint8_t j = 0; j < width; j++) {
			line |= (1 << j);
		}
		
		matrix[i + x_pos] |= line << y_pos;
		line = 0;
	}
}

ISR(TIMER0_OVF_vect) {
	PORTD = 0;
	PORTB = ~(1<<povCount);
	PORTD = matrix[povCount];
	
	if (povCount < 7) {
		povCount++;
	}
	else {
		povCount = 0;
	}
}
