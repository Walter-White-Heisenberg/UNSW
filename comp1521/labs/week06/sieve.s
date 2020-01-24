# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:

    li $t1, 0
    la $t0, prime
loop1:
    bge $t1, 1000, pre
    sll $t3, $t1 , 2
    add $t3, $t0, $t3
    li $t2 , 1
    sw $t2, 0($t3)
    
    addi $t1, $t1 ,1
    b loop1

pre:
    li $t1, 2
    
loop2:
   bge $t1, 1000, end
   sll $t3, $t1 , 2
   add $t3, $t0, $t3
   lw $t2, 0($t3)
   beqz $t2, increment
   move $a0, $t1          # printf("%d", 42)
   li $v0, 1
   syscall
   li   $a0, '\n'      # printf("%c", '\n');
   li   $v0, 11  
   syscall
   sll $t3, $t1 ,1
loop3:
   bge $t3, 1000, increment
   sll $t4, $t3 , 2
   add $t4, $t0, $t4
   li $t2 , 0
   sw $t2, 0($t4)
   add $t3, $t3, $t1
   b loop3
   
   
   
   
increment:   
   addi $t1, $t1 ,1
   b loop2
   
end:
    li $v0, 0           # return 0
    jr $31

    


.data
prime:
    .space 1000
