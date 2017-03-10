/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : rffe.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for accessing the features of the 3.3 GHz cavity
//           RFFE board V3.1.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "rffe.h"

void r_mx_tmp_fbo_wr(void)
{
   float temp;
   u32   reg;

   temp = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_MX_TMP_FBO_IDX));
   temp = (temp + 30.7692f) / 0.004006f;
   reg  = (u32) temp;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_MX_TMP_FBO_IDX, (u32) reg); /* R-MX-TMP-FBO */
}

void r_rf_tmp_fbo_wr(void)
{
   float temp;
   u32   reg;

   temp = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_RF_TMP_FBO_IDX));
   temp = (temp + 30.7692f) / 0.004006f;
   reg  = (u32) temp;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_RF_TMP_FBO_IDX, (u32) reg); /* R-RF-TMP-FBO */
}

void x_mx_tmp_fbo_wr(void)
{
   float temp;
   u32   reg;

   temp = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_MX_TMP_FBO_IDX));
   temp = (temp + 30.7692f) / 0.004006f;
   reg  = (u32) temp;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_MX_TMP_FBO_IDX, (u32) reg); /* X-MX-TMP-FBO */
}

void x_rf_tmp_fbo_wr(void)
{
   float temp;
   u32   reg;

   temp = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_RF_TMP_FBO_IDX));
   temp = (temp + 30.7692f) / 0.004006f;
   reg  = (u32) temp;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_RF_TMP_FBO_IDX, (u32) reg); /* X-RF-TMP-FBO */
}

void y_mx_tmp_fbo_wr(void)
{
   float temp;
   u32   reg;

   temp = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_MX_TMP_FBO_IDX));
   temp = (temp + 30.7692f) / 0.004006f;
   reg  = (u32) temp;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_MX_TMP_FBO_IDX, (u32) reg); /* Y-MX-TMP-FBO */
}

void y_rf_tmp_fbo_wr(void)
{
   float temp;
   u32   reg;

   temp = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_RF_TMP_FBO_IDX));
   temp = (temp + 30.7692f) / 0.004006f;
   reg  = (u32) temp;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_RF_TMP_FBO_IDX, (u32) reg); /* Y-RF-TMP-FBO */
}

void lo_tmp_fbo_wr(void)
{
   float voltage;
   u32   reg;

   voltage = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_TMP_FBO_IDX));
   voltage = voltage / 0.0000625f;
   reg     = (u32) voltage;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_TMP_FBO_IDX, (u32) reg); /* LO-TMP-FBO */
}

void lo_pwr_o_wr(void)
{
   float voltage;
   u32   reg;

   voltage = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PWR_O_IDX));
   voltage = voltage / 0.0000625f;
   reg     = (u32) voltage;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PWR_O_IDX, (u32) reg); /* LO-PWR-O */
}

void lo_phase_value_wr(float phase)
{
   u32   reg;

   *(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PHASE_IDX + SYS_INIT_NO_IRQ_MASK) = phase;
   phase = phase / 0.0000625f;
   reg   = (u32) phase;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PHASE_IDX, (u32) reg); /* LO-PHASE */
}

void lo_phase_wr(void)
{
   float phase;
   u32   reg;

   phase = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PHASE_IDX));
   phase = phase / 0.0000625f;
   reg   = (u32) phase;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PHASE_IDX, (u32) reg); /* LO-PHASE */
}

void cclk_dds_iotoggle(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_RESET_IDX);
   reg = (data & 0x00000001) << 2;
   reg |= 0x00000002;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_GPIO_O_IDX, (u32) reg); /* CCLK-DDS-GPIO-O */
   reg &= ~0x00000002;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_GPIO_O_IDX, (u32) reg); /* CCLK-DDS-GPIO-O */
}

void cclk_dds_reset_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_RESET_IDX);
   reg = (data & 0x00000001) << 2;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_GPIO_O_IDX, (u32) reg); /* CCLK-DDS-GPIO-O */
}

void cclk_dds_cfr1_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_CFR1_IDX);
   reg = data;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_CFR1_IDX, (u32) reg); /* CCLK-DDS-CFR1 */
}

void cclk_dds_cfr2_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_CFR2_IDX);
   reg = data;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_CFR2_IDX, (u32) reg); /* CCLK-DDS-CFR2 */
}

void cclk_dds_dac_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_DAC_IDX);
   reg = data;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_DAC_IDX, (u32) reg); /* CCLK-DDS-DAC */
}

void cclk_dds_ftw_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_FTW_IDX);
   reg = data;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_FTW_IDX, (u32) reg); /* CCLK-DDS-FTW */
}

void cclk_dds_phase_value_wr(float phase)
{
   u32   data;
   u32   reg;

   *(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_PHASE_IDX + SYS_INIT_NO_IRQ_MASK) = phase;
   data   = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_R_IDX);
   phase *= 45.51111f * (float) data;
   data   = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_N_IDX);
   phase /= (float) data;
   reg    = (u32) phase;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_POW_IDX, (u32) reg); /* CCLK-DDS-POW */
   cclk_dds_iotoggle();
}

void cclk_dds_phase_wr(void)
{
   u32   data;
   u32   reg;
   float phase;

   phase  = (*(volatile float *)(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_PHASE_IDX));
   data   = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_R_IDX);
   phase *= 45.51111f * (float) data;
   data   = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_N_IDX);
   phase /= (float) data;
   reg = (u32) phase;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_POW_IDX, (u32) reg); /* CCLK-DDS-POW */
}

void cclk_pll_r_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00000000;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_R_IDX);
   reg |= (data & 0x00003FFF) << 2;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_PLL_SPI_O_IDX, (u32) reg); /* CCLK-PLL-SPI-O */
}

void cclk_pll_n_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00000001;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_N_IDX);
   reg |= (data & 0x00001FFF) << 8;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_PLL_SPI_O_IDX, (u32) reg); /* CCLK-PLL-SPI-O */
}

void cclk_pll_f23_mux_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x001F8002;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_MUX_IDX);
   reg |= (data & 0x00000007) << 4;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_F2_IDX);
   reg |= (data & 0x00000001) << 7;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_F3_IDX);
   reg |= (data & 0x00000001) << 8;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_PLL_SPI_O_IDX, (u32) reg); /* CCLK-PLL-SPI-O */
}

void dio_o_wr(void)
{
   u32   data;
   u32   reg;

   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_DIO_TMP_FB_IDX);
   reg  = (data & 0x00000001) << 0;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_DIO_INT_REF_IDX);
   reg |= (data & 0x00000001) << 2;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_DIO_O_IDX, (u32) reg); /* DIO-O */
}

