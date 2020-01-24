#include <stdio.h>
#include <limits.h>
#include <stdint.h>
/*int main(void){
    uint16_t x = 0; 
    printf("%d\n",x ^ 0);
           
    return 0;    
}

int main(void) {

    char c;
    printf("char               %lu bytes min=%20d, max=%20d\n", sizeof c, CHAR_MIN, CHAR_MAX);
    signed char sc;
    printf("signed char        %lu bytes min=%20d, max=%20d\n", sizeof sc, SCHAR_MIN, SCHAR_MAX);
    unsigned char uc;
    printf("unsigned char      %lu bytes min=%20d, max=%20d\n", sizeof uc, 0, UCHAR_MAX);

    short s;
    printf("short              %lu bytes min=%20d, max=%20d\n", sizeof s, SHRT_MIN, SHRT_MAX);
    unsigned short us;
    printf("unsigned short     %lu bytes min=%20d, max=%20d\n", sizeof us, 0, USHRT_MAX);

    int i;
    printf("int                %lu bytes min=%20d, max=%20d\n", sizeof i, INT_MIN, INT_MAX);
    unsigned int ui;
    printf("unsigned int       %lu bytes min=%20d, max=%20d\n", sizeof ui, 0, UINT_MAX);

    long l;
    printf("long               %lu bytes min=%20ld, max=%20ld\n", sizeof l, LONG_MIN, LONG_MAX);
    unsigned long ul;
    printf("unsigned long      %lu bytes min=%20d, max=%20lu\n", sizeof ul, 0, ULONG_MAX);

    long long ll;
    printf("long long          %lu bytes min=%20lld, max=%20lld\n", sizeof ll, LLONG_MIN, LLONG_MAX);
    unsigned long long ull;
    printf("unsigned long long %lu bytes min=%20d, max=%20llu\n", sizeof ull, 0, ULLONG_MAX);

    return 0;
}



void print_bits(int value);
int get_nth_bit(int value, int n);

int main(void) {
    int a = 0;
    printf("Enter an int: ");
    scanf("%d", &a);
    print_bits(a);
    printf("\n");
    return 0;
}

// print the binary representation of a value
void print_bits(int value) {
    // sizeof returns size in bytes and 1 byte == 8 bits
    int how_many_bits = 8 * (sizeof value);
    for (int i = how_many_bits - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
    }
}

// extract the nth bit from a value
int get_nth_bit(int value, int n) {
    return (value >> n) & 1;
}
*/

void print_bits_hex(char *description, short n);
void print_bits(short value);
int get_nth_bit(short value, int n);

int main(void) {
    short a = 0;
    printf("Enter a: ");
    scanf("%hd", &a);
    short b = 0;
    printf("Enter b: ");
    scanf("%hd", &b);
    printf("Enter c: ");
    int c = 0;
    scanf("%d", &c);
    print_bits_hex("     a = ", a);
    print_bits_hex("     b = ", b);
    print_bits_hex("    ~a = ", ~a);
    printf("uint16_t = %d\n",(uint16_t) (~a));
    print_bits_hex(" a & b = ", a & b);
    print_bits_hex(" a | b = ", a | b);
    print_bits_hex(" a ^ b = ", a ^ b);
    print_bits_hex("a >> c = ", a >> c);
    print_bits_hex("a << c = ", a << c);
    return 0;
}

// print description then binary, hex and decimal representation of value
void print_bits_hex(char *description, short value) {
    printf("%s", description);
    print_bits(value);
    printf(" = 0x%04x = %d\n", value & 0xFFFF, value);
}

// print the binary representation of a value
void print_bits(short value) {
    // sizeof returns size in bytes and 1 byte == 8 bits
    int how_many_bits = 8 * (sizeof value);
    for (int i = how_many_bits - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
    }
}

// extract the nth bit from a value
int get_nth_bit(short value, int n) {
    return (value >> n) & 1;
}
// Andrew Taylor - andrewt@unsw.edu.au
// 16/9/2019
// Respresent set of small non-negative integers using bit-operations
/*
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef uint64_t set;

#define MAX_SET_MEMBER ((int)(8 * sizeof (set) - 1))
#define EMPTY_SET 0

set set_add(int x, set a);
set set_union(set a, set b);
set set_intersection(set a, set b);
int set_member(int x, set a);
int set_cardinality(set a);
set set_read(char *prompt);
void set_print(char *description, set a);

void print_bits_hex(char *description, set n);
void print_bits(set value);
int get_nth_bit(set value, int n);

int main(void) {
    printf("Set members can be 0-%d, negative number to finish\n", MAX_SET_MEMBER);
    set a = set_read("Enter set a: ");
    set b = set_read("Enter set b: ");
    print_bits_hex("a = ", a);
    print_bits_hex("b = ", b);
    set_print("a = ", a);
    set_print("b = ", b);
    set_print("a union b = ", set_union(a, b));
    set_print("a intersection b = ", set_intersection(a, b));
    printf("cardinality(a) = %d\n", set_cardinality(a));
    printf("is_member(42, a) = %d\n", set_member(42, a));
    return 0;
}

set set_add(int x, set a) {
    return a | ((set)1 << x);
}

set set_union(set a, set b) {
    return a|b;
}

set set_intersection(set a, set b) {
    return a&b;
}

// return a non-zero value iff x is a member of a
int set_member(int x, set a) {
    assert(x >= 0 && x < MAX_SET_MEMBER);
    return a & ((set)1 << x);
}

// return size of set
int set_cardinality(set a) {
    int n_members = 0;
    while (a != 0) {
        n_members += a & 1;
        a >>= 1;
    }
    return n_members;
}

set set_read(char *prompt) {
    printf("%s", prompt);
    set a = EMPTY_SET;
    int x;
    while (scanf("%d", &x) == 1 && x >= 0) {
        a = set_add(x, a);
    }
    return a;
}

// print out member of the set in increasing order
// for example {5,11,56}
void set_print(char *description, set a) {
    printf("%s", description);
    printf("{");
    int n_printed = 0;
    for (int i = 0; i < MAX_SET_MEMBER; i++) {
        if (set_member(i, a)) {
            if (n_printed > 0) {
                printf(",");
            }
            printf("%d", i);
            n_printed++;
        }
    }
    printf("}\n");
}

// print description then binary, hex and decimal representation of value
void print_bits_hex(char *description, set value) {
    printf("%s", description);
    print_bits(value);
    printf(" = 0x%08lx = %ld\n", value, value);
}

// print the binary representation of a value
void print_bits(set value) {
    // sizeof returns size in bytes and 1 byte == 8 bits
    int how_many_bits = 8 * (sizeof value);
    for (int i = how_many_bits - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
    }
}

// extract the nth bit from a value
int get_nth_bit(set value, int n) {
    return (value >> n) & 1;
}
*/
