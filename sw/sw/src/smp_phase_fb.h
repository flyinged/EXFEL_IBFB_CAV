/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : smp_phase_fb.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the sampling phase feedback. It contains the
//           feedback loop acting on the DDS chip of the RFFE board
//----------------------------------------------------------------------------
*/
#ifndef SMP_SYS_INIT_PHASE_FB_H_
#define SMP_SYS_INIT_PHASE_FB_H_
/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <math.h>
#include "sys_init.h"

/* Function declaration */
void smp_phase_fb_default(void);
void smp_phase_fb(void);

#endif /* DDS_PI_CTRL_H_ */
