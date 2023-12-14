#ifndef SRAM_TEST_H_
#define SRAM_TEST_H_


void SRAM_test(void);
int SRAM_write(uint16_t address, char data);
char SRAM_read(uint16_t address);


#endif 