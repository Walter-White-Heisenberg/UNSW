// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include <stdlib.h>
 
//these two are the helper functions I implemented
static int convertion(uint32_t original);
static uint64_t load_helper(int number, uint32_t address);

//every function below correspond to a operation on the assignment page
static void add(uint32_t d, uint32_t s, uint32_t t);
static void sub(uint32_t d, uint32_t s, uint32_t t);
static void and(uint32_t d, uint32_t s, uint32_t t);
static void or(uint32_t d, uint32_t s, uint32_t t);
static void xor(uint32_t d, uint32_t s, uint32_t t);
static void sllv(uint32_t d, uint32_t t, uint32_t s);
static void srlv(uint32_t d, uint32_t t, uint32_t s);
static void slt(uint32_t d, uint32_t s, uint32_t t);
static void sll(uint32_t d, uint32_t t, uint32_t little_I);
static void srl(uint32_t d, uint32_t t, uint32_t little_I);
static void mul(uint32_t d, uint32_t s, uint32_t t);
static void addi(uint32_t t, uint32_t s, int big_II);
static void andi(uint32_t t, uint32_t s, uint32_t big_I);
static void ori(uint32_t t, uint32_t s, uint32_t big_I);
static void xori(uint32_t t, uint32_t s, uint32_t big_I);
static void slti(uint32_t t, uint32_t s, int big_II);
static void lb(uint32_t t, int big_II, uint32_t s);
static void lh(uint32_t t, int big_II, uint32_t s);
static void lw(uint32_t t, int big_II, uint32_t s);
static void sb(uint32_t t, int big_II, uint32_t s);
static void sh(uint32_t t, int big_II, uint32_t s);
static void sw(uint32_t t, int big_II, uint32_t s);
static void syscall();


int execute_instruction(uint32_t instruction, uint32_t *program_counter) {
    uint32_t bit_0_5 = (instruction & 0x3F);//sub-operation code
    uint32_t little_I = ((instruction >> 6) & 0x1F);//little I, bit 6 to bit 11
    uint32_t d = ((instruction >> 11) & 0x1F);//d
    uint32_t t = ((instruction >> 16) & 0x1F);//t
    uint32_t s = ((instruction >> 21) & 0x1F);//s or b
    uint32_t bit_25_31 = ((instruction >> 26) & 0x3F);//operation code
    uint32_t big_I = (instruction & 0xFFFF);//big I
    int big_II = convertion(big_I); //the signed form of big_I
    if(bit_25_31 == 0){//if the front operation code is 0, we identify different funciton by sub-operation code
        switch(bit_0_5){
            case 32:
                add(d,s,t);
                break;
            case 34:
                sub(d,s,t);
                break;
            case 36:
                and(d,s,t);
                break;
            case 37:
                or(d,s,t);
                break;
            case 38:
                xor(d,s,t);
                break;
            case 4:
                sllv(d,t,s);
                break;
            case 6:
                srlv(d,t,s);
                break;
            case 42:
                slt(d,s,t);
                break;
            case 0:
                sll(d,t,little_I);
                break;
            case 2:
                srl(d,t,little_I);
                break;
            case 8://for jr
                (*program_counter) = s - 4;//the "-4" will be cancel later by "+= 4" in line 94, then PC will equal to s eventually
                break; 
            case 12:
                if(get_register(v0) == 10) return 1;//exit when the value stored is 10
                syscall();
            }//except for jr part, all functiontion need to have PC increased by 4.  
        (*program_counter) += 4;       
    }else if(bit_25_31 > 7){//when operation code is non-zero, we can identify different function by operation code
        switch(bit_25_31) {  
            case 28:
                mul(d,s,t);
                break;
            case 8:
                addi(t,s,big_I);
                break;
            case 12:
                andi(t,s,big_I);
                break;
            case 13:
                ori(t,s,big_I);
                break;
            case 14:
                xori(t,s,big_I);
                break;
            case 10:
                slti(t,s,big_I);
                break;
            case 0xF://lui
                set_register(t, big_I << 16);
                break;
            case 32:
                lb(t,big_II,s);
                break;
            case 33:
                lh(t,big_II,s);
                break;
            case 35:
                lw(t,big_II,s);
                break;
            case 40:
                sb(t,big_II,s);
                break;
            case 41:
                sh(t,big_II,s);
                break;
            case 43:
                sw(t,big_II,s);
                break;
            }
        (*program_counter) +=4;//all functiontion in the switch before need to have PC increased by 4.
    }else{
        //in this case, the values in the registers are compared with value in first sixteen digits, which means they need to be converted into signed form
        uint32_t s_value = convertion(get_register(s));
        uint32_t t_value = convertion(get_register(t));
        switch(bit_25_31) {////when operation code is non-zero, we can identify different function by operation code, in this case, PC doesn't always += 4(sometime they jump on other branch), so I separate them out 
            case 4://beq, if s_value = t_value then increases by constant in first 16 digits * 4, otherwise increased by 4 
                (*program_counter) += ((s_value == t_value) ? (big_II * 4) : 4);
                break;
            case 5://bne, almost same operation as beq
                (*program_counter) += ((s_value != t_value) ? (big_II * 4) : 4);
                break;
            case 6://blez, almost same operation as beq
                (*program_counter) += ((s_value <= 0) ? (big_II * 4) : 4);
                break;
            case 7://bgtz, almost same operation as beq                
                (*program_counter) += ((s_value > 0) ? (big_II * 4) : 4);
                break;
            case 1://bltz or bgez depens on t's value
                if(t == 0) //bltz, almost same operation as beq
                    (*program_counter) += ((s_value < 0) ? (big_II * 4) : 4);
                if(t == 1) //bgez, almost same operation as beq
                    (*program_counter) += ((s_value >= 0) ? (big_II * 4) : 4);
                break;
            case 2://j(I just follow the operation on the assignment page)
                (*program_counter) = (((*program_counter) & 0xF0000000) | ((instruction & 0x3FFFFFF) << 2));
                break;
            case 3://jal(I just follow the operation on the assignment page)
                set_register(ra, (*program_counter) + 4); 
                (*program_counter) = (((*program_counter) & 0xF0000000) | ((instruction & 0x3FFFFFF) << 2));
                break;
         }
    } 
    // Update program_counter to address of next instructions
    // Most instructions will simply do the following:
    // Jump & Branch instructions will do something different
    // 0 should be returned, unless an exit syscall is executed
    return 0;
}

