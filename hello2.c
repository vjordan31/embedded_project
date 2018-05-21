/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */
/***************************************************************************/
/*                                                                         */
/*     H E L L O . C                                                       */
/*                                                                         */
/*     Basic LOG event operation from main.                                */
/*                                                                         */
/***************************************************************************/

// Miniproject main
//---------------------------------------------------------
#include "hellocfg.h" //BIOS include file
#include "framework.h"
#include <stdio.h>
#include <time.h>
#include "swi.h"
#include "hwi.h"
#include "tsk.h"
#include "sem.h"
#include "log.h"
#include <clk.h>

#undef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC (300000000)
extern cregister volatile unsigned int TSCL;
extern cregister volatile unsigned int TSCH;


uint8_t dip1, dip2, dip6, dip7, dip8;
int state = 0;
int16_t s16;
int16_t volatile dip_mask = 0xffff;

clock_t clock(){
	unsigned int low = TSCL;
	unsigned int high = TSCH;
	if (high) return (clock_t)-1;
	return low;

}
Void main(Void) {
	initAll();
	LED_turnOff(LED_1);
	LED_turnOff(LED_2);
	return; // return to BIOS scheduler
}

Void clk_main (){
	clock_t start_t,end_t;
	int i,y, c = 0;

	TSCL = 0;
	start_t = clock();

	for (i=0; i < 5000; i++) for (y = 0; y < 5000; y++)c++;
	end_t = clock()	;

	LOG_printf("Seconds: %f ---Ticks: %d\n", (double)(end_t - start_t)/CLOCKS_PER_SEC, end_t - start_t);
    printf("Done!\n");
}

Void dipStatus_PRD(Void) {
	DIP_get(DIP_1, &dip1);
	DIP_get(DIP_2, &dip2);
	DIP_get(DIP_6, &dip6);
	DIP_get(DIP_7, &dip7);
	DIP_get(DIP_8, &dip8);

	if(dip1){
		LED_turnOff(LED_1);
	    LED_turnOff(LED_2);
	    dip_mask=0x0000;
	}
	    else if(!dip1){
	    dip_mask=0xffff;

	}
}
/*
 *  ======== PRD for LED1 and LED2 flashing 20Hz | When dip1 and !dip2 ========
 */
Void systemOnBufferLED_PRD(Void) {
	if (dip1 && !dip2) {
		//		LOG_printf(&trace, "LED1 and LED2 flashing 20Hz");
		LED_toggle(LED_1);
		LED_toggle(LED_2);
	}
}

/*
 *  ======== PRD for LED1 flashing 2Hz  | When dip1 and dip2 ========
 */
Void systemBufferPlaybackLED_PRD(Void) {
	if (dip1 && dip2) {
		//		LOG_printf(&trace, "LED1 flashing 2Hz");
		LED_toggle(LED_1);
	}
}

/*
 *  ======== PRD for LED2 flashing 6Hz  | When dip1 and dip2 and dip6 or dip7 or dip8 =======
 */
Void systemFilBufferPlaybackLED_PRD(Void) {
	if (dip1 && dip2 && (dip6 || dip7 || dip8)) {
		//		LOG_printf(&trace, "LED2 flashing 6Hz");
		LED_toggle(LED_2);
	}
}

/*
 *  ======== audio input | When dip1 and !dip2 ========
 */
void audioHWI(void) {

	s16 = read_audio_sample();
	if (MCASP->RSLOT) { // left channel only
		s16 &= dip_mask;
		//write_audio_sample(s16);
	}

	// do everything here
	if (dip1 && dip2) {
		// store in buffer
	}
	else if (dip1 && dip2 && (dip6 || dip7 || dip8)){
		// do filtering
		if (dip6){

		}
		if (dip7){

		}
		if (dip8){

		}
	}

     write_audio_sample(s16);
}

