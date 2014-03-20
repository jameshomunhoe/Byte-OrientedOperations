#include <stdio.h>
#include "Bytecode.h"
#include "ANDWF.h"
#include <math.h>

void andwf(Bytecode *code){

	int bankedValue = FSR[code->operand1+(FSR[BSR]<<8)]&FSR[WREG];
	int accessValue;
	
if(code->operand1 >= 0x00 && code->operand1 <= 0xff){
	
	if(code->operand1 >=0x80)
	accessValue = FSR[code->operand1+((0xf)<<8)]&FSR[WREG];
	else
	accessValue = FSR[code->operand1]&FSR[WREG];
	
	
	
	if(code->operand2 ==1){
		if(code->operand3==1){
			FSR[code->operand1+(FSR[BSR]<<8)] = bankedValue;
		}
		else{
			if(code->operand1 >=0x80)
			FSR[code->operand1+((0xf)<<8)] = accessValue;
			else 
			FSR[code->operand1] = accessValue;
		}
	}
	else{
		if(code->operand3==1)
			FSR[WREG] = bankedValue;
		else
			FSR[WREG] = accessValue;
	}
	}
else
	printf("Invalid operand1. File register must less than 0x100 and at least 0x00\n");
}
