la $a0, string0     #   printf("Enter a number: ");
    li $v0, 4
    syscall
.data
string0:
    .asciiz "Enter a number: "