void lo_pll_r_wr(void)
{
   u32   data;
   u32   reg;

   reg   = 0x00000000;
   data  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_R_IDX);
   reg  |= (data & 0x00003FFF) << 2;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PLL_SPI_O_IDX, (u32) reg); /* LO-PLL-SPI-O */
}

void lo_pll_ab_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x00000001;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_A_IDX);
   reg |= (data & 0x0000003F) << 2;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_B_IDX);
   reg |= (data & 0x00001FFF) << 8;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PLL_SPI_O_IDX, (u32) reg); /* LO-PLL-SPI-O */
}

void lo_pll_f23_mux_p_wr(void)
{
   u32   data;
   u32   reg;

   reg  = 0x001F8002;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_MUX_IDX);
   reg |= (data & 0x00000007) << 4;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_F2_IDX);
   reg |= (data & 0x00000001) << 7;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_F3_IDX);
   reg |= (data & 0x00000001) << 8;
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_P_IDX);
   reg |= (data & 0x00000003) << 22;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PLL_SPI_O_IDX, (u32) reg); /* LO-PLL-SPI-O */
}

void r_dsa_wr(u32 data)
{
   u32   reg;
   s32   phase;
   float ampl;

   /* Write attenuation */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX + SYS_INIT_NO_IRQ_MASK, (u32) data);
   /* Set DSA1 attenuator */
   if     (data < 19)
   {
      reg = 0;
   }
   else if(data < 50)
   {
      reg = data - 18;
   }
   else
   {
      reg = 31;
   }
   reg = ~(reg << 1) & 0x00000003F;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_ATT_O0_IDX, (u32) reg); /* R-DSA1 */
   /* Set DSA2 attenuator */
   if     (data < 18)
   {
      reg = data;
   }
   else if(data > 49)
   {
      reg = data - 49 + 18;
   }
   else
   {
      reg = 18;
   }
   reg  = ~(reg << 1) & 0x00000003F;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_ATT_O1_IDX, (u32) reg); /* R-DSA2 */
   /* Recalculate scaling */
   r_scale_wr();
   x_scale_wr();
   y_scale_wr();
   /* Attenuator calibration selection of table entry */
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_AC_R_IDX, data); /* R-DSA */
   /* Read back current phase correction setting */
   phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_PHASE_TABLE + (data * 4));
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_R_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, phase);
   /* Read back current amplitude correction setting */
   ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_AMPL_TABLE + (data * 4));
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_R_AMPL_IDX + SYS_INIT_NO_IRQ_MASK, ampl);
}

void x_dsa_wr(u32 data)
{
   u32   reg;
   s32   phase;
   float ampl;

   /* Write attenuation */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX + SYS_INIT_NO_IRQ_MASK, (u32) data);
   /* Set DSA1 attenuator */
   if     (data < 19)
   {
      reg = 0;
   }
   else if(data < 50)
   {
      reg = data - 18;
   }
   else
   {
      reg = 31;
   }
   reg  = ~(reg << 1) & 0x00000003F;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_ATT_O0_IDX, (u32) reg); /* X-DSA1 */
   /* Set DSA2 attenuator */
   if     (data < 18)
   {
      reg = data;
   }
   else if(data > 49)
   {
      reg = data - 49 + 18;
   }
   else
   {
      reg = 18;
   }
   reg  = ~(reg << 1) & 0x00000003F;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_ATT_O1_IDX, (u32) reg); /* X-DSA2 */
   /* Recalculate scaling */
   x_scale_wr();
   /* Attenuator calibration selection of table entry */
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_AC_X_IDX, data); /* X-DSA */
   /* Read back current phase correction setting */
   phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_PHASE_TABLE + (data * 4));
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_X_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, phase);
   /* Read back current amplitude correction setting */
   ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_AMPL_TABLE + (data * 4));
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_X_AMPL_IDX + SYS_INIT_NO_IRQ_MASK, ampl);
}

void y_dsa_wr(u32 data)
{
   u32   reg;
   s32   phase;
   float ampl;

   /* Write attenuation */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX + SYS_INIT_NO_IRQ_MASK, (u32) data);
   /* Set DSA1 attenuator */
   if     (data < 19)
   {
      reg = 0;
   }
   else if(data < 50)
   {
      reg = data - 18;
   }
   else
   {
      reg = 31;
   }
   reg  = ~(reg << 1) & 0x00000003F;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_ATT_O0_IDX, (u32) reg); /* Y-DSA1 */
   /* Set DSA2 attenuator */
   if     (data < 18)
   {
      reg = data;
   }
   else if(data > 49)
   {
      reg = data - 49 + 18;
   }
   else
   {
      reg = 18;
   }
   reg  = ~(reg << 1) & 0x00000003F;
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_ATT_O1_IDX, (u32) reg); /* Y-DSA2 */
   /* Recalculate scaling */
   y_scale_wr();
   /* Attenuator calibration selection of table entry */
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_AC_Y_IDX, data); /* Y-DSA */
   /* Read back current phase correction setting */
   phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_PHASE_TABLE + (data * 4));
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_Y_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, phase);
   /* Read back current amplitude correction setting */
   ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_AMPL_TABLE + (data * 4));
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_Y_AMPL_IDX + SYS_INIT_NO_IRQ_MASK, ampl);
}

void ib_r_index_wr(void)
{
   u32   index;
   s32   phase;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_INDEX_IDX);
   if (index < 360)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 4));
      XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, phase);
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 4));
      XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_AMPL_IDX + SYS_INIT_NO_IRQ_MASK, ampl);
   }
}

void ib_r_phase_wr(void)
{
   u32   index;
   s32   phase;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_INDEX_IDX);
   if (index < 360)
   {
      phase = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_PHASE_IDX);
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 4), phase);
   }
}

void ib_r_ampl_wr(void)
{
   u32   index;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_INDEX_IDX);
   if (index < 360)
   {
      ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_R_AMPL_IDX);
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 4), ampl);
   }
}

void ib_x_index_wr(void)
{
   u32   index;
   s32   phase;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_INDEX_IDX);
   if (index < 360)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 4));
      XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, phase);
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 4));
      XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_AMPL_IDX + SYS_INIT_NO_IRQ_MASK, ampl);
   }
}

void ib_x_phase_wr(void)
{
   u32   index;
   s32   phase;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_INDEX_IDX);
   if (index < 360)
   {
      phase = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_PHASE_IDX);
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 4), phase);
   }
}

void ib_x_ampl_wr(void)
{
   u32   index;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_INDEX_IDX);
   if (index < 360)
   {
      ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_X_AMPL_IDX);
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 4), ampl);
   }
}

