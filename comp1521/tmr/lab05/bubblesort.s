# read 10 numbers into an array
# bubblesort them
# then print the 10 numbers

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

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
    li $t0, 1
end0:
    beqz $t0, newstart 
    li $t0, 0
    li $t1, 1
    
loop2:
    beq $t1, 10, end0
    mul $t4, $t1, 4
    addi $t3, $t4, -4
    la $t2, numbers
    add $t3, $t3, $t2
    add $t4, $t4, $t2
    lw $t8, ($t4)
    lw $t7, ($t3)  
    bgt $t7, $t8, swap

increment:
    addi $t1, $t1, 1
    b loop2

swap:
    sw $t8, ($t3)
    sw $t7, ($t4)
    li $t1, 1
    b increment
    # PUT YOUR CODE HERE

newstart:
    li $t0, 0           # i = 0
loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    jr $31              # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

