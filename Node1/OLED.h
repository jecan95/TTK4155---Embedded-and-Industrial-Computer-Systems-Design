#include <stdint.h>

#define ASCII_OFFSET        32
#define FONT_LENGTH         8

void oled_init();
void set_line(int line);
void set_column(int col);
void set_position (int line, int column);
void clear_oled(void); 
void print_char(char car);
void print_string(const char* str);
void print_int(uint16_t num);

