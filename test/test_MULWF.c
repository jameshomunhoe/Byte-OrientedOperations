#include "unity.h"
#include "Bytecode.h"
#include "MULWF.h"
#include "CException.h"

void setUp() {}
void tearDown() {}

void test_mulwf_should_throw_invalid_operand1(){

	Instruction instruction = {
								.mnemonic = MULWF,
								.name = "mulwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xffff ,	//invalid value
					  .operand2 = ACCESS,		
					  .operand3 = -1			
					 };

	int Exception;
	
	Try{		 
	mulwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP1,Exception);
	;}
}

void test_mulwf_should_throw_invalid_operand2(){

	Instruction instruction = {
								.mnemonic = MULWF,
								.name = "mulwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,
					  .operand2 = W,	// invalid value, should be ACCESS or BANKED		
					  .operand3 = -1			
					 };

	int Exception;
	
	Try{		 
	mulwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);
	;}
}

void test_mulwf_should_throw_invalid_operand3(){

	Instruction instruction = {
								.mnemonic = MULWF,
								.name = "mulwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,
					  .operand2 = BANKED,
					  .operand3 = 0		// invalid value, should be empty (-1)	
					 };

	int Exception;
	
	Try{		 
	mulwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);
	;}
}


void test_mulwf_should_multiply_fileregister(){

	Instruction instruction = {
								.mnemonic = MULWF,
								.name = "mulwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x50 ,	//random file register for MUL instruction
					  .operand2 = ACCESS ,		
					  .operand3 = -1			
					 };
		
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0x38,FSR[PRODL]);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0x31,FSR[PRODL]);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[code.operand1] = 0xff;
	FSR[WREG] = 0x0a;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x09,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0xf6,FSR[PRODL]);
	
}

void test_mulwf_should_multiply_fileregister_more_than_0x80(){

	Instruction instruction = {
								.mnemonic = MULWF,
								.name = "mulwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	//random file register for MUL instruction
					  .operand2 = ACCESS ,
					  .operand3 = -1			
					 };
		
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[0xfff] = 0x08;
	FSR[WREG] = 0x07;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0x38,FSR[PRODL]);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[0xfff] = 0x07;
	FSR[WREG] = 0x07;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0x31,FSR[PRODL]);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[0xfff] = 0xff;
	FSR[WREG] = 0x0a;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x09,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0xf6,FSR[PRODL]);
	
}

void test_mulwf_should_multiply_fileregister_with_bsr(){

	Instruction instruction = {
								.mnemonic = MULWF,
								.name = "mulwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	//random file register for MUL instruction
					  .operand2 = BANKED ,
					  .operand3 = -1			
					 };
		
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0x08;
	FSR[0x2ff] = 0x07;
	FSR[WREG] = 0x07;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0x31,FSR[PRODL]);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[code.operand1] = 0x07;
	FSR[0x3ff] = 0xff;
	FSR[WREG] = 0x07;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x06,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0xf9,FSR[PRODL]);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[code.operand1] = 0xff;
	FSR[0x4ff] = 0xf0;
	FSR[WREG] = 0x0a;
	
	mulwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x09,FSR[PRODH]);
	TEST_ASSERT_EQUAL_HEX8(0x60,FSR[PRODL]);
	
}