static int convertion(uint32_t original){//when original exceeds positive limit for 16 bits, which means original is a negative integer, then I need o sub 2^16 to convert it into a integer
    int final = (original > 0x7fff) ? (original - 0x10000) : original;
    return final;
}

static void add(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t sum = s_value + t_value;
    set_register(d, sum);
}

static void sub(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t sub = s_value - t_value;
    set_register(d, sub);
}

static void and(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t and = s_value & t_value;
    set_register(d, and);
}

static void or(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t or = s_value | t_value;
    set_register(d, or);
}

static void xor(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t xor = s_value ^ t_value;
    set_register(d, xor);
}

static void sllv(uint32_t d, uint32_t t, uint32_t s){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t sllv = t_value << s_value;
    set_register(d, sllv);
}

static void srlv(uint32_t d, uint32_t t, uint32_t s){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t srlv = t_value >> s_value;
    set_register(d, srlv);
}

static void slt(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = get_register(s);
    uint32_t t_value = get_register(t);
    uint32_t slt = (convertion(s_value) < convertion(t_value));
    set_register(d, slt);
}

static void sll(uint32_t d, uint32_t t, uint32_t little_I){
    uint32_t t_value = get_register(t);
    uint32_t sll = t_value << little_I;
    set_register(d, sll);
}

static void srl(uint32_t d, uint32_t t, uint32_t little_I){
    uint32_t t_value = get_register(t);
    uint32_t srl = t_value >> little_I;
    set_register(d, srl);
}

static void mul(uint32_t d, uint32_t s, uint32_t t){
    uint32_t s_value = convertion(get_register(s));
    uint32_t t_value = convertion(get_register(t));
    uint32_t mul = s_value * t_value;
    set_register(d, mul);
}

static void addi(uint32_t t, uint32_t s, int big_II){
    uint32_t s_value = convertion(get_register(s));
    uint32_t addi = s_value + big_II;
    set_register(t, addi);
}


static void andi(uint32_t t, uint32_t s, uint32_t big_I){
    uint32_t s_value = get_register(s);
    uint32_t andi = s_value & big_I;
    set_register(t, andi);
}

