#include "unity.h"
#include "Bytecode.h"
#include "IORLW.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_iorlw_should_throw_invalid_oprand1(void)
{
	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xfff ,	//invalid input, out of range
					  .operand2 = -1 ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	int Exception;

	Try{
	iorlw(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP1,Exception);}
}

void test_iorlw_should_throw_invalid_oprand2(void)
{
	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = 1 ,		//invalid input, out of range
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	int Exception;

	Try{
	iorlw(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);}
}

void test_iorlw_should_throw_invalid_oprand3(void)
{
	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = -1 ,		
					  .operand3 = 1,	//invalid input, out of range
					  .absoluteAddress = 0x100
					 };
	int Exception;

	Try{
	iorlw(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);}
}

void test_iorlw_should_not_update_absoluteAddress(){

	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = 1 ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	int Exception;
	int absoluteCheck;
	
	Try{absoluteCheck =iorlw(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL_HEX16(INVALID_OP2,Exception);
	}
	
}

void test_iorlw_should_update_absoluteAddress(){

	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = -1 ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	int Exception;
	int absoluteCheck;
	
	absoluteCheck =iorlw(&code);

	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	
}

void test_iorlw_should_do_ior_properly(){

	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = -1 ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck;
	
	//Test with first set of value
	code.operand1 = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck = iorlw(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0f,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	code.operand1 = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck = iorlw(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	code.operand1 = 0x1f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck = iorlw(&code);
	TEST_ASSERT_EQUAL_HEX8(0x1f,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
	
}

void test_iorlw_should_update_status_flag(){

	Instruction instruction = {
								.mnemonic = IORLW,
								.name = "iorlw"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = -1 ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
					 
	int absoluteCheck;
	
	//Test with first set of value
	code.operand1 = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =iorlw(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0f,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
	
	//Test with second set of value
	code.operand1 = 0x0;
	FSR[WREG] = 0x0;
	
	absoluteCheck= iorlw(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[STATUS]);
	
	//Test with third set of value
	code.operand1 = 0xf0;
	FSR[WREG] = 0x0a;
	
	absoluteCheck=iorlw(&code);
	TEST_ASSERT_EQUAL_HEX8(0xfa,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
	
}



