#include <stdio.h>

extern unsigned char Mem[];
extern unsigned short int Code[];
extern char ac;
extern unsigned char flagZero;
extern unsigned char flagCarry;
extern unsigned char flagOverflow;

#define MAX +127
#define MIN -128
#define UNSIGNED_MAX 255


void updateFlags(char result, char a, char b, char isAddition)
{
    flagZero = (result == 0x00);

    
    int MSB_a = 0;
    int MSB_res = 0;
    /* determines the position of the MSB of the result and of the old acumulator value;
    the while loop breaks once there's a discrepacy between the two values;
    */
    while (MSB_a != MSB_res) {
        if (result != 0) {
            result >>= 1;
            MSB_res ++;
        }

        if(a != 0) {
            a >>= 1;
            MSB_a ++;
        }
    }
    
    //even though the loop can break when the MSB shifts to the leff, the flag only triggers if the MSB is greater than the old value;
    flagCarry = MSB_res > MSB_a;
    
    //flagCarry = ((unsigned int)a + (unsigned int)b) > UNSIGNED_MAX;

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
    unsigned short int pc;
    unsigned short int ir;

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
