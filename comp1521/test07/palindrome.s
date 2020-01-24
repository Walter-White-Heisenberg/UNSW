# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #
    li  $t0, 0
loop1:
    lb   $t1, line($t0)
    beqz $t1, pre
    addi $t0, $t0, 1
    b loop1
pre:
    addi $t0, $t0, -2
    li $t1, 0
loop2:
    slt  $t2, $t1, $t0
    beq  $t2, 0, yes
    lb   $t3, line($t0)
    lb   $t4, line($t1)
    bne  $t3, $t4, No
    addi $t1, $t1, 1
    addi $t0, $t0, -1
    b loop2
yes:
    la   $a0, palindrome
    li   $v0, 4
    syscall
    b End     
No:
    la   $a0, not_palindrome
    li   $v0, 4
    syscall
End:
    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