void ib_y_index_wr(void)
{
   u32   index;
   s32   phase;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_INDEX_IDX);
   if (index < 360)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 4));
      XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, phase);
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 4));
      XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_AMPL_IDX + SYS_INIT_NO_IRQ_MASK, ampl);
   }
}

void ib_y_phase_wr(void)
{
   u32   index;
   s32   phase;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_INDEX_IDX);
   if (index < 360)
   {
      phase = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_PHASE_IDX);
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 4), phase);
   }
}

void ib_y_ampl_wr(void)
{
   u32   index;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_INDEX_IDX);
   if (index < 360)
   {
      ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_IB_Y_AMPL_IDX);
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 4), ampl);
   }
}

void ac_r_phase_wr(void)
{
   u32   index;
   s32   phase;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX);
   if (index < 64)
   {
      phase = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_R_PHASE_IDX);
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_PHASE_TABLE + (index * 4), phase);
   }
}

void ac_r_ampl_wr(void)
{
   u32   index;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX);
   if (index < 64)
   {
      ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_R_AMPL_IDX);
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_AMPL_TABLE + (index * 4), ampl);
   }
}

void ac_x_phase_wr(void)
{
   u32   index;
   s32   phase;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX);
   if (index < 64)
   {
      phase = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_X_PHASE_IDX);
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_PHASE_TABLE + (index * 4), phase);
   }
}

void ac_x_ampl_wr(void)
{
   u32   index;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX);
   if (index < 64)
   {
      ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_X_AMPL_IDX);
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_AMPL_TABLE + (index * 4), ampl);
   }
}

void ac_y_phase_wr(void)
{
   u32   index;
   s32   phase;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX);
   if (index < 64)
   {
      phase = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_Y_PHASE_IDX);
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_PHASE_TABLE + (index * 4), phase);
   }
}

void ac_y_ampl_wr(void)
{
   u32   index;
   float ampl;

   index = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX);
   if (index < 64)
   {
      ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_Y_AMPL_IDX);
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_AMPL_TABLE + (index * 4), ampl);
   }
}

void r_scale_wr(void)
{
   float scale;

   scale  = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_SCALE_EGU_IDX);
   scale *= XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_SCALE_IDX);
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_SCALE_R_IDX, scale);
}

void x_scale_wr(void)
{
   float scale;

   scale  = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_SCALE_EGU_IDX);
   scale *= XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_SCALE_IDX);
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_SCALE_X_IDX, scale);
}

void y_scale_wr(void)
{
   float scale;

   scale  = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_SCALE_EGU_IDX);
   scale *= XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_SCALE_IDX);
   XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_SCALE_Y_IDX, scale);
}

