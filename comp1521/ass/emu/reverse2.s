# count in register $t0
# registers $t1 and $t2 used to hold temporary results
lui $2, 64 
ori $16, $2, 36
sb $29, ($16)
lw $17, ($16)
lh $18, ($16)
lb $19, ($16)
