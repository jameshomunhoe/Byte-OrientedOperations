#include <stdio.h>
#include "Bytecode.h"
#include "MULWF.h"
#include <math.h>

void mulwf(Bytecode *code){

int tempForAnswer;

if(code->operand1 >= 0x00 && code->operand1 <= 0xff){

		if(code->operand2==1){
			tempForAnswer = FSR[code->operand1+(FSR[BSR]<<8)]*FSR[WREG];
		}
		else{
			if(code->operand1 >=0x80)
			tempForAnswer = FSR[code->operand1+((0xf)<<8)]*FSR[WREG];
			else
			tempForAnswer = FSR[code->operand1]*FSR[WREG];
		}
		}
else
	printf("Invalid operand1. File register must less than 0x100 and at least 0x00\n");

	FSR[PRODH] = (tempForAnswer&0xff00)>>8;
	FSR[PRODL] = (tempForAnswer&0x00ff);
}