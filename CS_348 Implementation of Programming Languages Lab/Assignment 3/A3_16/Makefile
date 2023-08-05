lex.yy.c:	A3_16.l A3_16.c
	flex A3_16.l A3_16.c

a.out:	lex.yy.c
	cc lex.yy.c -ll

test: a.out
	./a.out A3_16.nc > output.txt

clean:
	rm lex.yy.c a.out