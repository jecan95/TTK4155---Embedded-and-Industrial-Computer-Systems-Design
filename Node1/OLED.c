#include "OLED.h" 
#include "fonts.h" 

#ifndef ADDRESS_C
#define ADDRESS_C  0x1000 
#endif

#ifndef ADDRESS_D
#define ADDRESS_D 0x1200 
#endif

#define PRINTABLE_CHAR_MIN ' '  
#define PRINTABLE_CHAR_MAX '~'  

int num_lines = 7; // Total number of lines on OLED
int num_columns = 127; // Total number of columns on OLED

void write_c(uint8_t cmd){
	volatile char* address = ADDRESS_C; // Set command address
	address[0] = cmd; // Send command to OLED
}

void write_d(uint8_t data){
	volatile char* address = ADDRESS_D; // Set data address
	address[0] = data; // Send data to OLED
}

void clear_oled() {
	for (int line = 0; line <= num_lines; line++) {
		set_position(line, 0); // Set cursor to start of line
		
		for (int column = 0; column <= num_columns; column++) {
			write_d(0); // Clear each column in line
		}
	}
}

void set_line(int line){
	if (line <= num_lines && line >= 0) {
		write_c(0xB0 + line); // Set line address in OLED
	}
}

void set_column(int column){
	if (column <= num_columns && column >= 0) {
		write_c(0x00 + (column & 0x0F)); // Set lower 4 bits of column address
		write_c(0x10 + ((column & 0xF0) >> 4)); // Set upper 4 bits of column address
	}
}

void set_position(int line, int column) {
	set_column(column); // Set current column
	set_line(line); // Set current line
}

void oled_init(){
	// Initialization commands for OLED display
	write_c(0xae); // display off
	
	write_c(0xaf); // display on
	clear_oled(); // Clear OLED display after initialization
}

void print_char(char car) {
	if (car >= PRINTABLE_CHAR_MIN && car <= PRINTABLE_CHAR_MAX) {
		int index = car - PRINTABLE_CHAR_MIN; // Calculate index in font array
		
		for (int i = 0; i < FONT_LENGTH; i++) {
			uint8_t character = pgm_read_byte(&(font8[index][i])); // Read character bitmap
			write_d(character); // Write character bitmap to OLED
		}
	}
}

void print_string(const char* str) {
	for (; *str != '\0'; ++str) {
		print_char(*str); // Print each character in string
	}
}

void print_int(uint16_t num) {
	char str[6]; // Buffer for integer string representation
	snprintf(str, sizeof(str), "%d", num); // Convert integer to string
	print_string(str); // Print string representation of integer
}
