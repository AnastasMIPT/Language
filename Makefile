EXECUTABLE   = backend_elf
second       = backend_x86
LIBS         = Words.h Func_s.h Func_b.h cache_list.h hash_table.h
SOURCEFILES  = backend_elf.cpp Commands.cpp ELF.cpp 
OBJFILES     = $(SOURCEFILES:.cpp=.o)
CFlags       = --std=c++17 -msse4 -O3
Warnings     =  -fmax-errors=10 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-result -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array -flto-odr-type-merging -fno-omit-frame-pointer -fPIE
NoWarnings   = -Wno-effc++

Dot_file_in  = ./resources/output.dot
Dot_file_png = ./resources/p_tree.png
git_branch   = b_translation


all: $(SOURCEFILES) $(LIBS) $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	@g++ $(OBJFILES) -o $@

%.o: %.cpp
	g++ $(CFlags) $(Warnings) $(NoWarnings) -c $< -o $@


clean:
	@rm -f *.o
install:
	@cp $(EXECUTABLE) /usr/local/bin/$(EXECUTABLE)
uninstall:
	@rm -f /usr/local/bin/$(EXECUTABLE)
push:
	@git push origin $(git_branch)
addall:
	@git add .
commit:
	@git commit -m "Automatic commit" -a
dot: $(Dot_file_in)
	@rm -f $(Dot_file_png)
	@dot -Tpng $(Dot_file_in) -o $(Dot_file_png)


