#include <stdio.h>
#include "Bytecode.h"
#include "RETURN.h"
#include <math.h>
#include "CException.h"


// pop = read dec counter
// push = inc and push

void return1(Bytecode *code){

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
	
	PC = (FSR[TOSU]<<16)+(FSR[TOSH]<<8)+FSR[TOSL];
	
	if(code->operand1 == 1){
		FSR[WREG] = WREGS;
		FSR[STATUS] = STATUSS;
		FSR[BSR] = BSRS;
	}
}
else
	Throw(INVALID_OP1);
}