void rffe_eeprom_rd(void)
{
   u32 timeout;
   u32 fifo_empty;
   u32 index;
   u32 phase;
   u32 phase_0deg;
   u32 phase_8deg;
   float ampl_0deg;
   float ampl_8deg;
   float ampl;
   float value;

   /* Wait in order not to overload I2C */
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   /* Read R attenuator calibration phase from EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_R_PHASE_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface  */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      phase = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_R_PHASE_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_PHASE_TABLE + (index * 4), phase); /* Write to correction table */
   }
   /* Read R attenuator calibration amplitude from EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_R_AMPL_BASE_IDX  + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      ampl = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_R_AMPL_BASE_IDX  + (index * 4)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_AMPL_TABLE + (index * 4), ampl); /* Write to correction table */
   }

   /* Read X attenuator calibration phase from EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_X_PHASE_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      phase = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_X_PHASE_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_PHASE_TABLE + (index * 4), phase); /* Write to correction table */
   }
   /* Read X attenuator calibration amplitude from EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_X_AMPL_BASE_IDX  + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      ampl = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_X_AMPL_BASE_IDX  + (index * 4)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_AMPL_TABLE + (index * 4), ampl); /* Write to correction table */
   }
   /* Read Y attenuator calibration phase from EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_Y_PHASE_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      phase = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_Y_PHASE_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_PHASE_TABLE + (index * 4), phase); /* Write to correction table */
   }
   /* Read Y attenuator calibration amplitude from EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_Y_AMPL_BASE_IDX  + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      ampl = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_Y_AMPL_BASE_IDX  + (index * 4)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_AMPL_TABLE + (index * 4), ampl); /* Write to correction table */
   }

   /* Read I/Q imbalance R phase from EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_PHASE_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 44; ++index)
   {
      /* Read neighbouring EEPROM calibration values */
      phase_0deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_PHASE_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      if (index < 44)
      {
         phase_8deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_PHASE_BASE_IDX + ((index + 1) * 4)); /* Read from EEPROM i2c interface */
      }
      else
      {
         phase_8deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_PHASE_BASE_IDX); /* Read from EEPROM i2c interface */
      }
      /* Interpolation between stored EEPROM calibration values */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 +  0), (((phase_0deg*8)+(phase_8deg*0))/8)); /* Write to correction table + 0 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 +  4), (((phase_0deg*7)+(phase_8deg*1))/8)); /* Write to correction table + 1 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 +  8), (((phase_0deg*6)+(phase_8deg*2))/8)); /* Write to correction table + 2 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 + 12), (((phase_0deg*5)+(phase_8deg*3))/8)); /* Write to correction table + 3 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 + 16), (((phase_0deg*4)+(phase_8deg*4))/8)); /* Write to correction table + 4 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 + 20), (((phase_0deg*3)+(phase_8deg*5))/8)); /* Write to correction table + 5 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 + 24), (((phase_0deg*2)+(phase_8deg*6))/8)); /* Write to correction table + 6 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32 + 28), (((phase_0deg*1)+(phase_8deg*7))/8)); /* Write to correction table + 7 ° */
   }
   /* Read I/Q imbalance R amplitude from EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_AMPL_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 44; ++index)
   {
      /* Read neighbouring EEPROM calibration values */
      ampl_0deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_AMPL_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      if (index < 44)
      {
         ampl_8deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_AMPL_BASE_IDX + ((index + 1) * 4)); /* Read from EEPROM i2c interface */
      }
      else
      {
         ampl_8deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_AMPL_BASE_IDX); /* Read from EEPROM i2c interface */
      }
      /* Interpolation between stored EEPROM calibration values */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 +  0), (((ampl_0deg*8.0f)+(ampl_8deg*0.0f))/8.0f)); /* Write to correction table + 0 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 +  4), (((ampl_0deg*7.0f)+(ampl_8deg*1.0f))/8.0f)); /* Write to correction table + 1 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 +  8), (((ampl_0deg*6.0f)+(ampl_8deg*2.0f))/8.0f)); /* Write to correction table + 2 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 + 12), (((ampl_0deg*5.0f)+(ampl_8deg*3.0f))/8.0f)); /* Write to correction table + 3 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 + 16), (((ampl_0deg*4.0f)+(ampl_8deg*4.0f))/8.0f)); /* Write to correction table + 4 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 + 20), (((ampl_0deg*3.0f)+(ampl_8deg*5.0f))/8.0f)); /* Write to correction table + 5 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 + 24), (((ampl_0deg*2.0f)+(ampl_8deg*6.0f))/8.0f)); /* Write to correction table + 6 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32 + 28), (((ampl_0deg*1.0f)+(ampl_8deg*7.0f))/8.0f)); /* Write to correction table + 7 ° */
   }

   /* Read I/Q imbalance X phase from EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_PHASE_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 44; ++index)
   {
      /* Read neighbouring EEPROM calibration values */
      phase_0deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_PHASE_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      if (index < 44)
      {
         phase_8deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_PHASE_BASE_IDX + ((index + 1) * 4)); /* Read from EEPROM i2c interface */
      }
      else
      {
         phase_8deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_PHASE_BASE_IDX); /* Read from EEPROM i2c interface */
      }
      /* Interpolation between stored EEPROM calibration values */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 +  0), (((phase_0deg*8)+(phase_8deg*0))/8)); /* Write to correction table + 0 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 +  4), (((phase_0deg*7)+(phase_8deg*1))/8)); /* Write to correction table + 1 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 +  8), (((phase_0deg*6)+(phase_8deg*2))/8)); /* Write to correction table + 2 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 + 12), (((phase_0deg*5)+(phase_8deg*3))/8)); /* Write to correction table + 3 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 + 16), (((phase_0deg*4)+(phase_8deg*4))/8)); /* Write to correction table + 4 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 + 20), (((phase_0deg*3)+(phase_8deg*5))/8)); /* Write to correction table + 5 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 + 24), (((phase_0deg*2)+(phase_8deg*6))/8)); /* Write to correction table + 6 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32 + 28), (((phase_0deg*1)+(phase_8deg*7))/8)); /* Write to correction table + 7 ° */
}

   /* Read I/Q imbalance X amplitude from EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_AMPL_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 44; ++index)
   {
      /* Read neighbouring EEPROM calibration values */
      ampl_0deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_AMPL_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      if (index < 44)
      {
         ampl_8deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_AMPL_BASE_IDX + ((index + 1) * 4)); /* Read from EEPROM i2c interface */
      }
      else
      {
         ampl_8deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_AMPL_BASE_IDX); /* Read from EEPROM i2c interface */
      }
      /* Interpolation between stored EEPROM calibration values */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 +  0), (((ampl_0deg*8.0f)+(ampl_8deg*0.0f))/8.0f)); /* Write to correction table + 0 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 +  4), (((ampl_0deg*7.0f)+(ampl_8deg*1.0f))/8.0f)); /* Write to correction table + 1 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 +  8), (((ampl_0deg*6.0f)+(ampl_8deg*2.0f))/8.0f)); /* Write to correction table + 2 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 + 12), (((ampl_0deg*5.0f)+(ampl_8deg*3.0f))/8.0f)); /* Write to correction table + 3 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 + 16), (((ampl_0deg*4.0f)+(ampl_8deg*4.0f))/8.0f)); /* Write to correction table + 4 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 + 20), (((ampl_0deg*3.0f)+(ampl_8deg*5.0f))/8.0f)); /* Write to correction table + 5 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 + 24), (((ampl_0deg*2.0f)+(ampl_8deg*6.0f))/8.0f)); /* Write to correction table + 6 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32 + 28), (((ampl_0deg*1.0f)+(ampl_8deg*7.0f))/8.0f)); /* Write to correction table + 7 ° */
   }

   /* Read I/Q imbalance Y phase from EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_PHASE_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 63; ++index)
   {
      /* Read neighbouring EEPROM calibration values */
      phase_0deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_PHASE_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      if (index < 44)
      {
         phase_8deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_PHASE_BASE_IDX + ((index + 1) * 4)); /* Read from EEPROM i2c interface */
      }
      else
      {
         phase_8deg = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_PHASE_BASE_IDX); /* Read from EEPROM i2c interface */
      }
      /* Interpolation between stored EEPROM calibration values */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 +  0), (((phase_0deg*8)+(phase_8deg*0))/8)); /* Write to correction table + 0 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 +  4), (((phase_0deg*7)+(phase_8deg*1))/8)); /* Write to correction table + 1 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 +  8), (((phase_0deg*6)+(phase_8deg*2))/8)); /* Write to correction table + 2 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 + 12), (((phase_0deg*5)+(phase_8deg*3))/8)); /* Write to correction table + 3 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 + 16), (((phase_0deg*4)+(phase_8deg*4))/8)); /* Write to correction table + 4 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 + 20), (((phase_0deg*3)+(phase_8deg*5))/8)); /* Write to correction table + 5 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 + 24), (((phase_0deg*2)+(phase_8deg*6))/8)); /* Write to correction table + 6 ° */
      XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32 + 28), (((phase_0deg*1)+(phase_8deg*7))/8)); /* Write to correction table + 7 ° */
   }

   /* Read I/Q imbalance Y amplitude from EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_AMPL_BASE_IDX + (index * 4) + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   }
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   for (index = 0; index <= 44; ++index)
   {
      /* Read neighbouring EEPROM calibration values */
      ampl_0deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_AMPL_BASE_IDX + (index * 4)); /* Read from EEPROM i2c interface */
      if (index < 44)
      {
         ampl_8deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_AMPL_BASE_IDX + ((index + 1) * 4)); /* Read from EEPROM i2c interface */
      }
      else
      {
         ampl_8deg = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_AMPL_BASE_IDX); /* Read from EEPROM i2c interface */
      }
      /* Interpolation between stored EEPROM calibration values */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 +  0), (((ampl_0deg*8.0f)+(ampl_8deg*0.0f))/8.0f)); /* Write to correction table + 0 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 +  4), (((ampl_0deg*7.0f)+(ampl_8deg*1.0f))/8.0f)); /* Write to correction table + 1 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 +  8), (((ampl_0deg*6.0f)+(ampl_8deg*2.0f))/8.0f)); /* Write to correction table + 2 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 + 12), (((ampl_0deg*5.0f)+(ampl_8deg*3.0f))/8.0f)); /* Write to correction table + 3 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 + 16), (((ampl_0deg*4.0f)+(ampl_8deg*4.0f))/8.0f)); /* Write to correction table + 4 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 + 20), (((ampl_0deg*3.0f)+(ampl_8deg*5.0f))/8.0f)); /* Write to correction table + 5 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 + 24), (((ampl_0deg*2.0f)+(ampl_8deg*6.0f))/8.0f)); /* Write to correction table + 6 ° */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32 + 28), (((ampl_0deg*1.0f)+(ampl_8deg*7.0f))/8.0f)); /* Write to correction table + 7 ° */
   }

   /* Read scaling defaults */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_SCALE_EGU_IDX + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_SCALE_IDX     + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_SCALE_EGU_IDX + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_SCALE_IDX     + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_SCALE_EGU_IDX + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_SCALE_IDX     + RFFE_READ_BACK_MASK, 1); /* Read back from EEPROM to i2c interface */
   timeout = 0;
   while ((((fifo_empty = XIo_In32(XPAR_PLB46_TO_IIC_MMAP_INST_BASEADDR)) & 0x00000001) != 0x00000001) && (timeout < 100000))
   {
      asm("nop");
      timeout++;
   }
   /* Set scaling defaults */
   value = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_SCALE_EGU_IDX); /* Read from EEPROM */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_SCALE_EGU_IDX + SYS_INIT_NO_IRQ_MASK, value);

   value = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_SCALE_IDX); /* Read from EEPROM */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_SCALE_IDX + SYS_INIT_NO_IRQ_MASK, value);

   value = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_SCALE_EGU_IDX); /* Read from EEPROM */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_SCALE_EGU_IDX + SYS_INIT_NO_IRQ_MASK, value);

   value = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_SCALE_IDX); /* Read from EEPROM */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_SCALE_IDX + SYS_INIT_NO_IRQ_MASK, value);

   value = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_SCALE_EGU_IDX); /* Read from EEPROM */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_SCALE_EGU_IDX + SYS_INIT_NO_IRQ_MASK, value);

   value = XIo_Infs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_SCALE_IDX); /* Read from EEPROM */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_SCALE_IDX + SYS_INIT_NO_IRQ_MASK, value);
}

