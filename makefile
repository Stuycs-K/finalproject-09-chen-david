
SHA.o: SHA.c SHA.h
	@gcc -c SHA.c

ENCODE: SHA.o SHA.h
	@gcc -o ENCODE SHA.o

encode: ENCODE
	@./ENCODE $(ARGS)
