#include <stdio.h>

extern unsigned char Mem[];
extern unsigned short int Code[];
extern char ac;  // 8-bit accumulator
extern unsigned char flagZero;
extern unsigned char flagCarry;
extern unsigned char flagOverflow;

void updateFlags(char result) {
    flagZero = (result == 0);
    flagCarry = (result < 0) || (result > 255);
    flagOverflow = ((result < -128) || (result > 127));
}

void dorun() {
    unsigned short int pc;  // program counter or instruction pointer
    unsigned short int ir;  // instruction register

    unsigned char opcode;
    unsigned char opALU;
    short addressOrValue;

    pc = 0;
    while (1) {
        ir = Code[pc++];                     // FETCH the instruction at the current PC and increment the PC
        opcode = (unsigned char)(ir >> 12);  // DECODE opcode
        opALU = (unsigned char)((ir & 0x0F00) >> 8);  // ALU operation
        addressOrValue = (char)(ir & 0x00FF);  // sign-extend the lower 8 bits

        switch (opcode) {  // EXECUTE based on opcode
            case 0x0F:  // HALT
                printf("HALT instruction executed\n");
                return;

            case 0x00:  // NOOP
                break;

            case 0x01:  // ADDI / SUBI
                if (opALU == 0x00) {  // ADDI
                    ac += addressOrValue;
                    updateFlags(ac);
                } else if (opALU == 0x01) {  // SUBI
                    ac -= addressOrValue;
                    updateFlags(ac);
                }
                break;

            case 0x02:  // ADD, SUB from memory
                if (opALU == 0x00) {  // ADD
                    ac += Mem[addressOrValue];
                    updateFlags(ac);
                } else if (opALU == 0x01) {  // SUB
                    ac -= Mem[addressOrValue];
                    updateFlags(ac);
                }
                break;

            case 0x03:  // CLAC
                ac = 0;
                flagZero = 1;
                flagCarry = 0;
                flagOverflow = 0;
                break;

            case 0x04:  // STORE
                Mem[addressOrValue] = ac;
                break;

            case 0x05:  // BEQZ
                if (ac == 0) {
                    pc = addressOrValue;
                }
                break;

            default:
                printf("Invalid instruction!\n");
                return;
        }
    }
}
