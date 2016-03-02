# TicTacToe
AI Project for Generalized Tic Tac Toe

In this project, I am building an AI to be able to solve generalized Tic Tac Toe within a reasonable amount of time. If you have questions about the project, please check the FAQ below. If you have any comments, please mail rdeepmath91@gmail.com

[INSTRUCTIONS]
Copy

[UPDATES]
v1.1
1. Create Board_Checker object as a private object for Board that enhances/allows the following operations:
	a. Check and update the number of winnable lines (rows, columns, both diagonals)
	b. Check whether the current board is a draw (check_draw)
2. Add two heuristic functions and test its variations with AI players

v1.0
Uploaded the first prototype with the first heuristic function (heu1)


[FAQ]
Q: What is generalized Tic Tac Toe?
A: Given a MxN board, let k = min(M,N). Two players alternatively put X and O mark until one of them manages to a consecutive sequence of k marks either vertically, horizontally, or diagonally. If none did so until the board filled up, it's a draw.

Q: What is a 'default game'?
A: A default game is a 3x3 board. You can choose your own board size by typing 'n' at the corresponding prompt.

