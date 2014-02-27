#include <stdio.h>
#include "Bytecode.h"
#include "Byte-OrientedOperations.h"
#include <math.h>

char FSR[0x1000];

void andwf(Bytecode *code){

	if(code->operand2 == 0)
		FSR[WREG] = FSR[code->operand1]&FSR[WREG];
		
	else
		FSR[code->operand1] = FSR[code->operand1]&FSR[WREG];

}
