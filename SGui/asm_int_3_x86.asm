.586              ;Target processor.  Use instructions for Pentium class machines
.MODEL FLAT, C    ;Use the flat memory model. Use C calling conventions
.CODE             ;Indicates the start of a code segment.

sGuiAsmInt3 PROC  
	int 3
	ret 
sGuiAsmInt3 ENDP 
END 