main:                  
    la $a0, string     
    li $v0, 4
    syscall
    li $v0, 5           
    syscall  
    move $s0, $v0       
    li $t1, 1           
loop1:
    bgt $t1, $s0, end1             
    li $t2, 1         
    li $t3, 0
loop2:
    bgt $t2, $t1, end2 
    li $t4, 1           
loop3:
    bgt $t4, $t2, end3 
    add $t3, $t3, $t4   
    addi $t4, $t4, 1    
    b loop3
end3:
    addi $t2, $t2, 1 
    b loop2
end2:
    move $a0, $t3       
    li $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall   
    addi $t1, $t1, 1 
    b loop1
end1:
    jr   $ra         
    .data
string:
    .asciiz "Enter how many: "


