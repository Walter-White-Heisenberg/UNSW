# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    li $t0, 0
loop1:
    bge $t0, 1000, pre
    mul $t1, $t0, 4
    la $t2, prime
    add $t2, $t1, $t2
    li  $t8, 1
    sw  $t8, ($t2)
    addi $t0, $t0, 1
    b loop1

pre:
    li $t0, 2
loop2:
    bge $t0, 1000, end
    mul $t1, $t0, 4
    la $t2, prime
    add $t2, $t1, $t2
    lw  $t3, ($t2)
    beqz $t3, increment
    
    move $a0, $t0
    li $v0, 1
    syscall
    
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    mul $t4, $t0, 2
    
loop3:
    bge $t4, 1000, increment
    mul $t5, $t4, 4
    la $t6, prime
    add $t6, $t5, $t6
    li  $t8, 0
    sw  $t8, ($t2)
    sw  $t8, ($t6)
    add $t4, $t4, $t0 
    b loop3
    
increment:    
    addi $t0, $t0, 1
    b loop2
    
    
    
end:
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000
