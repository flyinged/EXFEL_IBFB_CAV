/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : rffe.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for accessing the features of the 3.3 GHz cavity
//           RFFE board V3.1.
//----------------------------------------------------------------------------
*/
#ifndef RFFE_H_
#define RFFE_H_
/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <math.h>
#include "sys_init.h"

/* Data declaration */
/* RFFE I2C read back mask */
#define RFFE_READ_BACK_MASK       0x00001000     /* Memory offset which causes I2C read back */
/* RFFE ADC MAX11617 interface */
#define RFFE_ADC_CTRL_IDX         0x00000000     /* ADC-CTRL */
#define RFFE_R_MX_TMP_FBI_IDX     0x00000004     /* R-MX-TMP-FBI */
#define RFFE_R_RF_TMP_FBI_IDX     0x00000008     /* R-RF-TMP-FBI */
#define RFFE_X_MX_TMP_FBI_IDX     0x0000000C     /* X-MX-TMP-FBI */
#define RFFE_X_RF_TMP_FBI_IDX     0x00000010     /* X-RF-TMP-FBI */
#define RFFE_Y_MX_TMP_FBI_IDX     0x00000014     /* Y-MX-TMP-FBI */
#define RFFE_Y_RF_TMP_FBI_IDX     0x00000018     /* Y-RF-TMP-FBI */
#define RFFE_LO_TMP_FBI_IDX       0x0000001C     /* LO-TMP-FBI */
#define RFFE_LO_PWR_I_IDX         0x00000020     /* LO-PWR-I */
#define RFFE_DET_DC_IDX           0x00000024     /* DET_DC */
/* RFFE TMP LM73 interface */
#define RFFE_R_I_TMP_CFG_IDX      0x00000028     /* R-I-TMP-CFG */ 
#define RFFE_R_Q_TMP_CFG_IDX      0x0000002C     /* R-Q-TMP-CFG */
#define RFFE_X_I_TMP_CFG_IDX      0x00000030     /* X-I-TMP-CFG */
#define RFFE_X_O_TMP_CFG_IDX      0x00000034     /* X-O-TMP-CFG */
#define RFFE_Y_I_TMP_CFG_IDX      0x00000038     /* Y-I-TMP-CFG */
#define RFFE_Y_Q_TMP_CFG_IDX      0x0000003C     /* Y-Q-TMP-CFG */
#define RFFE_R_I_TMP_CTRL_IDX     0x00000040     /* R-I-TMP-CTRL */
#define RFFE_R_Q_TMP_CTRL_IDX     0x00000044     /* R-Q-TMP-CTRL */
#define RFFE_X_I_TMP_CTRL_IDX     0x00000048     /* X-I-TMP-CTRL */
#define RFFE_X_O_TMP_CTRL_IDX     0x0000004C     /* X-O-TMP-CTRL */
#define RFFE_Y_I_TMP_CTRL_IDX     0x00000050     /* Y-I-TMP-CTRL */
#define RFFE_Y_Q_TMP_CTRL_IDX     0x00000054     /* Y-Q-TMP-CTRL */
#define RFFE_R_I_TMP_IDX          0x00000058     /* R-I-TMP */
#define RFFE_R_Q_TMP_IDX          0x0000005C     /* R-Q-TMP */
#define RFFE_X_I_TMP_IDX          0x00000060     /* X-I-TMP */
#define RFFE_X_O_TMP_IDX          0x00000064     /* X-O-TMP */
#define RFFE_Y_I_TMP_IDX          0x00000068     /* Y-I-TMP */
#define RFFE_Y_Q_TMP_IDX          0x0000006C     /* Y-Q-TMP */
/* RFFE DAC DAC7678 interface */
#define RFFE_DAC1_INIT_IDX        0x00000080     /* DAC1-INIT */
#define RFFE_DAC2_INIT_IDX        0x00000084     /* DAC2-INIT */
#define RFFE_R_MX_TMP_FBO_IDX     0x00000088     /* R-MX-TMP-FBO */
#define RFFE_R_RF_TMP_FBO_IDX     0x0000008C     /* R-RF-TMP-FBO */
#define RFFE_X_MX_TMP_FBO_IDX     0x00000090     /* X-MX-TMP-FBO */
#define RFFE_X_RF_TMP_FBO_IDX     0x00000094     /* X-RF-TMP-FBO */
#define RFFE_Y_MX_TMP_FBO_IDX     0x00000098     /* Y-MX-TMP-FBO */
#define RFFE_Y_RF_TMP_FBO_IDX     0x0000009C     /* Y-RF-TMP-FBO */
#define RFFE_LO_TMP_FBO_IDX       0x000000A0     /* LO-TMP-FBO */
#define RFFE_LO_PHASE_IDX         0x000000A4     /* LO-PHASE */
#define RFFE_LO_PWR_O_IDX         0x000000A8     /* LO-PWR-O */
/* RFFE R ATT PCA9555 interface */
#define RFFE_R_ATT_O0_IDX         0x000000C8     /* R-ATT-O0 */
#define RFFE_R_ATT_O1_IDX         0x000000CC     /* R-ATT-O1 */
#define RFFE_R_ATT_P0_IDX         0x000000D0     /* R-ATT-P0 */
#define RFFE_R_ATT_P1_IDX         0x000000D4     /* R-ATT-P1 */
#define RFFE_R_ATT_C0_IDX         0x000000D8     /* R-ATT-C0 */
#define RFFE_R_ATT_C1_IDX         0x000000DC     /* R-ATT-C1 */
/* RFFE X ATT PCA9555 interface */
#define RFFE_X_ATT_O0_IDX         0x000000E8     /* X-ATT-O0 */
#define RFFE_X_ATT_O1_IDX         0x000000EC     /* X-ATT-O1 */
#define RFFE_X_ATT_P0_IDX         0x000000F0     /* X-ATT-P0 */
#define RFFE_X_ATT_P1_IDX         0x000000F4     /* X-ATT-P1 */
#define RFFE_X_ATT_C0_IDX         0x000000F8     /* X-ATT-C0 */
#define RFFE_X_ATT_C1_IDX         0x000000FC     /* X-ATT-C1 */
/* RFFE Y ATT PCA9555 interface */
#define RFFE_Y_ATT_O0_IDX         0x00000108     /* Y-ATT-O0 */
#define RFFE_Y_ATT_O1_IDX         0x0000010C     /* Y-ATT-O1 */
#define RFFE_Y_ATT_P0_IDX         0x00000110     /* Y-ATT-P0 */
#define RFFE_Y_ATT_P1_IDX         0x00000114     /* Y-ATT-P1 */
#define RFFE_Y_ATT_C0_IDX         0x00000118     /* Y-ATT-C0 */
#define RFFE_Y_ATT_C1_IDX         0x0000011C     /* Y-ATT-C1 */
/* RFFE I2C/SPI bridge SC18IS602B LO PLL ADF4107 interface */
#define RFFE_LO_PLL_SPI_O_IDX     0x00000120     /* LO-PLL-SPI-O */
#define RFFE_LO_PLL_SPI_CFG_IDX   0x00000128     /* LO-PLL-SPI-CFG */
#define RFFE_LO_PLL_GPIO_ENA_IDX  0x0000012C     /* LO-PLL-GPIO-ENA */
#define RFFE_LO_PLL_GPIO_CFG_IDX  0x00000130     /* LO-PLL-GPIO-CFG */
#define RFFE_LO_PLL_GPIO_I_IDX    0x00000134     /* LO-PLL-GPIO-I */
/* RFFE PCA9536 interface */
#define RFFE_DIO_I_IDX            0x00000138    /* DIO-I */
#define RFFE_DIO_O_IDX            0x0000013C    /* DIO-O */
#define RFFE_DIO_POL_IDX          0x00000140    /* DIO-POL */
#define RFFE_DIO_CFG_IDX          0x00000144    /* DIO-CFG */
/* RFFE I2C/SPI bridge SC18IS602B DDS AD9913 interface */
#define RFFE_CCLK_DDS_CFR1_IDX    0x00000148     /* CCLK-DDS-CFR1 */
#define RFFE_CCLK_DDS_CFR2_IDX    0x0000014C     /* CCLK-DDS-CFR2 */
#define RFFE_CCLK_DDS_DAC_IDX     0x00000150     /* CCLK-DDS-DAC */
#define RFFE_CCLK_DDS_FTW_IDX     0x00000154     /* CCLK-DDS-FTW */
#define RFFE_CCLK_DDS_POW_IDX     0x00000158     /* CCLK-DDS-POW */
#define RFFE_CCLK_DDS_SPI_CFG_IDX 0x00000168     /* CCLK-DDS-SPI-CFG */
#define RFFE_CCLK_DDS_GPIO_ENA_IDX 0x0000016C    /* CCLK-DDS-GPIO-ENA */
#define RFFE_CCLK_DDS_GPIO_CFG_IDX 0x00000170    /* CCLK-DDS-GPIO-CFG */
#define RFFE_CCLK_DDS_GPIO_O_IDX  0x00000174     /* CCLK-DDS-GPIO-O */
/* RFFE I2C/SPI bridge SC18IS602B IFPLL ADF4101 interface */
#define RFFE_CCLK_PLL_SPI_O_IDX   0x00000178     /* CCLK-PLL-SPI-O */
#define RFFE_CCLK_PLL_SPI_CFG_IDX 0x00000180     /* CCLK-PLL-SPI-CFG */
#define RFFE_CCLK_PLL_GPIO_ENA_IDX 0x00000184    /* CCLK-PLL-GPIO-ENA */
#define RFFE_CCLK_PLL_GPIO_CFG_IDX 0x00000188    /* CCLK-PLL-GPIO-CFG */
#define RFFE_CCLK_PLL_GPIO_I_IDX  0x0000018C     /* CCLK-PLL-GPIO-I */
/* EEPROM scaling interface */
#define RFFE_R_SCALE_EGU_IDX      0x00000190     /* Q-SCALE-EGU */
#define RFFE_X_SCALE_EGU_IDX      0x00000194     /* X-SCALE-EGU */
#define RFFE_Y_SCALE_EGU_IDX      0x00000198     /* Y-SCALE-EGU */
#define RFFE_R_SCALE_IDX          0x0000019C     /* Q-SCALE */
#define RFFE_X_SCALE_IDX          0x000001A0     /* X-SCALE */
#define RFFE_Y_SCALE_IDX          0x000001A4     /* Y-SCALE */
/* EEPROM attenuator calibration */
#define RFFE_AC_R_PHASE_BASE_IDX  0x000001C0     /* AC-R-PHASE for attenuator setting 0 dB ... 63 dB in 1 dB steps */
#define RFFE_AC_R_AMPL_BASE_IDX   0x000002C0     /* AC-R-AMPL  for attenuator setting 0 dB ... 63 dB in 1 dB steps */
#define RFFE_AC_X_PHASE_BASE_IDX  0x000003C0     /* AC-X-PHASE for attenuator setting 0 dB ... 63 dB in 1 dB steps */
#define RFFE_AC_X_AMPL_BASE_IDX   0x000004C0     /* AC-X-AMPL  for attenuator setting 0 dB ... 63 dB in 1 dB steps */
#define RFFE_AC_Y_PHASE_BASE_IDX  0x000005C0     /* AC-Y-PHASE for attenuator setting 0 dB ... 63 dB in 1 dB steps */
#define RFFE_AC_Y_AMPL_BASE_IDX   0x000006C0     /* AC-Y-AMPL  for attenuator setting 0 dB ... 63 dB in 1 dB steps */
/* EEPROM imbalance calibration */
#define RFFE_IB_R_PHASE_BASE_IDX  0x000007C0     /* IB-R-PHASE for attenuator setting 0 ° ... 360 ° in 4 ° steps */
#define RFFE_IB_R_AMPL_BASE_IDX   0x00000874     /* IB-R-AMPL  for attenuator setting 0 ° ... 360 ° in 4 ° steps */
#define RFFE_IB_X_PHASE_BASE_IDX  0x00000928     /* IB-X-PHASE for attenuator setting 0 ° ... 360 ° in 4 ° steps */
#define RFFE_IB_X_AMPL_BASE_IDX   0x000009DC     /* IB-X-AMPL  for attenuator setting 0 ° ... 360 ° in 4 ° steps */
#define RFFE_IB_Y_PHASE_BASE_IDX  0x00000A90     /* IB-Y-PHASE for attenuator setting 0 ° ... 360 ° in 4 ° steps */
#define RFFE_IB_Y_AMPL_BASE_IDX   0x00000B44     /* IB-Y-AMPL  for attenuator setting 0 ° ... 360 ° in 4 ° steps */

