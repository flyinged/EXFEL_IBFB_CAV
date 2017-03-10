/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : smp.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for accessing the features of the FPGA BPM
//           calculation firmware.
//----------------------------------------------------------------------------
*/
#ifndef SMP_H_
#define SMP_H_
/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xparameters.h>
#include <stdlib.h>
#include <math.h>
#include "rffe.h"
#include "adc16hl.h"
#include "sys_init.h"

/* Data declaration */
/* Sampling interface mapping FSM */
#define SMP_ENA_IDX               0x00000003          /* SMP-ENA */
#define SMP_MODE_IDX              0x00000002          /* SMP-MODE */
#define SMP_DONE                  0x00000007          /* SMP-DONE */
#define SMP_DCM_LOCK_IDX          0x0000000B          /* DCM-LOCK */
/* Timing */
#define SMP_B0_0_IDX              0x00000012          /* SMP-B0-0 */
#define SMP_B1_0_IDX              0x00000014          /* SMP-B1-0 */
#define SMP_B2_0_IDX              0x0000001A          /* SMP-B2-0 */
#define SMP_B3_0_IDX              0x0000001C          /* SMP-B3-0 */
#define SMP_S1_0_IDX              0x00000022          /* SMP-S1-0 */
#define SMP_S1_1_IDX              0x00000026          /* SMP-S1-1 */
#define SMP_S1_2_IDX              0x0000002A          /* SMP-S1-2 */
/* Trigger */
#define SMP_TRIG_VAL_IDX          0x0000002E          /* SMP-TRIG-VAL */
#define SMP_TRIG_CNT_FW_IDX       0x00000038          /* TRIG-CNT-FW */
#define SMP_TRIG_DEL_CNT_IDX      0x0000003C          /* TRIG-DEL-CNT */ 
/* ADC sampling adjustment */
#define SMP_ADC0_SYNC_IDX         0x00000043          /* If writen to this port ADC0-SYNC */
#define SMP_ADC1_SYNC_IDX         0x00000047          /* If writen to this port ADC1-SYNC */
#define SMP_ADC2_SYNC_IDX         0x0000004B          /* If writen to this port ADC2-SYNC */
#define SMP_ADC3_SYNC_IDX         0x0000004F          /* If writen to this port ADC3-SYNC */
#define SMP_ADC4_SYNC_IDX         0x00000053          /* If writen to this port ADC4-SYNC */
#define SMP_ADC5_SYNC_IDX         0x00000057          /* If writen to this port ADC5-SYNC */
#define SMP_ADC0_DONE_IDX         0x00000043          /* If read from this port ADC0-SYNC-DONE */
#define SMP_ADC1_DONE_IDX         0x00000047          /* If read from this port ADC1-SYNC-DONE */
#define SMP_ADC2_DONE_IDX         0x0000004B          /* If read from this port ADC2-SYNC-DONE */
#define SMP_ADC3_DONE_IDX         0x0000004F          /* If read from this port ADC3-SYNC-DONE */
#define SMP_ADC4_DONE_IDX         0x00000053          /* If read from this port ADC4-SYNC-DONE */
#define SMP_ADC5_DONE_IDX         0x00000057          /* If read from this port ADC5-SYNC-DONE */
#define SMP_ADC0_IDELAY_CNT_IDX   0x00000041          /* ADC0-SYNC-IDELAY-CNT */
#define SMP_ADC1_IDELAY_CNT_IDX   0x00000045          /* ADC1-SYNC-IDELAY-CNT */
#define SMP_ADC2_IDELAY_CNT_IDX   0x00000049          /* ADC2-SYNC-IDELAY-CNT */
#define SMP_ADC3_IDELAY_CNT_IDX   0x0000004D          /* ADC3-SYNC-IDELAY-CNT */
#define SMP_ADC4_IDELAY_CNT_IDX   0x00000051          /* ADC4-SYNC-IDELAY-CNT */
#define SMP_ADC5_IDELAY_CNT_IDX   0x00000055          /* ADC5-SYNC-IDELAY-CNT */
/* Baseline */
#define SMP_BL_ENA_IDX            0x00000063          /* BL-ENA */
#define SMP_BL_EXP_IDX            0x00000067          /* BL-EXP */
#define SMP_BL_DEL_IDX            0x0000006A          /* BL-DEL */
#define SMP_ADC0_BL_IDX           0x0000006E          /* ADC0-BL */
#define SMP_ADC1_BL_IDX           0x00000072          /* ADC1-BL */
#define SMP_ADC2_BL_IDX           0x00000076          /* ADC2-BL */
#define SMP_ADC3_BL_IDX           0x0000007A          /* ADC3-BL */
#define SMP_ADC4_BL_IDX           0x0000007E          /* ADC4-BL */
#define SMP_ADC5_BL_IDX           0x00000082          /* ADC5-BL */
/* I/Q imbalance correction */
#define SMP_IB_ENA_IDX            0x00000090          /* IB-ENA */
#define SMP_IB_R_PHASE_TABLE      0x00058000          /* [IB-R-INDEX, IB-R-PHASE] R Phase correcting BRAMM */
#define SMP_IB_R_AMPL_TABLE       0x00060000          /* [IB-R-INDEX, IB-R-AMPL]  R Amplitude correcting BRA */
#define SMP_IB_X_PHASE_TABLE      0x00068000          /* [IB-R-INDEX, IB-X-PHASE] X Phase correcting BRAM */
#define SMP_IB_X_AMPL_TABLE       0x00070000          /* [IB-R-INDEX, IB-X-AMPL]  X Amplitude correcting BRAM */
#define SMP_IB_Y_PHASE_TABLE      0x00078000          /* [IB-R-INDEX, IB-Y-PHASE] Y Phase correcting BRAM */
#define SMP_IB_Y_AMPL_TABLE       0x00080000          /* [IB-R-INDEX, IB-Y-AMPL]  Y Amplitude correcting BRAM */
/* Correction coefficients signals */
#define SMP_PHASE_R_IDX           0x00000096          /* Corrected reference channel phase */
#define SMP_PHASE_X_IDX           0x0000009A          /* Corrected x channel phase */
#define SMP_PHASE_Y_IDX           0x0000009E          /* Corrected y channel phase */
/* Attenuator calibration */
#define SMP_AC_ENA_IDX            0x000000A0          /* AC-ENA */
#define SMP_AC_R_IDX              0x000000A4          /* R-DSA */
#define SMP_AC_R_PHASE_TABLE      0x00088000          /* [R-DSA, AC-R-PHASE] R Phase correcting BRAMM */
#define SMP_AC_R_AMPL_TABLE       0x00090000          /* [R-DSA, AC-R-AMPL]  R Amplitude correcting BRA */
#define SMP_AC_X_IDX              0x000000A8          /* X-DSA */
#define SMP_AC_X_PHASE_TABLE      0x00098000          /* [X-DSA, AC-R-PHASE] R Phase correcting BRAMM */
#define SMP_AC_X_AMPL_TABLE       0x000A0000          /* [X-DSA, AC-R-AMPL]  R Amplitude correcting BRA */
#define SMP_AC_Y_IDX              0x000000AC          /* Y-DSA */
#define SMP_AC_Y_PHASE_TABLE      0x000A8000          /* [Y-DSA, AC-R-PHASE] R Phase correcting BRAMM */
#define SMP_AC_Y_AMPL_TABLE       0x000B0000          /* [Y-DSA, AC-R-AMPL]  R Amplitude correcting BRA */
/* Beam angle correction */
#define SMP_BA_ENA_IDX            0x000000B0          /* BA-ENA */
#define SMP_BA_X_IDX              0x000000B4          /* BA-X */
#define SMP_BA_Y_IDX              0x000000B8          /* BA-Y */
/* Scaling to engineering units calculation */
#define SMP_SCALE_R_IDX           0x000000D0          /* R-SCALE-EGU * R-SCALE */
#define SMP_SCALE_X_IDX           0x000000E0          /* X-SCALE-EGU * X-SCALE */
#define SMP_SCALE_Y_IDX           0x000000F0          /* Y-SCALE-EGU * Y-SCALE */
/* Rotation calculation */
#define SMP_ROT11_IDX             0x000000C0          /* ROT11 */
#define SMP_ROT12_IDX             0x000000C4          /* ROT12 */
#define SMP_ROT21_IDX             0x000000C8          /* ROT21 */
#define SMP_ROT22_IDX             0x000000CC          /* ROT22 */
/* MPS settings */
#define SYS_MPS_Q_THR_IDX         0x00000100          /* MPS Q threshold */
#define SYS_MPS_Q_MIN_IDX         0x00000104          /* MPS Q min */
#define SYS_MPS_Q_MAX_IDX         0x00000108          /* MPS Q max */
#define SYS_MPS_X_MIN_IDX         0x0000010C          /* MPS X min */
#define SYS_MPS_X_MAX_IDX         0x00000110          /* MPS X max */
#define SYS_MPS_Y_MIN_IDX         0x00000114          /* MPS Y min */
#define SYS_MPS_Y_MAX_IDX         0x00000118          /* MPS Y max */
/* Measurements */
#define SMP_Q_BRAM_BASE           0x00000000          /* Q BRAM */
#define SMP_X_BRAM_BASE           0x00008000          /* X BRAM */
#define SMP_Y_BRAM_BASE           0x00010000          /* Y BRAM */
/* Measurements validity */
#define SMP_Q_VALID_BRAM_BASE     0x00004000          /* Q-VALID BRAM */
#define SMP_X_VALID_BRAM_BASE     0x0000C000          /* X-VALID BRAM */
#define SMP_Y_VALID_BRAM_BASE     0x00014000          /* Y-VALID BRAM */
/* ADC buffer */
#define SMP_ADC0_BUFFER_BASE      0x000D0000          /* WAV-X-I */
#define SMP_ADC1_BUFFER_BASE      0x000D8000          /* WAV-X-Q */
#define SMP_ADC2_BUFFER_BASE      0x000E0000          /* WAV-REF-I */
#define SMP_ADC3_BUFFER_BASE      0x000E8000          /* WAV-REF-Q */
#define SMP_ADC4_BUFFER_BASE      0x000F0000          /* WAV-Y-I */
#define SMP_ADC5_BUFFER_BASE      0x000F8000          /* WAV-Y-Q */
/* CORDIC */
#define SMP_CD_R_PH_BRAM_BASE     0x00018000          /* R phase BRAM */
#define SMP_CD_R_PH_VAL_BRAM_BASE 0x0001C000          /* R phase valid BRAM */
#define SMP_CD_R_AM_BRAM_BASE     0x00020000          /* R amp BRAM */
#define SMP_CD_R_AM_VAL_BRAM_BASE 0x00024000          /* R amp valid BRAM */
#define SMP_CD_X_PH_BRAM_BASE     0x00028000          /* X phase BRAM */
#define SMP_CD_X_PH_VAL_BRAM_BASE 0x0002C000          /* X phase BRAM */
#define SMP_CD_X_AM_BRAM_BASE     0x00030000          /* X amp valid BRAM */
#define SMP_CD_X_AM_VAL_BRAM_BASE 0x00034000          /* X amp valid BRAM */
#define SMP_CD_Y_PH_BRAM_BASE     0x00038000          /* Y phase BRAM */
#define SMP_CD_Y_PH_VAL_BRAM_BASE 0x0003C000          /* Y phase BRAM */
#define SMP_CD_Y_AM_BRAM_BASE     0x00040000          /* Y amp valid BRAM */
#define SMP_CD_Y_AM_VAL_BRAM_BASE 0x00044000          /* Y amp valid BRAM */
/* Interpolation */
#define SMP_IP_T_BRAM_BASE        0x00048000          /* t_top BRAM */
#define SMP_IP_T_VAL_BRAM_BASE    0x0004C000          /* t_top BRAM valid */
#define SMP_IP_S_BRAM_BASE        0x00050000          /* s_top BRAM */
#define SMP_IP_S_VAL_BRAM_BASE    0x00054000          /* s_top BRAM valid */
/* Corrected phases */
#define SMP_R_PH_BRAM_BASE        0x000B8000          /* Corrected R phase BRAM */
#define SMP_R_PH_VAL_BRAM_BASE    0x000BC000          /* Corrected R phase BRAM valid */
#define SMP_X_PH_BRAM_BASE        0x000C0000          /* Corrected X phase BRAM */
#define SMP_X_PH_VAL_BRAM_BASE    0x000C4000          /* Corrected X phase BRAM valid */
#define SMP_Y_PH_BRAM_BASE        0x000C8000          /* Corrected Y phase BRAM */
#define SMP_Y_PH_VAL_BRAM_BASE    0x000CC000          /* Corrected Y phase BRAM valid */
/* Function declaration */
void smp_ena_wr(void);
void smp_mode_wr(void);
void smp_trig_val_wr(void);
void smp_b0_0_wr(void);
void smp_b1_0_wr(void);
void smp_b2_0_wr(void);
void smp_b3_0_wr(void);
void smp_s1_0_wr(void);
void smp_s1_1_wr(void);
void smp_s1_2_wr(void);
void bl_ena_wr(void);
void bl_exp_wr(void);
void bl_del_wr(void);
void smp_default(void);
void smp_init(void);

#endif /* SMP_H_ */

/* EOF */
