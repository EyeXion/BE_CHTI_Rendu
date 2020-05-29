	thumb
	area moncode, code, readwrite
	export calculModule
	import TabCos
	import TabSin

		
calculModule	proc
	;r0 : adresse de la table du signal
	;r1 : valeur de k
	push {lr}
	push {r4}
	push {r8}
	push {r0}
	; r2 adresse de la table
	ldr r2, =TabCos
	bl calcul
	mov r3, #0
    SMULL r2,r8,r0,r0
	pop {r0}
	ldr r2, =TabSin
	bl calcul
	mov r4, #0
    SMULL r4, r12, r0, r0
	add r0, r12, r8
	pop {r8}
	pop {r4}
	pop {pc}
	endp
		
calcul proc
	;r0 : adresse de la table du signal
	;r1 : valeur de k
	; r2 adresse de la table Cos ou Sin
	push {lr}
	bl	calculTrig
	pop {pc}
	endp
		
calculTrig proc 
	push {lr}
    ; r1 valeur de k
	; r2 adresse de la table Cos ou Sin
	; r3 : i
	; r12 : résultat
	ldr r3, =0x0
	ldr r12, =0x0
	bl debutBcl
	pop {pc}
	endp

debutBcl proc
	;r0 : adresse de la table du signal
	;r1 : valeur de k
	;r2 adresse de la table Cos ou Sin
	;r3 : valeur de i
	;r12 : resultat
	push {r4-r7}
boucle	mul r6, r1, r3 ; r6 : ik
    ; on ramène ik dans la plage [0;64-1]
	and	r6, r6, #63
	; on se décale jusqu'à l'indice désiré (arg angle)
    ldrsh r4, [r2, r6, LSL #1] ; r4 contient le sin(ik2pi/N)
	; on multiplie par l'échantillon
    ldrsh r5, [r0, r3, LSL #1]; r5 contient x(i)
    mla r7, r5, r4, r12 ; on multiplie et on ajoute le resultat aux precedants
	; r7 esr là car sinon ça fait une erreur donc registre auxlliaire
	mov r12, r7
	; on incremente le pas et on retourne au debut si i est inferieur à N
	add r3, #1
	cmp r3, #64
	bne boucle
	; la valeur de retour est en r12
	mov r0, r12; la valeur de retour est en r0
	pop {r4-r7}
	bx	lr
	endp	
	end
	