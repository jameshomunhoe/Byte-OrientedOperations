#include "unity.h"
#include "Bytecode.h"
#include "SUBWF.h"

void setUp() {}
void tearDown() {}

void test_subwf_should_print_invalid_file_register_address(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xffff ,	//random file register for SUB instruction
					  .operand2 = 0 ,		//0 = WREG, 1 = file
					  .operand3 = 0			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
					 
	subwf(&code);
}

void test_subwf_should_save_answer_in_WREG(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		//random file register for SUB instruction
					  .operand2 = 0 ,		//0 = WREG, 1 = file
					  .operand3 = 0			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[WREG]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[WREG]);
	
}

void test_subwf_should_save_answer_in_WREG_with_bsr(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		//random file register for SUB instruction
					  .operand2 = 0 ,		//0 = WREG, 1 = file
					  .operand3 = 1			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[WREG]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x09;
	FSR[0x250] = 0x10;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x09,FSR[WREG]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[0x250] = 0x0e;
	FSR[WREG] = 0x0a;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[WREG]);
	
}

void test_subwf_should_save_answer_in_fileregister(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		//random file register for SUB instruction
					  .operand2 = 1 ,		//0 = WREG, 1 = file
					  .operand3 = 0			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	
}

void test_subwf_should_save_answer_in_fileregister_more_than_0x80(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0xff ,		//random file register for SUB instruction
					  .operand2 = 1 ,		//0 = WREG, 1 = file
					  .operand3 = 0			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[0xfff] = 0x08;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0xfff]);
	
	//Test with second set of value
	FSR[0xfff] = 0x07;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0xfff]);
	
	//Test with third set of value
	FSR[0xfff] = 0x0f;
	FSR[WREG] = 0x0a;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0xfff]);
	
}

void test_subwf_should_save_answer_in_fileregister_with_bsr(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		//random file register for SUB instruction
					  .operand2 = 1 ,		//0 = WREG, 1 = file
					  .operand3 = 1			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	FSR[BSR] = 0x02;
	
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x250]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x09;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x250]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[0x250] = 0x0e;
	FSR[WREG] = 0x0a;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[0x250]);
	
}