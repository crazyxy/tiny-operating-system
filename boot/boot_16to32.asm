[bits 16]

; switch from 16bits real mode to 32bits protected mode
switch_to_pm:
	; disable interrupt
	cli 

	; initialize gdt
	lgdt [gdt_descriptor]
	
	; set the first bit of cr0
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	; far jump
	jmp CODE_SEG:init_pm

[bits 32]
init_pm:
	; update segment registers
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; update stack
	mov ebp, 0x90000
	mov esp, ebp
	
	; call a 32bits method
	call BEGIN_PM
