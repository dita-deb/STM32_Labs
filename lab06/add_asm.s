.section .text
.align
.global add_asm


add_asm:
		ADD r0,r0,r1 //r0=9
		ADD r0,r0,r2 //r0=9+2
		ADD r0,r0,r2 //r0=11+2
		ADD r0,r0,r3 //r0=13+1
		ADD r0,r0,r3 //r0=14+1
		ADD r0,r0,r4 //r0=15+5
		bx lr		//return 20
