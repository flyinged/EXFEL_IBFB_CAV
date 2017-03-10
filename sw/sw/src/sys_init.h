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
#ifndef SYS_INIT_H_
#define SYS_INIT_H_
/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rffe.h"
#include "adc16hl.h"
#include "smp.h"

/* Data declaration */
#define SYS_INIT_NO_IRQ_MASK           0x00001000          /* Memory offset which prevents interrupt issuing */
/* Sampling */
/* Initialization */
#define SYS_INIT_SMP_INIT_IDX          0x00000000          /* SMP-INIT */
/* Mode */
#define SYS_INIT_SMP_ENA_IDX           0x00000010          /* SMP-ENA */
#define SYS_INIT_SMP_MODE_IDX          0x00000014          /* SMP-MODE */
#define SYS_INIT_SMP_TRIG_VAL_IDX      0x00000018          /* SMP-TRIG-VAL */
/* Timing */
#define SYS_INIT_SMP_B0_0_IDX          0x00000020          /* SMP-B0-0 */
#define SYS_INIT_SMP_B1_0_IDX          0x00000024          /* SMP-B1-0 */
#define SYS_INIT_SMP_B2_0_IDX          0x00000028          /* SMP-B2-0 */
#define SYS_INIT_SMP_B3_0_IDX          0x0000002C          /* SMP-B3-0 */
#define SYS_INIT_SMP_S1_0_IDX          0x00000030          /* SMP-S1-0 */
#define SYS_INIT_SMP_S1_1_IDX          0x00000034          /* SMP-S1-1 */
#define SYS_INIT_SMP_S1_2_IDX          0x00000038          /* SMP-S1-2 */
/* Baseline */
#define SYS_INIT_BL_ENA_IDX            0x00000040          /* BL-ENA */
#define SYS_INIT_BL_EXP_IDX            0x00000044          /* BL-SMP-EXP */
#define SYS_INIT_BL_DEL_IDX            0x00000048          /* BL-DEL */
/* ADC16HL */
/* Initialization */
#define SYS_INIT_PB_INIT_IDX           0x00000050          /* Init of the ADC16HL board */
/* ADC16HL clock distribution */
#define SYS_INIT_GOE_IDX               0x00000060          /* GOE */
#define SYS_INIT_SYNC_IDX              0x00000064          /* SYNC */
#define SYS_INIT_CLK_PD_IDX            0x00000068          /* CLK-PD */
#define SYS_INIT_CLK_EN_IDX            0x0000006C          /* CLK-EN */
#define SYS_INIT_CLK_VBOOST_IDX        0x00000070          /* CLK-VBOOST */
#define SYS_INIT_CLK_SEL_IDX           0x00000074          /* CLK-SEL */
/* ADC16HL local oscillator */
#define SYS_INIT_SCK_OE_IDX            0x00000078          /* SCK-OE */
/* ADC16HL ADC */
#define SYS_INIT_ADC_SHDN_IDX          0x00000080          /* ADC-SHDN */
/* ADC16HL sampling clock distribution */
#define SYS_INIT_FPGA_CLK_MUX_IDX      0x00000090          /* FPGA-CLK-MUX */
#define SYS_INIT_FPGA_CLK_DIV_IDX      0x00000094          /* FPGA-CLK-DIV */
#define SYS_INIT_FPGA_CLK_DLY_IDX      0x00000098          /* FPGA-CLK-DLY */
/* ADC16HL power sync clock distribution */
#define SYS_INIT_PWR_CLK_MUX_IDX       0x000000A0          /* PWR-CLK-MUX */
#define SYS_INIT_PWR_CLK_DIV_IDX       0x000000A4          /* PWR-CLK-DIV */
#define SYS_INIT_PWR_CLK_DLY_IDX       0x000000A8          /* PWR-CLK-DLY */
/* ADC 0  */
#define SYS_INIT_ADC0_PGA_IDX          0x000000B0          /* ADC0-PGA */
#define SYS_INIT_ADC0_DAC_OFS_IDX      0x000000B4          /* ADC0-DAC-OFS */
#define SYS_INIT_ADC0_DAC_MUX_IDX      0x000000B8          /* ADC0-DAC-MUX */
#define SYS_INIT_ADC0_CLK_MUX_IDX      0x000000BC          /* ADC0-CLK-MUX */
#define SYS_INIT_ADC0_CLK_DIV_IDX      0x000000C0          /* ADC0-CLK-DIV */
#define SYS_INIT_ADC0_CLK_DLY_IDX      0x000000C4          /* ADC0-CLK-DLY */
/* ADC 1  */
#define SYS_INIT_ADC1_PGA_IDX          0x000000D0          /* ADC1-PGA */
#define SYS_INIT_ADC1_DAC_OFS_IDX      0x000000D4          /* ADC1-DAC-OFS */
#define SYS_INIT_ADC1_DAC_MUX_IDX      0x000000D8          /* ADC1-DAC-MUX */
#define SYS_INIT_ADC1_CLK_MUX_IDX      0x000000DC          /* ADC1-CLK-MUX */
#define SYS_INIT_ADC1_CLK_DIV_IDX      0x000000E0          /* ADC1-CLK-DIV */
#define SYS_INIT_ADC1_CLK_DLY_IDX      0x000000E4          /* ADC1-CLK-DLY */
/* ADC 2 */
#define SYS_INIT_ADC2_PGA_IDX          0x000000F0          /* ADC2-PGA */
#define SYS_INIT_ADC2_DAC_OFS_IDX      0x000000F4          /* ADC2-DAC-OFS */
#define SYS_INIT_ADC2_DAC_MUX_IDX      0x000000F8          /* ADC2-DAC-MUX */
#define SYS_INIT_ADC2_CLK_MUX_IDX      0x000000FC          /* ADC2-CLK-MUX */
#define SYS_INIT_ADC2_CLK_DIV_IDX      0x00000100          /* ADC2-CLK-DIV */
#define SYS_INIT_ADC2_CLK_DLY_IDX      0x00000104          /* ADC2-CLK-DLY */
/* ADC 3  */
#define SYS_INIT_ADC3_PGA_IDX          0x00000110          /* ADC3-PGA */
#define SYS_INIT_ADC3_DAC_OFS_IDX      0x00000114          /* ADC3-DAC-OFS */
#define SYS_INIT_ADC3_DAC_MUX_IDX      0x00000118          /* ADC3-DAC-MUX */
#define SYS_INIT_ADC3_CLK_MUX_IDX      0x0000011C          /* ADC3-CLK-MUX */
#define SYS_INIT_ADC3_CLK_DIV_IDX      0x00000120          /* ADC3-CLK-DIV */
#define SYS_INIT_ADC3_CLK_DLY_IDX      0x00000124          /* ADC3-CLK-DLY */
/* ADC 4  */
#define SYS_INIT_ADC4_PGA_IDX          0x00000130          /* ADC4-PGA */
#define SYS_INIT_ADC4_DAC_OFS_IDX      0x00000134          /* ADC4-DAC-OFS */
#define SYS_INIT_ADC4_DAC_MUX_IDX      0x00000138          /* ADC4-DAC-MUX */
#define SYS_INIT_ADC4_CLK_MUX_IDX      0x0000013C          /* ADC4-CLK-MUX */
#define SYS_INIT_ADC4_CLK_DIV_IDX      0x00000140          /* ADC4-CLK-DIV */
#define SYS_INIT_ADC4_CLK_DLY_IDX      0x00000144          /* ADC4-CLK-DLY */
/* ADC 5  */
#define SYS_INIT_ADC5_PGA_IDX          0x00000150          /* ADC5-PGA */
#define SYS_INIT_ADC5_DAC_OFS_IDX      0x00000154          /* ADC5-DAC-OFS */
#define SYS_INIT_ADC5_DAC_MUX_IDX      0x00000158          /* ADC5-DAC-MUX */
#define SYS_INIT_ADC5_CLK_MUX_IDX      0x0000015C          /* ADC5-CLK-MUX */
#define SYS_INIT_ADC5_CLK_DIV_IDX      0x00000160          /* ADC5-CLK-DIV */
#define SYS_INIT_ADC5_CLK_DLY_IDX      0x00000164          /* ADC5-CLK-DLY */
/* Sync */
#define SYS_INIT_ADC_SYNC_IDX          0x00000170          /* ADC-SYNC */
/* RFFE settings */
/* Initialization */
#define SYS_INIT_RFFE_INIT_IDX         0x00000200          /* RFFE-INIT */
#define SYS_INIT_RFFE_EEPROM_RD_IDX    0x00000204          /* RFFE-EEPROM-RD */
#define SYS_INIT_RFFE_EEPROM_WR_IDX    0x00000208          /* RFFE-EEPROM-WR */
/* RFFE temperature settings */
#define SYS_INIT_DIO_TMP_FB_IDX        0x00000210          /* DIO-TMP-FB */
#define SYS_INIT_R_RF_TMP_FBO_IDX      0x00000214          /* R-RF-TMP-FBO */
#define SYS_INIT_R_MX_TMP_FBO_IDX      0x00000218          /* R-MX-TMP-FBO */
#define SYS_INIT_X_RF_TMP_FBO_IDX      0x0000021C          /* X-RF-TMP-FBO */
#define SYS_INIT_X_MX_TMP_FBO_IDX      0x00000220          /* X-MX-TMP-FBO */
#define SYS_INIT_Y_RF_TMP_FBO_IDX      0x00000224          /* Y-RF-TMP-FBO */
#define SYS_INIT_Y_MX_TMP_FBO_IDX      0x00000228          /* Y-MX-TMP-FBO */
/* RFFE Reference source settings */
#define SYS_INIT_DIO_INT_REF_IDX       0x00000230          /* DIO-INT-REF */
/* RFFE CCLK DDS settings */
#define SYS_INIT_CCLK_DDS_RESET_IDX    0x00000240          /* CCLK-DDS-RESET */
#define SYS_INIT_CCLK_DDS_CFR1_IDX     0x00000244          /* CCLK-DDS-CFR1 */
#define SYS_INIT_CCLK_DDS_CFR2_IDX     0x00000248          /* CCLK-DDS-CFR2 */
#define SYS_INIT_CCLK_DDS_DAC_IDX      0x0000024C          /* CCLK-DDS-DAC */
#define SYS_INIT_CCLK_DDS_FTW_IDX      0x00000250          /* CCLK-DDS-FTW */
#define SYS_INIT_CCLK_DDS_PHASE_IDX    0x00000254          /* CCLK-DDS-PHASE */
/* RFFE CCLK PLL settings */
#define SYS_INIT_CCLK_PLL_R_IDX        0x00000260          /* CCLK-PLL-R */
#define SYS_INIT_CCLK_PLL_N_IDX        0x00000264          /* CCLK-PLL-N */
#define SYS_INIT_CCLK_PLL_F2_IDX       0x00000268          /* CCLK-PLL-F2 */
#define SYS_INIT_CCLK_PLL_F3_IDX       0x0000026C          /* CCLK-PLL-F3 */
#define SYS_INIT_CCLK_PLL_MUX_IDX      0x00000270          /* CCLK-PLL-MUX */
/* RFFE LO settings */
#define SYS_INIT_LO_PHASE_IDX          0x00000280          /* LO-PHASE */
#define SYS_INIT_LO_PLL_R_IDX          0x00000284          /* LO-PLL-R */
#define SYS_INIT_LO_PLL_P_IDX          0x00000288          /* LO-PLL-P */
#define SYS_INIT_LO_PLL_B_IDX          0x0000028C          /* LO-PLL-B */
#define SYS_INIT_LO_PLL_A_IDX          0x00000290          /* LO-PLL-A */
#define SYS_INIT_LO_PLL_F2_IDX         0x00000294          /* LO-PLL-F2 */
#define SYS_INIT_LO_PLL_F3_IDX         0x00000298          /* LO-PLL-F3 */
#define SYS_INIT_LO_PLL_MUX_IDX        0x0000029C          /* LO-PLL-MUX */
/* RFFE LO detector setting */
#define SYS_INIT_LO_PWR_O_IDX          0x000002B0          /* LO-PWR-O */
#define SYS_INIT_LO_TMP_FBO_IDX        0x000002B4          /* LO-TMP-FBO */
/* Attenuator */
#define SYS_INIT_R_DSA_IDX             0x000002C0          /* R-DSA */
#define SYS_INIT_X_DSA_IDX             0x000002C4          /* X-DSA */
#define SYS_INIT_Y_DSA_IDX             0x000002C8          /* Y-DSA */
/* RFFE GPIO attenuator settings */
#define SYS_INIT_R_DSA_DIO_IDX         0x000002D0          /* R-DSA-DIO */
#define SYS_INIT_XY_DSA_DIO_IDX        0x000002D4          /* XY-DSA-DIO */
/* Feedback settings*/
/* DDS feedback*/
#define SYS_INIT_PHASE_FB_ON_IDX       0x000002E0          /* PHASE-FB-ON */
#define SYS_INIT_PHASE_FB_REF_IDX      0x000002E4          /* PHASE-FB.VAL */
#define SYS_INIT_PHASE_FB_KP_IDX       0x000002E8          /* PHASE-FB.KP */
#define SYS_INIT_PHASE_FB_KI_IDX       0x000002EC          /* PHASE-FB.KI */
/* I/Q feedback */
#define SYS_INIT_PH_REF_FB_ON_IDX      0x00000300          /* PH-REF-FB-ON */
#define SYS_INIT_PH_REF_FB_REF_IDX     0x00000304          /* PH-REF-FB.VAL */
#define SYS_INIT_PH_REF_FB_KP_IDX      0x00000308          /* PH-REF-FB.KP */
#define SYS_INIT_PH_REF_FB_KI_IDX      0x0000030C          /* PH-REF-FB-KI */
/* Automatic gain control */
#define SYS_INIT_REF_GAIN_FB_ON_IDX    0x00000320          /* REF-GAIN-FB-ON */
#define SYS_INIT_X_GAIN_FB_ON_IDX      0x00000324          /* X-GAIN-FB-ON */
#define SYS_INIT_Y_GAIN_FB_ON_IDX      0x00000328          /* Y-GAIN-FB-ON */
/* Beam angle feedback */
#define SYS_INIT_BA_ENA_IDX            0x00000330          /* BA-ENA */
#define SYS_INIT_BA_FB_ENA_IDX         0x00000334          /* BA-FB-ENA */
#define SYS_INIT_BA_FB_THR_IDX         0x00000338          /* BA-FB-THR */
#define SYS_INIT_BA_X_IDX              0x0000033C          /* BA-X */
#define SYS_INIT_BA_Y_IDX              0x00000340          /* BA-Y */
/* Scaling */
#define SYS_INIT_R_SCALE_EGU_IDX       0x00000348          /* R-SCALE-EGU */
#define SYS_INIT_X_SCALE_EGU_IDX       0x0000034C          /* X-SCALE-EGU */
#define SYS_INIT_Y_SCALE_EGU_IDX       0x00000350          /* Y-SCALE-EGU */

