[extern isr_handler]
[extern irq_handler]

isr_common_stub:
	; 1. Save CPU state
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler

	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	sti
	iret

irq_common_stub:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call irq_handler

	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	popa
	add esp, 8
	sti
	iret


global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

isr0:
	cli
	push byte 0
	push byte 0
	jmp isr_common_stub

isr1:
	cli
	push byte 0
	push byte 1
	jmp isr_common_stub

isr2:
	cli
	push byte 0
	push byte 2
	jmp isr_common_stub

isr3:
	cli
	push byte 0
	push byte 3
	jmp isr_common_stub

isr4:
	cli
	push byte 0
	push byte 4
	jmp isr_common_stub

isr5:
	cli
	push byte 0
	push byte 5
	jmp isr_common_stub

isr6:
	cli
	push byte 0
	push byte 6
	jmp isr_common_stub

isr7:
	cli
	push byte 0
	push byte 7
	jmp isr_common_stub

isr8:
	cli
	push byte 0
	push byte 8
	jmp isr_common_stub

isr9:
	cli
	push byte 0
	push byte 9
	jmp isr_common_stub

isr10:
	cli
	push byte 0
	push byte 10
	jmp isr_common_stub

isr11:
	cli
	push byte 0
	push byte 11
	jmp isr_common_stub

isr12:
	cli
	push byte 0
	push byte 12
	jmp isr_common_stub

isr13:
	cli
	push byte 0
	push byte 13
	jmp isr_common_stub

isr14:
	cli
	push byte 0
	push byte 14
	jmp isr_common_stub

isr15:
	cli
	push byte 0
	push byte 15
	jmp isr_common_stub

isr16:
	cli
	push byte 0
	push byte 16
	jmp isr_common_stub

isr17:
	cli
	push byte 0
	push byte 17
	jmp isr_common_stub

isr18:
	cli
	push byte 0
	push byte 18
	jmp isr_common_stub

isr19:
	cli
	push byte 0
	push byte 19
	jmp isr_common_stub

isr20:
	cli
	push byte 0
	push byte 20
	jmp isr_common_stub

isr21:
	cli
	push byte 0
	push byte 21
	jmp isr_common_stub

isr22:
	cli
	push byte 0
	push byte 22
	jmp isr_common_stub

isr23:
	cli
	push byte 0
	push byte 23
	jmp isr_common_stub

isr24:
	cli
	push byte 0
	push byte 24
	jmp isr_common_stub

isr25:
	cli
	push byte 0
	push byte 25
	jmp isr_common_stub

isr26:
	cli
	push byte 0
	push byte 26
	jmp isr_common_stub

isr27:
	cli
	push byte 0
	push byte 27
	jmp isr_common_stub

isr28:
	cli
	push byte 0
	push byte 28
	jmp isr_common_stub

isr29:
	cli
	push byte 0
	push byte 29
	jmp isr_common_stub

isr30:
	cli
	push byte 0
	push byte 30
	jmp isr_common_stub

isr31:
	cli
	push byte 0
	push byte 31
	jmp isr_common_stub


%macro IRQ 2
	global irq%1
	irq%1:
		cli
		push byte %1 
		push byte %2
		jmp irq_common_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

