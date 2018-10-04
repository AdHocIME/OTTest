#include "nrf24_hal.h"
SPI_HandleTypeDef hspi1;


// Configure the GPIO lines of the nRF24L01 transceiver
// note: IRQ pin must be configured separately
void nRF24_GPIO_Init(void) {

    // Enable the nRF24L01 GPIO peripherals
	  /* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi1);
    // Configure CSN pin
	nRF24_CSN_H();

	// Configure CE pin
	nRF24_CE_L();
}

// Low level SPI transmit/receive function (hardware depended)
// input:
//   data - value to transmit via SPI
// return: value received from SPI
uint8_t nRF24_LL_RW(uint8_t data) {
	uint8_t  receiveData;
	HAL_StatusTypeDef result = HAL_SPI_TransmitReceive(&hspi1, &data, &receiveData, (uint16_t) 1, 1000);
	return receiveData;
}
