/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : att_fb.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the attenuation feedback. It contains the
//           feedback loop.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "att_fb.h"

void att_fb_default(void)
{
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ON_IDX + SYS_INIT_NO_IRQ_MASK,       1); /* 0 := disabled; 1 := enabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK,     70); /* 70% upper ADC level */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MIN_IDX + SYS_INIT_NO_IRQ_MASK,     50); /* 50% lower ADC level */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MIN_CNT_IDX + SYS_INIT_NO_IRQ_MASK,  1); /* 1 consecutive lower attenuation cases  */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK,  6); /* 6 dB Attenuator increment  */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ON_IDX   + SYS_INIT_NO_IRQ_MASK,       1); /* 0 := disabled; 1 := enabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK,       70); /* 70% upper ADC level */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MIN_IDX + SYS_INIT_NO_IRQ_MASK,       50); /* 50% lower ADC level */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MIN_CNT_IDX + SYS_INIT_NO_IRQ_MASK,    1); /* 1 consecutive lower attenuation cases  */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK,    6); /* 6 dB Attenuator increment  */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ON_IDX   + SYS_INIT_NO_IRQ_MASK,       1); /* 0 := disabled; 1 := enabled */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK,       70); /* 70% upper ADC level */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MIN_IDX + SYS_INIT_NO_IRQ_MASK,       50); /* 50% lower ADC level */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MIN_CNT_IDX + SYS_INIT_NO_IRQ_MASK,    1); /* 1 consecutive lower attenuation cases  */
   XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK,    6); /* 6 dB Attenuator increment  */
}

