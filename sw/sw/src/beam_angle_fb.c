/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : beam_angle_fb.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for scaling and correction of the measured, raw
//           charge and position by the firmware.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "beam_angle_fb.h"

void beam_angle_fb(void)
{
   /* Bunch counter */
   u32   i = 0;
   /* Requested bunches to measure */
   u32   SMP_B0_0 = 0;
   float Q_FB_THR = 1.0f;
   /* Beam angle feedback parameters */
   u32   PH_XY_R_OFS_FB_ON  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BA_FB_ENA_IDX);
   float PH_XY_R_OFS_FB_THR = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BA_FB_THR_IDX));
   if (isnanf(PH_XY_R_OFS_FB_THR))
   {
      PH_XY_R_OFS_FB_THR = 10.0f;
   }
   /* Measurements */
   float Q_RAW   = 0.0f;
   u32   Q_VALID = 0;
   s16   PH_REF_R = 0;
   float X_RAW = 0.0f;
   u32   X_VALID = 0;
   s16   PH_X_R = 0;
   float Y_RAW = 0.0f;
   u32   Y_VALID = 0;
   s16   PH_Y_R = 0;

   s16   PH_DIFF_R = 0;

   if (PH_XY_R_OFS_FB_ON == 1)
   {
      SMP_B0_0 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);
      Q_FB_THR = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Q_FB_THR_IDX);
      if (isnanf(Q_FB_THR))
      {
         Q_FB_THR = 1.0f;
      }
      for (i = 0; i < SMP_B0_0; ++i)
      {
         /* Read charge */
         Q_RAW   = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Q_BRAM_BASE       + (i * 4)); /* Get raw charge */
         Q_VALID = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Q_VALID_BRAM_BASE + (i * 4)); /* Get valid bit */
         if (isnanf(Q_RAW))
         {
            Q_RAW = 0.0f;
         }
         if ((Q_VALID == 1) && (Q_RAW > Q_FB_THR)) /* Ignore calculating the positions if invalid reading or almost no charge is measured... the positions may jump around then calculation almost 0, noisy position divided by almost 0, noisy charge */
         {
            /* Read reference phase */
            PH_REF_R = (s16) XIo_In16(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_R_PH_BRAM_BASE + (i * 4));
            /* Beam angle feedback for X */
            X_RAW   =  XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_X_BRAM_BASE       + (i * 4));
            X_VALID =  XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_X_VALID_BRAM_BASE + (i * 4));
            if (isnanf(X_RAW))
            {
               X_RAW = 0.0f;
            }
            if ((X_VALID == 1) && (((X_RAW > PH_XY_R_OFS_FB_THR) || (X_RAW < -PH_XY_R_OFS_FB_THR))))
            {
               PH_X_R = (s16) XIo_In16(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_X_PH_BRAM_BASE + (i * 4));
               PH_DIFF_R = PH_X_R - PH_REF_R;
               PH_DIFF_R = PH_DIFF_R % 11520; /* 180° in steps of 1/64 */
               if      (PH_DIFF_R <= -5760) /* -90° in steps of 1/64 */
               {
                  PH_DIFF_R = PH_DIFF_R + 11520; /* 180° in steps of 1/64 */
               }
               else if (PH_DIFF_R >=  5760) /* 90° in steps of 1/64 */
               {
                  PH_DIFF_R = PH_DIFF_R - 11520; /* 180° in steps of 1/64 */
               }
               XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BA_X_IDX, PH_DIFF_R);
            }
            /* Beam angle feedback for Y */
            Y_RAW   =  XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Y_BRAM_BASE       + (i * 4));
            Y_VALID =  XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Y_VALID_BRAM_BASE + (i * 4));
            if (isnanf(Y_RAW))
            {
               Y_RAW = 0.0f;
            }
            if ((Y_VALID == 1) && ((Y_RAW > PH_XY_R_OFS_FB_THR) || (Y_RAW < -PH_XY_R_OFS_FB_THR)))
            {
               PH_Y_R = (s16) XIo_In16(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Y_PH_BRAM_BASE + (i * 4));
               PH_DIFF_R = PH_Y_R - PH_REF_R;
               PH_DIFF_R = PH_DIFF_R % 11520; /* 180° in steps of 1/64 */
               if      (PH_DIFF_R <= -5760) /* -90° in steps of 1/64 */
               {
                  PH_DIFF_R = PH_DIFF_R + 11520; /* 180° in steps of 1/64 */
               }
               else if (PH_DIFF_R >=  5760) /* 90° in steps of 1/64 */
               {
                  PH_DIFF_R = PH_DIFF_R - 11520; /* 180° in steps of 1/64 */
               }
               XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BA_Y_IDX, PH_DIFF_R);
            }
            /* End for loop */
            break;
         }
      }
   }
}
