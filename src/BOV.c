#include <stdio.h>
#include "Bytecode.h"
#include "BOV.h"
#include <math.h>
#include "CException.h"

void bov(Bytecode *code){
	
	if(code->operand2 == -1){
		if(code->operand3 == -1){
		
			if((FSR[STATUS] & 0x08)>>3)
				PC = code->operand1;
			else
				PC++;
		}
		else
			Throw(INVALID_OP3);
	}
	else
		Throw(INVALID_OP2);
}