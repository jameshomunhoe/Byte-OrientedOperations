#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

#define WREG	0xfe8
#define BSR		0xfe0
#define PRODH	0xff4
#define PRODL	0xff3

unsigned char FSR[0x1000];
unsigned extern char FSR[];


typedef enum 	{
					ANDWF, //completed
					SUBWF, //completed	
					MULWF, //completed
					CPFSGT, //temporary stuck
					XORWF, //kenmun do
					IORWF, //kenmun do
					DCFSNZ, //kenmun do
					RRCF,	//kenmun do
				} Mnemonic;
				
typedef struct {
	Mnemonic	mnemonic;
	char *name;
} Instruction;

typedef struct {
	Instruction *instruction;
	int operand1;
	int operand2;
	int operand3;
} Bytecode;



#endif	// __BYTECODE_H__
