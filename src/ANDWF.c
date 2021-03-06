#include <stdio.h>
#include "Bytecode.h"
#include "ANDWF.h"
#include <math.h>
#include "CException.h"

//default = file register
//default = access bank
// ACCESS = -5,
// BANKED,
// F,
// W

/**
*	
*	Function Name 	: andwf
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: code.operand1,bankedAddress,accessAddress,bankedValue,accessValue
*	
*	Description		: This fuction will AND the input register address' value with the Working Register (WREG)
*
*
*
**/
int andwf(Bytecode *code){

	int bankedAddress;
	int accessAddress;
	int bankedValue;
	int accessValue;
	
		bankedAddress = (code->operand1&0xff)+((FSR[BSR])<<8);
		
	if(code->operand1 >= 0x80 && code->operand1 <= 0xff)
		accessAddress = (code->operand1&0xff)+((0xf)<<8);
	else if (code->operand1 >=0x100 && code->operand1 <=0xf7f)
		accessAddress = (code->operand1&0xff);
	else
		accessAddress = code->operand1;
		
		
		bankedValue = FSR[(code->operand1&0xff)+((FSR[BSR])<<8)]&FSR[WREG];
	
	if(code->operand1 >=0x80 && code->operand1 <=0xff)
		accessValue = FSR[(code->operand1&0xff)+((0xf)<<8)]&FSR[WREG];
	else if (code->operand1 >=0x100 && code->operand1 <=0xf7f)
		accessValue = FSR[(code->operand1&0xff)]&FSR[WREG];
	else
		accessValue = FSR[code->operand1]&FSR[WREG];
	
	
if(code->operand1 >= 0x00 && code->operand1 <= 0xfff){
	if(code->operand2 >= -5 && code->operand2 <= 1){
		if(code->operand3 >= -5 && code->operand3 <= 1){
	
			if(code->operand2 == -1 && code->operand3 == -1)
				FSR[accessAddress] = accessValue;
	
			else if(code->operand2 == F || code->operand2 == 1 ){
				if(code->operand3==BANKED || code->operand3 == 1)
					FSR[bankedAddress] = bankedValue;
				else if(code->operand3==ACCESS || code->operand3 == -1 ||code->operand3 == 0)
						FSR[accessAddress] = accessValue;
				else
					Throw(INVALID_OP3);
			}
	
			else if(code->operand2 == W || code->operand2 == 0){
				if(code->operand3==BANKED || code->operand3 == 1)
					FSR[WREG] = bankedValue;
				else if(code->operand3==ACCESS || code->operand3 == -1 || code->operand3 == 0)
						FSR[WREG] = accessValue;
				else
					Throw(INVALID_OP3);
			}
	
			else if(code->operand2 == ACCESS){
				if(code->operand3 == -1)
					FSR[accessAddress] = accessValue;
				else
					Throw(INVALID_OP3);
			}
	
			else if(code->operand2 == BANKED){
				if(code->operand3 == -1)
					FSR[bankedAddress] = bankedValue;
				else
					Throw(INVALID_OP3);
			}
			else
				Throw(INVALID_OP3);
				
			if((code->operand2 == BANKED) || code->operand3 == BANKED || code->operand3 == 1)
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
return code->absoluteAddress;	
}

void updateFlag (int value){
	
	FSR[STATUS] = 0;
	int valueCheck = value;
	
	if(valueCheck == 0)
	FSR[STATUS] = FSR[STATUS] | 0x04;
	
	if((valueCheck&0x80)>>7 == 1)
	FSR[STATUS] = FSR[STATUS] | 0x10;
	
}