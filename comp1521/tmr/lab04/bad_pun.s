    

main: 
la $a0, string
li $v0, 4
syscall
    
li $a0, '\n'
li $v0, 11
syscall
jr $ra
    .data
string:
    .asciiz "I MIPS you!"
