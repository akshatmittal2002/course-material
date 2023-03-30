Name			: Akshat Mittal
Roll No.		: 200101011
Assignment No.		: 4
Operating System	: LINUX
===================================================================================================
Files/Folders present inside zip folder:

	1. Task 1:
		i.  Assign04_Q1.py
	
	2. Task 2:
		i.  Document 1:
			a. Assign04_Q2_1.tex
			b. Assign04_Q2_1.aux
			c. Assign04_Q2_1.dvi
			d. Assign04_Q2_1.log
			e. Assign04_Q2_1.pdf
		
		ii.  Document 2:
			a. Assign04_Q2_2.tex
			b. Assign04_Q2_2.aux
			c. Assign04_Q2_2.dvi
			d. Assign04_Q2_2.log
			e. Assign04_Q2_2.pdf
	
	3. Readme.txt

===================================================================================================
For first task, run this command to play the game:
		
	python3 Assign04_Q1.py

Upon execution of this command, game will begin.

Process of the game:
	1. First of all, user will be asked to select his symbol; either X or O.
	2. Then user will be asked to select difficulty level; either E (for EASY) or H (for HARD).
	2. Once ready, press enter to start the game.
	3. First turn will be decided randomly and then moves will be alternate.
	4. 3x3 game board will be displayed, each box having a unique id. As game progresses, box id's will be replaced by symbols.
	5. In computer's turn, wait till computer select it's move.
	6. In EASY level, computer's move is just a random selection from all the availbale moves while in HARD level, computer uses MINIMAX algorithm to find best possible move.
	7. In user's turn, enter box id for the block you want to move. If invalid id is chosen, error message will be displayed.
	8. Victory/Loss/Draw message will be printed as soon as game ends.

===================================================================================================
For second task, first install basic LaTeX compiler using this command: (If already installed, ignore it)

	sudo apt install texlive-latex-base

Once LaTeX compiler has bee installed successfully, use this command to covert .tex into .dvi:

	latex Assign04_Q2_1.tex
	
	latex Assign04_Q2_2.tex

Now convert the generated .dvi files into .pdf using:

	dvipdf Assign04_Q2_1.dvi
	
	dvipdf Assign04_Q2_2.dvi

Now both LaTeX document are ready to be viewed.
===================================================================================================
