#include "unity.h"
#include "Bytecode.h"
#include "BNC.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_bnc_should_throw_error_operand2(){

	Instruction instruction = {
								.mnemonic = BNC,
								.name = "bnc"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = 1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200
					 };
	
	int Exception;
	
	Try{bnc(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);
	}

}

void test_bnc_should_throw_error_operand3(){

	Instruction instruction = {
								.mnemonic = BNC,
								.name = "bnc"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = -1,		
					  .operand3 = 1,
					  .absoluteAddress = 0x200
					 };
	
	int Exception;
	
	Try{bnc(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);
	}

}

void test_bnc_should_branch_when_no_carry(void)
{	
	Instruction instruction = {
								.mnemonic = BNC,
								.name = "bnc"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200
					 };
	
	int absoluteCheck;
	FSR[STATUS] = 0x00;
	absoluteCheck = bnc(&code);
	TEST_ASSERT_EQUAL_HEX16(0x100,absoluteCheck);

}

void test_bnc_should_not_branch_when_carry(void)
{	
	Instruction instruction = {
								.mnemonic = BNC,
								.name = "bnc"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x100,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200
					 };
	
	int absoluteCheck;
	FSR[STATUS] = 0x01;
	absoluteCheck = bnc(&code);
	TEST_ASSERT_EQUAL_HEX16(0x201,absoluteCheck);

}
