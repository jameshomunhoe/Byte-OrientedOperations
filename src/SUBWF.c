#include <stdio.h>
#include "Bytecode.h"
#include "SUBWF.h"
#include <math.h>
#include "CException.h"


void subwf(Bytecode *code){

	int bankedValue = FSR[code->operand1+(FSR[BSR]<<8)]-FSR[WREG];
	int accessValue;
	
	if(code->operand1 >=0x80)
		accessValue = FSR[code->operand1+((0xf)<<8)]-FSR[WREG];
	else
		accessValue = FSR[code->operand1]-FSR[WREG];
	
	
if(code->operand1 >= 0x00 && code->operand1 <= 0xff){
	if(code->operand2 >= -5 && code->operand2 <= 1){
		if(code->operand3 >= -5 && code->operand3 <= 1){
	
			if(code->operand2 == -1 && code->operand3 == -1){
				if(code->operand1 >=0x80)
					FSR[code->operand1+((0xf)<<8)] = accessValue;
				else 
					FSR[code->operand1] = accessValue;
			}
	
			else if(code->operand2 == F || code->operand2 == 1 ){
				if(code->operand3==BANKED || code->operand3 == 1){
					FSR[code->operand1+(FSR[BSR]<<8)] = bankedValue;
				}
				else if(code->operand3==ACCESS || code->operand3==-1 || code->operand3 == 0){
					if(code->operand1 >=0x80)
						FSR[code->operand1+((0xf)<<8)] = accessValue;
					else 
						FSR[code->operand1] = accessValue;
				}
				else
					Throw(INVALID_OP3);
			}
	
			else if(code->operand2 == W || code->operand2 == 0){
				if(code->operand3==BANKED || code->operand3 == 1)
					FSR[WREG] = bankedValue;
				else if(code->operand3==ACCESS || code->operand3==-1 || code->operand3 == 0)
					FSR[WREG] = accessValue;
				else
					Throw(INVALID_OP3);
			}
	
			else if(code->operand2 == ACCESS){
				if(code->operand3 == -1){
					if(code->operand1 >=0x80)
						FSR[code->operand1+((0xf)<<8)] = accessValue;
					else 
						FSR[code->operand1] = accessValue;
				}
				else
					Throw(INVALID_OP3);
			}
	
			else if(code->operand2 == BANKED){
				if(code->operand3 == -1)
					FSR[code->operand1+(FSR[BSR]<<8)] = bankedValue;
				else
					Throw(INVALID_OP3);
			}
			else
				Throw(INVALID_OP3);
				
			if((code->operand2 == BANKED) || code->operand3 == BANKED)
				updateFlag(bankedValue);
			else if(code->operand2 == -1 || code->operand2==1 || (code->operand2 == ACCESS&&code->operand3 == -1) )
				updateFlag(accessValue);
		}
		else
			Throw(INVALID_OP3);
	}
	else
		Throw(INVALID_OP2);
}
else
	Throw(INVALID_OP1);
	
code->absoluteAddress++;	
}

//status affected C,DC,Z,OV,N
//undone DC,OV
void updateFlag (int value){
	
	FSR[STATUS] = 0;
	int valueCheck = value;
	
	//zero
	if(valueCheck == 0)
	FSR[STATUS] = FSR[STATUS] | 0x04;
	
	//negative
	if((valueCheck)>7 == 1)
	FSR[STATUS] = FSR[STATUS] | 0x10;
	
	//carry
	if((valueCheck)>7 == 0)
	FSR[STATUS] = FSR[STATUS] | 0x01;
}