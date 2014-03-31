#include <stdio.h>
#include "Bytecode.h"
#include "TBLRD.h"
#include <math.h>
#include "CException.h"

//default = file register
//default = access bank
// ACCESS = -5,
// BANKED,
// F,
// W.

void tblrd(Bytecode *code){
	
	int TableAddress;
	TableAddress = (((FSR[TBLPTRU])<<16)+((FSR[TBLPTRH])<<8)+FSR[TBLPTRL]);
	
	FSR[TABLAT] = TABLE[TableAddress];
	
	PC++;

}