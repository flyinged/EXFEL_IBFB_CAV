/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : version.c
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyright© PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the compile date and time conversion.
//----------------------------------------------------------------------------
*/
/* Include files */
#include "version.h"

void software_version(void)
{
   /* Store the year */
   XIo_Out32(XPAR_VERSION_DATE_INST_BASEADDR + 0x00000018, DATE_YEAR);

   /* Store the month */
   XIo_Out32(XPAR_VERSION_DATE_INST_BASEADDR + 0x0000001C, DATE_MONTH);

   /* Store the day */
   XIo_Out32(XPAR_VERSION_DATE_INST_BASEADDR + 0x00000020, DATE_DAY);

   /* Store the hour */
   XIo_Out32(XPAR_VERSION_DATE_INST_BASEADDR + 0x00000024, TIME_HOUR);
   
   /* Store the minute */
   XIo_Out32(XPAR_VERSION_DATE_INST_BASEADDR + 0x00000028, TIME_MINUTE);

   return;
}

/* EOF */
