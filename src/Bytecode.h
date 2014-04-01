#ifndef	__BYTECODE_H__
#define	__BYTECODE_H__

#define WREG	0xfe8
#define BSR		0xfe0
#define PRODH	0xff4
#define PRODL	0xff3
#define STATUS	0xfd8
#define TBLPTRU	0xff8
#define TBLPTRH 0xff7
#define TBLPTRL	0xff6
#define TABLAT	0xff5
#define TOSU	0xfff
#define	TOSH	0xffe
#define TOSL	0xffd
#define STKPTR	0xffc

unsigned char FSR[0x1000];
unsigned extern char FSR[];
unsigned char TABLE[0x200000];
unsigned extern char TABLE[];

int PC;
extern int PC;



typedef enum 	{	INVALID_INPUT,
					INVALID_OP1,
					INVALID_OP2,
					INVALID_OP3,
					OUT_OF_TABLE
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
					IORLW, //completed  status affected Z,N
					BNC,   //completed  status affected none
					BOV,   //completed  status affected none
					RETURN,
					TBLRD, //temporary completed status affected none
					TBLWT_PREINC,//temporary completed status affected none
					XORWF, //kenmun do
					IORWF, 
					DCFSNZ, 
					RRCF,	
					MULLW,
					BTG,
					DAW,
					RCALL,
					POP,
					//TBLRD*+,//kenmun do
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
