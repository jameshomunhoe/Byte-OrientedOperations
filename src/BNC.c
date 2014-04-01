#include <stdio.h>
#include "Bytecode.h"
#include "BNC.h"
#include <math.h>
#include "CException.h"

void bnc(Bytecode *code){
	
	if(code->operand2 == -1){
		if(code->operand3 == -1){
		
			if(FSR[STATUS] & 0x01)
				PC+=2;
			else
				PC = code->operand1;
		}
		else
			Throw(INVALID_OP3);
	}
	else
		Throw(INVALID_OP2);
}