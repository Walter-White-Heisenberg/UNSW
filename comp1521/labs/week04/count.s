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
    bgt  $t0, $t1 end  

    move $a0, $t0     #   printf("%d" i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add  $t0, $t0 1   #   i++;

    b    loop         # goto loop;

end:
    li   $v0, 0       # return 0
    jr   $ra
    
    
    
        .data
string:    
        .asciiz "Enter a number: "
