/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : adc16hl.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for accessing the features of the ADC16HL data
//           acquisition board.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "adc16hl.h"

void adc_ctrl_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_PGA_IDX);
   reg  = (data & 0x00000001) << 0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_PGA_IDX);
   reg |= (data & 0x00000001) << 1;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_PGA_IDX);
   reg |= (data & 0x00000001) << 2;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_PGA_IDX);
   reg |= (data & 0x00000001) << 3;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_PGA_IDX);
   reg |= (data & 0x00000001) << 4;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_PGA_IDX);
   reg |= (data & 0x00000001) << 5;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC_SHDN_IDX);
   reg |= (data & 0x00000001) << 6;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SYNC_IDX);
   reg |= (data & 0x00000001) << 7;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_GOE_IDX);
   reg |= (data & 0x00000001) << 8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SCK_OE_IDX);
   reg |= (data & 0x00000001) << 11;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x3E, (u16)(reg)); /* ADC-CTRL */
}

void clk_pd_en_sel_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x4000000E;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_PD_IDX);
   reg |= (data & 0x00000001) << 26;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_EN_IDX);
   reg |= (data & 0x00000001) << 27;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_SEL_IDX);
   reg |= (data & 0x00000001) << 29;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void clk_vboost_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00022A09;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_VBOOST_IDX);
   reg |= (data & 0x00000001) << 16;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void fpga_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010000;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_FPGA_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_FPGA_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_FPGA_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void pwr_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010003;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PWR_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PWR_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PWR_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc0_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010005;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc1_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010004;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc2_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg = 0x00010007;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc3_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010006;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc4_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010002;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc5_clk_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00010001;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_CLK_MUX_IDX);
   reg |= (data & 0x00000003) << 17;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_CLK_DIV_IDX);
   reg |= (data & 0x000000FF) <<  8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_CLK_DLY_IDX);
   reg |= (data & 0x0000000F) <<  4;
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(reg)); /* CLK-O */
}

void adc0_dac_wr(void)
{
   float dac;
   u32   data;
   u32   reg;

   dac  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_DAC_OFS_IDX));
   dac = dac * 1241.21f;
   reg  = (((u32) dac) & 0x00000FFF) <<  0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_DAC_MUX_IDX);
   reg |= (data & 0x00000007) <<  12;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x22, (u16)(reg)); /* ADC0-DAC-REG */
}

void adc1_dac_wr(void)
{
   float dac;
   u32   data;
   u32   reg;

   dac  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_DAC_OFS_IDX));
   dac = dac * 1241.21f;
   reg  = (((u32) dac) & 0x00000FFF) <<  0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_DAC_MUX_IDX);
   reg |= (data & 0x00000007) <<  12;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x26, (u16)(reg)); /* ADC1-DAC-REG */
}


void adc2_dac_wr(void)
{
   float dac;
   u32   data;
   u32   reg;

   dac  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_DAC_OFS_IDX));
   dac = dac * 1241.21f;
   reg  = (((u32) dac) & 0x00000FFF) <<  0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_DAC_MUX_IDX);
   reg |= (data & 0x00000007) <<  12;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x2A, (u16)(reg)); /* ADC2-DAC-REG */
}

void adc3_dac_wr(void)
{
   float dac;
   u32   data;
   u32   reg;

   dac  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_DAC_OFS_IDX));
   dac = dac * 1241.21f;
   reg  = (((u32) dac) & 0x00000FFF) <<  0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_DAC_MUX_IDX);
   reg |= (data & 0x00000007) <<  12;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x2E, (u16)(reg)); /* ADC3-DAC-REG */
}

void adc4_dac_wr(void)
{
   float dac;
   u32   data;
   u32   reg;

   dac  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_DAC_OFS_IDX));
   dac  = dac * 1241.21f;
   reg  = (((u32) dac) & 0x00000FFF) <<  0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_DAC_MUX_IDX);
   reg |= (data & 0x00000007) <<  12;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x32, (u16)(reg)); /* ADC4-DAC-REG */
}

void adc5_dac_wr(void)
{
   float dac;
   u32   data;
   u32   reg;

   dac  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_DAC_OFS_IDX));
   dac  = dac * 1241.21f;
   reg  = (((u32) dac) & 0x00000FFF) <<  0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_DAC_MUX_IDX);
   reg |= (data & 0x00000007) <<  12;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x36, (u16)(reg)); /* ADC5-DAC-REG */
}

void adc_sync_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC_SYNC_IDX);
   reg  = data;

   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ADC0_SYNC_IDX, (u8) (reg)); /* ADC0-SYNC */
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ADC1_SYNC_IDX, (u8) (reg)); /* ADC1-SYNC */
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ADC2_SYNC_IDX, (u8) (reg)); /* ADC2-SYNC */
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ADC3_SYNC_IDX, (u8) (reg)); /* ADC3-SYNC */
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ADC4_SYNC_IDX, (u8) (reg)); /* ADC4-SYNC */
   XIo_Out8 (XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ADC5_SYNC_IDX, (u8) (reg)); /* ADC5-SYNC */
}

