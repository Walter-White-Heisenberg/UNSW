main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0
    
increment:
    add $t0, $t0, 1
loop:   
    bge  $t0, $t1 end 
    
    beq $t0, 13 increment
    move $a0, $t0          #   printf("%d\n", 42);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
    b increment


        
    
end:

    li $v0, 0           # return 0
    jr $31
