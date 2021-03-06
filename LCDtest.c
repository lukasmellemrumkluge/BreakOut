/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "charset.h"
#include <string.h>
//#include <stdio.h>


void lcd_update(char * text, int * readIndex, uint8_t line, uint8_t * buffer){
	//Scrolls

	//TODO : only scroll sometimes

	uint8_t offset = 128*line;

	//Shift entire register
	for(int i=offset; i<127+offset; i++){
		buffer[i] = buffer[i+1];
	}

	//Find next byte
	char c = text[*readIndex/5] - 0x20;
	buffer[127 + offset] = character_data[c][*readIndex%5];
	(*readIndex)++;
	
	lcd_push_buffer(buffer);
	
	//Start from beginning of string when end is reached.
	if((*readIndex)/5 >= strlen(text)){
		(*readIndex) = 0;
	}

}

void lcd_write_string(int slice, uint8_t line, char * text, uint8_t * buffer){
	//Slices are 0-127 (relative coordinates)
	//lines 0-3
	//Negative and large slice vals supported

	//Each char is 5 lines wide
	//No line breaks

	if(line>3 || line<0) return;
	// What about slice values over 127?

	//Calculate number of lines in text.
	int textLength = strlen(text);
	int textLines = textLength*5;

	//Current char
	uint8_t c;

	//Position in the text, in lines.
	int readIndex = 0;

	//Drawing position, in slices
	int rendPos = slice;
	int offset = line * 128;

	//Filling the required line of the buffer, once.
	while(1){
	//While loop supports multiple renderings of short words.

		for(int i=0; i<textLength; i++){
		//i is read position, in chars

			//Set c to the current char corrected for the charset
			c = text[i]-0x20;

			if(rendPos < 0){
				//Negative slice value:
				// Neg. values are handled by stepping through them, while
				// incrementing rendPos until the first char to be
				// rendered is reached. Then it renders the first,
				// partial char. The check for <5 is to catch half-chars.
				if(rendPos < -4){
					rendPos += 5;
				} else{
					for(int j = 0; j<5; j++){
						if(rendPos >= 0){
							buffer[rendPos+offset] = character_data[c][j];
						}
						rendPos++;
					}
				}
			//Rendering chars that fit completely
			} else if(rendPos%127 < 122){
				//Memory- and computation-saving
				buffer[offset+(rendPos++)] = character_data[c][0];
				buffer[offset+(rendPos++)] = character_data[c][1];
				buffer[offset+(rendPos++)] = character_data[c][2];
				buffer[offset+(rendPos++)] = character_data[c][3];
				buffer[offset+(rendPos++)] = character_data[c][4];
			} else {
				//Renders "tail", and catches end-of-render
				readIndex = i*5;
				for(uint8_t j = 0; rendPos<128; j++){
					buffer[offset+(rendPos++)] = character_data[c][j];
					readIndex++;
				}
				goto endlabel;
			}
		}
	}


	endlabel: while(1){
	    for(int i = 0; i<200000;i++){}
		lcd_update(text, &readIndex, line, buffer);
	}

}

int main(){

	//Initialize USB serial connection:
	init_usb_uart(9600);
	
	//Initialize the LCD
	init_spi_lcd();

	//initialize buffer of 512 8-bit vertical lines
	uint8_t buffer[512];

	//Set them all to be stripy (0xAA = 10101010)
	memset(buffer,0xAA,512);

    char * text = "Come inside! Best pizza in towm! One slice - only 5.45! Only at Pierre´s! ";
    lcd_write_string(10, 0, text, buffer);
	//Updates the LCD
	lcd_push_buffer(buffer);
	while(1){}
}
