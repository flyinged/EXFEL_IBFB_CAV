/*
//----------------------------------------------------------------------------
//                       Paul Scherrer Institute (PSI)
//----------------------------------------------------------------------------
// Unit    : version.h
// Author  : Goran Marinkovic, Section Diagnostic
// Version : $Revision: 1.1 $
//----------------------------------------------------------------------------
// Copyrightę PSI, Section Diagnostic
//----------------------------------------------------------------------------
// Comment : This file is used for the compile date and time conversion.
//----------------------------------------------------------------------------
*/
#ifndef VERSION_H_
#define VERSION_H_

/* Include files */
#include <xil_types.h>
#include <xio.h>
#include <xparameters.h>

/* Data declaration */
/* Output of __DATE__ : */
/* Jan  1 2015 */
/* Feb  1 2015 */
/* Mar  1 2015 */
/* Apr  1 2015 */
/* May  1 2015 */
/* Jun  1 2015 */
/* Jul  1 2015 */
/* Aug  1 2015 */
/* Sep  1 2015 */
/* Oct  1 2015 */
/* Nov  1 2015 */
/* Dec  1 2015 */
/* 0123456789A */
#define DATE_YEAR (((__DATE__[ 7] - '0') * 1000) + ((__DATE__[ 8] - '0') * 100) + ((__DATE__[ 9] - '0') * 10) + (__DATE__[10] - '0'))
#define DATE_MONTH (__DATE__[ 0] == 'J' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'n' ?  1 :\
                    __DATE__[ 0] == 'F' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'b' ?  2 :\
                    __DATE__[ 0] == 'M' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'r' ?  3 :\
                    __DATE__[ 0] == 'A' && __DATE__[ 1] == 'p' && __DATE__[ 2] == 'r' ?  4 :\
                    __DATE__[ 0] == 'M' && __DATE__[ 1] == 'a' && __DATE__[ 2] == 'y' ?  5 :\
                    __DATE__[ 0] == 'J' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'n' ?  6 :\
                    __DATE__[ 0] == 'J' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'l' ?  7 :\
                    __DATE__[ 0] == 'A' && __DATE__[ 1] == 'u' && __DATE__[ 2] == 'g' ?  8 :\
                    __DATE__[ 0] == 'S' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'p' ?  9 :\
                    __DATE__[ 0] == 'O' && __DATE__[ 1] == 'c' && __DATE__[ 2] == 't' ? 10 :\
                    __DATE__[ 0] == 'N' && __DATE__[ 1] == 'o' && __DATE__[ 2] == 'v' ? 11 :\
                    __DATE__[ 0] == 'D' && __DATE__[ 1] == 'e' && __DATE__[ 2] == 'c' ? 12 :\
                    0)
#define DATE_DAY   (__DATE__[ 4] == ' ' ? (__DATE__[ 5] - '0') : (((__DATE__[ 4] - '0') * 10) + (__DATE__[ 5] - '0')))

/* Output of __TIME__ : */
/* 14:30:30 */
/* 01234567 */
#define TIME_HOUR   (__TIME__[0] == ' ' ? (__TIME__[1] - '0') : (((__TIME__[0] - '0') * 10) + (__TIME__[1] - '0')))
#define TIME_MINUTE (__TIME__[3] == ' ' ? (__TIME__[4] - '0') : (((__TIME__[3] - '0') * 10) + (__TIME__[4] - '0')))

/* Function declaration */
void software_version(void);

#endif /* VERSION_H_ */

/* EOF */
