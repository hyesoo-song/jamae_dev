bank: bank.o
	gcc -o bank bank.o
bank.o: bank.c account.h
	gcc -c bank.c 
