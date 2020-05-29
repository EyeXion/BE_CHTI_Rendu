
TIM3_CCR3	equ	0x4000043C	; adresse registre PWM
	thumb
	area moncode, code, readwrite
	export timer_callback
	import SonEnCours ; Variable qui permet de sortir du while de jouerSon pour sortir de la fonction
	import etat
E_POS	equ	0
E_TAI	equ	4
E_SON	equ	8
E_RES	equ	12
E_PER	equ	16
deca	equ 32768

	 
timer_callback	proc
	push {lr}
	ldr r1, =etat ; structure etat déclarée en C
	
	ldr r2, [r1, #E_POS] ;r2 contient la pos actuelle
	ldr r0, [r1, #E_TAI] ; r0 contient la taille du son
	cmp r2, r0 ; on compare la taille et la pos actuelle
	beq silence ; on fait rien si on depasse la taille
	
	ldr r1, [r1, #E_SON] ; on charge tableau son
	ldrsh r3, [r1,r2, LSL #1]
	
	; on modifie la valeur (offset + echelle)
	add r3, #deca
	ldr r1, =etat ; structure etat déclarée en C
	ldr r12, [r1, #E_RES]
	mul r3,r12 ; 
	lsr r3,#16 ; mulplication pleine échelle puis division valeur max (règle de trois)
	
	ldr r12, =TIM3_CCR3
	str r3, [r12] ; on strore la valeur dans le registre du PWM
	add r2, #1; ; on déclale la pos de 1
	ldr r1, =etat ; structure etat déclarée en C
	str r2,[r1, #E_POS]
	b fin
	
silence
	mov r0, #0
	ldr r12, =TIM3_CCR3
	str r0, [r12]
	ldr r0, =SonEnCours
	mov r1, #0
	str r1, [r0]
	
	
fin
	pop {pc}
	endp
	end 
			