#include <stdio.h>
#include "Bytecode.h"
#include "RETURN.h"
#include <math.h>
#include "CException.h"


// pop = read dec counter
// push = inc and push

/**
*	
*	Function Name 	: return
*	Input			: Bytecode
*	Output			: Address from TopOfStack(TOS)
*	Destroy			: FSR[TOSU],FSR{TOSH],FSR[TOSL]
*	
*	Description		: This fuction will return to the address of TopOfStack
*
*
*
**/

int return1(Bytecode *code){

	//fixture shadow register
	int	WREGS = 0x12;
	int STATUSS = 0x20;
	int BSRS	= 0x8;

if(code->operand1 >= -1 && code->operand1 <=1){
	
	/* 
	not sure yet should include pop
	int stackAddress = PIC18Stack[FSR[STKPTR]];
	
	FSR[TOSU] = (stackAddress&0xff0000)>>16;
	FSR[TOSH] = (stackAddress&0xff00)>>8;
	FSR[TOSL] = stackAddress&0xff;

	FSR[STKPTR]--;
	*/
	
	if(code->operand1 == 1){
		FSR[WREG] = WREGS;
		FSR[STATUS] = STATUSS;
		FSR[BSR] = BSRS;
	}
	return (FSR[TOSU]<<16)+(FSR[TOSH]<<8)+FSR[TOSL];
}
else
	Throw(INVALID_OP1);
}