void rffe_eeprom_wr(void)
{
   u32 i;
   u32 index;
   u32 phase;
   float ampl;

   /* Write new scaling defaults to EEPROM */
   ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_SCALE_EGU_IDX);
   XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_SCALE_EGU_IDX, ampl); /* Write RFFE_R_SCALE_EGU to EEPROM */
   for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
   {
      asm("nop");
   }
   ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_SCALE_IDX);
   XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_SCALE_IDX, ampl);     /* Write RFFE_R_SCALE to EEPROM */
   for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
   {
      asm("nop");
   }
   ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_SCALE_EGU_IDX);
   XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_SCALE_EGU_IDX, ampl); /* Write RFFE_X_SCALE_EGU to EEPROM */
   for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
   {
      asm("nop");
   }
   ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_SCALE_IDX);
   XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_SCALE_IDX, ampl);     /* Write RFFE_X_SCALE to EEPROM */
   for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
   {
      asm("nop");
   }
   ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_SCALE_EGU_IDX);
   XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_SCALE_EGU_IDX, ampl); /* Write RFFE_Y_SCALE_EGU to EEPROM */
   for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
   {
      asm("nop");
   }
   ampl = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_SCALE_IDX);
   XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_SCALE_IDX, ampl);     /* Write RFFE_Y_SCALE to EEPROM */
   for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
   {
      asm("nop");
   }
   /* Write R attenuator calibration phase to EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_PHASE_TABLE + (index * 4)); /* Read from phase correction table */
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_R_PHASE_BASE_IDX + (index * 4), phase); /* Write to EEPROM AC-R-PHASE */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
   /* Write R attenuator calibration amplitude to EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_AMPL_TABLE + (index * 4)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_R_AMPL_BASE_IDX  + (index * 4), ampl); /* Write to EEPROM AC-R-AMPL */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }

   /* Write X attenuator calibration phase to EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_PHASE_TABLE + (index * 4)); /* Read from phase correction table */
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_X_PHASE_BASE_IDX + (index * 4), phase); /* Write to EEPROM AC-X-PHASE */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
   /* Write X attenuator calibration amplitude to EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_AMPL_TABLE + (index * 4)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_X_AMPL_BASE_IDX  + (index * 4), ampl); /* Write to EEPROM AC-X-AMPL */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }

   /* Write Y attenuator calibration phase to EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_PHASE_TABLE + (index * 4)); /* Read from phase correction table */
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_Y_PHASE_BASE_IDX + (index * 4), phase); /* Write to EEPROM AC-Y-PHASE */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
   /* Write Y attenuator calibration amplitude to EEPROM */
   for (index = 0; index <= 63; ++index)
   {
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_AMPL_TABLE + (index * 4)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_AC_Y_AMPL_BASE_IDX  + (index * 4), ampl); /* Write to EEPROM AC-Y-AMPL */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }

   /* Write I/Q imbalance R phase to EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 32)); /* Read from phase correction table */
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_PHASE_BASE_IDX + (index * 4), phase); /* Write to EEPROM IB-R-PHASE */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
   /* Write I/Q imbalance R amplitude to EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 32)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_R_AMPL_BASE_IDX  + (index * 4), ampl); /* Write to EEPROM IB-R-AMPL */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }

   /* Write I/Q imbalance X phase to EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 32)); /* Read from phase correction table */
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_PHASE_BASE_IDX + (index * 4), phase); /* Write to EEPROM IB-X-PHASE */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
   /* Write I/Q imbalance X amplitude to EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 32)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_X_AMPL_BASE_IDX  + (index * 4), ampl); /* Write to EEPROM IB-X-AMPL */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }

   /* Write I/Q imbalance Y phase to EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 32)); /* Read from phase correction table */
      XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_PHASE_BASE_IDX + (index * 4), phase); /* Write to EEPROM IB-Y-PHASE */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
   /* Write I/Q imbalance Y amplitude to EEPROM */
   for (index = 0; index <= 44; ++index)
   {
      ampl = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 32)); /* Read from amplitude correction table */
      XIo_Outfs(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_IB_Y_AMPL_BASE_IDX  + (index * 4), ampl); /* Write to EEPROM IB-Y-AMPL */
      for (i = 0; i < 625000; ++i) /* Wait for at least tWC = 5 ms for EEPROM Programming */
      {
         asm("nop");
      }
   }
}

