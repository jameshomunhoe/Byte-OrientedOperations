#include "unity.h"
#include "Bytecode.h"
#include "TBLRD.h"
#include "CException.h"


void setUp(void){}
void tearDown(void){}

void test_tblrd_should_read_value_into_TABLAT(void){

	Instruction instruction = {
								.mnemonic = TBLRD,
								.name = "tblrd"
							  };
	
	Bytecode code = { .instruction = &instruction,
					  .operand1 = -1,
					  .operand2 = -1,		
					  .operand3 = -1,
					  .absoluteAddress = 0x300
					 };
	
	PC = code.absoluteAddress;
	
	//fixture to read
	TABLE[0x11aaff] = 0x99;
	TABLE[0x123456] = 0xaa;
	TABLE[0x0abcde] = 0xff;	
	
	//1st set of value
	FSR[TBLPTRU] = 0x11;
	FSR[TBLPTRH] = 0xaa;
	FSR[TBLPTRL] = 0xff;
	
	tblrd(&code);
	TEST_ASSERT_EQUAL(0x99,FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX16(0x301,PC);

	//2nd set of value
	FSR[TBLPTRU] = 0x12;
	FSR[TBLPTRH] = 0x34;
	FSR[TBLPTRL] = 0x56;
	
	tblrd(&code);
	TEST_ASSERT_EQUAL(0xaa,FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX16(0x302,PC);

	
	//3rd set of value
	FSR[TBLPTRU] = 0x0a;
	FSR[TBLPTRH] = 0xbc;
	FSR[TBLPTRL] = 0xde;
	
	tblrd(&code);
	TEST_ASSERT_EQUAL(0xff,FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX16(0x303,PC);

	
}
