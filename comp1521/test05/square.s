main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0
    li $t1, 0     #i
    

loop1:    
    beq $t1, $t0 end
    li $t2, 0     #j          
    

loop2:
    beq $t2, $t0 Increment
    li   $a0, '*'      #   printf("%c", '*');
    li   $v0, 11
    syscall
    add $t2, $t2, 1
    b loop2

Increment:
    add $t1, $t1, 1
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    b loop1
end:

    li $v0, 0           # return 0
    jr $31
