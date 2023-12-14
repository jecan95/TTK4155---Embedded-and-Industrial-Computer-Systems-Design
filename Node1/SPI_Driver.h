#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

	void SPI_MasterInit(void);
	void SPI_Transmit(char);
	void SPI_SlaveInit(void);
	char SPI_SlaveReceive(void);

#endif 