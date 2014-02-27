#include "unity.h"
#include "Bytecode.h"
#include "Byte-OrientedOperations.h"

void setUp() {}
void tearDown() {}

void test_andwf_should_save_answer_in_WREG(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x050 ,	//random file register for adding
					  .operand2 = 0 ,		//0 = WREG, 1 = file
					  .operand3 = 1			//0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[WREG]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[WREG]);
	
}

void test_andwf_should_save_answer_in_fileregister(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x050 ,	//random file register for adding
					  .operand2 = 1 ,		//0 = WREG, 1 = file
					  .operand3 = 1			//0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x050]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x050]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[0x050]);
	
}