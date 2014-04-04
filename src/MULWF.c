#include <stdio.h>
#include "Bytecode.h"
#include "MULWF.h"
#include "CException.h"


//default = file register
//default = access bank
// ACCESS = -5,
// BANKED,
// F,
// W


/**
*	
*	Function Name 	: mulwf
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: FSR[PRODH],FSR[PRODL]
*	
*	Description		: This fuction will do multiplication between fileregister value and WorkingRegister(WREG), and answer will save it FSR[PRODH] and FSR[PRODL]
*
*
*
**/
int mulwf(Bytecode *code){

int tempForAnswer;

if(code->operand3 == -1){

	if(code->operand1 >= 0x00 && code->operand1 <= 0xfff){

		if(code->operand2 == -1){
			if(code->operand1 >= 0x80 && code->operand1 <= 0xff)
				tempForAnswer = FSR[code->operand1+((0xf)<<8)]*FSR[WREG];
			else
				tempForAnswer = FSR[code->operand1]*FSR[WREG];
		}
	
		if (code->operand2 == ACCESS || code->operand2 == 0){
			if((code->operand1 >= 0x00 && code->operand1 <= 0x7f) || (code->operand2 >= 0xf80 && code->operand2 <= 0xfff))
				tempForAnswer = FSR[code->operand1]*FSR[WREG];
			else if(code->operand1 >= 0x80 && code->operand1 <= 0xff)
				tempForAnswer = FSR[code->operand1+((0xf)<<8)]*FSR[WREG];
			else
				Throw(INVALID_OP2);
		}

		if(code->operand2 == BANKED ||code->operand2 == 1)
			tempForAnswer = FSR[code->operand1+(FSR[BSR]<<8)]*FSR[WREG];
	}
	else
		Throw(INVALID_OP1);
}
else
	Throw(INVALID_OP3);
	
	code->absoluteAddress++;
	FSR[PRODH] = (tempForAnswer&0xff00)>>8;
	FSR[PRODL] = (tempForAnswer&0x00ff);
	return code->absoluteAddress;
}






	
	
	
	
	
	// if(code->operand2==BANKED || code->operand2==1){
			// tempForAnswer = FSR[code->operand1+(FSR[BSR]<<8)]*FSR[WREG];
		// }
		// else if(code->operand2==ACCESS || code->operand2==-1 || code->operand2==0){
			// if(code->operand1 >=0x80)
			// tempForAnswer = FSR[code->operand1+((0xf)<<8)]*FSR[WREG];
			// else
			// tempForAnswer = FSR[code->operand1]*FSR[WREG];
		// }
		// else
			// Throw(INVALID_OP2);



