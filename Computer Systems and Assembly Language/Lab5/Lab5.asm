# Winter 2021 CSE12 Lab5 Template

##########################################################################
# Created by: Kunal Shah
# CruzID: kgshah
# 8 March 2021
#
# Assignment: Lab 4: Bitmap Display
# CSE 12, Computer Systems and Assembly Language
# UC Santa Cruz, Winter 2021
#
# Description:use Mars to create an asm file that accomplishes reasults described in this Lab 5 doc(https://docs.google.com/document/d/1gbjXJskhv0bnPKR-YSHpARIfDhk3EgWcu2AADJhzPlg/edit#)
#
# Notes: This program is intended to be run from the MARS IDE.
##########################################################################

#PseudoCode Begins
#Function 1 to convert 0x00xx00yy to xx and yy
#Function 2 to reverse the above function
#Function 3 to calculate pixel address using origin + 4 * (x + 128 * y)
#Function 4 to set the canvas to one color
#Function 5 to draw singular pixels in particular locations
#Function 6 to store a particular pixels color hex value
#Function 7 to draw a horizontal line
#Function 8 to draw a vertical line
#Function 9 to draw a crosshair using functions 6 to remember the color of that pixel and then functions 7 and 8 to draw the crosshair and the draw pixel to replace tht square
#
#Below is in the test file
#Call Function 4 with color green
#Call Function 6 twice once in top left with cyan and once in bottom left with yellow
#Calls function 7 for a yellow line
#Calls function 8 for a blue vertical line
#Calls Function 9 to draw a indigo crosshair
#end of codde
#
#
# REGISTER USAGE
# t0 - Iterative counter
# t1 - typically used to write simple numbers to
# t2 - store y or x value here for hori and vert line
# t3 - origin address
# t7 - horizontal and vertical 0-127 itterator(tecnically it goes to 128 but it dosent use that value
# s0 - store 0x00XX00YY for crosshair
# s1 - store 0x00RRGGBB for crosshair
# s2 - store x for crosshair
# s3 - store y for crosshair
# s4 - store current crosshair pixel here
# a0 - function inputs either color coords or address specified in the function comments
# a1 - function inputs either color coords or address specified in the function comments

######################################################
# Macros for instructor use (you shouldn't need these)
######################################################

