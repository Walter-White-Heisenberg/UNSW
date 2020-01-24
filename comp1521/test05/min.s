#  print the minimum of two integers
main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    bgt  $t0, $t1 first 
    move $a0, $t0          #   printf("%d\n", 42);
    li $v0, 1
    syscall
    
    b end

first:
    	
    move $a0, $t1          #   printf("%d\n", 42);
    li $v0, 1
    syscall
    
    b end	

end:
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    li $v0, 0           # return 0
    jr $31
    
    
    
    
