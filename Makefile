Project_name = main
all: clean runfile
	@./$(Project_name)
runfile: ofile
	@g++ $(Project_name).o -o $(Project_name)
ofile: $(Project_name).cpp Words.h
	@g++ --std=c++17 -msse4 -O0 -c $(Project_name).cpp
clean:
	@rm -f $(Project_name) $(Project_name).o
install:
	@cp $(Project_name) /usr/local/bin/$(Project_name)
uninstall:
	@rm -f /usr/local/bin/$(Project_name)
push:
	@git push origin master
addall:
	@git add .
commit:
	@git commit -m "Automatic commit" -a
