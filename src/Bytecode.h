#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

#define WREG	0xfe8
#define BSR		0xfe0
#define PRODH	0xff4
#define PRODL	0xff3
#define STATUS	0xfd8

unsigned char FSR[0x1000];
unsigned extern char FSR[];

typedef enum 	{	INVALID_INPUT,
					INVALID_OP1,
					INVALID_OP2,
					INVALID_OP3
				} ErrorMessage;
				
				
typedef enum 	{
					ACCESS = -5,
					BANKED,
					F,
					W
				} OperandInput;

typedef enum 	{
					ANDWF, //completed, status affected Z,N
					SUBWF, //completed	status affected C,DC,Z,OV,N
					MULWF, //completed,	status affected none
					CPFSGT,//completed 	status affected none
					IORLW,
					BNC,
					BOV,
					RETURN,
					//TBLRD*,
					//TBLRD+,
					XORWF, //kenmun do
					IORWF, //kenmun do
					DCFSNZ, //kenmun do
					RRCF,	//kenmun do
					MULLW,
					BTG,
					DAW,
					RCALL,
					POP,
					//TBLRD*+,
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
	int absoluteAddress;
} Bytecode;



#endif	// __BYTECODE_H__
