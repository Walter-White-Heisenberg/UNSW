# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:
    li $t2, 1
    li $a0, 0
loop3:    
    beq $t2, 10, end3
    mul $t3, $t2, 4
    la $t4, numbers 
    add $t5, $t3, $t4
    addi $t4, $t5, -4
    lw $t7, ($t4)
    lw $t8, ($t5)
    bge  $t8, $t7, increment
    addi $a0, $a0, 1
increment:
    addi $t2, $t2, 1
    b loop3

end3:
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

