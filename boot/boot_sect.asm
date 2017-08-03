[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print
call print_nl

call load_kernel

call switch_to_pm
jmp $

%include "boot_print.asm"
%include "boot_print_32bits.asm"
%include "boot_16to32.asm"
%include "boot_gdt.asm"
%include "boot_print_hex.asm"
%include "boot_disk.asm"


[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	call print_nl

	mov bx, KERNEL_OFFSET
	mov dh, 50  ; when kernel is larger, this number should increase
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret


[bits 32]
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm

	call KERNEL_OFFSET
	jmp $


BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Successfully landed in 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory.", 0


; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0

; Magic number
dw 0xaa55
