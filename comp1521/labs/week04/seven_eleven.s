main:                 # int main(void) {
                      # int i;  // in register $t0
    la   $a0, string    # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5          # scanf("%d", x);
    syscall
    move $t1, $v0     #   printf("%d" i);
    li    $t0, 1      # i = 1;
loop:                 # loop:
    bge  $t0, $t1 end  
    
    rem  $t3, $t0, 7 
    beqz $t3 seven_eleven
    
    rem  $t3, $t0, 11 
    beqz $t3 seven_eleven
    

    add  $t0, $t0 1   #   i++;

    b    loop         # goto loop;

    
seven_eleven:
    move $a0, $t0     #   printf("%d" i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    add  $t0, $t0 1   #   i++;
    b    loop 
    
end:
    li   $v0, 0       # return 0
    jr   $ra
    
        .data
string:    
        .asciiz "Enter a number: "
