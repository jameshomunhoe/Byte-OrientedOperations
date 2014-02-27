#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

typedef enum 	{
					ANDWF,
					CPFSGT,
					DCFSNZ,
					IORWF,
					MULWF,
					RRCF,
					SUBWF,
					XORWF,
					
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
