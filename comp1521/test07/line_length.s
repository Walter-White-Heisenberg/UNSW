# read a line and print its length

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line 
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #
    la   $a0, str1       # printf("Line length: ");
    li   $v0, 4
    syscall
    li  $t0, 0
loop1:
    lb  $t1, line($t0)
    beqz $t1, end
    add $t0, $t0, 1
    b loop1
end:
    move   $a0, $t0         # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Line length: "


# line of input stored here
line:
    .space 256
