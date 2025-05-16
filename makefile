
SHA.o: SHA.c SHA.h
	@gcc -c SHA.c -lm

ENCODE: SHA.o SHA.h
	@gcc -o ENCODE SHA.o -lm

encode: ENCODE
	@./ENCODE $(ARGS)
