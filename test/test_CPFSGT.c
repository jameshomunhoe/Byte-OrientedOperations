#include "unity.h"
#include "Bytecode.h"
#include "CPFSGT.h"
#include "CException.h"

void setUp() {}
void tearDown() {}


void test_cpfsgt_should_throw_invalid_operand1(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xffff ,	//invalid value
					  .operand2 = 0,		
					  .operand3 = -1			
					 };
					 
	int Exception;
	
	
	Try{		 
	cpfsgt(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP1,Exception);}
}

void test_cpfsgt_should_throw_invalid_operand2(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xf ,	
					  .operand2 = W,		//invalid value
					  .operand3 = -1			
					 };
					 
	int Exception;
	
	Try{		 
	cpfsgt(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP2,Exception);}
}

void test_cpfsgt_should_throw_invalid_operand3(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = BANKED,		
					  .operand3 = 2			//invalid value
					 };
					 
	int Exception;
	
	Try{		 
	cpfsgt(&code);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);}
}

void test_cpfsgt_should_not_increase_absoluteAddress_with_invalid_input(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = BANKED,		
					  .operand3 = 2,		
					  .absoluteAddress = 0x100
					 };
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x08;
	FSR[WREG] = 0x07;
	int Exception;
	int absoluteCheck;
	 
	Try{ 		 
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x100,absoluteCheck);}
	Catch(Exception){
	TEST_ASSERT_EQUAL(INVALID_OP3,Exception);
	}
	
}

void test_cpfsgt_should_not_skip_absoluteAddress_with_file_equal(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x50 ,	
					  .operand2 = ACCESS,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };

	int absoluteCheck;
					 
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x25;			//to make sure it use access
	FSR[code.operand1] = 0x5;
	FSR[WREG] = 0x5;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
}

void test_cpfsgt_should_not_skip_absoluteAddress_with_file_smaller_with_ACCESS(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x50 ,	
					  .operand2 = ACCESS,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
					 
	 int absoluteCheck;
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x18;			//to make sure it use access
	FSR[code.operand1] = 0x06;
	FSR[WREG] = 0x07;
		
	absoluteCheck =cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
}

void test_cpfsgt_should_not_skip_absoluteAddress_with_file_smaller_with_ACCESS_more_than_0x80(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x80 ,	
					  .operand2 = ACCESS,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
					 
	 int absoluteCheck; 
	
	FSR[BSR] = 0x02;
	FSR[0x280] = 0x18;			//to make sure it use access
	FSR[code.operand1+(0xf<<8)] = 0x6;
	FSR[WREG] = 0x07;
		
	absoluteCheck=cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
}

void test_cpfsgt_should_not_skip_absoluteAddress_with_file_smaller_with_BANKED(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = BANKED,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
					 
	int absoluteCheck; 
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x18;			//to make sure it use access
	FSR[code.operand1] = 0x06;
	FSR[WREG] = 0x20;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
}

void test_cpfsgt_should_not_skip_absoluteAddress_with_file_larger_with_default(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x50 ,	
					  .operand2 = -1,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
				
	 int absoluteCheck;
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x25;			//to make sure it use access
	FSR[code.operand1] = 0x5;
	FSR[WREG] = 0x20;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x101,absoluteCheck);
	
}


void test_cpfsgt_should_skip_absoluteAddress_with_file_larger_with_ACCESS(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x50 ,	
					  .operand2 = ACCESS,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
					 
	int absoluteCheck;
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x5;			//to make sure it use access
	FSR[code.operand1] = 0x25;
	FSR[WREG] = 0x20;
		
	absoluteCheck =cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
}

void test_cpfsgt_should_skip_absoluteAddress_with_file_larger_with_ACCESS_more_than_0x80(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x90 ,	
					  .operand2 = ACCESS,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
					 
	 int absoluteCheck;
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x5;			//to make sure it use access
	FSR[code.operand1+(0x0f<<8)] = 0x25;
	FSR[WREG] = 0x20;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
}

void test_cpfsgt_should_skip_absoluteAddress_with_file_larger_with_BANKED(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0xff ,	
					  .operand2 = BANKED,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
	
	  int absoluteCheck;
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x25;			//to make sure it use access
	FSR[code.operand1] = 0x5;
	FSR[WREG] = 0x20;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
}

void test_cpfsgt_should_skip_absoluteAddress_with_file_larger_with_default(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x50 ,	
					  .operand2 = -1,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
	int absoluteCheck; 
	
	FSR[BSR] = 0x02;
	FSR[0x2ff] = 0x5;			//to make sure it use access
	FSR[code.operand1] = 0x25;
	FSR[WREG] = 0x20;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
}

void test_cpfsgt_should_change_to_banked_mode_with_default_operand2(){

	Instruction instruction = {
								.mnemonic = CPFSGT,
								.name = "cpfsgt"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = 0x180 ,	
					  .operand2 = -1,		
					  .operand3 = -1,		
					  .absoluteAddress = 0x100
					 };
	 int absoluteCheck;
	
	FSR[code.operand1] = 0x25;
	FSR[WREG] = 0x20;
		
	absoluteCheck = cpfsgt(&code);
	TEST_ASSERT_EQUAL_HEX16(0x102,absoluteCheck);
	
}