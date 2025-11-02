global get_stack_top
get_stack_top:
	MOV eax, [esp + 4]
	RET