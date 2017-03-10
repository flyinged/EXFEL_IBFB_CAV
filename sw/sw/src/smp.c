/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : smp.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.3 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for accessing the features of the FPGA BPM
//           calculation firmware.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "smp.h"

void smp_ena_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_ENA_IDX);
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ENA_IDX, (u8) reg); /* SMP-ENA */
}

void smp_mode_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_MODE_IDX);
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_MODE_IDX, (u8) (reg)); /* SMP-MODE */
}

void smp_b0_0_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_B0_0_IDX, (u16)(reg)); /* SMP-B0-0 */
}

void smp_b1_0_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B1_0_IDX);
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_B1_0_IDX, (u32)(reg)); /* SMP-B1-0 */
}

void smp_b2_0_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B2_0_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_B2_0_IDX, (u16)(reg)); /* SMP-B2-0 */
}

void smp_b3_0_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B3_0_IDX);
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_B3_0_IDX, (u32)(reg)); /* SMP-B3-0 */
}

void smp_s1_0_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_S1_0_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_S1_0_IDX, (u16)(reg)); /* SMP-S1-0 */
}

void smp_s1_1_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_S1_1_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_S1_1_IDX, (u16)(reg)); /* SMP-S1-1 */
}

void smp_s1_2_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_S1_2_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_S1_2_IDX, (u16)(reg)); /* SMP-S1-2 */
}

void smp_trig_val_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_TRIG_VAL_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_TRIG_VAL_IDX, (u16)(reg)); /* SMP-TRIG-VAL */
}

void bl_ena_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BL_ENA_IDX);
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BL_ENA_IDX, (u8) (reg)); /* BL-ENA */
}

void bl_exp_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BL_EXP_IDX);
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BL_EXP_IDX, (u8) (reg)); /* BL-EXP */
}

void bl_del_wr(void)
{
   u32   reg;

   reg = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BL_DEL_IDX);
   XIo_Out16(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BL_DEL_IDX, (u16)(reg)); /* BL-DEL */
}

void smp_default(void)
{
   /* MPS settings */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_Q_THR_IDX,    3.0f); /* MSP charge threshold 5 pC */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_Q_MIN_IDX,    0.0f); /* MSP min charge 0 pC */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_Q_MAX_IDX, 3000.0f); /* MSP max charge 3000 pC */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_X_MIN_IDX,  -10.0f); /* MSP min X position -10.0 mm */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_X_MAX_IDX,   10.0f); /* MSP max X position  10.0 mm */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_Y_MIN_IDX,  -10.0f); /* MSP min Y position -10.0 mm */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SYS_MPS_Y_MAX_IDX,   10.0f); /* MSP max Y position  10.0 mm */
   /* SMP settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_ENA_IDX      + SYS_INIT_NO_IRQ_MASK,         1); /* 0 := disabled; 1 := enabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_MODE_IDX     + SYS_INIT_NO_IRQ_MASK,         0); /* trigger 0 := external; 1 := internal */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_TRIG_VAL_IDX + SYS_INIT_NO_IRQ_MASK,     10000); /* trigger value if internal trigger mode */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX     + SYS_INIT_NO_IRQ_MASK,      2708); /* bunch timing B0.0 (number of bunches) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B1_0_IDX     + SYS_INIT_NO_IRQ_MASK,     49000); /* bunch timing B1.0 (train trigger delay to first sample enable window) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B2_0_IDX     + SYS_INIT_NO_IRQ_MASK,        36); /* bunch timing B2.0 (train trigger delay to next sample enable window) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B3_0_IDX     + SYS_INIT_NO_IRQ_MASK, 200000000); /* bunch timing B3.0 (train trigger timeout for first sample enable window) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_S1_0_IDX     + SYS_INIT_NO_IRQ_MASK,         4); /* bunch timing S1.0 (bunch trigger delay to first sample enable window) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_S1_1_IDX     + SYS_INIT_NO_IRQ_MASK,        32); /* bunch timing S1.1 (sample enable window) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_S1_2_IDX     + SYS_INIT_NO_IRQ_MASK,        16); /* bunch timing S1.2 (pretrigger samples if internal trigger mode) */
   /* SMP baseline calculation settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BL_ENA_IDX       + SYS_INIT_NO_IRQ_MASK,        1); /* 0 := disabled; 1 := enabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BL_EXP_IDX       + SYS_INIT_NO_IRQ_MASK,        5); /* power of 2 for number of samples used for baseline calculation */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BL_DEL_IDX       + SYS_INIT_NO_IRQ_MASK,       32); /* delay used for baseline calculation */
   /* Rotation calculation settings */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ROT11_IDX, 1.0); /* No rotation */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ROT12_IDX, 0.0); /* No rotation */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ROT21_IDX, 0.0); /* No rotation */
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ROT22_IDX, 1.0); /* No rotation */
   /* Charge threshold */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Q_FB_THR_IDX     + SYS_INIT_NO_IRQ_MASK,  3.0f);
   /* Average calculation */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Q_TRAIN_AVG_IDX  + SYS_INIT_NO_IRQ_MASK,  0.0f);
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_TRAIN_AVG_IDX  + SYS_INIT_NO_IRQ_MASK,  0.0f);
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_TRAIN_AVG_IDX  + SYS_INIT_NO_IRQ_MASK,  0.0f);
}

void smp_init(void)
{
   u32   i;

   /* Initialize RFFE */
   rffe_init();
   for (i = 0; i < 1000000; ++i) /* Wait for 8 ms for RFFE to stabilize */
   {
      asm("nop");
   }
   /* Initialize ADC16HL card */
   adc16hl_init();
   for (i = 0; i < 1000000; ++i) /* Wait for 8 ms for RFFE to stabilize */
   {
      asm("nop");
   }
   /* Initialize FPGA firmware */
   adc_sync_wr(); /* Synchronize ADCs to FPGA internal clock */
   for (i = 0; i < 1000000; ++i) /* Wait for 8 ms for RFFE to stabilize */
   {
      asm("nop");
   }
   /* Trigger */
   smp_mode_wr();     /* Set mode to FPGA */
   smp_trig_val_wr(); /* Set trigger value for self triggered mode and trigger to signal counter */
   /* Timing */
   smp_b0_0_wr();
   smp_b1_0_wr();
   smp_b2_0_wr();
   smp_b2_0_wr();
   smp_b3_0_wr();
   smp_s1_0_wr();
   smp_s1_1_wr();
   smp_s1_2_wr();
   /* Baseline calculation */
   bl_ena_wr();     /* Enable/disable */
   bl_exp_wr();     /* Exponent to be used */
   bl_del_wr();     /* Delay */
   /* Scaling */
   r_scale_wr();    /* Reference channel */
   x_scale_wr();    /* X channel */
   y_scale_wr();    /* y channel */
   /* Measurement start */
   smp_ena_wr();
}

/* EOF */
