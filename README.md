
# My own programming language and compiler for it.
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