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

/**
*	
*	Function Name 	: cpfsgt
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: null
*	
*	Description		: This fuction will skip if the file register is greater than Working Register(WREG)
*
*
*
**/
int cpfsgt(Bytecode *code){

if(code->operand3 == -1){

	if(code->operand1 >= 0x00 && code->operand1 <= 0xfff){

		if(code->operand2 ==-1){
			if(code->operand1 >= 0x80 && code->operand1 <= 0xff){
				if(FSR[(code->operand1&0xff)+((0xf)<<8)] > FSR[WREG])
					code->absoluteAddress+=2;
				else
					code->absoluteAddress++;
			}
			else
				if(FSR[code->operand1] > FSR[WREG])
					code->absoluteAddress+=2;
				else
					code->absoluteAddress++;
		}
			
		else if(code->operand2==ACCESS || code->operand2==0){
			if((code->operand1 >= 0x00 && code->operand1 <= 0x7f) || (code->operand1 >= 0x100 && code->operand1 <= 0xf7f)){
				if(FSR[code->operand1&0xff]>FSR[WREG])
					code->absoluteAddress+=2;
				else
					code->absoluteAddress++;
			}
			else{
				if(FSR[(code->operand1&0xff)+((0xf)<<8)]>FSR[WREG])
					code->absoluteAddress+=2;
				else
					code->absoluteAddress++;
			}
		}
		
		else if(code->operand2==BANKED || code->operand2==1){
			if(FSR[(code->operand1&0xff)+(FSR[BSR]<<8)] > FSR[WREG])
				code->absoluteAddress+=2;
			else
				code->absoluteAddress++;
		}
		
		
	}
	else
		Throw(INVALID_OP1);
}
else
	Throw(INVALID_OP3);
	
return code->absoluteAddress;
}