#define SYS_INIT_R_SCALE_IDX           0x00000354          /* R-SCALE */
#define SYS_INIT_X_SCALE_IDX           0x00000358          /* X-SCALE */
#define SYS_INIT_Y_SCALE_IDX           0x0000035C          /* Y-SCALE */
/* RFFE I/Q imbalance correction tables */
#define SYS_INIT_IB_ENA_IDX            0x00000370          /* IB-ENA */

#define SYS_INIT_IB_R_INDEX_IDX        0x00000374          /* IB-R-INDEX */
#define SYS_INIT_IB_R_PHASE_IDX        0x00000378          /* IB-R-PHASE */
#define SYS_INIT_IB_R_AMPL_IDX         0x0000037C          /* IB-R-AMPL */

#define SYS_INIT_IB_X_INDEX_IDX        0x00000384          /* IB-X-INDEX */
#define SYS_INIT_IB_X_PHASE_IDX        0x00000388          /* IB-X-PHASE */
#define SYS_INIT_IB_X_AMPL_IDX         0x0000038C          /* IB-X-AMPL */

#define SYS_INIT_IB_Y_INDEX_IDX        0x00000394          /* IB-Y-INDEX */
#define SYS_INIT_IB_Y_PHASE_IDX        0x00000398          /* IB-Y-PHASE */
#define SYS_INIT_IB_Y_AMPL_IDX         0x0000039C          /* IB-Y-AMPL */
/* RFFE attenuator calibration tables */
#define SYS_INIT_AC_ENA_IDX            0x000003A0          /* AC-R-PHASE */

