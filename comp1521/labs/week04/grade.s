main:                 # int main(void) {
    la   $a0, string0    # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5          # scanf("%d", x);
    syscall
    
    bgt  $v0, 84 High 
    
    bgt  $v0, 74 Dist  
    
    bgt  $v0, 64 Cred  
    
    bgt  $v0, 49 Pass 
    
    bgt  $v0, -1  Fail 
    
    High:
    la   $a0, string1  
    li   $v0, 4       
    syscall
    b end
    
    Dist:
    la   $a0, string2  
    li   $v0, 4       
    syscall
    b end
    
    Cred:
    la   $a0, string3  
    li   $v0, 4       
    syscall
    b end
    
    Pass:
    la   $a0, string4  
    li   $v0, 4       
    syscall
    b end
    
    Fail:
    la   $a0, string5  
    li   $v0, 4       
    syscall
    b end
    
    end:
    li   $v0, 0          # return 0
    jr   $ra
    
    .data   
string0:
    .asciiz "Enter a mark: "    
string1:
    .asciiz "HD\n"
string2:
    .asciiz "DN\n"
string3:
    .asciiz "CR\n"
string4:
    .asciiz "PS\n"
string5:
    .asciiz "FL\n"    
