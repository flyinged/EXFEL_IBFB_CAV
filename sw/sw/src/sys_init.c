/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : sys_init.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for setting new values in the BPM FPGA.
//           Sometimes values have to be rescaled or combined with other values
//           before they are written to the hardware registers.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "sys_init.h"

void sys_init_decode(void)
{
   u32   fifo_not_empty;
   u32   addr;
   u32   data;

   while ((fifo_not_empty = XIo_In32(XPAR_SYS_INIT_INST_BASEADDR)) & 0x00000001);
   {
      addr = XIo_In32(XPAR_SYS_INIT_INST_BASEADDR + 0x00000004);
      data = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + addr);

      switch (addr)
      {
      /* Sampling */
      /* Initialization */
      case SYS_INIT_SMP_INIT_IDX:
         smp_init();
         break;
      /* Mode */
      case SYS_INIT_SMP_ENA_IDX:
         smp_ena_wr();
         break;
      case SYS_INIT_SMP_MODE_IDX:
         smp_mode_wr();
         break;
      case SYS_INIT_SMP_TRIG_VAL_IDX:
         smp_trig_val_wr();
         break;
      /* Timing */
      case SYS_INIT_SMP_B0_0_IDX:
         smp_b0_0_wr();
         break;
      case SYS_INIT_SMP_B1_0_IDX:
         smp_b1_0_wr();
         break;
      case SYS_INIT_SMP_B2_0_IDX:
         smp_b2_0_wr();
         break;
      case SYS_INIT_SMP_B3_0_IDX:
         smp_b3_0_wr();
         break;
      case SYS_INIT_SMP_S1_0_IDX:
         smp_s1_0_wr();
         break;
      case SYS_INIT_SMP_S1_1_IDX:
         smp_s1_1_wr();
         break;
      case SYS_INIT_SMP_S1_2_IDX:
         smp_s1_2_wr();
         break;
      /* Baseline */
      case SYS_INIT_BL_ENA_IDX:
        bl_ena_wr();
        break;
      case SYS_INIT_BL_EXP_IDX:
        bl_exp_wr();
        break;
      case SYS_INIT_BL_DEL_IDX:
        bl_del_wr();
        break;
      /* ADC16HL */
      /* Initialization */
      case SYS_INIT_PB_INIT_IDX:
         adc16hl_init();
         break;
      /* ADC16HL control register */
      case SYS_INIT_ADC0_PGA_IDX:
      case SYS_INIT_ADC1_PGA_IDX:
      case SYS_INIT_ADC2_PGA_IDX:
      case SYS_INIT_ADC3_PGA_IDX:
      case SYS_INIT_ADC4_PGA_IDX:
      case SYS_INIT_ADC5_PGA_IDX:
      case SYS_INIT_ADC_SHDN_IDX:
      case SYS_INIT_SYNC_IDX:
      case SYS_INIT_GOE_IDX:
      case SYS_INIT_SCK_OE_IDX:
         adc_ctrl_wr();
         break;
      case SYS_INIT_CLK_PD_IDX:
      case SYS_INIT_CLK_EN_IDX:
      case SYS_INIT_CLK_SEL_IDX:
         clk_pd_en_sel_wr();
         break;
      case SYS_INIT_CLK_VBOOST_IDX:
         clk_vboost_wr();
         break;
      /* ADC16HL sampling clock distribution */
      case SYS_INIT_FPGA_CLK_MUX_IDX:
      case SYS_INIT_FPGA_CLK_DIV_IDX:
      case SYS_INIT_FPGA_CLK_DLY_IDX:
         fpga_clk_wr();
         break;
      /* ADC16HL power sync clock distribution */
      case SYS_INIT_PWR_CLK_MUX_IDX:
      case SYS_INIT_PWR_CLK_DIV_IDX:
      case SYS_INIT_PWR_CLK_DLY_IDX:
         pwr_clk_wr();
         break;
      /* ADC 0  */
      case SYS_INIT_ADC0_DAC_OFS_IDX:
      case SYS_INIT_ADC0_DAC_MUX_IDX:
         adc0_dac_wr();
         break;
      case SYS_INIT_ADC0_CLK_MUX_IDX:
      case SYS_INIT_ADC0_CLK_DIV_IDX:
      case SYS_INIT_ADC0_CLK_DLY_IDX:
         adc0_clk_wr();
         break;
      /* ADC 1  */
      case SYS_INIT_ADC1_DAC_OFS_IDX:
      case SYS_INIT_ADC1_DAC_MUX_IDX:
         adc1_dac_wr();
         break;
      case SYS_INIT_ADC1_CLK_MUX_IDX:
      case SYS_INIT_ADC1_CLK_DIV_IDX:
      case SYS_INIT_ADC1_CLK_DLY_IDX:
         adc1_clk_wr();
         break;
      /* ADC 2 */
      case SYS_INIT_ADC2_DAC_OFS_IDX:
      case SYS_INIT_ADC2_DAC_MUX_IDX:
         adc2_dac_wr();
         break;
      case SYS_INIT_ADC2_CLK_MUX_IDX:
      case SYS_INIT_ADC2_CLK_DIV_IDX:
      case SYS_INIT_ADC2_CLK_DLY_IDX:
         adc2_clk_wr();
         break;
      /* ADC 3  */
      case SYS_INIT_ADC3_DAC_OFS_IDX:
      case SYS_INIT_ADC3_DAC_MUX_IDX:
         adc3_dac_wr();
         break;
      case SYS_INIT_ADC3_CLK_MUX_IDX:
      case SYS_INIT_ADC3_CLK_DIV_IDX:
      case SYS_INIT_ADC3_CLK_DLY_IDX:
         adc3_clk_wr();
         break;
      /* ADC 4  */
      case SYS_INIT_ADC4_DAC_OFS_IDX:
      case SYS_INIT_ADC4_DAC_MUX_IDX:
         adc4_dac_wr();
         break;
      case SYS_INIT_ADC4_CLK_MUX_IDX:
      case SYS_INIT_ADC4_CLK_DIV_IDX:
      case SYS_INIT_ADC4_CLK_DLY_IDX:
         adc4_clk_wr();
         break;
      /* ADC 5  */
      case SYS_INIT_ADC5_DAC_OFS_IDX:
      case SYS_INIT_ADC5_DAC_MUX_IDX:
         adc5_dac_wr();
         break;
      case SYS_INIT_ADC5_CLK_MUX_IDX:
      case SYS_INIT_ADC5_CLK_DIV_IDX:
      case SYS_INIT_ADC5_CLK_DLY_IDX:
         adc5_clk_wr();
         break;
      /* Sync */
      case SYS_INIT_ADC_SYNC_IDX:
         adc_sync_wr();
         break;
      /* RFFE settings */
      /* Initialization */
      case SYS_INIT_RFFE_INIT_IDX:
         rffe_init();
         break;
      case SYS_INIT_RFFE_EEPROM_RD_IDX:
         rffe_eeprom_rd();
         break;
      case SYS_INIT_RFFE_EEPROM_WR_IDX:
         rffe_eeprom_wr();
         break;
      case SYS_INIT_R_RF_TMP_FBO_IDX:
         r_rf_tmp_fbo_wr();
         break;
      case SYS_INIT_R_MX_TMP_FBO_IDX:
         r_mx_tmp_fbo_wr();
         break;
      case SYS_INIT_X_RF_TMP_FBO_IDX:
         x_rf_tmp_fbo_wr();
         break;
      case SYS_INIT_X_MX_TMP_FBO_IDX:
         x_mx_tmp_fbo_wr();
         break;
      case SYS_INIT_Y_RF_TMP_FBO_IDX:
         y_rf_tmp_fbo_wr();
         break;
      case SYS_INIT_Y_MX_TMP_FBO_IDX:
         y_mx_tmp_fbo_wr();
         break;
      /* RFFE temperature settings */
      case SYS_INIT_DIO_TMP_FB_IDX:
      /* RFFE Reference source settings */
      case SYS_INIT_DIO_INT_REF_IDX:
         dio_o_wr();
         break;
      /* RFFE CCLK DDS settings */
      case SYS_INIT_CCLK_DDS_RESET_IDX:
         cclk_dds_reset_wr();
         break;
      case SYS_INIT_CCLK_DDS_CFR1_IDX:
         cclk_dds_cfr1_wr();
         cclk_dds_iotoggle();
         break;
      case SYS_INIT_CCLK_DDS_CFR2_IDX:
         cclk_dds_cfr2_wr();
         cclk_dds_iotoggle();
         break;
      case SYS_INIT_CCLK_DDS_DAC_IDX:
         cclk_dds_dac_wr();
         cclk_dds_iotoggle();
         break;
      case SYS_INIT_CCLK_DDS_FTW_IDX:
         cclk_dds_ftw_wr();
         cclk_dds_iotoggle();
         break;
      case SYS_INIT_CCLK_DDS_PHASE_IDX:
         cclk_dds_phase_wr();
         cclk_dds_iotoggle();
         break;
      /* RFFE CCLK PLL settings */
      case SYS_INIT_CCLK_PLL_R_IDX:
         cclk_pll_r_wr();
         break;
      case SYS_INIT_CCLK_PLL_N_IDX:
         cclk_pll_n_wr();
         break;
      case SYS_INIT_CCLK_PLL_MUX_IDX:
      case SYS_INIT_CCLK_PLL_F2_IDX:
      case SYS_INIT_CCLK_PLL_F3_IDX:
         cclk_pll_f23_mux_wr();
         break;
      /* RFFE LO settings */
      case SYS_INIT_LO_PHASE_IDX:
         lo_phase_wr();
         break;
      case SYS_INIT_LO_PLL_R_IDX:
         lo_pll_r_wr();
         break;
      case SYS_INIT_LO_PLL_A_IDX:
      case SYS_INIT_LO_PLL_B_IDX:
         lo_pll_ab_wr();
         break;
      case SYS_INIT_LO_PLL_F2_IDX:
      case SYS_INIT_LO_PLL_F3_IDX:
      case SYS_INIT_LO_PLL_MUX_IDX:
      case SYS_INIT_LO_PLL_P_IDX:
         lo_pll_f23_mux_p_wr();
         break;
      /* RFFE LO detector setting */
      case SYS_INIT_LO_PWR_O_IDX:
         lo_pwr_o_wr();
         break;
      case SYS_INIT_LO_TMP_FBO_IDX:
         lo_tmp_fbo_wr();
         break;
      /* Attenuator */
      case SYS_INIT_R_DSA_IDX:
         r_dsa_wr(data);
         break;
      case SYS_INIT_X_DSA_IDX:
         x_dsa_wr(data);
         break;
      case SYS_INIT_Y_DSA_IDX:
         y_dsa_wr(data);
         break;
      /* RFFE GPIO attenuator settings */
      case SYS_INIT_R_DSA_DIO_IDX:
         break;
      case SYS_INIT_XY_DSA_DIO_IDX:
         break;
      /* Feedback settings*/
      /* DDS feedback*/
      case SYS_INIT_PHASE_FB_ON_IDX:
         break;
      case SYS_INIT_PHASE_FB_REF_IDX:
         break;
      case SYS_INIT_PHASE_FB_KP_IDX:
         break;
      case SYS_INIT_PHASE_FB_KI_IDX:
         break;
      /* I/Q feedback */
      case SYS_INIT_PH_REF_FB_ON_IDX:
         break;
      case SYS_INIT_PH_REF_FB_REF_IDX:
         break;
      case SYS_INIT_PH_REF_FB_KP_IDX:
         break;
      case SYS_INIT_PH_REF_FB_KI_IDX:
         break;
      /* Automatic gain control */
      case SYS_INIT_REF_GAIN_FB_ON_IDX:
         break;
      case SYS_INIT_X_GAIN_FB_ON_IDX:
         break;
      case SYS_INIT_Y_GAIN_FB_ON_IDX:
         break;
      /* I/Q Imbalance */
      case SYS_INIT_IB_R_INDEX_IDX:
         ib_r_index_wr();
         break;
      case SYS_INIT_IB_R_PHASE_IDX:
         ib_r_phase_wr();
         break;
      case SYS_INIT_IB_R_AMPL_IDX:
         ib_r_ampl_wr();
         break;
      case SYS_INIT_IB_X_INDEX_IDX:
         ib_x_index_wr();
         break;
      case SYS_INIT_IB_X_PHASE_IDX:
         ib_x_phase_wr();
         break;
      case SYS_INIT_IB_X_AMPL_IDX:
         ib_x_ampl_wr();
         break;
      case SYS_INIT_IB_Y_INDEX_IDX:
         ib_y_index_wr();
         break;
      case SYS_INIT_IB_Y_PHASE_IDX:
         ib_y_phase_wr();
         break;
      case SYS_INIT_IB_Y_AMPL_IDX:
         ib_y_ampl_wr();
         break;
       /* Attenuator calibration */
       case SYS_INIT_AC_R_PHASE_IDX:
         ac_r_phase_wr();
         break;
       case SYS_INIT_AC_R_AMPL_IDX:
         ac_r_ampl_wr();
         break;
       case SYS_INIT_AC_X_PHASE_IDX:
         ac_x_phase_wr();
         break;
       case SYS_INIT_AC_X_AMPL_IDX:
         ac_x_ampl_wr();
         break;
       case SYS_INIT_AC_Y_PHASE_IDX:
         ac_y_phase_wr();
         break;
       case SYS_INIT_AC_Y_AMPL_IDX:
         ac_y_ampl_wr();
         break;
      /* Scaling / Calibration */
      case SYS_INIT_R_SCALE_EGU_IDX:
         r_scale_wr();
         break;
      case SYS_INIT_R_SCALE_IDX:
         r_scale_wr();
         break;
      case SYS_INIT_X_SCALE_EGU_IDX:
         x_scale_wr();
         break;
      case SYS_INIT_X_SCALE_IDX:
         x_scale_wr();
         break;
      case SYS_INIT_Y_SCALE_EGU_IDX:
         y_scale_wr();
         break;
      case SYS_INIT_Y_SCALE_IDX:
         y_scale_wr();
         break;
      default:
/*         xil_printf("Unknown addr %d data %d.\n\r", addr, data);*/
         break;
      }
   }
}

/* EOF */
