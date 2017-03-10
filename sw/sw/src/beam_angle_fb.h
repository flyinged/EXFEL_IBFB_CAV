/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : beam_angle_fb.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the beam angle correction feedback.
//----------------------------------------------------------------------------
*/
#ifndef BEAM_ANGLE_FB_H_
#define BEAM_ANGLE_FB_H_
/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <math.h>
#include "sys_init.h"

/* Function declaration */
void beam_angle_fb(void);

#endif /* BEAM_ANGLE_FB_H_ */
