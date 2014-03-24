#include "unity.h"
#include "Bytecode.h"
#include "SUBWF.h"
#include "CException.h"

void setUp() {}
void tearDown() {}

void test_subwf_should_throw_invalid_operand1(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xffff ,	//random file register for SUB instruction
					  .operand2 = 0 ,		//0 = WREG, 1 = file
					  .operand3 = 0			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
					 
	int Exception;
	
	Try{		 
	subwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP1,Exception);
	}
}

void test_subwf_should_throw_invalid_operand2(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = 2 ,		//invalid value
					  .operand3 = 0			
					 };
					 
	int Exception;
	
	Try{		 
	subwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);
	}
}

void test_subwf_should_throw_invalid_operand3(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = ACCESS ,		
					  .operand3 = ACCESS		//repeated,ACCES is operand 2 value	
					 };
					 
	int Exception;
	
	Try{		 
	subwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);
	}
}


void test_subwf_should_save_answer_in_WREG_with_input_0(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,			
					  .operand2 = 0 ,			//0 = WREG, -1/1 = file
					  .operand3 = ACCESS		//-1/0 = bsr ignore, 1 = bank with bsr
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

void test_subwf_should_save_answer_in_WREG_with_input_W(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,			
					  .operand2 = W ,			//0 = WREG, -1/1 = file
					  .operand3 = ACCESS		//-1/0 = bsr ignore, 1 = bank with bsr
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

void test_subwf_should_save_answer_in_WREG_with_bsr_with_input_1(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		//0 = WREG, -1/1 = file
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

void test_subwf_should_save_answer_in_WREG_with_bsr_with_input_BANKED(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		//0 = WREG, -1/1 = file
					  .operand3 = BANKED			//-1/0 = bsr ignore, 1 = bank with bsr
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

void test_subwf_should_save_answer_in_fileregister_with_input_1(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 1 ,		//0 = WREG, -1/1 = file
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

void test_subwf_should_save_answer_in_fileregister_with_input_F(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = F ,		//0 = WREG, -1/1 = file
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
					  .operand1 =0xff ,		
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
					  .operand1 =0x50 ,		
					  .operand2 = F ,		//0 = WREG, 1 = file
					  .operand3 = BANKED			//-1/0 = bsr ignore, 1 = bank with bsr
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

void test_andwf_should_update_status_flag(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 1 ,		//0 = WREG, -1/1 = file
					  .operand3 = 0			//-1/0 = bsr ignore, 1 = bank with bsr
					 };
		
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[STATUS]);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[STATUS]);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	
}