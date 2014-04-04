#include <stdio.h>
#include "Bytecode.h"
#include "BNC.h"
#include <math.h>
#include "CException.h"

/**
*	
*	Function Name 	: bnc
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: null
*	
*	Description		: This fuction will branch if the FSR[STATUS] has no carry
*
*
*
**/
int bnc(Bytecode *code){
	
	if(code->operand2 == -1){
		if(code->operand3 == -1){
		
			if(FSR[STATUS] & 0x01){
				code->absoluteAddress++;
				return code->absoluteAddress;
			}
			else
				return code->operand1;
		}
		else
			Throw(INVALID_OP3);
	}
	else
		Throw(INVALID_OP2);
}