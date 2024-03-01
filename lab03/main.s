.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

//data section of the program
.section .data
.align

//these values will follow each other word by word in the memory space starting from address 0x20000000
grades: .word 1,20,30,40,50,80,99,100,-1 //grades array (place values here)
min: .word 0 	//assigned a word of memory space for minimum (first word space following -1)
max: .word 0 	//assigned a word of memory space for maximum (second word space following minimum)
avg: .word 0 	//assigned a word of memory space for average (word space following maximum)
med: .word 0 	//assigned a word of memory space for median  (word space following average)


//code section of the program
.section .text
.align
.global main

main: //BEGIN MAIN LOOP PROGRAM
LDR r0, =grades 	//pointer to the start of the array
MOV r2, #0 			//sum=0
MOV r3, #0 			//length=0
MOV r4, #101 		//current minimum= 101 (any number will be smaller than 101 as a minimum in this array)
MOV r5, #-1 		//current maximum= -1  (any number will be greater than -1 as a maximum in this array)


gradeLoop:
LDR r1, [r0] 		//loads element into r0
CMP r1, #-1 		//compares r1 and -1
BEQ comp_Avg 		//if r1=-1 then branch to comp_Avg
ADD r2, r2, r1 		//if not add r1 to r2(sum)
ADD r3, r3, #1 		//add +1 to length

CMP r1, r4 			//compares r1 and r4 (current minimum)
IT LT 				//if-then block for less than
LDRLT r4, [r0] 		//if r1<r4 then load r0(current element) into r4

CMP r5, r1 			//compares r5(current maximum) and r1
IT LT 				//if-then block for less than
LDRLT r5, [r0] 		//if r5<r1 then load r0(current element) into r5

ADD r0, r0, #4 		//advance pointer to next word in array
B gradeLoop			//branch back to gradeLoop

comp_Avg:
UDIV r2, r2, r3 //r2(avg)= r2(sum)/r3(length)

storeValues:
LDR r0,=min 		//address for min loaded into r0
STR r4, [r0] 		//store r4 into that memory space
LDR r0,=max 		//address for max loaded into r0
STR r5, [r0] 		//store r5 into that memory space
LDR r0,=avg 		//address for min loaded into r0
STR r2, [r0] 		//store r2 into that memory space

//now I'll work on median using a bubble sort method
bubbleSort:

LDR r0, =grades 	//start at the beginning of the array
//r3 holds the length of the array from the main and gradeloop
SUB r1, r3, #1 		//r1=i=(r3)length-1
loop_i:
CMP r1, #0 			//compare i and 0
BLE calc_med 		//if i<=0 then branch to calc_med
MOV r2, #1 			//r2=j=1

loop_j:
CMP r2, r1 					//compare j and r1
BGT esc_j 					//if j>i then branch to esc_j
SUB r7, r2, #1 				//r7= j-1
LDR r4, [r0, r7, LSL #2] 	//array[j-1]
LDR r5, [r0, r2, LSL #2] 	//array[j]

CMP r4, r5 					//compare r4 and r5
ITT GT 						//if-then-then greater than block
STRGT r5, [r0, r7, LSL #2] 	//store array [j-1]
STRGT r4, [r0, r2, LSL #2] 	//store array[j]

ADD r2, r2, #1 				//iterations: j++
B loop_j

esc_j:
SUB r1,r1,#1 				//iterations: i--
B loop_i

calc_med: 					//concluded bubble sort now to calculate median
LDR r0, =grades 			//start array grades from beginning
MOV r2, #2 					//need to divide the Length
UDIV r1, r3, r2				//r1=Length/2

MOV r4, #1 					//needed for the AND operation
AND r4, r3, r4 				//r4= r3 AND r4
CMP r4, #1					//compare if r4 = 1
BNE even_med 				//otherwise continue to odd_med

odd_med:
ADD r0, r0, r1, LSL #2 		//finding the middle number
LDR r1, [r0] 				//loading that value into r1
B storeVal_med

even_med:
ADD r0, r0, r1, LSL #2 		//finding the middle number
SUB r0, r0, #4 				//moving down a word to the previous element of array
LDR r3, [r0] 				//loading r0 into r3
LDR r1, [r0, #4] 			//loading r0+4 into r1
ADD r1, r1, r3 				//adding the two middle numbers

MOV r2, #2 					//move 2 into r2
UDIV r1, r1, r2 			//dividing r1=r1/2

storeVal_med:
LDR r0, =med
STRB r1, [r0] 				//store median value into memory


endp: b endp 				//Forever Loop
