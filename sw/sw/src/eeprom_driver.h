/*
 * eeprom_test.h
 *
 *  Created on: 24.11.2011
 *      Author: koprek_w
 */

#ifndef EEPROM_TEST_H_
#define EEPROM_TEST_H_

#include "xparameters.h"

#define EEPROM_BASE_ADDR XPAR_GPAC_EEPROM_0_BASEADDR // 65536 x 8-bit

#define EEPROM_SIZE 65536 // 65536 x 8-bit

//regs
#define EEPROM_REG_IDLE 0x00
#define EEPROM_REG_TRG  0x00
#define EEPROM_REG_CTRL 0x04
#define EEPROM_REG_DATA 0x08
#define EEPROM_REG_WP   0x0C


int eepromWrite(u16 addr, u8 data);
int eepromRead(u16 addr, u8 *data);

#endif /* EEPROM_TEST_H_ */
