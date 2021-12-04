	.arch msp430g2553
	.p2align 1,0
	.text
	.extern buzzer_set_period
	.extern period		;global variable that will keep track of the current period
	.extern s_state	        ;global variable that will keep track of the current song state
	.extern buzzer_init
	.global song

jt:
	.word case0
	.word case1
	.word case2
	.word case3

song:
	call #buzzer_init
	cmp #5, &s_state
	jhs default

	mov &s_state, r12
	add r12, r12
	mov jt(r12), r0

case0:
	mov #3000, &period
	mov #1, &s_state
	jmp final
case1:
	mov #1400, &period
	mov #2, &s_state
	jmp final
case2:
	mov #1000, &period
	mov #3, &s_state
	jmp final
case3:
	mov #6000, &period
	mov #0, &s_state
	jmp final
default:
	mov #200, &period
	mov #0, &s_state
	
final:
	mov &period, r12
	call #buzzer_set_period
	pop r0