# Macro that stores the value in %reg on the stack 
#	and moves the stack pointer.
.macro push(%reg)
	subi $sp $sp 4
	sw %reg 0($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#	loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw %reg 0($sp)
	addi $sp $sp 4	
.end_macro

#################################################
# Macros for you to fill in (you will need these)
#################################################

# Macro that takes as input coordinates in the format
#	(0x00XX00YY) and returns x and y separately.
# args: 
#	%input: register containing 0x00XX00YY
#	%x: register to store 0x000000XX in
#	%y: register to store 0x000000YY in
.macro getCoordinates(%input %x %y)

        #Divides by FFFF +1 in order to make our remainder and whole number the 2 parts of x and y
	li $t1, 65536
        div %input, $t1
        mfhi %y
        mflo %x
	
.end_macro

# Macro that takes Coordinates in (%x,%y) where
#	%x = 0x000000XX and %y= 0x000000YY and
#	returns %output = (0x00XX00YY)
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%output: register to store 0x00XX00YY in
.macro formatCoordinates(%output %x %y)
	
        #Multiplys the x by FFFF +1 to move it up a certin number of places and then add x and y to get the coordinate in aforementioned form
	li $t0, 65536
        mult %x, $t0
        mflo $t1
        addi %output $t1, %y
	
.end_macro 

# Macro that converts pixel coordinate to address
# 	output = origin + 4 * (x + 128 * y)
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%origin: register containing address of (0, 0)
#	%output: register to store memory address in
.macro getPixelAddress(%output %x %y %origin)
	
        #128 * y
        li $t0, 128
        mult $t0, %y
        mflo $t0

        #x + 128 * y
        add $t0, %x, $t0
        
        # 4 * (x + 128 * y)
        li $t1, 4
        mult $t0, $t1
        mflo $t0
        
        # output = origin + 4 * (x + 128 * y)
        add %output, %origin, $t0
        
.end_macro


.data
originAddress: .word 0xFFFF0000

.text
# prevent this file from being run as main
li $v0 10 
syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
# Clear_bitmap: Given a color, will fill the bitmap 
#	display with that color.
# -----------------------------------------------------
# Inputs:
#	$a0 = Color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
clear_bitmap: nop
	#sets origin address and max pixel loop counter
        lw $t0, originAddress
	addi $t1, $t0, 65532

        #Loop to set every pixel to a designated color
        Clear_bitmap_loop:
        sw $a0, 0($t0)
        addi $t0, $t0, 4
        ble $t0, $t1, Clear_bitmap_loop
	
 	jr $ra

#*****************************************************
# draw_pixel: Given a coordinate in $a0, sets corresponding 
#	value in memory to the color given by $a1
# -----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#		$a1 = color of pixel in format (0x00RRGGBB)
#	Outputs:
#		No register outputs
#*****************************************************
draw_pixel: nop
        
        #Sets a particular pixel to a certian color given coordinates
        lw $t3, originAddress
        getCoordinates ($a0, $t1, $t2)
        getPixelAddress($t0, $t1, $t2, $t3)
	sw $a1, 0($t0)
	
	jr $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#	Outputs:
#		Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	
        #Reads an stores the color of a pixel to  registar for later use
        lw $t3, originAddress
        getCoordinates($a0, $t1, $t2)
        getPixelAddress($t0, $t1, $t2, $t3)
        lw $v0, 0($t0)
        
	jr $ra

#*****************************************************
# draw_horizontal_line: Draws a horizontal line
# ----------------------------------------------------
# Inputs:
#	$a0 = y-coordinate in format (0x000000YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_horizontal_line: nop
	
        #sets orignin address and loop counter
	li $t7, 0
	lw $t3, originAddress
	
        #sets all pixels in a horiontal line to a color one by one
	hori_loop:
	getPixelAddress($t1, $t7, $a0, $t3)
	addi $t7, $t7, 1
	sw $a1, 0($t1)
	bne $t7, 128, hori_loop
	
	
 	jr $ra


#*****************************************************
# draw_vertical_line: Draws a vertical line
# ----------------------------------------------------
# Inputs:
#	$a0 = x-coordinate in format (0x000000XX)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_vertical_line: nop
	
	#sets orignin address and loop counter
	li $t7, 0
	lw $t3, originAddress
	
        #sets all pixels in a vertical line to a color one by one
	vert_loop:
	getPixelAddress($t1, $a0, $t7, $t3)
	addi $t7, $t7, 1
	sw $a1, 0($t1)
	bne $t7, 128, vert_loop
	
 	jr $ra


#*****************************************************
# draw_crosshair: Draws a horizontal and a vertical 
#	line of given color which intersect at given (x, y).
#	The pixel at (x, y) should be the same color before 
#	and after running this function.
# -----------------------------------------------------
# Inputs:
#	$a0 = (x, y) coords of intersection in format (0x00XX00YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_crosshair: nop
	push($ra)
	push($s0)
	push($s1)
	push($s2)
	push($s3)
	push($s4)
	push($s5)
	move $s5 $sp

	move $s0 $a0  # store 0x00XX00YY in s0
	move $s1 $a1  # store 0x00RRGGBB in s1
	getCoordinates($a0 $s2 $s3)  # store x and y in s2 and s3 respectively
	
	# get current color of pixel at the intersection, store it in s4
	jal get_pixel
	move $s4, $v0
	
	# draw horizontal line (by calling your `draw_horizontal_line`) function
	move $a1, $s1
	move $a0, $s3
	jal draw_horizontal_line

	# draw vertical line (by calling your `draw_vertical_line`) function
	move $a1, $s1
	move $a0, $s2
	jal draw_vertical_line

	# restore pixel at the intersection to its previous color
	move $a0, $s0
	move $a1, $s4
	jal draw_pixel

	move $sp $s5
	pop($s5)
	pop($s4)
	pop($s3)
	pop($s2)
	pop($s1)
	pop($s0)
	pop($ra)
	jr $ra