void rffe_default(void)
{
   u32   index;
   float ac_attenuator;
   float ac_value;

   /* DIO-TMP-FB RFFE temperature regulation */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_DIO_TMP_FB_IDX  + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := feedback; 1 := control */
   /* DIO-INT-REF RFFE local oscillator */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_DIO_INT_REF_IDX + SYS_INIT_NO_IRQ_MASK, 0); /* 0 := off; 1 := on */
   /* R-DSA */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX       + SYS_INIT_NO_IRQ_MASK, 32); /* 0...62 dB */
   /* X-DSA */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX       + SYS_INIT_NO_IRQ_MASK, 32); /* 0...62 dB */
   /* Y-DSA */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX       + SYS_INIT_NO_IRQ_MASK, 32); /* 0...62 dB */
   /* LO-PHASE phase shifter by means of a DAC */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PHASE_IDX    + SYS_INIT_NO_IRQ_MASK, 0.0f); /* 0.0...4.0 Volt */
   /* LO-PLL settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_R_IDX    + SYS_INIT_NO_IRQ_MASK, 24); /* R factor */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_A_IDX    + SYS_INIT_NO_IRQ_MASK, 14); /* A factor */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_B_IDX    + SYS_INIT_NO_IRQ_MASK, 22); /* B factor */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_MUX_IDX  + SYS_INIT_NO_IRQ_MASK,  1); /* MUX 0 := TRI-STATE; 1 := LOCK DET.; 2 := N DIV.; 3 := DVDD; 4 := R DIV.; 5 := N CH LOCK; 6 := SDO; 7 := DGND*/
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_F2_IDX   + SYS_INIT_NO_IRQ_MASK,  1); /* F2 0 := negative; 1 := positive */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_F3_IDX   + SYS_INIT_NO_IRQ_MASK,  0); /* F3 0 := normal; 1 := tri state */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PLL_P_IDX    + SYS_INIT_NO_IRQ_MASK,  1); /* P factor 0 := 8/9; 1 := 16/17; 2 := 32/33; 3 := 64/65 */
   /* CCLK-DDS settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_CFR1_IDX  + SYS_INIT_NO_IRQ_MASK, 0x00000000); /* DDS CFR1 register */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_CFR2_IDX  + SYS_INIT_NO_IRQ_MASK, 0x00001432); /* DDS CFR2 register */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_DAC_IDX   + SYS_INIT_NO_IRQ_MASK, 0x007F13FF); /* DDS DAC register */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_FTW_IDX   + SYS_INIT_NO_IRQ_MASK, 0x20000000); /* DDS FTW register */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_PHASE_IDX + SYS_INIT_NO_IRQ_MASK, 0.0f);       /* DDS phase */
   /* CCLK-PLL settings */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_R_IDX   + SYS_INIT_NO_IRQ_MASK,  1); /* R factor */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_N_IDX   + SYS_INIT_NO_IRQ_MASK,  6); /* N factor */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_MUX_IDX + SYS_INIT_NO_IRQ_MASK,  1); /* MUX 0 := TRI-STATE; 1 := LOCK DET.; 2 := N DIV.; 3 := DVDD; 4 := R DIV.; 5 := N CH LOCK; 6 := SDO; 7 := DGND*/
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_F2_IDX  + SYS_INIT_NO_IRQ_MASK,  1); /* F2 0 := negative; 1 := positive */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_PLL_F3_IDX  + SYS_INIT_NO_IRQ_MASK,  0); /* F3 0 := normal; 1 := tri state */
   /* TMP-FB-INIT */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_RF_TMP_FBO_IDX + SYS_INIT_NO_IRQ_MASK, 45.0f); /* RF part temperature setting °C*/
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_MX_TMP_FBO_IDX + SYS_INIT_NO_IRQ_MASK, 45.0f); /* MX part temperature setting °C*/
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_RF_TMP_FBO_IDX + SYS_INIT_NO_IRQ_MASK, 45.0f); /* RF part temperature setting °C*/
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_MX_TMP_FBO_IDX + SYS_INIT_NO_IRQ_MASK, 45.0f); /* MX part temperature setting °C*/
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_RF_TMP_FBO_IDX + SYS_INIT_NO_IRQ_MASK, 45.0f); /* RF part temperature setting °C*/
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_MX_TMP_FBO_IDX + SYS_INIT_NO_IRQ_MASK, 45.0f); /* MX part temperature setting °C*/
   /* Angle correction */
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BA_ENA_IDX, 1);                                    /* BA-ENA correction switched on */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BA_FB_ENA_IDX + SYS_INIT_NO_IRQ_MASK, 1);     /* BA-FB-ENA correction switched on */
   XIo_Outfs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BA_FB_THR_IDX + SYS_INIT_NO_IRQ_MASK, 10.0f); /* BA-FB-THR set to 2.0 */
   /* Load the default values to the attenuator calibration table */
   ac_attenuator = 0.0f;
   for (index = 64; index <= 127; ++index)
   {
      ac_value = powf(10, ((ac_attenuator - 63.0f)/20.0f));
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_R_AMPL_TABLE + (index * 4), ac_value); /* Write to correction table */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_X_AMPL_TABLE + (index * 4), ac_value); /* Write to correction table */
      XIo_Outfs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_AC_Y_AMPL_TABLE + (index * 4), ac_value); /* Write to correction table */
      ac_attenuator += 1.0f;
   }
}

