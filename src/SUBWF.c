#include <stdio.h>
#include "Bytecode.h"
#include "SUBWF.h"
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
*	Function Name 	: subwf
*	Input			: Bytecode
*	Output			: code.absoluteAddress
*	Destroy			: code.operand1,bankedAddress,accessAddress,bankedValue,accessValue
*	
*	Description		: This fuction will subtract the input register address' value with the Working Register (WREG)
*
*
*
**/
int subwf(Bytecode *code){

	int bankedAddress;
	int accessAddress;
	int bankedValue;
	int accessValue;
	int forOVBSR = FSR[(code->operand1&0xff)+((FSR[BSR])<<8)];
	int forOVACS = FSR[code->operand1];
	int forOVBankF = FSR[(code->operand1&0xff)+((0xf)<<8)];
	int oriWreg = FSR[WREG];
	
		bankedAddress = (code->operand1&0xff)+((FSR[BSR])<<8);
		
	if(code->operand1 >= 0x80 && code->operand1 <= 0xff)
		accessAddress = (code->operand1&0xff)+((0xf)<<8);
	else if (code->operand1 >=0x100 && code->operand1 <=0xf7f)
		accessAddress = (code->operand1&0xff);
	else
		accessAddress = code->operand1;
		
		
		bankedValue = FSR[(code->operand1&0xff)+((FSR[BSR])<<8)]-FSR[WREG];
	
	if(code->operand1 >=0x80 && code->operand1 <=0xff)
		accessValue = FSR[(code->operand1&0xff)+((0xf)<<8)]-FSR[WREG];
	else if (code->operand1 >=0x100 && code->operand1 <=0xf7f)
		accessValue = FSR[(code->operand1&0xff)]-FSR[WREG];
	else
		accessValue = FSR[code->operand1]-FSR[WREG];
	
	
if(code->operand1 >= 0x00 && code->operand1 <= 0xfff){
	if(code->operand2 >= -5 && code->operand2 <= 1){
		if(code->operand3 >= -5 && code->operand3 <= 1){
	
			if(code->operand2 == -1 && code->operand3 == -1)
				FSR[accessAddress] = accessValue;
	
			else if(code->operand2 == F || code->operand2 == 1 ){
				if(code->operand3==BANKED || code->operand3 == 1)
					FSR[bankedAddress] = bankedValue;
				else if(code->operand3==ACCESS || code->operand3 == -1 ||code->operand3 == 0){
					if(code->operand3 == -1 && (code->operand1 >= 0x100 && code->operand1 <= 0xf7f))
						Throw(INVALID_OP2);
					else
						FSR[accessAddress] = accessValue;
				}
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
				updateFlag(bankedValue,forOVBSR,oriWreg);
			else if(code->operand2 == -1 || code->operand2==1 || (code->operand2 == ACCESS&&code->operand3 == -1) ){
				if(code->operand1 >=0x80 && code->operand1 <=0xff)
					updateFlag(accessValue,forOVBankF,oriWreg);
				else
					updateFlag(accessValue,forOVACS,oriWreg);
			}
				
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

//status affected C,DC,Z,OV,N
//undone DC,OV
void updateFlag (int value,int original, int wreg){
	
	FSR[STATUS] = 0;
	int valueCheck = value;
	int forCompare;
	int twoCompforWreg;
	
	twoCompforWreg = (~wreg)+1;
	
	forCompare = original&0x7f + wreg&0x7f;
	
	
	//OV
	if(((forCompare&0x80)>>7)==0 && ((valueCheck&0x10)>>8)==1 || (((forCompare&0x80)>>7)==1 && ((valueCheck&0x10)>>8)==0))
		FSR[STATUS] = FSR[STATUS] | 0x08;

	//zero
	if(valueCheck == 0)
	FSR[STATUS] = FSR[STATUS] | 0x04;
	
	//negative
	if((valueCheck&0x80)>>7 == 1)
	FSR[STATUS] = FSR[STATUS] | 0x10;
	
	//carry
	if(valueCheck >= 0 && (valueCheck&0x80)>>7 == 0)
	FSR[STATUS] = FSR[STATUS] | 0x01;
}

