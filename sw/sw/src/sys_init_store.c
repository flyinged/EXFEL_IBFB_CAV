/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : sys_init_store.c
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
#include "sys_init.h"

void sys_init_copy(void)
{
      u32   data_u32   = 0;
      float data_float = 0.0f;
      u32   phase   = 0;
      u32   index   = 0;

      /* Bunchtrain timing */
      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);        /* SMP_B0_0 */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_SMP_B0_0_IDX , data_u32);

       /* Attenuator feedback att_fb */
      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ON_IDX);  /* REF_GAIN_FB_ON */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_REF_GAIN_FB_ON_IDX , data_u32);

      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX);           /* R_DSA */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_R_DSA_IDX , data_u32);

      /* X attenuator feedback required? */
      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ON_IDX);    /* X_GAIN_FB_ON */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_X_GAIN_FB_ON_IDX , data_u32);

      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX);           /* X_DSA */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_X_DSA_IDX , data_u32);

      /* Y attenuator feedback required? */
      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ON_IDX);    /* Y_GAIN_FB_ON */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_Y_GAIN_FB_ON_IDX , data_u32);

      data_u32  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX);           /* Y_DSA */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_Y_DSA_IDX , data_u32);

       /* Sampling phase feedback smp_phase_fb */
      data_u32 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_ON_IDX);      /* SYS_INIT_PHASE_FB_ON */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PHASE_FB_ON_IDX , data_u32);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_REF_IDX);   /* SYS_INIT_PHASE_FB_REF */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PHASE_FB_REF_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_KP_IDX);    /* SYS_INIT_PHASE_FB_KP */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PHASE_FB_KP_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PHASE_FB_KI_IDX);    /* SYS_INIT_PHASE_FB_KI */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PHASE_FB_KI_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_CCLK_DDS_PHASE_IDX); /* DDS_PHASE */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_CCLK_DDS_PHASE_IDX , data_float);

       /* I/Q phase feedback iq_phase_fb */
      data_u32 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_ON_IDX);     /* SYS_INIT_PH_REF_FB_ON */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PH_REF_FB_ON_IDX , data_u32);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_REF_IDX);  /* SYS_INIT_PH_REF_FB_REF */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PH_REF_FB_REF_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_KP_IDX);   /* SYS_INIT_PH_REF_FB_KP */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PH_REF_FB_KP_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_PH_REF_FB_KI_IDX);   /* SYS_INIT_PH_REF_FB_KI */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_PH_REF_FB_KI_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_LO_PHASE_IDX);       /* SYS_INIT_LO_PHASE */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_LO_PHASE_IDX , data_float);

       /* I/Q imbalance correction */
      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_IB_ENA_IDX);                /* IB_ENA */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_ENA_IDX , data_u32);

      /* Read current Reference phase */
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_CD_R_PH_BRAM_BASE);
      /* Retrieve index from phase */
      index = phase >> 22;

       XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_R_INDEX_IDX , index);                     /* IB_R_INDEX */

      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_PHASE_TABLE + (index * 4));     /* IB_R_PHASE */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_R_PHASE_IDX, data_u32);

      data_float = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_R_AMPL_TABLE + (index * 4));    /* IB_R_AMPL */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_R_AMPL_IDX , data_float);

      /* Read current X phase */
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_CD_X_PH_BRAM_BASE);
      /* Retrieve index from phase */
      index = phase >> 22;

      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_X_INDEX_IDX , index);                     /* IB_X_INDEX */

      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_PHASE_TABLE + (index * 4));     /* IB_X_PHASE */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_X_PHASE_IDX, data_u32);

      data_float = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_X_AMPL_TABLE + (index * 4));    /* IB_X_AMPL */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_X_AMPL_IDX , data_float);

      /* Read current Y phase */
      phase = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_CD_Y_PH_BRAM_BASE);
      /* Retrieve index from phase */
      index = phase >> 22;

      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_Y_INDEX_IDX , index);                     /* IB_Y_INDEX */

      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_PHASE_TABLE + (index * 4));     /* IB_Y_PHASE */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_Y_PHASE_IDX, data_u32);

      data_float = XIo_Infs(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_IB_Y_AMPL_TABLE + (index * 4));    /* IB_Y_AMPL */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_IB_Y_AMPL_IDX , data_float);

       /* Attenuator calibration */
      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_AC_ENA_IDX);                /* AC_ENA */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_ENA_IDX , data_u32);

      data_u32 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_R_PHASE_IDX);                 /* AC_R_PHASE */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_R_PHASE_IDX , data_u32);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_R_AMPL_IDX);                /* AC_R_AMPL */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_R_AMPL_IDX , data_float);

      data_u32 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_X_PHASE_IDX);                 /* AC_X_PHASE */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_X_PHASE_IDX , data_u32);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_X_AMPL_IDX);                /* AC_X_AMPL */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_X_AMPL_IDX , data_float);

      data_u32 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_Y_PHASE_IDX);                 /* AC_Y_PHASE */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_Y_PHASE_IDX , data_u32);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_AC_Y_AMPL_IDX);                /* AC_Y_AMPL */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_AC_Y_AMPL_IDX , data_float);

       /* Beam angle feedback beam_angle_fb */
      data_u32 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BA_FB_ENA_IDX);        /* PH_XY_R_OFS_FB_ON */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_BA_FB_ENA_IDX , data_u32);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_BA_FB_THR_IDX);      /* PH_XY_R_OFS_FB_THR */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_BA_FB_THR_IDX , data_float);

      data_float = XIo_Infs(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Q_FB_THR_IDX);       /* Q_FB_THR */
      XIo_Outfs(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_Q_FB_THR_IDX , data_float);

      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BA_ENA_IDX);                /* BA_ENA */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_BA_ENA_IDX , data_u32);

      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BA_X_IDX);                  /* BA_X */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_BA_X_IDX , data_u32);

      data_u32 = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_BA_Y_IDX);                  /* BA_Y */
      XIo_Out32(XPAR_MEAS_BRAM_CNTLR_INST_BASEADDR + SYS_INIT_BA_Y_IDX , data_u32);
}

/* EOF */
