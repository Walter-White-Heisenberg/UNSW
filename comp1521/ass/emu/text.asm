
	USER TEXT SEGMENT
[0x00400000]	0x8fa40000  lw $4, 0($29)                   ; 183: lw $a0 0($sp)		# argc
[0x00400004]	0x27a50004  addiu $5, $29, 4                ; 184: addiu $a1 $sp 4		# argv
[0x00400008]	0x24a60004  addiu $6, $5, 4                 ; 185: addiu $a2 $a1 4		# envp
[0x0040000c]	0x00041080  sll $2, $4, 2                   ; 186: sll $v0 $a0 2
[0x00400010]	0x00c23021  addu $6, $6, $2                 ; 187: addu $a2 $a2 $v0
[0x00400014]	0x0c100009  jal 0x00400024 [main]           ; 188: jal main
[0x00400018]	0x00000000  nop                             ; 189: nop
[0x0040001c]	0x3402000a  ori $2, $0, 10                  ; 191: li $v0 10
[0x00400020]	0x0000000c  syscall                         ; 192: syscall			# syscall 10 (exit)
[0x00400024]	0x34080000  ori $8, $0, 0                   ; 4: li $t0, 0           # count = 0
[0x00400028]	0x2901000a  slti $1, $8, 10                 ; 7: bge $t0, 10, print  # while (count < 10) {
[0x0040002c]	0x1020000f  beq $1, $0, 60 [print-0x0040002c]
[0x00400030]	0x3c011001  lui $1, 4097 [string0]          ; 8: la $a0, string0     # printf("Enter a number: ");
[0x00400034]	0x34240028  ori $4, $1, 40 [string0]
[0x00400038]	0x34020004  ori $2, $0, 4                   ; 9: li $v0, 4
[0x0040003c]	0x0000000c  syscall                         ; 10: syscall
[0x00400040]	0x34020005  ori $2, $0, 5                   ; 12: li $v0, 5           #   scanf("%d", &numbers[count]);
[0x00400044]	0x0000000c  syscall                         ; 13: syscall             #
[0x00400048]	0x34010004  ori $1, $0, 4                   ; 14: mul $t1, $t0, 4     #   calculate &numbers[count]
[0x0040004c]	0x71014802  mul $9, $8, $1
[0x00400050]	0x3c011001  lui $1, 4097 [numbers]          ; 15: la $t2, numbers     #
[0x00400054]	0x342a0000  ori $10, $1, 0 [numbers]
[0x00400058]	0x012a4820  add $9, $9, $10                 ; 16: add $t1, $t1, $t2   #
[0x0040005c]	0xad220000  sw $2, 0($9)                    ; 17: sw $v0, ($t1)       #   store entered number in array
[0x00400060]	0x21080001  addi $8, $8, 1                  ; 19: add $t0, $t0, 1     #   count++;
[0x00400064]	0x0401fff1  bgez $0 -60 [read-0x00400064]   ; 20: b read              # }
[0x00400068]	0x3c011001  lui $1, 4097 [string1]          ; 23: la $a0, string1     # printf("Reverse order:\n");
[0x0040006c]	0x34240039  ori $4, $1, 57 [string1]
[0x00400070]	0x34020004  ori $2, $0, 4                   ; 24: li $v0, 4
[0x00400074]	0x0000000c  syscall                         ; 25: syscall
[0x00400078]	0x34080009  ori $8, $0, 9                   ; 26: li $t0, 9           # count = 9;
[0x0040007c]	0x29010000  slti $1, $8, 0                  ; 28: blt $t0, 0, end1    # while (count >= 0) {
[0x00400080]	0x1420000e  bne $1, $0, 56 [end1-0x00400080]
[0x00400084]	0x34010004  ori $1, $0, 4                   ; 30: mul $t1, $t0, 4     #   printf("%d", numbers[count])
[0x00400088]	0x71014802  mul $9, $8, $1
[0x0040008c]	0x3c011001  lui $1, 4097 [numbers]          ; 31: la $t2, numbers     #   calculate &numbers[count]
[0x00400090]	0x342a0000  ori $10, $1, 0 [numbers]
[0x00400094]	0x012a4820  add $9, $9, $10                 ; 32: add $t1, $t1, $t2   #
[0x00400098]	0x8d240000  lw $4, 0($9)                    ; 33: lw $a0, ($t1)       #   load numbers[count] into $a0
[0x0040009c]	0x34020001  ori $2, $0, 1                   ; 34: li $v0, 1
[0x004000a0]	0x0000000c  syscall                         ; 35: syscall
[0x004000a4]	0x3404000a  ori $4, $0, 10                  ; 37: li   $a0, '\n'      #   printf("%c", '\n');
[0x004000a8]	0x3402000b  ori $2, $0, 11                  ; 38: li   $v0, 11
[0x004000ac]	0x0000000c  syscall                         ; 39: syscall
[0x004000b0]	0x2108ffff  addi $8, $8, -1                 ; 41: sub $t0, $t0,1      #   count--;
[0x004000b4]	0x0401fff2  bgez $0 -56 [next-0x004000b4]   ; 42: b next              # }
[0x004000b8]	0x03e00008  jr $31                          ; 45: jr $31              # return
