/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : adc16hl.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for accessing the features of the ADC16HL data
//           acquisition board.
//----------------------------------------------------------------------------
*/
#ifndef ADC16HL_H_
#define ADC16HL_H_

/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <math.h>
#include "sys_init.h"

/* Function declaration */
void adc_ctrl_wr(void);
void clk_pd_en_sel_wr(void);
void clk_vboost_wr(void);
void fpga_clk_wr(void);
void pwr_clk_wr(void);
void adc0_clk_wr(void);
void adc1_clk_wr(void);
void adc2_clk_wr(void);
void adc3_clk_wr(void);
void adc4_clk_wr(void);
void adc5_clk_wr(void);
void adc0_dac_wr(void);
void adc1_dac_wr(void);
void adc2_dac_wr(void);
void adc3_dac_wr(void);
void adc4_dac_wr(void);
void adc5_dac_wr(void);
void adc_sync_wr(void);
void adc16hl_default(void);
void adc16hl_init(void);

#endif /* ADC16HL_H_ */

/* EOF */
