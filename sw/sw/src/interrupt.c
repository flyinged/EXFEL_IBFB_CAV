/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : interrupt.c
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
/* Include files */
#include "interrupt.h"

void deviceDriverHandler(void *CallbackRef)
{
   /* Get interrupt source */
   unsigned int stat;

   XIo_Out32(XPAR_JMP_INST_BASEADDR, 0x00000004);
   /* enable FPU present in MBR */
   mtmsr(mfmsr() | XREG_MSR_FLOATING_POINT_UNIT_ENABLE);

   /* Handle bunch train done */
   stat = XIo_In32(XPAR_INTC_INST_BASEADDR + XIN_IPR_OFFSET);
   if ((stat & BUNCH_TRAIN_DONE) != 0)
   {
      /* Call interrupt routine(s) for BUNCH_TRAIN_DONE signal */
      sys_init_copy();
      scaling();
      beam_angle_fb();
      smp_phase_fb();
      iq_phase_fb();
      att_fb();
      /* Acknowledge interrupt */
      XIo_Out32(XPAR_INTC_INST_BASEADDR + XIN_IAR_OFFSET, BUNCH_TRAIN_DONE);
   }
   if ((stat & SYS_INIT_DONE) != 0)
   {
      /* Call interrupt routine for new value setting */
      sys_init_decode();
      /* Acknowledge interrupt */
      XIo_Out32(XPAR_INTC_INST_BASEADDR + XIN_IAR_OFFSET, SYS_INIT_DONE);
   }
   /* This read prevents strange effects from posted writes */
   stat = XIo_In32(XPAR_INTC_INST_BASEADDR + XIN_IPR_OFFSET);
   XIo_Out32(XPAR_JMP_INST_BASEADDR, 0x00000000);
}

int initPPCInterrupts()
{
   /* Initialize the exception table */
   Xil_ExceptionInit();

   /* Register the interrupt controller handler with the exception table */
   Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)deviceDriverHandler, XPAR_INTC_INST_DEVICE_ID);

   /* Enable exceptions */
   Xil_ExceptionEnable();

   /* Enable interrupts for all devices that cause interrupts, and enable the INTC master enable bit */
   XIntc_Out32(XPAR_INTC_INST_BASEADDR + XIN_IER_OFFSET, BUNCH_TRAIN_DONE | SYS_INIT_DONE);

   /* Set the master enable bit */
   XIntc_Out32(XPAR_INTC_INST_BASEADDR + XIN_MER_OFFSET, XIN_INT_MASTER_ENABLE_MASK | XIN_INT_HARDWARE_ENABLE_MASK);

   return(0);
}

/* EOF */
