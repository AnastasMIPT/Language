
# My own programming language and compiler for it.

This repository contains a compiler for my own c-like programming language.
My language: 
* Turing-complete
* Supports loops and conditions
* Supports functions and recursion.
The [master](https://github.com/AnastasMIPT/Language/tree/master) branch contains the first version of my language interpreter, implemented using my stack [processor and assembler](https://github.com/AnastasMIPT/Kompil) I wrote. The current branch contains the latest version of my compiler which compiles a program written in my language into an executable elf file on the x86 architecture.

## The first stage: building a tree according to the program
Here is an example program on my language:

![factorial prgrams](resources/factorial.png)

How does it turn into tree? First, the program is tokenized. 
This happens using the Tocens () function in main.cpp.

![tocens](resources/Tocens.png)
This function analyzes the text of the program breaking it into nodes with a certain type. It also fills in the arrays Ids, IdsFunc, IdsParam, that are responsible for local variables, function parameters, and the functions themselves.
This is a tree of this program:

![factorial tree](resources/factorial_tree.png)

After tranclation by backend_x86.cpp:

![after transl](resources/after_translation1.png)

## ELF file and compilation to binary code.

![ELF](resources/ELF.png)

You can read about this [here](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)