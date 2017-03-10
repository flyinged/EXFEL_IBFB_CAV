/*
 * eeprom_test.c
 *
 *  Created on: 24.11.2011
 *      Author: koprek_w
 */

#include <stdio.h>
#include "xbasic_types.h"
#include "xio.h"
#include "eeprom_driver.h"

int eepromRead(u16 addr, u8 *data) {

	int i;

	//set up read operation
	XIo_Out32(EEPROM_BASE_ADDR+EEPROM_REG_CTRL, addr*2+1);
	//trigger operation
	XIo_Out32(EEPROM_BASE_ADDR+EEPROM_REG_TRG, 0);
	//wait for operation completion
	for (i=0; i<125000; i++) {
		if (XIo_In32(EEPROM_BASE_ADDR+EEPROM_REG_IDLE) == 1) {
			*data = (u8)XIo_In32(EEPROM_BASE_ADDR+EEPROM_REG_DATA);
			return 0;
		}
	}

	//timeout
	return -1;
}

int eepromWrite(u16 addr, u8 data) {

	int i;

	//XIo_Out32(EEPROM_BASE_ADDR+EEPROM_REG_WP, 0);
	//set up write operation
	XIo_Out32(EEPROM_BASE_ADDR+EEPROM_REG_CTRL, addr*2);
	//put data
	XIo_Out32(EEPROM_BASE_ADDR+EEPROM_REG_DATA, (u32)data);
	//trigger operation
	XIo_Out32(EEPROM_BASE_ADDR+EEPROM_REG_TRG, 0);
	//wait for operation completion
	for (i=0; i<125000; i++)
		if (XIo_In32(EEPROM_BASE_ADDR+EEPROM_REG_IDLE) == 1)
			return 0;

	//timeout
	return -1;
}


