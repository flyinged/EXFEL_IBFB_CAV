/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : scaling.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for scaling and cleaning the measurement tables
//           in the firmware.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "scaling.h"

void scaling(void)
{
   /* Bunch counter */
   u32   i = 0;
   /* Requested bunches to measure */
   u32   SMP_B0_0 = 0;
   float Q_FB_THR = 1.0f;
   /* Measurements */
   u32   q_addr_val = 0;
   u32   x_addr_pos = 0;
   u32   y_addr_pos = 0;
   float Q_RAW = 0.0f;
   float Q_AVG = 0.0f;
   float Q_CNT = 0.0f;
   float X_RAW = 0.0f;
   float X_AVG = 0.0f;
   float X_CNT = 0.0f;
   float Y_RAW = 0.0f;
   float Y_AVG = 0.0f;
   float Y_CNT = 0.0f;

   /* Charge addresses */
   q_addr_val = XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Q_BRAM_BASE;
   /* Position addresses */
   x_addr_pos = XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_X_BRAM_BASE;
   y_addr_pos = XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_Y_BRAM_BASE;
   /* Load parameters and values and check valid range */
   SMP_B0_0 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);
   Q_FB_THR = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Q_FB_THR_IDX);
   if (isnanf(Q_FB_THR))
   {
      Q_FB_THR = 1.0f;
   }
   /* Do the scaling and correction */
   for (i = 0; i < 3072; ++i) /* For all possible position the the charge and position tables of the FPGA firmware */
   {
      if (i < SMP_B0_0) /* If charge and position is required for this bunch measurement */
      {
         /* Read charge */
         Q_RAW = XIo_Infs(q_addr_val); /* Get raw charge */
         if (isnanf(Q_RAW))
         {
            Q_RAW = 0.0f;
         }
         /* Clean memory from unnecessary jumping measurements */
         if (Q_RAW < Q_FB_THR) /* Ignore calculating the positions if almost no charge is measured... the positions may jump around then calculation almost 0, noisy position divided by almost 0, noisy charge */
         {
             /* Set too small position values to 0.0f */
             *(volatile float *)(x_addr_pos) = 0.0f;
             *(volatile float *)(y_addr_pos) = 0.0f;
         }
         else
         {
            Q_RAW = XIo_Infs(q_addr_val); /* Get raw charge */
            if (!(isnanf(Q_RAW)))
            {
               Q_AVG += Q_RAW;
               Q_CNT += 1.0f;
            }
            X_RAW = XIo_Infs(x_addr_pos); /* Get raw x position */
            if (!(isnanf(X_RAW)))
            {
               X_AVG += X_RAW;
               X_CNT += 1.0f;
            }
            Y_RAW = XIo_Infs(y_addr_pos); /* Get raw y position */
            if (!(isnanf(Y_RAW)))
            {
               Y_AVG += Y_RAW;
               Y_CNT += 1.0f;
            }
         }
      }
      else
      {
         /* Set unused positions to 0.0f */
         *(volatile float *)(q_addr_val) = 0.0f;
         *(volatile float *)(x_addr_pos) = 0.0f;
         *(volatile float *)(y_addr_pos) = 0.0f;
      }
      q_addr_val += 4;
      x_addr_pos += 4;
      y_addr_pos += 4;
   }

   /* Average calculation over relevant data of bunchtrain */
   if (Q_CNT > 0.0f)
   {
      Q_AVG /= Q_CNT;
   }
   else
   {
      Q_AVG = 0.0f;
   }
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Q_TRAIN_AVG_IDX  + SYS_INIT_NO_IRQ_MASK, Q_AVG);

   if (X_CNT > 0.0f)
   {
      X_AVG /= X_CNT;
   }
   else
   {
      X_AVG = 0.0f;
   }
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_TRAIN_AVG_IDX  + SYS_INIT_NO_IRQ_MASK, X_AVG);

   if (Y_CNT > 0.0f)
   {
      Y_AVG /= Y_CNT;
   }
   else
   {
      Y_AVG = 0.0f;
   }
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_TRAIN_AVG_IDX  + SYS_INIT_NO_IRQ_MASK, Y_AVG);
}