#define SYS_INIT_AC_R_PHASE_IDX        0x000003A8          /* AC-R-PHASE */
#define SYS_INIT_AC_R_AMPL_IDX         0x000003AC          /* AC-R-AMPL */

#define SYS_INIT_AC_X_PHASE_IDX        0x000003B8          /* AC-X-PHASE */
#define SYS_INIT_AC_X_AMPL_IDX         0x000003BC          /* AC-X-AMPL */

#define SYS_INIT_AC_Y_PHASE_IDX        0x000003C8          /* AC-Y-PHASE */
#define SYS_INIT_AC_Y_AMPL_IDX         0x000003CC          /* AC-Y-AMPL */
/* Charge threshold */
#define SYS_INIT_Q_FB_THR_IDX          0x000003D0          /* Q-FB-THR */
/* Average calculation */
#define SYS_INIT_Q_TRAIN_AVG_IDX       0x000003E0          /* Q-TRAIN-AVG */
#define SYS_INIT_X_TRAIN_AVG_IDX       0x000003E4          /* X-TRAIN-AVG */
#define SYS_INIT_Y_TRAIN_AVG_IDX       0x000003E8          /* Y-TRAIN-AVG */
/* Automatic gain control continued */
#define SYS_INIT_REF_GAIN_FB_MAX_IDX     0x00000400        /* REF-GAIN-FB-MAX */
#define SYS_INIT_REF_GAIN_FB_MIN_IDX     0x00000404        /* REF-GAIN-FB-MIN */
#define SYS_INIT_REF_GAIN_FB_MIN_CNT_IDX 0x00000408        /* REF-GAIN-FB-MIN-CNT */
#define SYS_INIT_REF_GAIN_FB_ATT_INC_IDX 0x0000040C        /* REF-GAIN-FB-ATT-INC */

