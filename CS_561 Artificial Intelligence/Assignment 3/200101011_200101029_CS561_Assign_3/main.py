#Import necessary modules.
import random #For random choice.
import os #For clearing screen and obtaining width of screen.
import time #For sleep
import platform #For finding platform of user.
plt = platform.system()
#Find width of screen to centre align.
width = os.get_terminal_size().columns
#==================================================================================================
#Define various functions to be used in our game.
#Function to clear out the terminal screen.
def screen_clear():
    if plt == 'Windows':
        _ = os.system('cls')
    else:
        _ = os.system('clear')
#==================================================================================================
#Function to print a message, center aligned.
def print_message(string):
	length = (width - len(string))//2
	print('\n\033[0;93m',end='')
	for k in range(length):
		print('*',end='')
	print(string,end='')
	for k in range(length):
		print('*',end='')
	print('\033[0m\n')
#==================================================================================================
#Function to print win/loss/draw message.
def print_end(string):
	print('\n\033[1;96m' + string.center(width) + '\033[0m')
#==================================================================================================
#Function to print symbol.
#Made this function because I used different colours for symbols. :-)
def print_symbol(symbol):
	if(symbol == 'X'):
		print('\033[1;96m' + symbol + '\033[0;92m' , end = '')
	elif(symbol == 'O'):
		print('\033[1;93m' + symbol + '\033[0;92m' , end = '')
	else:
		print('\033[1;97m' + symbol + '\033[0;92m' , end = '')
#==================================================================================================
#Function to print our board as a 3x3 matrix.
def print_grid(matrix):
	print('\033[0;92m' , end = '')
	print('\t\t\t _____ _____ _____ ')
	print('\t\t\t|     |     |     |')
	print('\t\t\t|  ' , end = ''), print_symbol(matrix[0][0]), print('  |  ' , end = ''), print_symbol(matrix[0][1]), print('  |  ' , end = ''), print_symbol(matrix[0][2]), print('  |')
	print('\t\t\t|_____|_____|_____|')
	print('\t\t\t|     |     |     |')
	print('\t\t\t|  ' , end = ''), print_symbol(matrix[1][0]), print('  |  ' , end = ''), print_symbol(matrix[1][1]), print('  |  ' , end = ''), print_symbol(matrix[1][2]), print('  |')
	print('\t\t\t|_____|_____|_____|')
	print('\t\t\t|     |     |     |')
	print('\t\t\t|  ' , end = ''), print_symbol(matrix[2][0]), print('  |  ' , end = ''), print_symbol(matrix[2][1]), print('  |  ' , end = ''), print_symbol(matrix[2][2]), print('  |')
	print('\t\t\t|_____|_____|_____|')
	print('\033[0m')
#==================================================================================================
#Function to print thinking...... :-)
def time_lapse():
	print('Thinking.',end='', flush=True) #Made flush true, otherwise prints all simultaneously.
	time.sleep(0.2)
	for j in range(4):
		print('.',end='',flush=True)
		time.sleep(0.2)
	print('.')
#==================================================================================================
#Function to check if any further move is availbale on our board.
def move_left(matrix):
	#Return TRUE if any of the 9 blocks is empty, i.e., have it's id instead of a symbol.
	for i in range(3):
		for j in range(3):
			if(matrix[i][j]!='X' and matrix[i][j]!='O'):
				return True
	#If no, return FALSE.
	return False
#==================================================================================================
#Make 3 x 3 board on which our game will be played.
grid = [['1','2','3'],['4','5','6'],['7','8','9']]
#Clear screen at start of python program.
screen_clear()
#Print welcome message.
print_message(" WELCOME TO TIC-TAC-TOE GAME ")
#Print that game is between user and computer; center aligned.
print('\033[0;93m' + 'Game:  PLAYER  v/s  COMPUTER'.center(width) + '\033[0m\n')
#Ask user to enter his/her symbol to be used in game.
user_symbol = input('Choose your symbol (X/O): ')
#If user selects some invalid symbol, print error message and again prompt user to enter symbol.
#Repeat till user doesn't enter valid one.
while(user_symbol not in ['X','O']):
	user_symbol = input('\033[0;91mERROR: Invalid input\033[0m\nChoose a valid symbol (X/O): ')
#Now, if user selects 'X', computer will be 'O' and vice-versa.
computer_symbol = ' '
if(user_symbol == 'O'):
	computer_symbol = 'X'
else:
	computer_symbol = 'O'
#Once symbol has been assigned, print them once.
print('\n\t\tPLAYER: ', end = ''), print_symbol(user_symbol), print('\033[0m\n')
print('\t\tCOMPUTER: ', end = ''), print_symbol(computer_symbol), print('\033[0m')
#Ask user for difficulty level; either Easy or Hard.
#Repeat till user doesn't enter valid one.
level = input('\nSelect difficulty level (E for Easy / H for Hard): ')
while(level not in ['E','H']):
	level = input('\033[0;91mERROR: Invalid input\033[0m\nChoose a valid difficulty level (E for Easy / H for Hard): ')
