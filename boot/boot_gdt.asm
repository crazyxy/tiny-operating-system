; GDT

gdt_start:
	
; null entry with 8 bytes
gdt_null:
	dd 0x0
	dd 0x0

gdt_code:
	dw 0xffff	; limit
	dw 0x0		; base
	db 0x0		; base
	db 0x9a		; flag
	db 0xcf		; flag
	db 0x0		; base


gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 0x92
	db 0xcf
	db 0x0

gdt_end:


gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data-gdt_start