static void ori(uint32_t t, uint32_t s, uint32_t big_I){
    uint32_t s_value = get_register(s);
    uint32_t ori = s_value | big_I;
    set_register(t, ori);
}

static void xori(uint32_t t, uint32_t s, uint32_t big_I){
    uint32_t s_value = get_register(s);
    uint32_t xori = s_value ^ big_I;
    set_register(t, xori);
}

static void slti(uint32_t t, uint32_t s, int big_II){
    uint32_t s_value = get_register(s);
    uint32_t slti = convertion(s_value) < big_II;
    set_register(t, slti);
}

static uint64_t load_helper(int number, uint32_t address){
    uint64_t final = 0;
    for(uint32_t i = 0;i < number;i++){
        uint32_t tmp = get_byte(address);
        final = final + (uint64_t)(tmp << (i * 8));
        address++;      
    }
    return final;
}

static void lb(uint32_t t, int big_II, uint32_t s){
    uint32_t final = load_helper(1,big_II + get_register(s));
    final = ((final >> 7) & 1) * 0xFFFFFF00 + final;//if the eighth digit is 1, which means the 1 byte number loaded is negative
    //the statement will be 1 then the 24 digits at left will be filled with 1 to make the whole register negative
    //if the eighth digit is 0, the statement will be 0, the program will do nothing
    set_register(t, final);  

}

static void lh(uint32_t t, int big_II, uint32_t s){
    uint32_t final = load_helper(2,big_II + get_register(s));
    final = final + (convertion(final) < 0) * (0xFFFF0000);//reason same as above, except that I only use 16 bits, 
    //because half byte is 16 bits, so I can use function "convertion" to convert
    set_register(t, final); 
}

static void lw(uint32_t t, int big_II, uint32_t s){
    set_register(t, load_helper(4, big_II + get_register(s)));//register is 32 bits, so I don't need to worry about sign or not
}

static void sb(uint32_t t, int big_II, uint32_t s){//I only need to store one byte once for sb
    uint32_t t_value = get_register(t);
    set_byte(big_II + get_register(s),t_value & 0xFF); 
}

static void sh(uint32_t t, int big_II, uint32_t s){//I need to store one byte twice for sh, because 
    uint32_t t_value = get_register(t);
    set_byte(big_II + get_register(s), t_value & 0xFF);
    set_byte(big_II + 1 + get_register(s), (t_value >> 8) & 0xFF);//address will plus one to get next address
}

static void sw(uint32_t t, int big_II, uint32_t s){//I need to store one byte for four times
    uint32_t t_value = get_register(t);
    uint32_t value = big_II + get_register(s);
    for(int i = 0; i < 4; i++){//the address will change for four times
        set_byte(value + i, t_value & 0xFF);
        t_value = t_value >> 8;
    }  
}

static void syscall(void){
    int value = 0, scaned_char; //I have to create following values at the beginning due to the drawback of function "switch", they maybe used in following case
    char tmp;                   //same as above
    uint32_t address, character;//same as above
    switch(get_register(v0)){
        case 1://print an integer
            value = get_register(a0);
            printf("%d", value);
            break;
        case 4://print string
            for(int i = 0;get_byte(get_register(a0)+i) != '\0';i++){
                printf("%c",get_byte(get_register(a0)+i));//the character will be print one by one as i increases
            }
            break;
        case 5://scan an integer
            scanf("%d",&value);
            set_register(v0,value);
            break;
        case 8://scan a string, null terminated the string if the maximum length is reached
               //or replace left byte with null terminator after new line if '\n' is read
            address = get_register(a0);
            for(int i = 0; i < get_register(a1); i++){
                //if a new line is already scaned, left byte will be filled wil '\0'
                //if counter == number of byte allocated - 1, the string will also be terminated with '\0'
                if(value == 1 || i == get_register(a1) - 1) set_byte(address + i,'\0');
                else{
                    scaned_char = getchar();
                    set_byte(address + i,scaned_char);
                    if (scaned_char == '\n') value = 1;//"value" will be 1 as soon as a new line is read
                }
            }
            break;
        case 11://print char
            character = get_register(a0) & 0xFF;//get the first 8 digits
            printf("%c",character);
            break;
        case 12://scan a char
            scanf("%c",&tmp);
            set_register(v0,tmp);
            break;
    }
}