#Promt to press Enter to start the game.
input('\nPress ENTER to start the game')
#Clear screen and print initial grid with box id's.
#As game progress, box id's will be replaced by symbols.
screen_clear()
print('\n')
print('\n\t\tPLAYER: ', end = ''), print_symbol(user_symbol), print('\033[0m\n')
print('\t\tCOMPUTER: ', end = ''), print_symbol(computer_symbol), print('\033[0m\n')
#Print initial grid.
print_grid(grid)
#==================================================================================================
#Function to check if someone won or not.
def win_check(matrix):
	#Check all 8 possibilities of win, i.e., 3 rows, 3 columns and 2 diagonals.
	#If user has won, rerurn -10
	#I am returning -10 when user wins because in minimax algorithm, I will be using user as minimizer while computer as maximizer.
	if(((matrix[0][0] == matrix[0][1]) and (matrix[0][1] == matrix[0][2]) and (matrix[0][2] == user_symbol)) #Row 1
	or ((matrix[1][0] == matrix[1][1]) and (matrix[1][1] == matrix[1][2]) and (matrix[1][2] == user_symbol)) #Row 2
	or ((matrix[2][0] == matrix[2][1]) and (matrix[2][1] == matrix[2][2]) and (matrix[2][2] == user_symbol)) #Row 3
	or ((matrix[0][0] == matrix[1][0]) and (matrix[1][0] == matrix[2][0]) and (matrix[2][0] == user_symbol)) #Column 1
	or ((matrix[0][1] == matrix[1][1]) and (matrix[1][1] == matrix[2][1]) and (matrix[2][1] == user_symbol)) #Column 2
	or ((matrix[0][2] == matrix[1][2]) and (matrix[1][2] == matrix[2][2]) and (matrix[2][2] == user_symbol)) #Column 3
	or ((matrix[0][0] == matrix[1][1]) and (matrix[1][1] == matrix[2][2]) and (matrix[2][2] == user_symbol)) #Diagonal left-to-right
	or ((matrix[0][2] == matrix[1][1]) and (matrix[1][1] == matrix[2][0]) and (matrix[2][0] == user_symbol))): #Diagonal right-to-left
		return -10
	#If computer has won, return +10.
	elif(((matrix[0][0] == matrix[0][1]) and (matrix[0][1] == matrix[0][2]) and (matrix[0][2] == computer_symbol)) #Row 1
	or ((matrix[1][0] == matrix[1][1]) and (matrix[1][1] == matrix[1][2]) and (matrix[1][2] == computer_symbol)) #Row 2
	or ((matrix[2][0] == matrix[2][1]) and (matrix[2][1] == matrix[2][2]) and (matrix[2][2] == computer_symbol)) #Row 3
	or ((matrix[0][0] == matrix[1][0]) and (matrix[1][0] == matrix[2][0]) and (matrix[2][0] == computer_symbol)) #Column 1
	or ((matrix[0][1] == matrix[1][1]) and (matrix[1][1] == matrix[2][1]) and (matrix[2][1] == computer_symbol)) #Column 2
	or ((matrix[0][2] == matrix[1][2]) and (matrix[1][2] == matrix[2][2]) and (matrix[2][2] == computer_symbol)) #Column 3
	or ((matrix[0][0] == matrix[1][1]) and (matrix[1][1] == matrix[2][2]) and (matrix[2][2] == computer_symbol)) #Diagonal left-to-right
	or ((matrix[0][2] == matrix[1][1]) and (matrix[1][1] == matrix[2][0]) and (matrix[2][0] == computer_symbol))): #Diagonal right-to-left
		return 10
	#If no one has won, return 0.
	else:
		return 0
#==================================================================================================
#MINIMAX algorith function.
# I am using computer as maximizer while player as minimizer.
def minimax_algo(matrix,depth,is_computer):
	#Calculate score using win_check function.
	score = win_check(matrix)
	#If computer wins, return corresponding score.
	if(score==10):
		return (score-depth)
	#If user wins, return corresponding score.
	if(score==-10):
		return (score+depth)
	#If no further move is possible, i.e., game is drawn, rerturn 0.
	if(move_left(matrix)==False):
		return 0
	#If move is of user, make all possible moves and calculate best score using recursion.
	if( not is_computer):
		best = 100
		for i in range(3):
			for j in range(3):
				if(matrix[i][j]!='X' and matrix[i][j]!='O'):
					#Store box id, make move, calculate score, replace back box with id.
					temp = matrix[i][j]
					matrix[i][j] = user_symbol
					best = min(best , minimax_algo(matrix,depth+1,not is_computer)) #Player is minimizer.
					matrix[i][j] = temp
		return best
	#Else if computer's move, make all possible moves and calculate best score using recursion.
	else:
		best = -100
		for i in range(3):
			for j in range(3):
				if(matrix[i][j]!='X' and matrix[i][j]!='O'):
					#Store box id, make move, calculate score, replace back box with id.
					temp = matrix[i][j]
					matrix[i][j] = computer_symbol
					best = max(best , minimax_algo(matrix,depth+1,not is_computer)) #Computer is maximizer.
					matrix[i][j] = temp
		return best
