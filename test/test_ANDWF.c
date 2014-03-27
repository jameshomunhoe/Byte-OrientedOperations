#include "unity.h"
#include "Bytecode.h"
#include "ANDWF.h"
#include "CException.h"

void setUp() {}
void tearDown() {}



void test_andwf_should_throw_invalid_operand1(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xffff ,	//invalid input, out of range
					  .operand2 = -1 ,		
					  .operand3 = -1		
					 };
					 
	int Exception;
	
	Try{		 
	andwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP1,Exception);
	;}
	
}

void test_andwf_should_throw_invalid_operand2(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = 2 ,		//invalid input
					  .operand3 = BANKED	
					 };
					 
	int Exception;
	
	Try{		 
	andwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);
	;}
	
}

void test_andwf_should_throw_invalid_operand3(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = ACCESS,	
					  .operand3 = ACCESS	//invalid, repeat
					 };
					 
	int Exception;
	
	Try{		 
	andwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);
	;}
	
}

void test_andwf_should_not_update_absoluteAddress(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = ACCESS ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	int Exception;
	PC = code.absoluteAddress;
	
	Try{andwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL_HEX16(0x100,PC);
	}
	
}

void test_andwf_should_update_absoluteAddress(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = ACCESS ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
}

void test_andwf_should_save_answer_in_WREG_with_input_0(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 0 ,		
					  .operand3 = ACCESS,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_WREG_with_input_W(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		
					  .operand3 = 0,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_WREG_with_bsr_with_input_1(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		
					  .operand3 = 1	,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	FSR[BSR] = 0x02;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x09;
	FSR[0x250] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[0x250] = 0xff;
	FSR[WREG] = 0x1a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x1a,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_WREG_with_bsr_with_input_BANKED(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		
					  .operand3 = BANKED,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	FSR[BSR] = 0x02;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x09;
	FSR[0x250] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[0x250] = 0xff;
	FSR[WREG] = 0x1a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x1a,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_fileregister_with_input_1(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 1 ,		
					  .operand3 = 0	,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_fileregister_with_input_F(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = F ,		
					  .operand3 = 0	,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_fileregister_with_default_operand3(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 1 ,		
					  .operand3 = -1	,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_fileregister_more_than_0x80(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x80 ,		
					  .operand2 = 1 ,		
					  .operand3 = ACCESS,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[0xf80] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0xf80]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[0xf80] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0xf80]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[0xf80] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[0xf80]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_fileregister_with_bsr(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = F ,		
					  .operand3 = BANKED,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x250]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[code.operand1] = 0x09;
	FSR[0x350] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x350]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[code.operand1] = 0x0f;
	FSR[0x450] = 0xff;
	FSR[WREG] = 0x1a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x1a,FSR[0x450]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_save_answer_in_fileregister_with_ACCESS_in_operand2(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = ACCESS ,		
					  .operand3 = -1	,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x0a,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
}

void test_andwf_should_save_answer_in_fileregister_with_BANKED_in_operand2(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = BANKED ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x250]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[code.operand1] = 0x09;
	FSR[0x350] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x350]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[code.operand1] = 0x0f;
	FSR[0x450] = 0xff;
	FSR[WREG] = 0x1a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x1a,FSR[0x450]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}

void test_andwf_should_update_status_flag(){

	Instruction instruction = {
								.mnemonic = ANDWF,
								.name = "andwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		//random file register for AND instruction
					  .operand2 = -1 ,		//0 = WREG, -1/1 = file
					  .operand3 = -1,		//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
					 
	PC = code.absoluteAddress;				 
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x101,PC);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x07,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x102,PC);
	
	//Test with third set of value
	FSR[code.operand1] = 0xff;
	FSR[WREG] = 0x8a;
	
	andwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x8a,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x10,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x103,PC);
	
}
