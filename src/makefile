make: 	main.o command_execution.o input_handling.o  	
	@gcc -Wall main.o command_execution.o input_handling.o -o shell
	@echo "Compilation successful"

main.o: main.c command_execution.h input_handling.h
	@gcc -Wall -c main.c

commandExecution.o: command_execution.c command_execution.h	
	@gcc -Wall -c command_execution.c
	
input_handling.o: input_handling.c input_handling.h
	@gcc -Wall -c input_handling.c	

clean: 
	@rm -f *.o shell
	@echo "Removed build files"

run:
	@./shell