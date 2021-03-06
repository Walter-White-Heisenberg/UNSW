# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall
    
    bge $v0, 85 ,HD
    
    bge $v0, 75 ,Dis
    
    bge $v0, 65, CR
    
    bge $v0, 50, PA
     
    la $a0, fl          # printf("FL\n");
    li $v0, 4
    syscall
    
    jr $ra
PA:
    la $a0, ps         # printf("FL\n");
    li $v0, 4
    syscall
    
    jr $ra
CR:
    la $a0, cr          # printf("FL\n");
    li $v0, 4
    syscall
    
    jr $ra
Dis:
    la $a0, dn          # printf("FL\n");
    li $v0, 4
    syscall
    
    jr $ra
HD:
    la $a0, hd          # printf("FL\n");
    li $v0, 4
    syscall
    
    jr $ra              # return

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
