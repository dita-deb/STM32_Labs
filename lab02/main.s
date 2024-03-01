/**
  *****************************************************************************
  *  Math (Basic)
  *
  *      This program performs a basic mathematical operation using the ARM
  *      registers as variable holders.
  *
  *****************************************************************************
  */

.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.section .text
.align
.global main



/**
  *============================================================================
  *  main()
  *      @param   None
  *      @return  None
  *
  *      @brief
  *         -Compute the required equation and hold it in an infinite loop when done.
  *============================================================================
  */
  
main:

	//-- initialize variables -------------------------------------------------

	mov   r1, #92	 //r1=first two digits
	mov   r2, #21	 //r2=next two digits
	mov   r3, #15	 //r3=last two digits
	mov   r0, #0     //r0 = 0 ; initialized

	//-- evaluate equation -----------------------------------------------------

	mov   r4, #10000 	//r4=place value of r1
	mul   r1, r1, r4    // r1 = (r1 * r4) ; r1 = (92 * 10000)

	mov r4, #100		//r4= place value of r2
	mul   r2, r2, r4 	// r2 = (r2 * r4) ; r2 = (21 * 100)

	add r0,r1,r2 		//r0 = r1+r2 ; r0 = (920000+2100)
	add r0,r0, r3 		//r0 = r0+r3 ; r0 = (922100 + 15)

forever:
	b     forever
