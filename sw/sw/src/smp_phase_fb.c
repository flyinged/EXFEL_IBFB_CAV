/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : smp_phase_fb.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the sampling phase feedback. It contains the
//           feedback loop acting on the DDS chip of the RFFE board
//----------------------------------------------------------------------------
*/
/* Include files */
#include "smp_phase_fb.h"

void smp_phase_fb_default(void)
{
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_ON_IDX  + SYS_INIT_NO_IRQ_MASK,   1); /* 0 := disabled; 1 := enabled */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_REF_IDX + SYS_INIT_NO_IRQ_MASK, 0.0); /* regulate to this value */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_KP_IDX  + SYS_INIT_NO_IRQ_MASK, 0.1); /* proportional coefficient of PI feedback */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_KI_IDX  + SYS_INIT_NO_IRQ_MASK, 1.0); /* integral coefficient of PI feedback */
}

void smp_phase_fb(void)
{
   /* Bunch counter */
   u32   i = 0;
   /* Requested bunches to measure */
   u32   SMP_B0_0 = 0;
   /* DDS PI feedback control */
   u32   SYS_INIT_PHASE_FB_ON = 0;
   float SYS_INIT_PHASE_FB_REF = 0.0f;
   float SYS_INIT_PHASE_FB_KP = 0.0f;
   float SYS_INIT_PHASE_FB_KI = 0.0f;
   float PH_TOP_R = 0.0f;
   float PH_TOP_R_FB_C0 = 0.0f;
   float SYS_INIT_PHASE_FB_ERR = 0.0f;
   static float SYS_INIT_PHASE_FB_P = 0.0;
   static float SYS_INIT_PHASE_FB_I = 0.0;
   /* Measurements */
   s32   AMP_TOP_R = 0;
   u32   AMP_TOP_VALID_R = 0;
   s32   PH_TOP_R_RAW = 0;
   float SYS_INIT_PHASE_FB_VAL = 0.0f;
   float DDS_PHASE = 0.0f;

   /* Feedback required? */
   SYS_INIT_PHASE_FB_ON = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_ON_IDX);
   if (SYS_INIT_PHASE_FB_ON == 1)
   {
      /* Load parameters and values and check valid range */
      SMP_B0_0 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);
      SYS_INIT_PHASE_FB_KP = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_KP_IDX));
      if (isnanf(SYS_INIT_PHASE_FB_KP))
      {
         SYS_INIT_PHASE_FB_KP = 0.0f;
      }
      SYS_INIT_PHASE_FB_KI = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_KI_IDX));
      if (isnanf(SYS_INIT_PHASE_FB_KI))
      {
         SYS_INIT_PHASE_FB_KI = 0.0f;
      }
      SYS_INIT_PHASE_FB_REF = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_REF_IDX));
      if (isnanf(SYS_INIT_PHASE_FB_REF))
      {
         SYS_INIT_PHASE_FB_REF = 0.0f;
      }
      /* Search first occurance */
      for (i = 0; i < SMP_B0_0; ++i) /* For all possible charge and position entries in the tables of the FPGA firmware */
      {
         /* Read amplitude */
         AMP_TOP_R       = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IP_S_BRAM_BASE     + (i * 4));
         AMP_TOP_VALID_R = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IP_S_VAL_BRAM_BASE + (i * 4));
         if ((AMP_TOP_VALID_R == 1) && (AMP_TOP_R > 400)) /* Ignore calculating the positions if almost no charge is measured... the positions may jump around then calculation almost 0, noisy position divided by almost 0, noisy charge */
         {
            PH_TOP_R_RAW = (s32) (XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IP_T_BRAM_BASE + (i * 4))); /* Read the top phase from the second interpolation buffer */
            PH_TOP_R     = PH_TOP_R_RAW * 0.0009765625f; /* Convert to float */
            /* The following makes sure the phase is in a valid range */
            if (PH_TOP_R > 180.0f) /* Warp around */
            {
               PH_TOP_R_FB_C0 = PH_TOP_R - 360.0f;
            }
            else if (PH_TOP_R > 0.0f)
            {
               PH_TOP_R_FB_C0 = PH_TOP_R;
            }
            else if (PH_TOP_R > -180.0f)
            {
               PH_TOP_R_FB_C0 = PH_TOP_R;
            }
            else /* Warp around */
            {
               PH_TOP_R_FB_C0 = PH_TOP_R + 360.0f;
            }
            /* Calculate the feedback */
            SYS_INIT_PHASE_FB_ERR  = SYS_INIT_PHASE_FB_REF - PH_TOP_R_FB_C0;
            SYS_INIT_PHASE_FB_P    = SYS_INIT_PHASE_FB_ERR * SYS_INIT_PHASE_FB_KP;
            SYS_INIT_PHASE_FB_I    = SYS_INIT_PHASE_FB_ERR * SYS_INIT_PHASE_FB_KI + SYS_INIT_PHASE_FB_I;
            SYS_INIT_PHASE_FB_I    = fmod(SYS_INIT_PHASE_FB_I, 180.0f);
            SYS_INIT_PHASE_FB_VAL  = SYS_INIT_PHASE_FB_P   + SYS_INIT_PHASE_FB_I;
            /* Scale to DDS chip requirement */
            DDS_PHASE = SYS_INIT_PHASE_FB_VAL + 180.0f;
            cclk_dds_phase_value_wr(DDS_PHASE);
            /* End for loop */
            break;
         }
      }
   }
   else
   {
      SYS_INIT_PHASE_FB_I = 0.0f;
   }
}
