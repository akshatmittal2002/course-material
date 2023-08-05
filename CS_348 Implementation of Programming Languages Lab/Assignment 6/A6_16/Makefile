nanoC: lex.yy.o A6_16.tab.o A6_16_translator.o 
	g++ lex.yy.o A6_16.tab.o A6_16_translator.o -lfl -o nanoC

A6_16_translator.o: A6_16_translator.h A6_16_translator.cpp
	g++ -c A6_16_translator.h
	g++ -c A6_16_translator.cpp

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

A6_16.tab.o: A6_16.tab.c
	g++ -c A6_16.tab.c

lex.yy.c: A6_16.l A6_16.tab.h A6_16_translator.h
	flex A6_16.l

A6_16.tab.c: A6_16.y
	bison -dt A6_16.y

A6_16.tab.h: A6_16.y
	bison -dt A6_16.y

libA6_16.a: A6_16.o
	ar -rcs libA6_16.a A6_16.o

A6_16.o: A6_16.c myl.h
	gcc -c A6_16.c

A6_16.c:
	touch A6_16.c

test: nanoC libA6_16.a
	@mkdir -p Output_files
	@mkdir -p Binary_files

	./nanoC 1 < Input_files/A6_16_test1.nc > Output_files/A6_16_quads1.out
	mv A6_16_1.s Output_files/A6_16_1.s
	gcc -c Output_files/A6_16_1.s -o Output_files/A6_16_1.o
	gcc Output_files/A6_16_1.o -o Binary_files/test1 -L. -lA6_16 -no-pie

	./nanoC 2 < Input_files/A6_16_test2.nc > Output_files/A6_16_quads2.out
	mv A6_16_2.s Output_files/A6_16_2.s
	gcc -c Output_files/A6_16_2.s -o Output_files/A6_16_2.o
	gcc Output_files/A6_16_2.o -o Binary_files/test2 -L. -lA6_16 -no-pie

	./nanoC 3 < Input_files/A6_16_test3.nc > Output_files/A6_16_quads3.out
	mv A6_16_3.s Output_files/A6_16_3.s
	gcc -c Output_files/A6_16_3.s -o Output_files/A6_16_3.o
	gcc Output_files/A6_16_3.o -o Binary_files/test3 -L. -lA6_16 -no-pie

	./nanoC 4 < Input_files/A6_16_test4.nc > Output_files/A6_16_quads4.out
	mv A6_16_4.s Output_files/A6_16_4.s
	gcc -c Output_files/A6_16_4.s -o Output_files/A6_16_4.o
	gcc Output_files/A6_16_4.o -o Binary_files/test4 -L. -lA6_16 -no-pie

	./nanoC 5 < Input_files/A6_16_test5.nc > Output_files/A6_16_quads5.out
	mv A6_16_5.s Output_files/A6_16_5.s
	gcc -c Output_files/A6_16_5.s -o Output_files/A6_16_5.o
	gcc Output_files/A6_16_5.o -o Binary_files/test5 -L. -lA6_16 -no-pie

clean:
	rm -f lex.yy.c *.tab.c *.tab.h *.output *.o *.s *.a *.out *.gch nanoC Output_files/* Binary_files/*
	rmdir Binary_files Output_files
