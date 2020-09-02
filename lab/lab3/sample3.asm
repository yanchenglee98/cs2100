# sample3.asm
       .data 0x10000100
msg:   .asciiz "Hello"
       .text
main:  li $v0, 4     # print string call
       la $a0, msg   # load msg into $a0
       syscall
       lb $t0 4($a0) # load 'o' into $t0
       addi $t0, $t0, -32 # change $t0 to ASCII value of 'O'
       sb $t0, 4($a0)   # store $t0 into the memory location of 'o'
       syscall # perform another syscall
       li $v0, 10
       syscall
