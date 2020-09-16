# arrayFunction_ans.asm
	.data 
array: .word 8, 2, 1, 6, 9, 7, 3, 5, 0, 4
newl:	.asciiz "\n"
size: .word 10 # add size variable, modify this is array size is changed

    .text
main:
    # 1. Setup the parameter(s)
    # Call the printArray function to print the original content
	la $a0, array # load array 
	la $a1, size
    lw $a1, 0($a1)
	jal printArray

	# 2. Ask the user for two indices
	li   $v0, 5         	#System call code for read_int
	syscall           
	addi $t0, $v0, 0    	# first user input in $t0
 
	li   $v0, 5         	#System call code for read_int
	syscall           
	addi $t1, $v0, 0    	# second user input in $t1

	# 3. Setup the parameter(s)
    # Call the reverseArray function
	la $a0, array # load array 
	li $a1, 10 # load size variable
	jal reverseArray

    # 4. Setup the parameter(s)
    # Call the printArray function to print the modified array
	la $a0, array # load array 
	li $a1, 10 # load size variable
	jal printArray
	
	#End of main, make a syscall to "exit"
	li   $v0, 10   			# system call code for exit
	syscall	       			# terminate program
	

#######################################################################
###   Function printArray   ### 
#Input: Array Address in $a0, Number of elements in $a1
#Output: None
#Purpose: Print array elements
#Registers used: $t0, $t1, $t2, $t3
#Assumption: Array element is word size (4-byte)

printArray:
	addi $t1, $a0, 0	# $t1 is the pointer to the item
	sll  $t2, $a1, 2	# $t2 is the offset beyond the last item
	add  $t2, $a0, $t2 	# $t2 is pointing beyond the last item
l1:	
	beq  $t1, $t2, e1
	lw   $t3, 0($t1)	# $t3 is the current item
	li   $v0, 1   		# system call code for print_int
	addi $a0, $t3, 0    # integer to print
	syscall       		# print it
	addi $t1, $t1, 4
	j l1				# Another iteration
e1:
	li   $v0, 4   		# system call code for print_string
	la   $a0, newl    	# 
	syscall       		# print newline
	jr 	$ra				# return from this function


##################################################################
###   Function reverseArray                                    ### 
# Input: Array Address in $a0, Number of elements in $a1
# Output: NIL, as the array items are modified directly 
# Purpose: Reverse the array items, array pointer approach must be
#          used. 
# Registers used: <Fill in with your register usage>
# Registers used: $t0, $t1, $t2, $t3, $t7
# Assumption: Array element is word size (4-byte)
#             $a0 is valid and $a1 is positive integer

reverseArray:
    # Your implementation here
	sll $t0, $t0, 2 # multiply left index by 4 since int is word (4 bytes)
	add $t0, $a0, $t0 # set up left pointer
	sll $t1, $t1, 2 # multiply right index by 4 since int is word (4 bytes)
	add $t1, $a0, $t1 # set up right pointer

loop:
	slt $t3, $t0, $t1
	beq $t3, $zero, end
	lw $t4, 0($t0)
	lw $t5, 0($t1)
	sw $t4, 0($t1)
	sw $t5, 0($t0)
	addi $t0, $t0, 4
	addi $t1, $t1, -4
	j loop
end:
	jr 		$ra			# return from this function
