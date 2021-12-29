.global gethid
gethid:
	li a7, 1
	ecall
	ret
.global fork
fork:
	li a7, 2
	ecall
	ret
.global exec
exec:
	li a7, 3
	ecall
	ret
.global exit
exit:
	li a7, 4
	ecall
	ret