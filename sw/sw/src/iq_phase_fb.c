/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : iq_phase_fb.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the I/Q phase feedback. It contains the
//           feedback loop.
//----------------------------------------------------------------------------
*/
/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <math.h>
#include "sys_init.h"

void iq_phase_fb_default(void)
{
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_ON_IDX  + SYS_INIT_NO_IRQ_MASK,    1); /* 0 := disabled; 1 := enabled */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_REF_IDX + SYS_INIT_NO_IRQ_MASK, 45.0); /* regulate to this value */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_KP_IDX  + SYS_INIT_NO_IRQ_MASK,  0.1); /* proportional coefficient of PI feedback */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_KI_IDX  + SYS_INIT_NO_IRQ_MASK,  1.0); /* integral coefficient of PI feedback */
}

void iq_phase_fb(void)
{
   /* Bunch counter */
   u32   i = 0;
   /* Requested bunches to measure */
   u32   SMP_B0_0 = 0;
   /* I/Q PI feedback control */
   u32   SYS_INIT_PH_REF_FB_ON  = 0;
   float SYS_INIT_PH_REF_FB_REF = 0.0f;
   float SYS_INIT_PH_REF_FB_KP  = 0.0f;
   float SYS_INIT_PH_REF_FB_KI  = 0.0f;
   float PH_REF_R = 0.0f;
   float SYS_INIT_PH_REF_FB_ERR = 0.0f;
   float SYS_INIT_PH_REF_FB_P = 0.0f;
   float SYS_INIT_PH_REF_FB_I = 0.0f;
   float SYS_INIT_PH_REF_FB_ANG = 0.0f;
   float SYS_INIT_PH_REF_FB_COR = 0.0f;
   static float SYS_INIT_PH_REF_FB_VAL = 0.0f;
   /* Measurements */
   s32   AMP_TOP_R = 0;
   s32   PH_REF_R_RAW  = 0;

   /* Feedback required? */
   SYS_INIT_PH_REF_FB_ON  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_ON_IDX);
   if (SYS_INIT_PH_REF_FB_ON == 1)
   {
      /* Load parameters and values and check valid range */
      SMP_B0_0 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);
      SYS_INIT_PH_REF_FB_REF = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_REF_IDX));
      if (isnanf(SYS_INIT_PH_REF_FB_REF))
      {
         SYS_INIT_PH_REF_FB_REF = 0.0f;
      }
      SYS_INIT_PH_REF_FB_KP  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_KP_IDX));
      if (isnanf(SYS_INIT_PH_REF_FB_KP))
      {
         SYS_INIT_PH_REF_FB_KP = 0.0f;
      }
      SYS_INIT_PH_REF_FB_KI  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_KI_IDX));
      if (isnanf(SYS_INIT_PH_REF_FB_KI))
      {
         SYS_INIT_PH_REF_FB_KI = 0.0f;
      }
      /* Search first occurance */
      for (i = 0; i < SMP_B0_0; ++i) /* For all possible charge and position entries in the tables of the FPGA firmware */
      {
         /* Read amplitude */
         AMP_TOP_R   = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IP_S_BRAM_BASE + (i * 4));
         if (AMP_TOP_R > 400) /* Ignore calculating the positions if almost no charge is measured... the positions may jump around then calculation almost 0, noisy position divided by almost 0, noisy charge */
         {
            /* Convert angle 0...360° to 0...180,-180...0 */
            PH_REF_R_RAW  = (s32) (XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_CD_R_PH_BRAM_BASE + (i * 4)));
            PH_REF_R      = PH_REF_R_RAW * 0.0000002384185791f;
            if (PH_REF_R > 180.0f)
            {
               PH_REF_R = PH_REF_R - 360.0f;
            }
            /* Error calculation */
            SYS_INIT_PH_REF_FB_ERR = SYS_INIT_PH_REF_FB_REF - PH_REF_R;
            /* Proportional calculation including saturation */
            SYS_INIT_PH_REF_FB_P = SYS_INIT_PH_REF_FB_ERR * SYS_INIT_PH_REF_FB_KP;
            if (SYS_INIT_PH_REF_FB_P > 90.0f)
            {
               SYS_INIT_PH_REF_FB_P = 90.0f;
            }
            else if (SYS_INIT_PH_REF_FB_P < -90.0f)
            {
               SYS_INIT_PH_REF_FB_P = -90.0f;
            }
            /* Integral calculation including saturation */
            /* SYS_INIT_PH_REF_FB_I = SYS_INIT_PH_REF_FB_ERR * SYS_INIT_PH_REF_FB_KI + SYS_INIT_PH_REF_FB_I; the integral part is now in the SYS_INIT_PH_REF_FB_VAL because it is at the same time the DAC value */
            SYS_INIT_PH_REF_FB_I = SYS_INIT_PH_REF_FB_ERR * SYS_INIT_PH_REF_FB_KI;
            if (SYS_INIT_PH_REF_FB_I > 180.0f)
            {
               SYS_INIT_PH_REF_FB_I = 180.0f;
            }
            else if (SYS_INIT_PH_REF_FB_I < -180.0f)
            {
               SYS_INIT_PH_REF_FB_I = -180.0f;
            }
            /* Correction angle including saturation */
            SYS_INIT_PH_REF_FB_ANG = SYS_INIT_PH_REF_FB_P + SYS_INIT_PH_REF_FB_I;
            if (SYS_INIT_PH_REF_FB_ANG > 180.0f)
            {
               SYS_INIT_PH_REF_FB_ANG = 180.0f;
            }
            else if (SYS_INIT_PH_REF_FB_ANG < -180.0f)
            {
               SYS_INIT_PH_REF_FB_ANG = -180.0f;
            }
            SYS_INIT_PH_REF_FB_COR = SYS_INIT_PH_REF_FB_ANG / 115.0f;
            SYS_INIT_PH_REF_FB_VAL = SYS_INIT_PH_REF_FB_VAL + SYS_INIT_PH_REF_FB_COR;
            if (SYS_INIT_PH_REF_FB_VAL < 0.0f)
            {
               SYS_INIT_PH_REF_FB_VAL = 4.0f + SYS_INIT_PH_REF_FB_VAL;
            }
            else if (SYS_INIT_PH_REF_FB_VAL > 4.0f)
            {
               SYS_INIT_PH_REF_FB_VAL = SYS_INIT_PH_REF_FB_VAL - 4.0f;
            }
            lo_phase_value_wr(SYS_INIT_PH_REF_FB_VAL);
            /* End for loop */
            break;
         }
      }
   }
   else
   {
      SYS_INIT_PH_REF_FB_VAL = 0.0f;
   }
}