/* Function declaration */
void r_rf_tmp_fbo_wr(void);
void r_mx_tmp_fbo_wr(void);
void x_rf_tmp_fbo_wr(void);
void x_mx_tmp_fbo_wr(void);
void y_rf_tmp_fbo_wr(void);
void y_mx_tmp_fbo_wr(void);
void lo_tmp_fbo_wr(void);
void lo_pwr_o_wr(void);
void lo_phase_value_wr(float phase);
void lo_phase_wr(void);
void cclk_dds_iotoggle(void);
void cclk_dds_reset_wr(void);
void cclk_dds_cfr1_wr(void);
void cclk_dds_cfr2_wr(void);
void cclk_dds_dac_wr(void);
void cclk_dds_ftw_wr(void);
void cclk_dds_phase_value_wr(float phase);
void cclk_dds_phase_wr(void);
void cclk_pll_r_wr(void);
void cclk_pll_n_wr(void);
void cclk_pll_f23_mux_wr(void);
void dio_o_wr(void);
void lo_pll_r_wr(void);
void lo_pll_ab_wr(void);
void lo_pll_f23_mux_p_wr(void);
void r_dsa_wr(u32 data);
void x_dsa_wr(u32 data);
void y_dsa_wr(u32 data);
void ib_r_index_wr(void);
void ib_r_phase_wr(void);
void ib_r_ampl_wr(void);
void ib_x_index_wr(void);
void ib_x_phase_wr(void);
void ib_x_ampl_wr(void);
void ib_y_index_wr(void);
void ib_y_phase_wr(void);
void ib_y_ampl_wr(void);
void ac_r_phase_wr(void);
void ac_r_ampl_wr(void);
void ac_x_phase_wr(void);
void ac_x_ampl_wr(void);
void ac_y_phase_wr(void);
void ac_y_ampl_wr(void);
void r_scale_wr(void);
void x_scale_wr(void);
void y_scale_wr(void);
void r_att_cal_wr(void);
void x_att_cal_wr(void);
void y_att_cal_wr(void);
void rffe_eeprom_rd(void);
void rffe_eeprom_wr(void);
void rffe_default(void);
void rffe_init(void);

#endif /* RFFE_H_ */

/* EOF */
