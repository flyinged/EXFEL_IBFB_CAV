/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : interrupt.h
// Author  : Waldemar Koprek, Section Diagnostic
//           Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This is a interrupt controller initialization. It configures the
//           interrupt subroutines to be called.
//----------------------------------------------------------------------------
*/
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/* Include files */
#include <xintc_l.h>
#include <xil_exception.h>
#include <xio.h>
#include <xparameters.h>
#include "beam_angle_fb.h"
#include "smp_phase_fb.h"
#include "iq_phase_fb.h"
#include "att_fb.h"
#include "sys_init.h"
#include "sys_init_store.h"
#include "scaling.h"

/* Data declaration */
#define BUNCH_TRAIN_DONE          0x00000001
#define SYS_INIT_DONE             0x00000002

#define XREG_MSR_FLOATING_POINT_UNIT_ENABLE  0x00002000

/* Function declaration */
int initPPCInterrupts();

#endif /* INTERRUPT_H_ */

/* EOF */
