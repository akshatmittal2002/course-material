# Bison
y.tab.c: A4_16.y 
	bison -dty A4_16.y

y.tab.h: A4_16.y
	bison -dty A4_16.y

y.tab.o: y.tab.c 
	cc -c y.tab.c

# Lexer 
lex.yy.c: A4_16.l y.tab.h
	flex A4_16.l

lex.yy.o: lex.yy.c 
	cc -c lex.yy.c 

# User C object code
A4_16.o: A4_16.c 
	cc -c A4_16.c

# Combine 3 object files
a.out: lex.yy.o A4_16.o y.tab.o
	cc lex.yy.o A4_16.o y.tab.o -lfl

# Run test
test: a.out A4_16.nc
	./a.out A4_16.nc > output.txt

# Clean
clean:
	rm -f y.tab.* lex.yy.* A4_16.o a.out