#==================================================================================================
#Function that uses minimax function to find all possible best moves and return any one of them.
def best_choice(matrix):
	#A list to store score of every move.
	score = [-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000]
	#Now apply minimax, if a move is poosible and calculate the score for that move and replace it in list.
	for i in range(3):
		for j in range(3):
			if(matrix[i][j]!='X' and matrix[i][j]!='O'):
				#Store box id, make move, calculate score, replace back box with id.
				temp = matrix[i][j]
				matrix[i][j] = computer_symbol
				score[(3*i)+j] = minimax_algo(matrix,0,False) #False since next move is of user.
				matrix[i][j] = temp
	#Now find the maximum score using max function on list.
	maximum = max(score)
	#A list to store box id's for which score is maximum
	max_indices = []
	#For list of scores, if a score is equal to maximum, insert that box id into new list.
	for i in range(9):
		if(score[i] == maximum):
			max_indices.append(i+1)
	#After all box with maximum sore has been identified, return any random box id out of them.
	#Be sure to convert it into string as our main program take box id as a string and not an integer.
	return ((str)(random.choice(max_indices)))
#==================================================================================================
#Now the game begins!
#Declare a global variable that governs if game has been win by player or computer or ended in a draw.
win = False
#Select first turn using random function.
first_turn = random.choice([1,2])
#Declare a list consisting of box id's of available boxes. As a box is selected, it's id is removed from the list.
moves = ['1','2','3','4','5','6','7','8','9']
#Run a loop 9 times for taking player move and computer's move alternatively.
for i in range(1,10):
	#Check if user has been allocated first turn. If yes, then he will move at odd turns (1,3,5,7,9).
	#If no, then he will move at even turns (2,4,6,8).
	if(((first_turn == 1) and (i%2 == 1)) or ((first_turn == 2) and (i%2 == 0))):
		print('Your turn')
		#Take user input for box id.
		user_choice = input('Choose your square (1-9): ')
		#Apply validity check on input.
		#If invalid, print suitable error message and ask for new input.
		while(user_choice not in moves):
			try:
				val = int(user_choice)
				if(val<=9 and val>=1):
					user_choice = input('\033[0;91mERROR: This square is already filled\033[0m\nChoose valid square (1-9): ')
				else:
					user_choice = input('\033[0;91mERROR: Invalid input\033[0m\nChoose valid square (1-9): ')
			except ValueError:
				user_choice = input('\033[0;91mERROR: Invalid input\033[0m\nChoose valid square (1-9): ')
		#Once user inputs correct choice, remove that box id from available box id's list.
		moves.remove(user_choice)
		#Clear screen
		screen_clear()
		#Print the last move of user.
		print('\nYour last move: ' + user_choice)
		print('\n\t\tPLAYER: ', end = ''), print_symbol(user_symbol), print('\033[0m\n')
		print('\t\tCOMPUTER: ', end = ''), print_symbol(computer_symbol), print('\033[0m\n')
		#Now replace the box chosen by user with symbol of user in the original grid.
		user_choice = ((int)(user_choice))-1
		grid[(user_choice)//3][(user_choice)%3] = user_symbol
		#Print updated 3 x 3 board.
		print_grid(grid)
		#Check if after latest move, user won the game.
		if(win_check(grid) == -10):
			#If yes, print suitable message, make win as TRUE and break out from the loop.
			print_end('Congratulations! You won!')
			win = True
			break
	else:
		#Now if current turn is not of user, then it will be of computer.
		print('Computer\'s turn')
		#Calling function time_lapse.
		time_lapse()
		#If user selects EASY level, select computer's move randomly from available choices.
		if(level == 'E' or i == 1):
			computer_choice = random.choice(moves)
		#Else select computer's move using minimax algo.
		else:
			computer_choice = best_choice(grid)
		#Remove the box id selected for computer's move from list.
		moves.remove(computer_choice)
		#Clear screen
		screen_clear()
		#Print last move of computer.
		print('\nComputer\'s last move: ' + computer_choice)
		print('\n\t\tPLAYER: ', end = ''), print_symbol(user_symbol), print('\033[0m\n')
		print('\t\tCOMPUTER: ', end = ''), print_symbol(computer_symbol), print('\033[0m\n')
		#Replace the box chosen by computer with symbol of computer in the original grid.
		computer_choice = ((int)(computer_choice))-1
		grid[(computer_choice)//3][(computer_choice)%3] = computer_symbol
		#Print updated 3 x 3 board.
		print_grid(grid)
		#Check if after latest move, computer won the game.
		if(win_check(grid) == 10):
			#If yes, print suitable message, make win as TRUE and break out from the loop.
			print_end('Oops! You Lost! Better luck next time!')
			win = True
			break
#==================================================================================================
#If nobody wins the game, win will be FALSE, and hence print draw message.
if(not win):
	print_end('Match Drawn! Well Played!')
#Print Game Over message at end.
print_message(" GAME OVER ")
#End of python script.
#==================================================================================================