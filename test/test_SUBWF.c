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

void test_subwf_should_not_update_absoluteAddress(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = ACCESS ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
	int absoluteCheck;						
	int Exception;
	
	Try{subwf(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL_HEX16(0x100,absoluteCheck);
	}
}

void test_subwf_should_update_absoluteAddress(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = ACCESS ,		
					  .operand3 = -1,
					  .absoluteAddress = 0x100
					 };
					 
	int absoluteCheck;
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
}

void test_subwf_should_save_answer_in_WREG_with_input_0(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,			
					  .operand2 = 0 ,			//0 = WREG, -1/1 = file
					  .operand3 = ACCESS,		//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					};
	
	int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_WREG_with_input_W(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,			
					  .operand2 = W ,			//0 = WREG, -1/1 = file
					  .operand3 = ACCESS,		//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	 
	int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_WREG_with_bsr_with_input_1(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		//0 = WREG, -1/1 = file
					  .operand3 = 1,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck;
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x09;
	FSR[0x250] = 0x10;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x09,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[0x250] = 0x0e;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_WREG_with_bsr_with_input_BANKED(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = W ,		//0 = WREG, -1/1 = file
					  .operand3 = BANKED,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
					 	
	int absoluteCheck;
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x09;
	FSR[0x250] = 0x10;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x09,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[0x250] = 0x0e;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[WREG]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_fileregister_with_input_1(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 1 ,		//0 = WREG, -1/1 = file
					  .operand3 = 0	,		//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_fileregister_with_input_F(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = F ,		//0 = WREG, -1/1 = file
					  .operand3 = 0,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
					 
	int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_andwf_should_save_answer_in_fileregister_with_default_operand3(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = F ,		//0 = WREG, -1/1 = file
					  .operand3 = -1,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
		
	int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_fileregister_more_than_0x80(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0xff ,		
					  .operand2 = 1 ,		//0 = WREG, 1 = file
					  .operand3 = 0	,		//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
		
	int absoluteCheck;
	//Test with first set of value
	FSR[0xfff] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0xfff]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[0xfff] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0xfff]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[0xfff] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0xfff]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_fileregister_with_bsr(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = F ,		//0 = WREG, 1 = file
					  .operand3 = BANKED,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck;
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x250]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[code.operand1] = 0x09;
	FSR[0x350] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x350]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[code.operand1] = 0x0f;
	FSR[0x450] = 0x0e;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[0x450]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_fileregister_with_input_ACCESS_in_operand2(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = ACCESS ,		//0 = WREG, -1/1 = file
					  .operand3 = -1,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	 int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_fileregister_with_input_BANKED_in_operand2(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = BANKED ,		//0 = WREG, 1 = file
					  .operand3 = -1,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck;
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[code.operand1] = 0xff;
	FSR[0x250] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x250]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[BSR] = 0x03;
	FSR[code.operand1] = 0x09;
	FSR[0x350] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x350]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[BSR] = 0x04;
	FSR[code.operand1] = 0x0f;
	FSR[0x450] = 0x0e;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x04,FSR[0x450]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_save_answer_in_BANKED(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0xffe ,		
					  .operand2 = BANKED ,		//0 = WREG, 1 = file
					  .operand3 = -1,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck; 
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[0x2fe] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x2fe]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[0x2fe] = 0x09;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x02,FSR[0x2fe]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[0x2fe] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x2fe]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
}

void test_subwf_should_auto_switch_to_banked_mode(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x200 ,		
					  .operand2 = -1 ,		//0 = WREG, 1 = file
					  .operand3 = -1,			//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	int absoluteCheck;
	//Test with first set of value
	FSR[BSR] = 0x02;
	FSR[0x200] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x200]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
}

void test_andwf_should_update_status_flag(){

	Instruction instruction = {
								.mnemonic = SUBWF,
								.name = "subwf"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 =0x50 ,		
					  .operand2 = 1 ,		//0 = WREG, -1/1 = file
					  .operand3 = 0	,		//-1/0 = bsr ignore, 1 = bank with bsr
					  .absoluteAddress = 0x100
					 };
	
	 int absoluteCheck;
	//Test with first set of value
	FSR[code.operand1] = 0x08;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
	//Test with second set of value
	FSR[code.operand1] = 0x07;
	FSR[WREG] = 0x07;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x00,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
	//Test with third set of value
	FSR[code.operand1] = 0x0f;
	FSR[WREG] = 0x0a;
	
	absoluteCheck =subwf(&code);
	TEST_ASSERT_EQUAL_HEX8(0x05,FSR[0x50]);
	TEST_ASSERT_EQUAL_HEX8(0x01,FSR[STATUS]);
	TEST_ASSERT_EQUAL_HEX16(0x103,absoluteCheck);
	
}
