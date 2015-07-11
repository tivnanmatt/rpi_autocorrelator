.section .init
.globl _start
_start:

@ set GPIO and Clock base locations

@ GPIO Base
ldr r12, =0x20200000

@ ...................................................................................
@ set GPIO inputs and outputs

@ GPIO 16 - OK LED  - output
mov r0, #1
lsl r0, #18

@GPIO 17 - signal - input

str r0, [r12, #4]

@GPIO 22 - transfer - output
mov r0, #1
lsl r0, #6

@GPIO 23 - rpi1 ready - input

@GPIO 24 - rpi2 ready - output 
mov r1, #1
lsl r1, #12
and r0, r0, r1

str r0, [r12, #8]

@ .................................................................................................. 

@  Blink OK LED
@ OK LED is on when pin 16 is low 
main:
	ldr r6, =1
	lsl r6, #23

	wait_for_rpi1:
		ldr r0, [r12, #52]
		and r0, r6
		cmp r0, #0
	beq wait_for_rpi1




ldr r6, =1
lsl r6,#16

mov r1, #20

blink:
str r6, [r12,#40]

ldr r0, =1000000
wait1:
	sub r0,#1
	cmp r0, #0
bne wait1

str r6 ,[r12,#28]

ldr r0, =1000000
wait2:
	sub r0,#1
	cmp r0, #0
bne wait2

sub r1, #1
cmp r1, #0

bne blink

b main
