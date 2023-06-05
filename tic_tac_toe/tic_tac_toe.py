

"""
creates a matrix NxN and initializes all elements to 0
parameter: N size of matrix
return:  matrix
"""
def create_matrix(N):
    board = []
    for i in range(N):
        row = ["-"] * N
        board.append(row)
    return board
#........................................................
"""
print a matrix
parameter: matrix- The board of the game
return:  none
"""
def print_matrix(matrix):
    print("\033[0;33m" + "----"*N + "\033[0;0m")
    for row in matrix:
        print("\033[0;33m" + "|" + "\033[0;0m", end="")
        for cell in row:
            print("\033[0;32m" + " " + cell + " " + "\033[0;0m" + "\033[0;33m" + "|" + "\033[0;0m", end="")
        print("\n" + "\033[0;33m" + "----"*N + "\033[0;0m")
    print("")

#........................................................
"""
checks the winner in a tic-tac-toe game by checking the rows, columns, and diagonals
parameter: matrix-The board of the game
return: the character representing the winning player if there is a winner, or "C" if there is no winner
"""
def check_winner(matrix):
    #check rows x
    for x in matrix:
        if len(set(x)) == 1 and x[0] != "-":
            return x[0]
    #check columns y
    for y in range(N):
        if len(set([matrix[i][y] for i in range(N)])) == 1 and matrix[0][y] != "-":
            return matrix[0][y]
    # Check diagonals
    if len(set([matrix[i][i] for i in range(N)])) == 1 and matrix[0][0] != "-":
        return matrix[0][0]
    if len(set([matrix[i][N-i-1] for i in range(N)])) == 1 and matrix[0][N-1] != "-":
        return matrix[0][N-1]
    # No winner
    return "C"

#.............................................................
"""
Performs the computer's turn and puts an X or O in the first empty place
parameter: matrix- The board of the game, computer_sign- X or O
return: the updated matrix or original matrix- if it reaches the end of the function without finding empty place
"""

def computer_move(matrix, computer_sign, user_sign):
    # check if the computer can win and put there
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j] == "-":
                matrix[i][j] = computer_sign
                result = check_winner(matrix)
                if result == computer_sign:
                    return matrix
                else:
                    matrix[i][j] = "-"
    # check if the user can win and block him
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j] == "-":
                matrix[i][j] = user_sign
                result = check_winner(matrix)
                if result == user_sign:
                    matrix[i][j] = computer_sign
                    return matrix
                else:
                    matrix[i][j] = "-"

    # check if the middle empty and put there
    result = check_the_middle(matrix, computer_sign)
    if result == True:
        return matrix

    # check if the corners empty and put there
    result = check_the_corners(matrix, computer_sign)
    if result == True:
        return matrix

    # put in the next empty place
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j] == "-":
                matrix[i][j] = computer_sign
                return matrix

    return matrix

#...........................................................
"""
run game
parameter: matrix- The board of the game, user_sign- X or O, computer_sign- X or O
return: the sign of the winner or C if it is tie
"""
def run_game(matrix, user_sign, computer_sign):
    round = 0
    print_matrix(matrix)
    while round < 9:
        print("\033[32m IT IS YOUR TURN! \033[0m")
        print("Where would you like to place?")
        while 1:
            while True:
                try:
                    row = int(input("Enter a row number "))
                    if row >= 0 and row < N:
                        break
                    else:
                        print("\033[31m Wrong row. Please enter again \033[0m")
                except ValueError:
                    print("\033[31m Invalid input. Please enter a valid number. \033[0m")
            while True:
                try:
                    column = int(input("Enter a column number "))
                    if column >= 0 and column < N:
                        break
                    else:
                        print("\033[31m Wrong column. Please enter again \033[0m")
                except ValueError:
                    print("\033[31m Invalid input. Please enter a valid number. \033[0m")
            if matrix[row][column] == "-":
                matrix[row][column] = user_sign
                print_matrix(matrix)
                winner_sign = check_winner(matrix)
                if winner_sign != "C":
                    return winner_sign
                break
            else:
                print("The place is already taken, please enter again")
        print("IT IS MY TURN!")
        matrix = computer_move(matrix,computer_sign,user_sign)
        print_matrix(matrix)
        winner_sign = check_winner(matrix)
        if winner_sign != "C":
            return winner_sign
        round += 1
        if check_full(matrix) == True:
            return "C"
    winner_sign = check_winner(matrix)
    if winner_sign == "C":
        return "C"

#...........................................................
"""
checks if the tic-tac-toe board is full
parameter: matrix- The board of the game
return: True if the board is full False if not
"""
def check_full(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j] == "-":
                return False
    return True

#...........................................................
"""
choose either the 'X' or 'O' 
parameter: NONE
return: user sign and computer sign
"""
def choose_sign():
    while 1:
        user_sign = input("choose X or O: ")
        if user_sign.lower() == "x":
            user_sign = "X"
            computer_sign = "O"
            break
        if user_sign.lower() == "o":
            user_sign = "O"
            computer_sign = "X"
            break
        else:
            print("The character you entered is incorrect, please enter again")
    return user_sign, computer_sign
"""
check if the middle empty and put there  
parameter: matrix- The board of the game, computer_sign- X or O
return: update matrix if it was empty or the same matrix if not
"""
def check_the_middle(matrix,computer_sign):
    middle = N // 2
    if N % 2 != 0:
        if  matrix[middle][middle] == "-":
            matrix[middle][middle] = computer_sign
            return True
    else:
        if  matrix[middle -1][middle -1] == "-":
            matrix[middle -1][middle -1] = computer_sign
            return True
        if matrix[middle - 1][middle] == "-":
            matrix[middle - 1][middle] = computer_sign
            return True
        if  matrix[middle][middle -1] == "-":
            matrix[middle][middle -1] = computer_sign
            return True
        if  matrix[middle][middle] == "-":
            matrix[middle][middle] = computer_sign
            return True
    return False


"""
check if the corners empty and put there  
parameter: matrix- The board of the game, computer_sign- X or O
return: update matrix if it was empty or the same matrix if not
"""
def check_the_corners(matrix,computer_sign):
    if matrix[0][0] == "-":
        matrix[0][0] = computer_sign
        return True
    if matrix[0][N-1] == "-":
        matrix[0][N-1] = computer_sign
        return True
    if matrix[N-1][0] == "-":
        matrix[N-1][0] = computer_sign
        return True
    if matrix[N-1][N-1] == "-":
        matrix[N-1][N-1] = computer_sign
        return True
    return False


#main
N = 3
play_again = True
while play_again:
    matrix = create_matrix(N)
    user_sign, computer_sign = choose_sign()

    winner_sign = run_game(matrix, user_sign, computer_sign)
    if winner_sign == user_sign:
        print("\033[32m YOU ARE THE WINNER \033[0m")
    if winner_sign == computer_sign:
        print("\033[31m GAME OVER!\033[0m")
        print("\033[31m You lost \033[0m")
    if winner_sign == "C":
        print("\033[34m IT IS A TIE \033[0m")

    play_again_choice = input("Do you want to play again?(Y/N)")
    if play_again_choice.lower() != "y":
        play_again = False