void rffe_init(void)
{
   u32   i;
   u32   data;

   /* Wait for 64 ms for RFFE to have stabilized the power supply */
   for (i = 0; i < 8000000; ++i)
   {
      asm("nop");
   }
   /* Shut down the LM73 in order to fix latch up of chip due to slow power up */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_I_TMP_CFG_IDX, (u32) 0x000000C0); /* R-I-TMP-CFG = 0xC0 := B7:Full Power Down:1:power down, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_Q_TMP_CFG_IDX, (u32) 0x000000C0); /* R-Q-TMP-CFG = 0xC0 := B7:Full Power Down:1:power down, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_I_TMP_CFG_IDX, (u32) 0x000000C0); /* X-I-TMP-CFG = 0xC0 := B7:Full Power Down:1:power down, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_O_TMP_CFG_IDX, (u32) 0x000000C0); /* X-Q-TMP-CFG = 0xC0 := B7:Full Power Down:1:power down, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_I_TMP_CFG_IDX, (u32) 0x000000C0); /* Y-I-TMP-CFG = 0xC0 := B7:Full Power Down:1:power down, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_Q_TMP_CFG_IDX, (u32) 0x000000C0); /* Y-Q-TMP-CFG = 0xC0 := B7:Full Power Down:1:power down, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   for (i = 0; i < 2000000; ++i) /* Wait for 16 ms for shut down to be active. This is a data sheet requirement for slow power supply ramp up */
   {
      asm("nop");
   }
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_I_TMP_CFG_IDX, (u32) 0x00000040); /* R-I-TMP-CFG = 0x40 := B7:Full Power Down:0:power up, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_Q_TMP_CFG_IDX, (u32) 0x00000040); /* R-Q-TMP-CFG = 0x40 := B7:Full Power Down:0:power up, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_I_TMP_CFG_IDX, (u32) 0x00000040); /* X-I-TMP-CFG = 0x40 := B7:Full Power Down:0:power up, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_O_TMP_CFG_IDX, (u32) 0x00000040); /* X-Q-TMP-CFG = 0x40 := B7:Full Power Down:0:power up, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_I_TMP_CFG_IDX, (u32) 0x00000040); /* Y-I-TMP-CFG = 0x40 := B7:Full Power Down:0:power up, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_Q_TMP_CFG_IDX, (u32) 0x00000040); /* Y-Q-TMP-CFG = 0x40 := B7:Full Power Down:0:power up, B6:reserved:1:recommended, B5:ALERT Enable:0:enable, B4:ALERT Polarity:0:active-low, B3:ALERT Reset:0:keep it, B2:One Shot:0:continous, B1-0:Reserved:00:recommended */
   /* RFFE-ADC-INIT */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_ADC_CTRL_IDX, (u32) 0x000000A2); /* ADC-CTRL = 0xA2 := B7:REG:1:setup byte, B6-4:SEL:010:External reference and AIN_/REF reference input, B3:CLK:0:internal clock, B2:BIP/UNI_B:0:unipolar, B1:RST_B:1:no reset, B0:X:0:meaning less */
   /* TMP-INIT LM73 */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_I_TMP_CTRL_IDX, (u32) 0x00000068); /* R-I-TMP-CTRL = 0x68 := B7:TO_DIS:0:Enable, B6-5:RES:11:0.03125°C/LSB, B4:reserved:0:recommended, B3:ALRT_STAT:1:ALERT output pin is high, B2:THI:0:recommended, B1:TLOW:0:recommended, DAV:0:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_Q_TMP_CTRL_IDX, (u32) 0x00000068); /* R-Q-TMP-CTRL = 0x68 := B7:TO_DIS:0:Enable, B6-5:RES:11:0.03125°C/LSB, B4:reserved:0:recommended, B3:ALRT_STAT:1:ALERT output pin is high, B2:THI:0:recommended, B1:TLOW:0:recommended, DAV:0:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_I_TMP_CTRL_IDX, (u32) 0x00000068); /* X-I-TMP-CTRL = 0x68 := B7:TO_DIS:0:Enable, B6-5:RES:11:0.03125°C/LSB, B4:reserved:0:recommended, B3:ALRT_STAT:1:ALERT output pin is high, B2:THI:0:recommended, B1:TLOW:0:recommended, DAV:0:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_O_TMP_CTRL_IDX, (u32) 0x00000068); /* X-Q-TMP-CTRL = 0x68 := B7:TO_DIS:0:Enable, B6-5:RES:11:0.03125°C/LSB, B4:reserved:0:recommended, B3:ALRT_STAT:1:ALERT output pin is high, B2:THI:0:recommended, B1:TLOW:0:recommended, DAV:0:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_I_TMP_CTRL_IDX, (u32) 0x00000068); /* Y-I-TMP-CTRL = 0x68 := B7:TO_DIS:0:Enable, B6-5:RES:11:0.03125°C/LSB, B4:reserved:0:recommended, B3:ALRT_STAT:1:ALERT output pin is high, B2:THI:0:recommended, B1:TLOW:0:recommended, DAV:0:recommended */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_Q_TMP_CTRL_IDX, (u32) 0x00000068); /* Y-Q-TMP-CTRL = 0x68 := B7:TO_DIS:0:Enable, B6-5:RES:11:0.03125°C/LSB, B4:reserved:0:recommended, B3:ALRT_STAT:1:ALERT output pin is high, B2:THI:0:recommended, B1:TLOW:0:recommended, DAV:0:recommended */
   /* TMP-INIT DAC */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_DAC1_INIT_IDX, (u32) 0x00000000); /* DAC1-INIT = 0 := B15-5:X:0:not used, B4:AR:0:Disable internal reference, B3-0:X:0:not used */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_DAC2_INIT_IDX, (u32) 0x00000000); /* DAC1-INIT = 0 := B15-5:X:0:not used, B4:AR:0:Disable internal reference, B3-0:X:0:not used */
   /* DIO-INIT */
   dio_o_wr();
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_DIO_POL_IDX, (u32) 0x00000000); /* DIO-POL = 0x00 := B7-4:X:"0000":not used, B3-0:N:"0000":Input Port register data retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_DIO_CFG_IDX, (u32) 0x00000002); /* DIO-CFG = 0x02 := B7-4:X:"0000":not used, B3:C3:"0":Enabled as an output, B2:C2:"0":Enabled as an output, B1:C1:"1":Enabled as an input, B0:C0:"0":Enabled as an output */
   /* R-ATT-INIT */
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX); /* R-DSA */
   r_dsa_wr(data);
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_ATT_P0_IDX, (u32) 0x00); /* R-ATT-P0 = 0x00 := B7-0:N0:"00000000":Input port data polarity is retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_ATT_P1_IDX, (u32) 0x00); /* R-ATT-P1 = 0x00 := B7-0:N0:"00000000":Input port data polarity is retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_ATT_C0_IDX, (u32) 0x00); /* R-ATT-C0 = 0x00 := B7-0:C0:"00000000":Port pin is enabled as an output */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_R_ATT_C1_IDX, (u32) 0x00); /* R-ATT-C1 = 0x00 := B7-0:C0:"00000000":Port pin is enabled as an output */
   /* X-ATT-INIT */
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX); /* X-DSA */
   x_dsa_wr(data);
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_ATT_P0_IDX, (u32) 0x00); /* X-ATT-P0 = 0x00 := B7-0:N0:"00000000":Input port data polarity is retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_ATT_P1_IDX, (u32) 0x00); /* X-ATT-P1 = 0x00 := B7-0:N0:"00000000":Input port data polarity is retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_ATT_C0_IDX, (u32) 0x00); /* X-ATT-C0 = 0x00 := B7-0:C0:"00000000":Port pin is enabled as an output */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_X_ATT_C1_IDX, (u32) 0x00); /* X-ATT-C1 = 0x00 := B7-0:C0:"00000000":Port pin is enabled as an output */
   /* Y-ATT-INIT */
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX); /* Y-DSA */
   y_dsa_wr(data);
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_ATT_P0_IDX, (u32) 0x00); /* Y-ATT-P0 = 0x00 := B7-0:N0:"00000000":Input port data polarity is retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_ATT_P1_IDX, (u32) 0x00); /* Y-ATT-P1 = 0x00 := B7-0:N0:"00000000":Input port data polarity is retained */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_ATT_C0_IDX, (u32) 0x00); /* Y-ATT-C0 = 0x00 := B7-0:C0:"00000000":Port pin is enabled as an output */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_Y_ATT_C1_IDX, (u32) 0x00); /* Y-ATT-C1 = 0x00 := B7-0:C0:"00000000":Port pin is enabled as an output */
   /* LO-PLL-INIT */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PLL_GPIO_CFG_IDX, (u32) 0xA9); /* LO-PLL-GPIO-CFG = 0xA9 := B7-6:SS3:"10":input-only (high-impedance), B5-4:SS2:"10":input-only (high-impedance), B3-2:SS1:"10":input-only (high-impedance), B1-0:SS0:"01":push-pull */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PLL_GPIO_ENA_IDX, (u32) 0x02); /* LO-PLL-GPIO-ENA = 0x02 := B7-4:X:"0000":not used, B3:SS3:0:disable GPIO, B2:SS2:0:disable GPIO, B1:SS1:1:enable GPIO, B0:SS0:0:disable GPIO */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_LO_PLL_SPI_CFG_IDX,  (u32) 0x01); /* LO-PLL-SPI-CFG  = 0x01 := B7-6:X:"00":reserved, B5:ORDER:"0":MSB of the data word is transmitted first, B4:X:"0":reserved, B3-2:MODE:"00":CPOL = 0 CPHA = 0, B1-0:F:"01":SPI clock rate 461 kHz */
   /* CCLK-DDS-INIT */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_GPIO_O_IDX,   (u32) 0x04); /* CCLK-DDS-GPIO-O   = 0x04 := Reset DDS chip */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_GPIO_CFG_IDX, (u32) 0x95); /* CCLK-DDS-GPIO-CFG = 0x95 := B7-6:SS3:"10":input-only (high-impedance), B5-4:SS2:"01":push-pull, B3-2:SS1:"01":push-pull, B1-0:SS0:"01":push-pull */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_GPIO_ENA_IDX, (u32) 0x06); /* CCLK-DDS-GPIO-ENA = 0x06 := B7-4:X:"0000":not used, B3:SS3:0:disable GPIO, B2:SS2:1:enable GPIO, B1:SS1:1:enable GPIO, B0:SS0:0:disable GPIO */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_DDS_SPI_CFG_IDX,  (u32) 0x00); /* CCLK-DDS-SPI-CFG  = 0x00 := B7-6:X:"00":reserved, B5:ORDER:"0":MSB of the data word is transmitted first, B4:X:"0":reserved, B3-2:MODE:"00":CPOL = 0 CPHA = 0, B1-0:F:"08":SPI clock rate 1843 kHz */
   /* CCLK-PLL-INIT */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_PLL_GPIO_CFG_IDX, (u32) 0xA9); /* CCLK-PLL-GPIO-CFG = 0xA9 := B7-6:SS3:"10":input-only (high-impedance), B5-4:SS2:"10":input-only (high-impedance), B3-2:SS1:"10":input-only (high-impedance), B1-0:SS0:"01":push-pull */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_PLL_GPIO_ENA_IDX, (u32) 0x02); /* CCLK-PLL-GPIO-ENA = 0x02 := B7-4:X:"0000":not used, B3:SS3:0:disable GPIO, B2:SS2:0:disable GPIO, B1:SS1:1:enable GPIO, B0:SS0:0:disable GPIO */
   XIo_Out32(XPAR_PLB46_TO_IIC_MMAP_INST_MEM0_BASEADDR + RFFE_CCLK_PLL_SPI_CFG_IDX,  (u32) 0x01); /* CCLK-PLL-SPI-CFG  = 0x01 := B7-6:X:"00":reserved, B5:ORDER:"0":MSB of the data word is transmitted first, B4:X:"0":reserved, B3-2:MODE:"00":CPOL = 0 CPHA = 0, B1-0:F:"01":SPI clock rate 461 kHz */
   /* LO-INIT */
   lo_phase_wr();
   lo_pll_r_wr();
   lo_pll_ab_wr();
   lo_pll_f23_mux_p_wr();
   /* CCLK-INIT0 */
   /* CCLK-DDS-INIT Reset DDS chip */
   for (i = 0; i < 4000000; ++i) /* Wait for 32 ms for DDS to work */
   {
      asm("nop");
   }
   cclk_dds_reset_wr();
   for (i = 0; i < 4000000; ++i) /* Wait for 32 ms for DDS to work */
   {
      asm("nop");
   }
   cclk_dds_cfr1_wr();
   cclk_dds_iotoggle();
   cclk_dds_cfr2_wr();
   cclk_dds_iotoggle();
   cclk_dds_dac_wr();
   cclk_dds_iotoggle();
   cclk_dds_ftw_wr();
   cclk_dds_iotoggle();
   cclk_dds_phase_wr();
   cclk_dds_iotoggle();
   for (i = 0; i < 4000000; ++i) /* Wait for 32 ms for DDS to work */
   {
      asm("nop");
   }
   /* CCLK-INIT1 */
   cclk_pll_r_wr();
   cclk_pll_n_wr();
   cclk_pll_f23_mux_wr();
   for (i = 0; i < 2000000; ++i) /* Wait for 16 ms for PLL to startup stable */
   {
      asm("nop");
   }
   /* TMP-FB-INIT */
   r_rf_tmp_fbo_wr();
   r_mx_tmp_fbo_wr();
   x_rf_tmp_fbo_wr();
   x_mx_tmp_fbo_wr();
   y_rf_tmp_fbo_wr();
   y_mx_tmp_fbo_wr();
   /* Read calibration values from EEPROM */
   rffe_eeprom_rd();
   /* Show I/Q imbalance calibration values from EEPROM */
   ib_r_index_wr();
   ib_x_index_wr();
   ib_y_index_wr();
   /* I/Q imbalance correction */
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_IB_ENA_IDX, 1);                                    /* IB-ENA I/Q imbalance correction switched on */
   /* Attenuator calibration */
   XIo_Out32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_AC_ENA_IDX, 1);                                    /* AC-ENA attenuator calibration switched on */
   /* Set and show the attenuator calibration values from EEPROM */
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX); /* R-DSA */
   r_dsa_wr(data);
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX); /* X-DSA */
   x_dsa_wr(data);
   data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX); /* Y-DSA */
   y_dsa_wr(data);
}

/* EOF */