void att_fb(void)
{
   /* Bunch counter */
   u32   i = 0;
   /* Requested bunches to measure */
   u32   SMP_B0_0 = 0;
   /* Attenuation feedback control */
   u32        REF_GAIN_FB_ON          = 0;  /* Feedback enable */
   u32        REF_GAIN_FB_MAX         = 70; /* Upper limit in % to increase attenuation */
   u32        REF_GAIN_FB_MIN         = 50; /* Lower limit in % to decrease attenuation */
   u32        REF_GAIN_FB_MIN_CNT     = 1;  /* Consecutive occurrences needed in order to decrease attenuation */
   u32        REF_GAIN_FB_ATT_INC     = 6;  /* Attenuator increment */
   static u32 REF_GAIN_FB_MIN_COUNTER = 0;  /* Counter checking consecutive cases for decreasing attenuation */

   u32        X_GAIN_FB_ON          = 0;  /* Feedback enable */
   u32        X_GAIN_FB_MAX         = 70; /* Upper limit in % to increase attenuation */
   u32        X_GAIN_FB_MIN         = 50; /* Lower limit in % to decrease attenuation */
   u32        X_GAIN_FB_MIN_CNT     = 1;  /* Consecutive occurrences needed in order to decrease attenuation */
   u32        X_GAIN_FB_ATT_INC     = 6;  /* Attenuator increment */
   static u32 X_GAIN_FB_MIN_COUNTER = 0;  /* Counter checking consecutive cases for decreasing attenuation */

   u32        Y_GAIN_FB_ON          = 0;  /* Feedback enable */
   u32        Y_GAIN_FB_MAX         = 70; /* Upper limit in % to increase attenuation */
   u32        Y_GAIN_FB_MIN         = 50; /* Lower limit in % to decrease attenuation */
   u32        Y_GAIN_FB_MIN_CNT     = 1; /* Consecutive occurrences needed in order to decrease attenuation */
   u32        Y_GAIN_FB_ATT_INC     = 6;  /* Attenuator increment */
   static u32 Y_GAIN_FB_MIN_COUNTER = 0;  /* Counter checking consecutive cases for decreasing attenuation */

   u32   change    = 0;
   /* Measurements */
   u32   AMP_REF_R = 0; /* Currently measured amplitude */
   u32   R_DSA     = 0; /* Currently set attenuation */
   u32   AMP_X_R   = 0; /* Currently measured amplitude */
   u32   X_DSA     = 0; /* Currently set attenuation */
   u32   AMP_Y_R   = 0; /* Currently measured amplitude */
   u32   Y_DSA     = 0; /* Currently set attenuation */

   /* Load parameters and values and check valid range */
   SMP_B0_0 = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_B0_0_IDX);
   /* Reference attenuator feedback required? */
   REF_GAIN_FB_ON = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ON_IDX); /* Feedback enable */
   if (REF_GAIN_FB_ON == 1) /* Feedback required? */
   {
      /* Load the settings from user */
      R_DSA               = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_R_DSA_IDX);               /* Currently set attenuation */

      REF_GAIN_FB_MAX     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MAX_IDX);     /* Upper limit in % to increase attenuation */
      if (REF_GAIN_FB_MAX > 100)                                                                           /* Range check if upper limit is set to overdrive the ADC permanently */
      {
         REF_GAIN_FB_MAX = 100;
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK, REF_GAIN_FB_MAX);
      }
      if (REF_GAIN_FB_MAX < GAIN_FB_MAX_MIN_THR)                                                           /* Range check if lower limit is set to a value lower than the threshold */
      {
         REF_GAIN_FB_MAX = GAIN_FB_MAX_MIN_THR;
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK, REF_GAIN_FB_MAX);
      }
      REF_GAIN_FB_MIN     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MIN_IDX);     /* Lower limit in % to decrease attenuation */
      if ((REF_GAIN_FB_MIN + GAIN_FB_MAX_MIN_THR) > REF_GAIN_FB_MAX)                                       /* Range check if lower limit is higher than upper limit including a threshold */
      {
         if (REF_GAIN_FB_MIN > GAIN_FB_MAX_MIN_THR)                                                        /* Range check if lower limit is higher than the threshold to prevent underflow */
         {
            REF_GAIN_FB_MIN = REF_GAIN_FB_MAX - GAIN_FB_MAX_MIN_THR;
         }
         else
         {
            REF_GAIN_FB_MIN = 0;
         }
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MIN_IDX + SYS_INIT_NO_IRQ_MASK, REF_GAIN_FB_MIN);
      }

      /* Scaling to ADC codes */
      REF_GAIN_FB_MAX = REF_GAIN_FB_MAX * GAIN_FB_MAX_AMP / 100;                                           /* Scale from % values to ADC codes */
      REF_GAIN_FB_MIN = REF_GAIN_FB_MIN * GAIN_FB_MAX_AMP / 100;                                           /* Scale from % values to ADC codes */

      REF_GAIN_FB_MIN_CNT = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_MIN_CNT_IDX); /* Consecutive occurrences needed in order to decrease attenuation */
      /* Search maximum occurrence */
      change = 0; /* Keep it as it is */
      for (i = 0; i < SMP_B0_0; ++i) /* For all possible charge entries in the tables of the FPGA firmware */
      {
         AMP_REF_R = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + SMP_CD_R_AM_BRAM_BASE + (i * 4)); /* Currently measured amplitude */
         if      (AMP_REF_R >= GAIN_FB_MAX_SAT_AMP) /* Amplitude way too big? */
         {
            change = 4; /* Increase attenuation */
            break;      /* End for loop */
         }
         else if (AMP_REF_R > REF_GAIN_FB_MAX) /* Amplitude too big? */
         {
            change = 1; /* Request that at least one bunch does not require attenuation change keep it as it is */
            break;      /* End for loop */
         }
         else if (AMP_REF_R > REF_GAIN_FB_MIN)
         {
             change = 3; /* Request that at least one bunch does not require attenuation change keep it as it is */
         }
         else if ((AMP_REF_R > 200))  /* Amplitude too small (only noise) or attenuation still to big? */
         {
            if (change == 0) /* If till now the attenuation shall be kept */
            {
               change = 2; /* Decrease attenuation */
            }
         }
         else if (R_DSA > 20)  /* Amplitude too small (only noise) or attenuation still to big? */
         {
            if (change == 0) /* If till now the attenuation shall be kept */
            {
               change = 5; /* Decrease attenuation */
            }
         }
      }
      /* Set attenuator if necessary */
      switch(change)
      {
         /* Increase attenuation */
         case 1:
            REF_GAIN_FB_ATT_INC     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ATT_INC_IDX); /* Value to increase attenuation if at upper limit */
            if (REF_GAIN_FB_ATT_INC > 63)  /* Range check if attenuator increment is too high and will exceed the total available attenuation range */
            {
               REF_GAIN_FB_ATT_INC = 63;
               XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK, REF_GAIN_FB_ATT_INC);
            }
            if (REF_GAIN_FB_ATT_INC == 0)  /* Range check if attenuator increment is 0 which is not feasible it has at least to be 1 */
            {
               REF_GAIN_FB_ATT_INC = 1;
               XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_REF_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK, REF_GAIN_FB_ATT_INC);
            }
            /* Change the attenuation */
            R_DSA += REF_GAIN_FB_ATT_INC;
            if (R_DSA > 63) /* Attenuator overflow? */
            {
               R_DSA = 63; /* Saturate at 63 dB */
            }
            r_dsa_wr(R_DSA);
            REF_GAIN_FB_MIN_COUNTER = 0;
            break;
         case 4:
            /* Change the attenuation for 6 dB */
            R_DSA += 6;
            if (R_DSA > 63) /* Attenuator overflow? */
            {
               R_DSA = 63; /* Saturate at 63 dB */
            }
            r_dsa_wr(R_DSA);
            REF_GAIN_FB_MIN_COUNTER = 0;
            break;
         /* Decrease attenuation */
         case 2:
            if (R_DSA > 0) /* At the minimum of the attenuator? */
            {
               if (REF_GAIN_FB_MIN_COUNTER > REF_GAIN_FB_MIN_CNT)
               {
                  R_DSA -= 1;
                  REF_GAIN_FB_MIN_COUNTER = 0;
               }
               else
               {
                  ++REF_GAIN_FB_MIN_COUNTER;
               }
            }
            r_dsa_wr(R_DSA); /* Set attenuation */
            break;
         case 5:
            if (R_DSA > 0) /* At the minimum of the attenuator? */
            {
               R_DSA -= 1;
               REF_GAIN_FB_MIN_COUNTER = 0;
            }
            r_dsa_wr(R_DSA); /* Set attenuation */
            break;
            /* Keep it as it is */
         default:
            REF_GAIN_FB_MIN_COUNTER = 0;
            break;
      }
   }

   /* X attenuator feedback required? */
   X_GAIN_FB_ON = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ON_IDX); /* Feedback enable */

   if (X_GAIN_FB_ON == 1) /* Feedback required? */
   {
      /* Load the settings from user */
      X_DSA = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_DSA_IDX); /* Currently set attenuation */

      X_GAIN_FB_MAX     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MAX_IDX);     /* Upper limit in % to increase attenuation */
      if (X_GAIN_FB_MAX > 100)                                                                         /* Range check if upper limit is set to overdrive the ADC permanently */
      {
         X_GAIN_FB_MAX = 100;
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK, X_GAIN_FB_MAX);
      }
      if (X_GAIN_FB_MAX < GAIN_FB_MAX_MIN_THR)                                                           /* Range check if lower limit is set to a value lower than the threshold */
      {
         X_GAIN_FB_MAX = GAIN_FB_MAX_MIN_THR;
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK, X_GAIN_FB_MAX);
      }

      X_GAIN_FB_MIN     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MIN_IDX);     /* Lower limit in % to decrease attenuation */
      if ((X_GAIN_FB_MIN + GAIN_FB_MAX_MIN_THR) > X_GAIN_FB_MAX)                                       /* Range check if lower limit is higher than upper limit including a threshold */
      {
         if (X_GAIN_FB_MIN > GAIN_FB_MAX_MIN_THR)                                                      /* Range check if lower limit is higher than the threshold to prevent underflow */
         {
            X_GAIN_FB_MIN = X_GAIN_FB_MAX - GAIN_FB_MAX_MIN_THR;
         }
         else
         {
            X_GAIN_FB_MIN = 0;
         }
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MIN_IDX + SYS_INIT_NO_IRQ_MASK, X_GAIN_FB_MIN);
      }

      /* Scaling to ADC codes */
      X_GAIN_FB_MAX = X_GAIN_FB_MAX * GAIN_FB_MAX_AMP / 100;                                           /* Scale from % values to ADC codes */
      X_GAIN_FB_MIN = X_GAIN_FB_MIN * GAIN_FB_MAX_AMP / 100;                                           /* Scale from % values to ADC codes */

      X_GAIN_FB_MIN_CNT = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_MIN_CNT_IDX); /* Consecutive occurrences needed in order to decrease attenuation */

      /* Search maximum occurrence */
      change = 0; /* Keep it as it is */
      for (i = 0; i < SMP_B0_0; ++i) /* For all possible charge entries in the tables of the FPGA firmware */
      {
         AMP_X_R = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + 0x00030000 + (i * 4)); /* Currently measured amplitude */
         if      (AMP_X_R >= GAIN_FB_MAX_SAT_AMP) /* Amplitude way too big? */
         {
            change = 4; /* Increase attenuation */
            break;      /* End for loop */
         }
         else if (AMP_X_R > X_GAIN_FB_MAX) /* Amplitude too big? */
         {
            change = 1; /* Increase attenuation */
            break;      /* End for loop */
         }
         else if (AMP_X_R > X_GAIN_FB_MIN)
         {
             change = 3; /* Request that at least one bunch does not require attenuation change keep it as it is */
         }
         else /* Amplitude too small? */
         {
            if (change == 0) /* If till now the attenuation shall be kept */
            {
               change = 2; /* Decrease attenuation */
            }
         }
      }
      /* Set attenuator if necessary */
      switch(change)
      {
         /* Increase attenuation */
         case 1:
            X_GAIN_FB_ATT_INC     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ATT_INC_IDX); /* Value to increase attenuation if at upper limit */
            if (X_GAIN_FB_ATT_INC > 63)  /* Range check if attenuator increment is too high and will exceed the total available attenuation range */
            {
               X_GAIN_FB_ATT_INC = 63;
               XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK, X_GAIN_FB_ATT_INC);
            }
            if (X_GAIN_FB_ATT_INC == 0)  /* Range check if attenuator increment is 0 which is not feasible it has at least to be 1 */
            {
               X_GAIN_FB_ATT_INC = 1;
               XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_X_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK, X_GAIN_FB_ATT_INC);
            }
            /* Change the attenuation */
            X_DSA += X_GAIN_FB_ATT_INC;
            if (X_DSA > 63) /* Attenuator overflow? */
            {
               X_DSA = 63; /* Saturate at 63 dB */
            }
            x_dsa_wr(X_DSA);
            X_GAIN_FB_MIN_COUNTER = 0;
            break;
         case 4:
            /* Change the attenuation for 6 dB */
            X_DSA += 6;
            if (X_DSA > 63) /* Attenuator overflow? */
            {
               X_DSA = 63; /* Saturate at 63 dB */
            }
            x_dsa_wr(X_DSA);
            X_GAIN_FB_MIN_COUNTER = 0;
            break;
         /* Decrease attenuation */
         case 2:
            if (X_DSA > 0) /* At the minimum of the attenuator? */
            {
               if (X_GAIN_FB_MIN_COUNTER > X_GAIN_FB_MIN_CNT)
               {
                  X_DSA -= 1;
                  X_GAIN_FB_MIN_COUNTER = 0;
               }
               else
               {
                  ++X_GAIN_FB_MIN_COUNTER;
               }
            }
            x_dsa_wr(X_DSA); /* Set attenuation */
            break;
         /* Keep it as it is */
         default:
            X_GAIN_FB_MIN_COUNTER = 0;
            break;
      }
   }

   /* Y attenuator feedback required? */
   Y_GAIN_FB_ON = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ON_IDX); /* Feedback enable */
   if (Y_GAIN_FB_ON == 1) /* Feedback required? */
   {
      /* Load the settings from user */
      Y_DSA = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_DSA_IDX); /* Currently set attenuation */

      Y_GAIN_FB_MAX     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MAX_IDX);     /* Upper limit in % to increase attenuation */
      if (Y_GAIN_FB_MAX > 100)                                                                         /* Range check if upper limit is set to overdrive the ADC permanently */
      {
         Y_GAIN_FB_MAX = 100;
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK, Y_GAIN_FB_MAX);
      }
      if (Y_GAIN_FB_MAX < GAIN_FB_MAX_MIN_THR)                                                           /* Range check if lower limit is set to a value lower than the threshold */
      {
         Y_GAIN_FB_MAX = GAIN_FB_MAX_MIN_THR;
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MAX_IDX + SYS_INIT_NO_IRQ_MASK, Y_GAIN_FB_MAX);
      }

      Y_GAIN_FB_MIN     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MIN_IDX);     /* Lower limit in % to decrease attenuation */
      if ((Y_GAIN_FB_MIN + GAIN_FB_MAX_MIN_THR) > Y_GAIN_FB_MAX)                                       /* Range check if lower limit is higher than upper limit including a threshold */
      {
         if (Y_GAIN_FB_MIN > GAIN_FB_MAX_MIN_THR)                                                      /* Range check if lower limit is higher than the threshold to prevent underflow */
         {
            Y_GAIN_FB_MIN = Y_GAIN_FB_MAX - GAIN_FB_MAX_MIN_THR;
         }
         else
         {
            Y_GAIN_FB_MIN = 0;
         }
         XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MIN_IDX + SYS_INIT_NO_IRQ_MASK, Y_GAIN_FB_MIN);
      }

      /* Scaling to ADC codes */
      Y_GAIN_FB_MAX = Y_GAIN_FB_MAX * GAIN_FB_MAX_AMP / 100;                                           /* Scale from % values to ADC codes */
      Y_GAIN_FB_MIN = Y_GAIN_FB_MIN * GAIN_FB_MAX_AMP / 100;                                           /* Scale from % values to ADC codes */

      Y_GAIN_FB_MIN_CNT = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_MIN_CNT_IDX); /* Consecutive occurrences needed in order to decrease attenuation */

      /* Search maximum occurrence */
      change = 0; /* Keep it as it is */
      for (i = 0; i < SMP_B0_0; ++i) /* For all possible charge entries in the tables of the FPGA firmware */
      {
         AMP_Y_R = XIo_In32(XPAR_BPM_CAV_EXFEL_INST_MEM0_BASEADDR + 0x00040000 + (i * 4)); /* Currently measured amplitude */
         if      (AMP_Y_R >= GAIN_FB_MAX_SAT_AMP) /* Amplitude way too big? */
         {
            change = 4; /* Increase attenuation */
            break;      /* End for loop */
         }
         else if (AMP_Y_R > Y_GAIN_FB_MAX) /* Amplitude too big? */
         {
            change = 1; /* Increase attenuation */
            break;      /* End for loop */
         }
         else if (AMP_Y_R > Y_GAIN_FB_MIN)
         {
             change = 3; /* Request that at least one bunch does not require attenuation change keep it as it is */
         }
         else /* Amplitude too small? */
         {
            if (change == 0) /* If till now the attenuation shall be kept */
            {
               change = 2; /* Decrease attenuation */
            }
         }
      }
      /* Set attenuator if necessary */
      switch(change)
      {
         /* Increase attenuation */
         case 1:
            Y_GAIN_FB_ATT_INC     = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ATT_INC_IDX); /* Value to increase attenuation if at upper limit */
            if (Y_GAIN_FB_ATT_INC > 63)  /* Range check if attenuator increment is too high and will exceed the total available attenuation range */
            {
               Y_GAIN_FB_ATT_INC = 63;
               XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK, Y_GAIN_FB_ATT_INC);
            }
            if (Y_GAIN_FB_ATT_INC == 0)  /* Range check if attenuator increment is 0 which is not feasible it has at least to be 1 */
            {
               Y_GAIN_FB_ATT_INC = 1;
               XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_Y_GAIN_FB_ATT_INC_IDX + SYS_INIT_NO_IRQ_MASK, Y_GAIN_FB_ATT_INC);
            }
            /* Change the attenuation */
            Y_DSA += Y_GAIN_FB_ATT_INC;
            if (Y_DSA > 63) /* Attenuator overflow? */
            {
               Y_DSA = 63; /* Saturate at 63 dB */
            }
            y_dsa_wr(Y_DSA);
            Y_GAIN_FB_MIN_COUNTER = 0;
            break;
         case 4:
            /* Change the attenuation for 6 dB */
            Y_DSA += 6;
            if (Y_DSA > 63) /* Attenuator overflow? */
            {
               Y_DSA = 63; /* Saturate at 63 dB */
            }
            y_dsa_wr(Y_DSA);
            Y_GAIN_FB_MIN_COUNTER = 0;
            break;
         /* Decrease attenuation */
         case 2:
            if (Y_DSA > 0) /* At the minimum of the attenuator? */
            {
               if (Y_GAIN_FB_MIN_COUNTER > Y_GAIN_FB_MIN_CNT)
               {
                  Y_DSA -= 1;
                  Y_GAIN_FB_MIN_COUNTER = 0;
               }
               else
               {
                  ++Y_GAIN_FB_MIN_COUNTER;
               }
            }
            y_dsa_wr(Y_DSA); /* Set attenuation */
            break;
         /* Keep it as it is */
         default:
            Y_GAIN_FB_MIN_COUNTER = 0;
            break;
      }
   }
}
