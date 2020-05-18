Project_name = main
libs         = Words.h
CFlags       = --std=c++17 -O3
Dot_file_in  = ./resources/output.dot
Dot_file_png = ./resources/p_tree.png
git_branch   = b_translation


all: clean runfile
	@./$(Project_name)
runfile: ofile
	@g++ $(Project_name).o -o $(Project_name)
ofile: $(Project_name).cpp $(libs)
	@g++ $(CFlags) -c $(Project_name).cpp
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


