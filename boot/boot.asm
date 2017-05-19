[org 0x7c00]

mov bx, HELLO
call print

call print_nl

mov bx, GOODBYE
call print

call print_nl

mov dx, 0x12fe
call print_hex


jmp $


%include "boot_print.asm"
%include "boot_print_hex.asm"

HELLO:
	db 'Hello, World', 0

GOODBYE:
	db 'Goodbye', 0

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0

; Magic number
dw 0xaa55
