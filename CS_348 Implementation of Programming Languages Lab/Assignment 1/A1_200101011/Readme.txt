Name:       Akshat Mittal
Roll No:    200101011
Assign No:  1
=================================================

Set A: Question 5

Instruction to assemble and run:
    $ nasm -f elf64 A1A_200101011.asm  	(Assemble)
    $ gcc A1A_200101011.o -no-pie    	(Link)
    $ ./a.out                          	(Run)

Note:
    1. Negative numbers were not being compared properly, due to sign bit and hence, results are not correct. Avoid negative numbers.
    2. K must be between 1 and N only.
    3. In case of repeated numbers, all indices are printed for kth largest element.
=================================================

Set B: Question 6

Instruction to assemble and run:
    $ nasm -f elf64 A1B_200101011.asm  	(Assemble)
    $ gcc A1B_200101011.o -no-pie    	(Link)
    $ ./a.out                          	(Run)