#include "unity.h"
#include "Bytecode.h"
#include "BOV.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_bov_should_throw_error_operand2(){

	Instruction instruction = {
								.mnemonic = BOV,
								.name = "bov"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = 1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200
					 };
	
	int Exception;
	
	Try{bov(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);
	}

}

void test_bov_should_throw_error_operand3(){

	Instruction instruction = {
								.mnemonic = BOV,
								.name = "bov"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = -1,		
					  .operand3 = 1,
					  .absoluteAddress = 0x200
					 };
	
	int Exception;
	
	Try{bov(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);
	}

}

void test_bov_should_branch_when_overflow(void)
{	
	Instruction instruction = {
								.mnemonic = BOV,
								.name = "bov"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200
					 };
	
	PC = code.absoluteAddress;
	FSR[STATUS] = 0x8;
	bov(&code);
	TEST_ASSERT_EQUAL_HEX16(0x100,PC);

}

void test_bov_should_not_branch_when_not_overflow(void)
{	
	Instruction instruction = {
								.mnemonic = BOV,
								.name = "bov"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200
					 };
	
	PC = code.absoluteAddress;
	FSR[STATUS] = 0x01;
	bov(&code);
	TEST_ASSERT_EQUAL_HEX16(0x202,PC);

}
