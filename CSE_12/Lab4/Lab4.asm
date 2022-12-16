##########################################################################
# Created by: Kunal Shah
# CruzID: 
# 28 February 2021
#
# Assignment: Lab 4: Matching brackets
# CSE 12, Computer Systems and Assembly Language
# UC Santa Cruz, Winter 2021
#
# Description: This program checks .txt files to ensure that they have matching brackets:
#https://docs.google.com/document/d/1eAuMXh1R_FHgsgjq9WS_1yl_yXX-4vvDx9cO9WcSNC0/edit#
#
# Notes: This program is intended to be run from the MARS IDE.
##########################################################################

#PseudoCode Begins
#Open File
#Read File to Memory
#iterative for loop legenth of string in memory
#       next char jump placeholder
#       +1 iteration var to go to the next character
#       if it is a closing bracket then end code with correct error message by jumping to mismatch error
#       if it is a letter next character jump
#       if it is a matching braket delete the top of the stack(pop) and jump back to next char above and add 1 to a var
#       if nothing left from the txt file jump to nothingleft
#       else add to the stack
#       
#mismatch error jumper
# state char number(iterator number) that there is an mismatch
#end code using syscall 10
#
#nothing left jumper
# if there is something lef t in the stack jump to mismatch error
# else state sucess and number of matching vars and end using syscall 10


# REGISTER USAGE
# t0 - Stack Tracker
# t1 - first char of file
# t2 - charcter legenth counter
# t3 - filename legenth counter
# t4 - bracket counter
# t5 - indexer
# t6 - loop iterator
# s0 - file name location
# s1 - (currently unused) first letter of filename
# s2 - current char
# s3 - (currently unused) current bracket value bracket
# s4 - current bracket value
# s5 - descriptor
# s7 - max string legenth for filename

.data
        retreived_filename: .asciiz "You entered the file:\n"
        mismatch_error: .asciiz "ERROR - There is a brace mismatch: "
        pos_msg: .asciiz " at index "
        still_error: .asciiz "ERROR - Brace(s) still on stack: "
        suc_msg: .asciiz "SUCCESS: There are "
        brace_msg: .asciiz " pairs of braces."
        inv_msg: .asciiz "ERROR: Invalid program argument."
        buffer_space: .space 128
        newline: .asciiz "\n"
        filename: .space 128

.text
#print You entered the file and new line
li $v0, 4
la $a0, retreived_filename
syscall

#Look at address in a1 for file name and print file name
lw $s0, ($a1)
move $a0, $s0
li $v0, 4
syscall

#Making sure file name starts with a letter
lb $t1, 0($s0)
blt $t1, 'A', wrong_fname
bgt $t1, 'z', wrong_fname
bge $t1, '[', less_ch
OK:
move $t2, $s0
li $t3, 0

#reading String legenth for file name
loop:
lb $s6, ($t2)
beqz $s6, str_len
addi $t3, $t3, 1
addi $t2, $t2, 1
j loop
str_len:
li $s7, 20 #CHANGE MAX FILELEGENTH HERE
bgt $t3, $s7, wrong_fname

li $t5, 0 #counter
li $t6, 0 #loop iterator
li $t0, 0 #track stack

#open file
move $a0, $s0
li $v0, 13
li $a1, 0
li $a2, 0
syscall
move $s5, $v0

#read file
read_file:
move $a0, $s5
li $v0, 14
la $a1, buffer_space
li $a2, 128
syscall
move $t1, $v0
beqz $t1, finish
la $t4, buffer_space

#check if parenthese and if opening then store if closing pop or error
loop1:
lb $s2, ($t4)
beqz $s2, read_file
beq $s2, '[', store_on_stack
beq $s2, ']', load_s_stack
beq $s2, '{', store_on_stack
beq $s2, '}', load_c_stack
beq $s2, '(', store_on_stack
beq $s2, ')', load_sm_stack
addi $t6, $t6, 1
addi $t4, $t4, 1
j loop1

#stack add logic
store_on_stack:
addi $sp, $sp, -1
sb $s2, 0($sp)
addi $t0, $t0, 1
addi $t6, $t6, 1
addi $t4, $t4, 1
j loop1

#brcket pop
load_s_stack:
lb $s4, ($sp)
addi $sp, $sp, 1
subi $t0, $t0, 1
bne $s4, '[', notOk
addi $t5, $t5, 1
addi $t6, $t6, 1
addi $t4, $t4, 1
j loop1  

#brace pop
load_c_stack:
lb $s4, ($sp)
addi $sp, $sp, 1
subi $t0, $t0, 1
bne $s4, '{', notOk
addi $t5, $t5, 1
addi $t6, $t6, 1
addi $t4, $t4, 1
j loop1 

#para pop
load_sm_stack:
lb $s4, ($sp)
addi $sp, $sp, 1
subi $t0, $t0, 1
bne $s4, '(', notOk
addi $t5, $t5, 1
addi $t6, $t6, 1
addi $t4, $t4, 1
j loop1 

#mismatch error message ending
notOk:
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, mismatch_error
syscall
li $v0, 11
move $a0, $s2
syscall
li $v0, 4
la $a0, pos_msg
syscall
li $v0, 1
move $a0, $t6
syscall
li $v0, 4
la $a0, newline
syscall
j close_file
finish:
bnez $t0,not_balance

#sucess ending
print_success:
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, suc_msg
syscall
li $v0, 1
move $a0, $t5
syscall
li $v0, 4
la $a0, brace_msg
syscall
li $v0, 4
la $a0, newline
syscall
j close_file

#unbalanced error message
not_balance:
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, still_error
syscall

loop2:
beqz $t0, stop
lb $a0, 0($sp)
addi $sp, $sp, 1
li $v0, 11
syscall
subi $t0, $t0, 1
j loop2

#end of code stuff below:
stop:

li $v0, 4
la $a0, newline
syscall

#close file
close_file:
li $v0, 16
move $a0, $s5
syscall
j terminate

less_ch:
blt $t1, 'a', wrong_fname
j OK

wrong_fname:
li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, inv_msg
syscall

li $v0, 4
la $a0, newline
syscall

#End code
terminate:
li $v0, 10
syscall
