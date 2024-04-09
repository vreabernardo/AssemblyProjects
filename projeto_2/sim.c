/*
CPU-Mem architecture simulator
AC 2023/24 LEI FCT/UNL
Adaptado de versões anteriores
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PROMPT "cmd> " // command line prompt sign
#define MAXSZ 100      // max command line size

#define MAXDATAMEM 4096 // 256 x 8 bit
#define MAXCODEMEM 4096 // 256 x 16 bit

unsigned char Mem[MAXDATAMEM];   // simulated data memory (256 x 8 bits)
unsigned short Code[MAXCODEMEM]; // simulated data memory (256 x 8 bits)
char ac;
unsigned char flagZero;
unsigned char flagCarry;
unsigned char flagOverflow;

extern void dorun();

char *trim(char l[])
{
    int first = 0;
    int last = strlen(l) - 1; // last char at string 'l'

    while (isspace(l[first])) // ignore "spaces" at start
        first++;
    while (isspace(l[last])) // ignore "spaces" at the end
        last--;
    l[last + 1] = '\0';
    return &(l[first]);
}

char *getarg(char l[])
{
    int i = 0;
    while (!isspace(l[i]) && l[i] != '\0')
        i++;
    l[i] = '\0';
    i++;
    while (isspace(l[i]) && l[i] != '\0')
        i++;
    return &(l[i]);
}

int doload(char arg[])
{
    FILE *f = fopen(arg, "r");
    if (f == NULL)
        return 0; // erro
    int addr = 0;
    short int unsigned word;

    while (fscanf(f, "%hx", &word) > 0) // read next word
        Code[addr++] = word;
    for (int i = 0; i < addr; i++)
        printf("0x%02x: 0x%02x\n", i, Code[i]);
    fclose(f);
    return addr;
}

void dopoke(char arg[])
{
    int addr;
    int val;
    if (sscanf(arg, "%i%i", &addr, &val) != 2 || addr < 0 || addr >= MAXDATAMEM)
        printf("invalid arg(s)\n");
    Mem[addr] = val;
}

void dopeek(char arg[])
{
    int addr;
    if (sscanf(arg, "%i", &addr) != 1 || addr >= MAXDATAMEM || addr < 0)
        printf("invalid address\n");
    else
        printf("0x%x: 0x%hx\n", addr, Mem[addr]);
}

void dodump(char arg[])
{
    int count;
    if (sscanf(arg, "%i", &count) != 1 || count >= MAXDATAMEM || count < 0)
        printf("invalid size\n");
    else
    {

        printf("Accumulator: 0x%02x\n", ac);
        printf("Flag Zero 0x%01x\n", flagZero);
        printf("Flag Carry 0x%01x\n", flagCarry);
        printf("Flag Overflow 0x%01x\n", flagOverflow);
        printf("-------------------------\n");
        for (int i = 0; i < count; i++)
            printf("0x%x: 0x%02x\n", i, Mem[i]);
    }
}

/*-------------------------------------------------------*/
int main()
{
    char line[MAXSZ];

    printf("cpu-AC simulator console\n");
    printf(PROMPT);
    fflush(stdout);

    while (fgets(line, MAXSZ, stdin) != NULL)
    {
        char *cmd = trim(line);
        char *arg = getarg(cmd);
        if (strcmp(cmd, "load") == 0)
        {
            int n = doload(arg);
            printf("read %d 32-bit words\n", n);
        }
        else if (strcmp(cmd, "run") == 0)
        {
            dorun();
            // printf("executed %d instructions\n");
        }
        else if (strcmp(cmd, "poke") == 0)
            dopoke(arg);
        else if (strcmp(cmd, "peek") == 0)
            dopeek(arg);
        else if (strcmp(cmd, "dump") == 0)
            dodump(arg);
        else if (strcmp(cmd, "exit") == 0)
            return 0; // exit program
        else
            printf("unknown command!\n");
        printf(PROMPT);
        fflush(stdout);
    }
}
