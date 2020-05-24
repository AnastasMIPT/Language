
NameOfFile = experement
NasmFlags = -f elf64
LinkFlags = -s -o
RemFlags = -r -f

all: cleaning comfile

cleaning:
	@rm $(RemFlags) $(NameOfFile).com *.o

comfile: ofile
	@ld $(LinkFlags) $(NameOfFile).com $(NameOfFile).o
	@./$(NameOfFile).com
ofile:
	@nasm $(NasmFlags) $(NameOfFile).asm

edb:
	@edb --run $(NameOfFile).com
	@clear
cedb: all edb
	@clear
	
