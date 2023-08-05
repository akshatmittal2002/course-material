nanoC: lex.yy.o A5_16.tab.o A5_16_translator.o 
	g++ lex.yy.o A5_16.tab.o A5_16_translator.o -lfl -o nanoC

A5_16_translator.o: A5_16_translator.h A5_16_translator.cpp
	g++ -c A5_16_translator.h
	g++ -c A5_16_translator.cpp

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

A5_16.tab.o: A5_16.tab.c
	g++ -c A5_16.tab.c

lex.yy.c: A5_16.l A5_16.tab.h A5_16_translator.h
	flex A5_16.l

A5_16.tab.c: A5_16.y
	bison -dt A5_16.y

A5_16.tab.h: A5_16.y
	bison -dt A5_16.y

test: nanoC
	@mkdir -p Output_files

	./nanoC 1 < Input_files/A5_16_test1.nc > Output_files/A5_16_quads1.out

	./nanoC 2 < Input_files/A5_16_test2.nc > Output_files/A5_16_quads2.out

	./nanoC 3 < Input_files/A5_16_test3.nc > Output_files/A5_16_quads3.out

	./nanoC 4 < Input_files/A5_16_test4.nc > Output_files/A5_16_quads4.out

	./nanoC 5 < Input_files/A5_16_test5.nc > Output_files/A5_16_quads5.out

clean:
	rm -f lex.yy.c *.tab.c *.tab.h *.output *.o *.s *.a *.out *.gch nanoC Output_files/* Binary_files/*
	rmdir Output_files
