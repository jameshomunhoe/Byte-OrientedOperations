#include <stdio.h>
#include "Bytecode.h"
#include "ANDWF.h"
#include <math.h>

void andwf(Bytecode *code){

if(code->operand1 >= 0x00 && code->operand1 <= 0xff){
	
	if(code->operand2 ==1){
		if(code->operand3==1){
			FSR[code->operand1+(FSR[BSR]<<8)] = FSR[code->operand1+(FSR[BSR]<<8)]&FSR[WREG];
		}
		else{
			FSR[code->operand1] = FSR[code->operand1]&FSR[WREG];
		}
	}
	else{
		if(code->operand3==1)
			FSR[WREG] = FSR[code->operand1+(FSR[BSR]<<8)]&FSR[WREG];
		else
			FSR[WREG] = FSR[code->operand1]&FSR[WREG];
	}
	}
else
	printf("Invalid operand1. File register must less than 0x100 and at least 0x00\n");
}
