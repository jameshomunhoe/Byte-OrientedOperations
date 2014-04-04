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

/**
*	
*	Function Name 	: tblrd
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: FSR[TABLAT]
*	
*	Description		: This fuction will read the table and save the value in table latch (TABLAT)
*
*
*
**/

int tblrd(Bytecode *code){
	
	int TableAddress;
	TableAddress = (((FSR[TBLPTRU])<<16)+((FSR[TBLPTRH])<<8)+FSR[TBLPTRL]);
	
	FSR[TABLAT] = TABLE[TableAddress];
	
	code->absoluteAddress++;
	return code->absoluteAddress;

}