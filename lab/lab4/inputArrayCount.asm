# arrayCount.asm
  .data 
arrayA: .word 11, 0, 31, 22, 9, 17, 6, 9   # arrayA has 8 values
count:  .word 0             # initialise counter

  .text
main:
######################################
# setup the variable mappings
######################################

    la $t0, arrayA
    la $t8, count

######################################
# read in user input for array 
######################################

    addi $t1, $t0, 0 # start point
    addi $t2, $t0, 32 # end point

loop1:  slt $t3, $t1, $t2 # loop condition HLL: i < 8
        beq $t3, $zero, end1 # loop condition assembly: t1 < t2
        li $v0, 5 # system call for read_int
        syscall # get the integer
        sw $v0, 0($t1) # store input into array
        addi $t1, $t1, 4 # move pointer to next element
        j loop1 # go back to start of loop
end1:

######################################
# read in user input, X 
######################################

    li $v0, 5 # system call for read_int
    syscall # get the integer
    add $t5, $v0, $zero # load input into register

######################################
# counting elements <= to X in arrayA
######################################
    addi $t1, $t0, 0 # start point
    addi $t2, $t0, 32 # end point
    lw $s1, 0($t8) # load value of count

loop: slt $t3, $t1, $t2 # loop condition HLL: i < 8
      beq $t3, $zero, end # loop condition assembly: t1 < t2
      lw $t4, 0($t1) # load array element
      slt $s0, $t5, $t4 # check <= input, arr[i] <= input 
      bne $s0, $zero, skip # (complement) arr[i] > input (if true goto skip)
      addi $s1, $s1, 1 # increment counter 
skip: addi $t1, $t1, 4 # move pointer to next element
      j loop # go back to start of loop
end:

######################################
# printing result
######################################

    li   $v0, 1    # system call code for print_int
    add  $a0, $s1, $zero    # integer to print
    syscall        # print the integer

######################################
# terminating program
######################################

    li  $v0, 10
    syscall
