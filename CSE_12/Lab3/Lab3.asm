##########################################################################
# Created by: Shah, Kunal
# CruzID
# 9 February 2021
#
# Assignment: Lab 3: ascii pyramid generator
# CSE 12, Computer Systems and Assembly Language
# UC Santa Cruz, Winter 2021
#
# Description: This program prints a ascii art triangle to the screen. according to:
#https://docs.google.com/document/d/1eAuMXh1R_FHgsgjq9WS_1yl_yXX-4vvDx9cO9WcSNC0/edit#
#
# Notes: This program is intended to be run from the MARS IDE.
##########################################################################

# REGISTER USAGE
#$t5: Row aggregator (loop counter for row)
#$t6: Left astrix collumn aggregator (loop counter for left collumns)
#$t7: Right astrix collumn aggregator (loop counter for right collumns)
#$a0: used to display information using syscall
#$v0: Used for user inout
#$s0: Used to save user input

.data
	prompt:	.asciiz "Enter the height of the pattern (must be greater than 0):	"
	low_input_error: .asciiz "Invlid Entry!\n"
	astrix_tab: .asciiz "*	"
	tab_astrix: .asciiz "	*"
	new_line: .asciiz "\n"
.text
must_input_positive:
	li $v0, 4											#Prompt user to input number
	la $a0, prompt
	syscall
	
	li $v0, 5											#Inputing action
	syscall
	
	move $s0 $v0											#saving inputed number for future use in s0 registrar
	
	bgtz $v0, print_pyramid										# if valid number is input then start printing pyrabid else continue downwards
	
	li $v0, 4											#(else of above statement) display Invalid error message
	la $a0, low_input_error
	syscall
	
	j must_input_positive										#once invalid error message is displayed re-querry user for a valid number
	
print_pyramid:
	li $t5, 0											#set registrar t5 to 0 just in case
	
row_initiate:
	addi $t5, $t5, 1										#t5 keeps track of which row we on and itterates every time I want to move on to the next row
	
	li $t6, 1											#resets registrar t6, and t7 to 0
	li $t7, 1

left_astrix_set:
	bge $t6, $t5, row_number_disp									#Keep addinf left side astrix's until aggregator hits its desired value
	li $v0, 4
	la $a0, astrix_tab
	syscall
	addi $t6, $t6, 1
	j left_astrix_set

row_number_disp:
	li $v0,1											#Displays the correct row number
	move $a0, $t5
	syscall
	
right_astrix_set:
	bge $t7, $t5, nrow_end										#Keep addinf right side astrix's until aggregator hits its desired value
	li $v0, 4
	la $a0, tab_astrix
	syscall
	addi $t7, $t7, 1
	j right_astrix_set
	
nrow_end:
	bge $t5, $s0, task_end										#check if we need to complete another row or end the program
	
	li $v0, 4											#this ath is taken if we dont end the program so we start off by creating a new line
	la $a0, new_line
	syscall
	
	j row_initiate											#go back to start the next row
		
task_end:
	li $v0, 10											#allows for me to jump to the end of the code from conditional above and end the program via the below command
	syscall	
