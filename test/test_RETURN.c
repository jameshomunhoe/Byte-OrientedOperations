#include "unity.h"
#include "Bytecode.h"
#include "RETURN.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}


void test_return1_should_throw_invalid_operand1(void)
{
	Instruction instruction = {
								.mnemonic = RETURN,
								.name = "return"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 2,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200000
					 };
	
	int Exception;
	
	Try{
	return1(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP1,Exception);}
}

void test_return1_should_return_PC(void)
{
	Instruction instruction = {
								.mnemonic = RETURN,
								.name = "return"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = -1,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200000
					 };

	PC = code.absoluteAddress;
	FSR[STKPTR] = 2;
	FSR[TOSU] = 0x12;
	FSR[TOSH] = 0x34;
	FSR[TOSL] = 0x56;
	
	return1(&code);
	TEST_ASSERT_EQUAL_HEX32(0x123456,PC);
}

void test_return1_should_return_PC_and_shadow_register(void)
{
	Instruction instruction = {
								.mnemonic = RETURN,
								.name = "return"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 1,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x200000
					 };
					
	PC = code.absoluteAddress;
	FSR[WREG] = 0x01;
	FSR[STATUS] = 0x01;
	FSR[BSR] = 0x01;
	
	FSR[STKPTR] = 2;
	FSR[TOSU] = 0x12;
	FSR[TOSH] = 0x34;
	FSR[TOSL] = 0x56;
	
	return1(&code);
	TEST_ASSERT_EQUAL_HEX32(0x123456,PC);
	TEST_ASSERT_EQUAL(0x12,FSR[WREG]);
	TEST_ASSERT_EQUAL(0x20,FSR[STATUS]);
	TEST_ASSERT_EQUAL(0x08,FSR[BSR]);
}
