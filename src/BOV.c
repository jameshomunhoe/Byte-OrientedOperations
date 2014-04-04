#include <stdio.h>
#include "Bytecode.h"
#include "BOV.h"
#include <math.h>
#include "CException.h"


/**
*	
*	Function Name 	: bov
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: null
*	
*	Description		: This fuction will branch if the FSR[STATUS] has OverFlow
*
*
*
**/
int bov(Bytecode *code){
	
	if(code->operand2 == -1){
		if(code->operand3 == -1){
		
			if((FSR[STATUS] & 0x08)>>3)
				return code->operand1;
			else{
				code->absoluteAddress++;
				return code->absoluteAddress;
			}
		}
		else
			Throw(INVALID_OP3);
	}
	else
		Throw(INVALID_OP2);
}