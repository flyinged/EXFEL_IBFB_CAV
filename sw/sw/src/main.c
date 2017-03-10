/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : main.c
// Author  : Waldemar Koprek, Section Diagnostic
//           Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.4 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This is the main of the Cavity BPM (BPM_FPGA) application.
//----------------------------------------------------------------------------
*/
/* Include files */
#include <xio.h>
#include <xpseudo_asm_gcc.h>
#include <xil_cache.h>
#include <sleep.h>
#include <stdio.h>
#include <xparameters.h>
#include "version.h"
#include "interrupt.h"
#include "sys_init.h"
#include "rffe.h"
#include "adc16hl.h"
#include "smp.h"
#include "smp_phase_fb.h"
#include "iq_phase_fb.h"
#include "att_fb.h"
#include "eeprom_driver.h" //ML84 added for IBFB

static void init_system()
{
   u32   reg;
   u8 bpm_id, router, enable;

   /* Set up all components with default values only when FPGA is loaded but not when coming from reset but system was already set up */
   reg  = XIo_In32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_INIT_IDX);
   reg &= 0x00000001;
   if (reg == 0x00000000)
   {
      rffe_default();
      adc16hl_default();
      smp_default();
      smp_phase_fb_default();
      iq_phase_fb_default();
      att_fb_default();
      XIo_Out32(XPAR_SYS_INIT_INST_MEM0_BASEADDR + SYS_INIT_SMP_INIT_IDX + SYS_INIT_NO_IRQ_MASK, 1); /* 0 := newly loaded FPGA; 1 := already set up */
   }

   /* ML84 addition for IBFB */
   /* First read BPM_ID from EEPROM */
   eepromRead(0x0040, &bpm_id);
   /* Then write BPM_ID to BPM ROUTER component. Set also all transceivers to NO LOOPBACK mode */
   XIo_Out32(XPAR_IBFB_BPM_ROUTER_0_BASEADDR + 0x4, (((u32)bpm_id)<<24));
   /* KW84 added router configuration and BPM enable */
   eepromRead(0x0041, &router);
   eepromRead(0x0042, &enable);
   XIo_Out32(XPAR_IBFB_BPM_ROUTER_0_BASEADDR + 0x24, (((u32)router)<<8)+(u32)enable);

   /* Initialize interrupts */
   (void) initPPCInterrupts();

   return;
}

#define CACHEABLE_REGION_MASK 0x1

int main()
{
   /* Enable caches */
   Xil_ICacheEnableRegion(CACHEABLE_REGION_MASK);
   Xil_DCacheEnableRegion(CACHEABLE_REGION_MASK);

   /* Store software compilation date and time */
   software_version();

   /* Stop currently enabled sampling */
   XIo_Out8(XPAR_BPM_CAV_EXFEL_INST_BASEADDR + SMP_ENA_IDX, (u8) 0); /* SMP-ENA */

   /* Initialize BPM FPGA software */
   init_system();

   /* Initialize system */
   smp_init();

   /* Test */
   xil_printf("Init BPM_FPGA\r\n");

   /* Wait for next interrupt to be issued */
   for(;;) 
   {
      ;
   }

   /* Should never be reached due to endless loop stated before */
   /* Xil_DCacheDisable(); */
   /* Xil_ICacheDisable(); */

   /* return(0); */
}

/* EOF */
