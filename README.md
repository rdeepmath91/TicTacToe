# TicTacToe
AI Project for Generalized Tic Tac Toe - Raymond Christopher

In this project, I am building an AI to play a generalized TicTacToe which will make every move within a reasonable amount of time. If you have any questions regarding the project, please check the FAQ below or otherwise you can also ask me at rdeepmath91 at gmail.com with the tag [AI - TicTacToe] on the Subject. Thanks!

[CHANGELOG] <br/>
v1.2 <br/>
1. [MAJOR] Optimize the MaxMin strategy with Alpha-Beta pruning. The code now runs 20-30x faster! <br/>
2. [MAJOR] Create a variable WIN_SEQ representing the number of consecutive marks to win the game. Previously, WIN_SEQ is fithe smaller number between the # of rows and columns. Now human player can choose to set this value before starting a non-default game. (The default game would be 3x3 board with WIN_SEQ = 3) <br/>
3. Migrate the update and update_lines to Board_Checker class <br/>
4. Reorganize minor parts of the code and add description to some classes and methods <br/>

v1.1 <br/>
1. Create Board_Checker object as a private object for Board that enhances/allows the following operations: <br/>
	a. Check and update the number of winnable lines (rows, columns, both diagonals) <br/>
	b. Check whether the current board is a draw (check_draw) <br/>
2. Heuristic function <br/>
	a. Add another heuristic function (heu2) and a combined heuristic (final_heu) which will be used in the MinMax <br/>
	b. Playtest varieties of AI Players (by altering final_heu) playing against each other <br/>
3. Print the move logs to "moves.txt" 

v1.0 <br/>
Upload the first prototype with the first heuristic function (heu1) and MinMax. <br/>

[INSTRUCTIONS] <br/>
Simply copy all the files into one folder, and you can compile using either your favorite Editor (i.e. Sublime Text) or IDE. The following web should guide you step-by-step just in case http://stephencoakley.com/2015/01/21/guide-setting-up-a-simple-c-development-environment-on-windows

[FAQ] <br/>
Q: What is a generalized TicTacToe? <br />
A: Given a MxN board, let k = min(M,N). Two players alternatively put X and O mark until one of them manages to a consecutive sequence of k marks either vertically, horizontally, or diagonally. If none did so until the board filled up, it's a draw. <br /> 

Q: What is a 'default game'? <br />
A: A default game is a 3x3 board where the player who puts 3 consecutive marks horizontally, vertically or diagonally wins. <br/>

