#include <stdio.h>

extern unsigned char Mem[];
extern unsigned short int Code[];
extern char ac;
extern unsigned char flagZero;
extern unsigned char flagCarry;
extern unsigned char flagOverflow;
char old_ac;

#define MAX +127
#define MIN -128
#define MSB_MASK 0x80

void updateFlagsADD(char result, char a, char b)
{
    flagZero = result == 0x00;

    flagCarry = ((unsigned int)a + (unsigned int)b) > 0xFF;

    // when the inputs have opposite signs, and the output has a different sign from the first operand.
    // *Doest work because of Undefined Behaviour in C, we need to catch the overflow before doing the operation*
    /* flagOverflow = ((!(a & MSB_MASK) & !((char)b & MSB_MASK) & (result & MSB_MASK)) || // +a + b = -c
                    ((a & MSB_MASK) & ((char)b & MSB_MASK) & !(result & MSB_MASK)))       // -a - b = +c
                   >> 7;    // shift from msb to lsb to get only 0 or 1.
    */

    flagOverflow = (b > 0 && a > MAX - b) || (b < 0 && a < MIN - b);
}

void updateFlagsSUB(char result, char a, char b)
{
    flagZero = result == 0x00;

    flagCarry = ((unsigned int)a + (unsigned int)b) > 0xFF;

    // when the inputs have opposite signs, and the output has a different sign from the first operand.
    // *Doest work because of Undefined Behaviour in C, we need to catch the overflow before doing the operation*
    /* flagOverflow = ((!(a & MSB_MASK) & ((char)b & MSB_MASK) & (result & MSB_MASK)) || // +a - b = -c
                    ((a & MSB_MASK) & !(char)b & MSB_MASK & !(result & MSB_MASK)))       // -a + b = +c
                   >> 7;    // shift from msb to lsb to get only 0 or 1.
    */

    flagOverflow = (b > 0 && a < MIN + b) || (b < 0 && a > MAX + b);
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
        ir = Code[pc++];                             // FETCH the instruction at the current PC and increment the PC
        opcode = (unsigned char)(ir >> 12);          // DECODE opcode
        opALU = (unsigned char)((ir & 0x0F00) >> 8); // ALU operation
        addressOrValue = (char)(ir & 0x00FF);        // sign-extend the lower 8 bits

        /*
        printf("PC: 0x%02x, IR: 0x%04x, opcode: 0x%02x, opALU: 0x%02x, addressOrValue: 0x%02x\n", pc, ir, opcode, opALU, addressOrValue);
        printf("Accumulator: 0x%02x, Zero: %d, Carry: %d, Overflow: %d\n", ac, flagZero, flagCarry, flagOverflow);
        */

        switch (opcode)
        {          // EXECUTE based on opcode
        case 0x0F: // HALT
            printf("HALT instruction executed\n");
            return;

        case 0x00: // NOOP
            break;

        case 0x01: // ADDI / SUBI
            old_ac = ac;
            if (opALU == 0x00)
            { // ADDI
                ac += addressOrValue;

                updateFlagsADD(ac, old_ac, addressOrValue);
            }
            else if (opALU == 0x01)
            { // SUBI
                ac -= addressOrValue;

                updateFlagsSUB(ac, old_ac, addressOrValue);
            }
            break;

        case 0x02: // ADD, SUB from memory
            old_ac = ac;
            if (opALU == 0x00)
            { // ADD
                ac += Mem[addressOrValue];
                updateFlagsADD(ac, old_ac, Mem[addressOrValue]);
            }
            else if (opALU == 0x01)
            { // SUB
                ac -= Mem[addressOrValue];
                updateFlagsSUB(ac, old_ac, Mem[addressOrValue]);
            }
            break;

        case 0x03: // CLAC
            ac = 0;
            flagZero = 1;
            break;

        case 0x04: // STORE
            Mem[addressOrValue] = ac;
            break;

        case 0x05: // BEQZ
            if (ac == 0)
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
