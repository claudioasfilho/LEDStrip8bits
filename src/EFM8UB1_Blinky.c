//-----------------------------------------------------------------------------
// EFM8UB1_Blinky.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This program flashes the red/green/blue LED on the EFM8UB1 STK board about
// five times a second using the interrupt handler for Timer2.
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC0 / 8
//   Timer2 - 5 Hz interrupt
//   P1.4   - LED green
//   P1.5   - LED blue
//   P1.6   - LED red
//   P2.3   - Display enable
//
//-----------------------------------------------------------------------------
// How To Test: EFM8UB1 STK
//-----------------------------------------------------------------------------
// 1) Place the switch in "AEM" mode.
// 2) Connect the EFM8UB1 STK board to a PC using a mini USB cable.
// 3) Compile and download code to the EFM8UB1 STK board.
//    In Simplicity Studio IDE, select Run -> Debug from the menu bar,
//    click the Debug button in the quick menu, or press F11.
// 4) Run the code.
//    In Simplicity Studio IDE, select Run -> Resume from the menu bar,
//    click the Resume button in the quick menu, or press F8.
// 5) The RGB LED should alternate colors at approximately 5 Hz.
//
// Target:         EFM8UB1
// Tool chain:     Generic
//
// Release 0.1 (MW, ST)
//    - Initial Revision
//    - 10 OCT 2014
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8UB1_Register_Enums.h>
#include <InitDevice.h>


//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
SI_SBIT (DISP_EN, SFR_P2, 3);          // Display Enable
#define DISP_BC_DRIVEN   0             // 0 = Board Controller drives display
#define DISP_EFM8_DRIVEN 1             // 1 = EFM8 drives display


void ANYCOLORS (void);
void LEDSLOOP (void);
//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
  // Disable the watchdog here
}

void logicZero()
{
	#pragma asm
	   SETB P1.4;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   CLR P1.4;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	   NOP;
	#pragma endasm
}

void logicOne()
{

}

void logicReseta()
{
	//static unsigned int counterLedReset;


	//for(counterLedReset=0 ; counterLedReset<390; counterLedReset++)__asm__("NOP");


}
 
//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main (void)
{
   enter_DefaultMode_from_RESET();

   DISP_EN = DISP_BC_DRIVEN;           // Display not driven by EFM8

   IE_EA = 0;                          // Enable global interrupts

   LEDSLOOP();

#if 0
#pragma asm

DELAY MACRO CNT;
	  REPT  CNT;
	   NOP;
	   ENDM
	  ENDM

LOGICAZERO MACRO;
SETB P1.4;
REPT  13;
	NOP;
	ENDM
CLR P1.4;
REPT  40;
	NOP;
	ENDM
SETB P1.4;
ENDM

LOGICAONE MACRO;
SETB P1.4;
REPT  22;
	NOP;
	ENDM
CLR P1.4;
REPT  27;
	NOP;
	ENDM
SETB P1.4;
ENDM

LOGICBZERO MACRO;
SETB P1.4;
REPT  8;
	NOP;
	ENDM
CLR P1.4;
REPT  40;
	NOP;
	ENDM
SETB P1.4;
ENDM

LOGICBONE MACRO;
SETB P1.4;
REPT  22;
	NOP;
	ENDM
CLR P1.4;
REPT  15;
	NOP;
	ENDM
SETB P1.4;
ENDM


DELAY1US MACRO;
REPT  48;
	NOP;
	ENDM
ENDM


LOGICARESET MACRO;
CLR P1.4;
REPT  80;
	DELAY1US;
	ENDM
SETB P1.4;
ENDM

COLORRED Macro;

;GREEN

	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;

;RED

	LOGICAONE;
	LOGICAONE;
	LOGICAONE;
	LOGICAONE;
	LOGICAONE;
	LOGICAONE;
	LOGICAONE;
	LOGICAONE;

;BLUE
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;
	LOGICAZERO;



	ENDM

BMOVE   MACRO   cnt
LOCAL   lab
		MOV     R2,#cnt

lab:    MOV     A,@R1
		MOV     @R0,A
		INC     R0
		INC     R1
		DJNZ    R2,lab
		ENDM


COLORBLUE Macro;

	;GREEN
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;


	;RED
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;

	;BLUE

		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;

		ENDM

COLORGREEN Macro;

	;GREEN
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;
		LOGICAONE;


	;RED
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;

	;BLUE
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		ENDM





COLORTEST Macro;

		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		LOGICAZERO;
		ENDM




SETB P1.4;

 COLORTEST
 ANYCOLORS:	MOV B,#08h;
 			MOV A, #0Fh;
 BBSTART:	CLR C;
 			RLC A;
 			JC CASELONE;
 CASELONE:	LOGICBONE;
 			JMP BBEND;
 CASELZERO: 	LOGICBZERO;
 BBEND: 		DJNZ B, BBSTART;
 COLORTEST;

 LOGICARESET;
 END

#pragma endasm

#endif

}
