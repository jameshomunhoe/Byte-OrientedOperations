#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

#define WREG	0xfe8
#define BSR		0xfe0

char FSR[0x1000];
extern char FSR[];


typedef enum 	{
					ANDWF, //completed
					SUBWF, //completed	
					XORWF,
					IORWF,
					MULWF,
					CPFSGT,
					DCFSNZ,
					RRCF,	
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
