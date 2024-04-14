#include <stdio.h>

extern unsigned char Mem[];
extern unsigned short int Code[];
extern char ac;
extern unsigned char flagZero;
extern unsigned char flagCarry;
extern unsigned char flagOverflow;

#define MAX +127
#define MIN -128

void updateFlags(char result, char a, char b, char isAddition)
{
    flagZero = (result == 0x00);

    flagCarry = ((unsigned int)a + (unsigned int)b) > 0xFF;

    if (isAddition)
    {
        flagOverflow = (b > 0 && a > MAX - b) || (b < 0 && a < MIN - b);
    }
    else
    {
        flagOverflow = (b < 0 && a > MAX + b) || (b > 0 && a < MIN + b);
    }
}

void dorun()
{
    unsigned short int pc; // program counter or instruction pointer
    unsigned short int ir; // instruction register

    unsigned char opcode;
    unsigned char opALU;
    short addressOrValue;

    pc = 0;
    while (1)
    {
        ir = Code[pc++];
        opcode = (unsigned char)(ir >> 12);
        opALU = (unsigned char)((ir & 0x0F00) >> 8);
        addressOrValue = (char)(ir & 0x00FF);

        /*
        printf("PC: 0x%02x, IR: 0x%04x, opcode: 0x%02x, opALU: 0x%02x, addressOrValue: 0x%02x\n", pc, ir, opcode, opALU, addressOrValue);
        printf("Accumulator: 0x%02x, Zero: %d, Carry: %d, Overflow: %d\n", ac, flagZero, flagCarry, flagOverflow);
        */

        switch (opcode)
        {
        case 0x0F: // HALT
            printf("HALT instruction executed\n");
            return;

        case 0x00: // NOOP
            break;

        case 0x01: // ADDI, SUBI
        {
            char oldAc = ac;
            if (opALU == 0x00)
            { // ADDI
                ac += addressOrValue;
                updateFlags(ac, oldAc, addressOrValue, 1);
            }
            else if (opALU == 0x01)
            { // SUBI
                ac -= addressOrValue;
                updateFlags(ac, oldAc, addressOrValue, 0);
            }
            break;
        }

        case 0x02: // ADD, SUB
        {
            char oldAc = ac;
            if (opALU == 0x00)
            { // ADD
                ac += (char)Mem[addressOrValue];
                updateFlags(ac, oldAc, Mem[addressOrValue], 1);
            }
            else if (opALU == 0x01)
            { // SUB
                ac -= (char)Mem[addressOrValue];
                updateFlags(ac, oldAc, Mem[addressOrValue], 0);
            }
            break;
        }

        case 0x03: // CLAC "clear acumulator"
            ac = 0;
            flagZero = 1;
            flagCarry = 0;
            flagOverflow = 0;
            break;

        case 0x04: // STORE
            Mem[addressOrValue] = ac;
            break;

        case 0x05: // BEQZ
            if (ac == 0x00)
            {
                pc = addressOrValue;
            }
            break;

        default:
            printf("Invalid instruction!\n");
            return;
        }
    }
}
