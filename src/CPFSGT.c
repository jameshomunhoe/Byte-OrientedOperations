#include <stdio.h>
#include "Bytecode.h"
#include "CPFSGT.h"
#include "CException.h"

//default = file register
//default = access bank
// ACCESS = -5,
// BANKED,
// F,
// W

//input fileaddress,access/bank


void cpfsgt(Bytecode *code){

if(code->operand3 == -1){

	if(code->operand1 >= 0x00 && code->operand1 <= 0xff){

		if(code->operand2==BANKED || code->operand2==1){
			if(FSR[code->operand1+(FSR[BSR]<<8)] > FSR[WREG])
				code->absoluteAddress = code->absoluteAddress + 2;
			else
				code->absoluteAddress++;
		}
	
		else if(code->operand2==ACCESS || code->operand2==-1 || code->operand2==0){
			if(code->operand1 >=0x80){
				if(FSR[code->operand1+((0xf)<<8)]>FSR[WREG])
					code->absoluteAddress = code->absoluteAddress + 2;
				else
					code->absoluteAddress++;
			}
			else{
				if(FSR[code->operand1]>FSR[WREG])
					code->absoluteAddress = code->absoluteAddress + 2;
				else
					code->absoluteAddress++;
			}
		}
		else
			Throw(INVALID_OP2);
	}
	else
		Throw(INVALID_OP1);
}
else
	Throw(INVALID_OP3);
}