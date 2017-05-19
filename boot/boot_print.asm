; Function for printing string in bx
print:
	pusha

start:
	mov al, [bx]
	cmp al, 0
	je done

	mov ah, 0x0e
	int 0x10

	add bx, 1
	jmp start

done:
	popa
	ret


; Function for printing a new line
; \n contains two characters:
; 0x0a is newline char
; 0x0d is carriage return
print_nl:
	pusha

	mov ah, 0x0e
	mov al, 0x0a
	int 0x10
	mov al, 0x0d
	int 0x10

	popa
	ret
