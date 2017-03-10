/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : att_fb.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the attenuation feedback. It contains the
//           feedback loop.
//----------------------------------------------------------------------------
*/
#ifndef ATT_FB_H_
#define ATT_FB_H_

/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include "sys_init.h"

/* Data declaration */
#define GAIN_FB_MAX_MIN_THR       10    /* Gain threshold between upper an lower limits in % */
#define GAIN_FB_MAX_AMP           76313 /* Max Amplitude after CORDIC = Max_ADC_Code * sqrt(2) * K_CORDIC = 32768 * 1.414213562 * 1.646760258 = 76313 */
#define GAIN_FB_MAX_SAT_AMP       72497 /* 95 % Max Amplitude after CORDIC = 0.95 * Max_ADC_Code * sqrt(2) * K_CORDIC = 32768 * 1.414213562 * 1.646760258 = 72497 */

/* Function declaration */
void att_fb_default(void);
void att_fb(void);

#endif /* ATT_FB_H_ */