void adc16hl_default(void)
{
   /* ADC0 clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* ADC1 clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* ADC2 clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* ADC3 clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* ADC4 clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* ADC5 clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* FPGA clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_FPGA_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_FPGA_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_FPGA_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* Power clock setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PWR_CLK_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := Bypassed; 1 := Divided; 2 := Delayed; 3 := Div. and Del. */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PWR_CLK_DIV_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* divider 1...255 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PWR_CLK_DLY_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* delay 150 ps steps 0...15 */
   /* Clock distribution chip various settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_VBOOST_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := no boosting; 1 := boosted */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_PD_IDX     + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := operating; 1 := power down */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_EN_IDX     + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := disabled; 1 := enabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CLK_SEL_IDX    + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := local; 1 := external (sma) */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_GOE_IDX        + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := enabled; 1 := disabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SYNC_IDX       + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := sync; 1 := done */
   /* Local 160 MHz oscillator chip various settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SCK_OE_IDX     + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := disabled; 1 := enabled */
   /* ADC chip various setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_PGA_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := gain 1; 1 := gain 1.5 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_PGA_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := gain 1; 1 := gain 1.5 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_PGA_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := gain 1; 1 := gain 1.5 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_PGA_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := gain 1; 1 := gain 1.5 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_PGA_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := gain 1; 1 := gain 1.5 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_PGA_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := gain 1; 1 := gain 1.5 */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC_SHDN_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := operating; 1 := shutdown */
   /* DAC analog offset setting */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_DAC_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 3); /* 0 := DAC; 1 := 1k GND; 2 := 100k GND; 3 := High Z */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_DAC_OFS_IDX + SYS_INIT_NO_IRQ_MASK, 1.25f); /* offset value V */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_DAC_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 3); /* 0 := DAC; 1 := 1k GND; 2 := 100k GND; 3 := High Z */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_DAC_OFS_IDX + SYS_INIT_NO_IRQ_MASK, 1.25f); /* offset value V */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_DAC_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 3); /* 0 := DAC; 1 := 1k GND; 2 := 100k GND; 3 := High Z */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_DAC_OFS_IDX + SYS_INIT_NO_IRQ_MASK, 1.25f); /* offset value V */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_DAC_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 3); /* 0 := DAC; 1 := 1k GND; 2 := 100k GND; 3 := High Z */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_DAC_OFS_IDX + SYS_INIT_NO_IRQ_MASK, 1.25f); /* offset value V */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_DAC_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 3); /* 0 := DAC; 1 := 1k GND; 2 := 100k GND; 3 := High Z */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_DAC_OFS_IDX + SYS_INIT_NO_IRQ_MASK, 1.25f); /* offset value V */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_DAC_MUX_IDX + SYS_INIT_NO_IRQ_MASK, 3); /* 0 := DAC; 1 := 1k GND; 2 := 100k GND; 3 := High Z */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_DAC_OFS_IDX + SYS_INIT_NO_IRQ_MASK, 1.25f); /* offset value V */
}

void adc16hl_init(void)
{
   u32   i;
   u32   data;
   u32   reg;

   /* Prepare ADCs and clock distribution chip for configuration */
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x3E, (u16)(0x0040)); /* ADC-CTRL = 0x0040 := ADC shut down, GOE = disable, SYNC = enabled */
   XIo_Out32(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x1C, (u32)(0x80000000)); /* CLK-O = 0x80000000 := Clock distribution RESET */
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   /* Clock distribution chip register R0 to R7 configuration (the following config. order matters) */
   fpga_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   adc5_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   adc4_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   pwr_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   adc1_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   adc0_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   adc3_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   adc2_clk_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   /* Clock distribution chip SPI register R9 settings */
   clk_vboost_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   /* Clock distribution chip SPI register R14 settings */
   clk_pd_en_sel_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   /* Configure ADC programmable gain, clock distribution global output and optional oscillator enable */
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC0_PGA_IDX);
   reg  = (data & 0x00000001) << 0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC1_PGA_IDX);
   reg |= (data & 0x00000001) << 1;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC2_PGA_IDX);
   reg |= (data & 0x00000001) << 2;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC3_PGA_IDX);
   reg |= (data & 0x00000001) << 3;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC4_PGA_IDX);
   reg |= (data & 0x00000001) << 4;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC5_PGA_IDX);
   reg |= (data & 0x00000001) << 5;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_ADC_SHDN_IDX);
   reg |= (data & 0x00000001) << 6;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_GOE_IDX);
   reg |= (data & 0x00000001) << 8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SCK_OE_IDX);
   reg |= (data & 0x00000001) << 11;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x3E, (u16)(reg)); /* ADC-CTRL */
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   /* Synchronize clock outputs (this is important if a clock divider was used) */
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SYNC_IDX);
   reg |= (data & 0x00000001) << 7;
   XIo_Out16(XPAR_PLB46_TO_FASTLINK_MMAP_INST_MEM0_BASEADDR + 0x3E, (u16)(reg)); /* ADC-CTRL */
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
   /* Configure offset DAC with value and output resistance */
   adc0_dac_wr();
   adc1_dac_wr();
   adc2_dac_wr();
   adc3_dac_wr();
   adc4_dac_wr();
   adc5_dac_wr();
   for (i = 0; i < 1000000; ++i) /* Wait for clock to stabilize */
   {
      asm("nop");
   }
}

/* EOF */
