compile: file12.o main.o
	@gcc -o program file12.o main.o
	
main.o: main.c file12.h
	@gcc -c main.c
	
file12.o: file12.c file12.h
	@gcc -c file12.c
	
run:
	@./program $(ARGS)
	
clean:
	rm *.o
	rm program
	rm output.txt

