[org 0x7c00]



mov al, [0x8000]
int 0x10


jmp $

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0

; Magic number
dw 0xaa55
