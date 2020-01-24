# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {

    la $a0, prompt     # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall
    move $t0, $v0
    li $t1, 1
loop1:
    bgt $t1, $t0 end
    li $t2, 1
    li $t5, 0
loop2:
    bgt $t2, $t1 increment
    li $t3, 1
    
    
loop3:
    add $t5 ,$t5, $t3
    addi $t3 ,$t3, 1
    bge $t2, $t3, loop3
    
    
    addi $t2 ,$t2, 1
    b loop2
increment:   
    move $a0, $t5          #   printf("%d", 42);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    addi $t1 ,$t1, 1
    
    b loop1
    
    
    
    

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
