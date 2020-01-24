// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"

/*
 * print a MIPS instruction (no newline)
 * run reference implementation if unsure what to print
 */
void print_instruction(uint32_t instruction) {
    uint32_t bit_0_5 = (instruction & 0x3F);//subinstruction code
    uint32_t little_I = ((instruction >> 6) & 0x1F);//little I,bit 6 to bit 11
    uint32_t d = ((instruction >> 11) & 0x1F);//d
    uint32_t t = ((instruction >> 16) & 0x1F);//t
    uint32_t s = ((instruction >> 21) & 0x1F);//s or b
    uint32_t bit_25_31 = ((instruction >> 26) & 0x3F);//instruction code
    uint32_t big_I = (instruction & 0xFFFF);//big I
    int big_II = (big_I > 32767) ? (big_I - 65536) : big_I; //the signed form of big_I
    if(bit_25_31 == 0){//if the front operation code is 0, we identify different funciton by sub-operation code
        switch(bit_0_5){
            case 32:
                printf("add $%d, $%d, $%d",d,s,t);
                break;
            case 34:
                printf("sub $%d, $%d, $%d",d,s,t);
                break;
            case 36:
                printf("and $%d, $%d, $%d",d,s,t);
                break;
            case 37:
                printf("or $%d, $%d, $%d",d,s,t);
                break;
            case 38:
                printf("xor $%d, $%d, $%d",d,s,t);
                break;
            case 4:
                printf("sllv $%d, $%d, $%d",d,t,s);
                break;
            case 6:
                printf("srlv $%d, $%d, $%d",d,t,s);
                break;
            case 42:
                printf("slt $%d, $%d, $%d",d,s,t);
                break;
            case 0:
                printf("sll $%d, $%d, %d",d,t,little_I);
                break;
            case 2:
                printf("srl $%d, $%d, %d",d,t,little_I);
                break;
            case 8:
                printf("jr $%d",s);
                break; 
            case 12:
                printf("syscall");
            }       
    }else {
        switch(bit_25_31) {//when operation code is non-zero, we can identify different function by operation code 
            case 28:
                printf("mul $%d, $%d, $%d",d,s,t);
                break;
            case 8:
                printf("addi $%d, $%d, %d",t,s,big_II);
                break;
            case 12:
                printf("andi $%d, $%d, %d",t,s,big_II);
                break;
            case 13:
                printf("ori $%d, $%d, %d",t,s,big_II);
                break;
            case 14:
                printf("xori $%d, $%d, %d",t,s,big_II);
                break;
            case 10:
                printf("slti $%d, $%d, %d",t,s,big_II);
                break;
            case 0xF:
                printf("lui $%d, %d",t,big_II);
                break;
            case 32:
                printf("lb $%d, %d($%d)",t,big_I,s);
                break;
            case 33:
                printf("lh $%d, %d($%d)",t,big_I,s);
                break;
            case 35:
                printf("lw $%d, %d($%d)",t,big_I,s);
                break;
            case 40:
                printf("sb $%d, %d($%d)",t,big_I,s);
                break;
            case 41:
                printf("sh $%d, %d($%d)",t,big_I,s);
                break;
            case 43:
                printf("sw $%d, %d($%d)",t,big_I,s);
                break;
            case 4:
                printf("beq $%d, $%d, %d",s,t,big_II);
                break;
            case 5:
                printf("bne $%d, $%d, %d",s,t,big_II);
                break;
            case 6:
                printf("blez $%d, %d",s,big_II);
                break;
            case 7:
                printf("bgtz $%d, %d",s,big_II);
                break;
            case 1://bltz or bgez depens on t's value
                if(t == 0) printf("bltz $%d, %d",s,big_II);
                if(t == 1) printf("bgez $%d, %d",s,big_II);
                break;
            case 2:
                printf("j %#x",instruction & 0x3FFFFFF);
                break;
            case 3:
                printf("jal %#x",instruction & 0x3FFFFFF);
                break;
        }
    }
}
