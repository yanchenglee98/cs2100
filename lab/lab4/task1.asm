# messages.asm
  .data 
str: .asciiz "the answer = "
  .text

main: 
    li $v0, 5 # system call for read_int
    syscall # print the integer
    add $t0, $v0, $zero # load input into register

    li   $v0, 4    # system call code for print_string
    la   $a0, str  # address of string to print
    syscall        # print the string

    li   $v0, 1    # system call code for print_int
    add  $a0, $t0, $zero    # integer to print
    syscall        # print the integer

    li   $v0, 10   # system call code for exit
    syscall        # terminate program