#define SYS_INIT_X_GAIN_FB_MAX_IDX     0x00000420          /* X-GAIN-FB-MAX */
#define SYS_INIT_X_GAIN_FB_MIN_IDX     0x00000424          /* X-GAIN-FB-MIN */
#define SYS_INIT_X_GAIN_FB_MIN_CNT_IDX 0x00000428          /* X-GAIN-FB-MIN-CNT */
#define SYS_INIT_X_GAIN_FB_ATT_INC_IDX 0x0000042C          /* X-GAIN-FB-ATT-INC */

#define SYS_INIT_Y_GAIN_FB_MAX_IDX     0x00000440          /* Y-GAIN-FB-MAX */
#define SYS_INIT_Y_GAIN_FB_MIN_IDX     0x00000444          /* Y-GAIN-FB-MIN */
#define SYS_INIT_Y_GAIN_FB_MIN_CNT_IDX 0x00000448          /* Y-GAIN-FB-MIN-CNT */
#define SYS_INIT_Y_GAIN_FB_ATT_INC_IDX 0x0000044C          /* Y-GAIN-FB-ATT-INC */

/* Function declaration */
#define XIo_Outfs(OutAddress, Value)   ((*(volatile float *)(OutAddress)) = (Value))
#define XIo_Infs(InAddress)             (*(volatile float *)(InAddress))

void sys_init_decode(void);

#endif /* SYS_INIT_H_ */

/* EOF */
