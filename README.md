# TicTacToe
AI Project for Generalized Tic Tac Toe

In this project, I am building an AI to play a generalized TicTacToe which will makes every move within a reasonable amount of time. If you have any questions regarding the project, please check the FAQ below. If it doesn't answer your questions, please mail to rdeepmath91@gmail.com with the tag [AI - TicTacToe] on the Subject. Thanks!

[UPDATES] <br/>
v1.1 <br/>
1. Create Board_Checker object as a private object for Board that enhances/allows the following operations: <br/>
	a. Check and update the number of winnable lines (rows, columns, both diagonals) <br/>
	b. Check whether the current board is a draw (check_draw) <br/>
2. Heuristic function <br/>
	a. Add another heuristic function (heu2) and a combined heuristic (final_heu) which will be used in the MinMax <br/>
	b. Playtest varieties of AI Players (by altering final_heu) playing against each other <br/>
3. Output the move logs to "moves.txt" 

v1.0 <br/>
Upload the first prototype with the first heuristic function (heu1) and MinMax. <br/>

[INSTRUCTIONS] <br/>
Simply put all the files into one folder, and you can compile using either your favorite Editor (i.e. Sublime Text) or IDE. The following web should guide you step-by-step just in case http://stephencoakley.com/2015/01/21/guide-setting-up-a-simple-c-development-environment-on-windows

[FAQ] <br/>
Q: What is a generalized TicTacToe? <br />
A: Given a MxN board, let k = min(M,N). Two players alternatively put X and O mark until one of them manages to a consecutive sequence of k marks either vertically, horizontally, or diagonally. If none did so until the board filled up, it's a draw. <br /> 

Q: What is a 'default game'? <br />
A: A default game is a 3x3 board. You can choose your own board size by typing 'n' at the corresponding prompt.

