Project_name = backend_x86
libs         = Words.h
CFlags       = --std=c++17 -O3
Warnings     = -Werror -fmax-errors=1 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-result -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array -flto-odr-type-merging -fno-omit-frame-pointer -fPIE
Dot_file_in  = ./resources/output.dot
Dot_file_png = ./resources/p_tree.png
git_branch   = b_translation


all: clean runfile
	@./$(Project_name)
runfile: ofile
	@g++ $(Project_name).o -o $(Project_name)
ofile: $(Project_name).cpp $(libs)
	@g++ $(CFlags) $(Warnings) -c $(Project_name).cpp
clean:
	@rm -f $(Project_name) $(Project_name).o
install:
	@cp $(Project_name) /usr/local/bin/$(Project_name)
uninstall:
	@rm -f /usr/local/bin/$(Project_name)
push:
	@git push origin $(git_branch)
addall:
	@git add .
commit:
	@git commit -m "Automatic commit" -a
dot: $(Dot_file_in)
	@rm -f $(Dot_file_png)
	@dot -Tpng $(Dot_file_in) -o $(Dot_file_png)


