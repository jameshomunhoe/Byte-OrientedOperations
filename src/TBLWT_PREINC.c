#include <stdio.h>
#include "Bytecode.h"
#include "TBLWT_PREINC.h"
#include <math.h>
#include "CException.h"

//default = file register
//default = access bank
// ACCESS = -5,
// BANKED,
// F,
// W.

void tblwt_preinc(Bytecode *code){

	int TableAddress;
	
	if((((FSR[TBLPTRU])<<16)+((FSR[TBLPTRH])<<8)+FSR[TBLPTRL]) == 0x200000)
		Throw(OUT_OF_TABLE);
	
	if(FSR[TBLPTRL] == 0xff && FSR[TBLPTRH] != 0xff){
		FSR[TBLPTRL]++;
		FSR[TBLPTRH]++;
	}
		
	else if(FSR[TBLPTRL] == 0xff && FSR[TBLPTRH] == 0xff){
		FSR[TBLPTRL]++;
		FSR[TBLPTRH]++;
		FSR[TBLPTRU]++;
	}
	
	else
		FSR[TBLPTRL]++;
	
	
	TableAddress = (((FSR[TBLPTRU])<<16)+((FSR[TBLPTRH])<<8)+FSR[TBLPTRL]);
	
	TABLE[TableAddress] = FSR[TABLAT];
	
	PC++;
	
}