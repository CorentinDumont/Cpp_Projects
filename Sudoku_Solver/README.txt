### Sudoku solver: ####

This is an automatic solver for 9*9 sudoku. It uses a backtracking algorithm (makes hypothesis and go back when it led to a mistake).

#######################################

### How to use: ###

1 - Write the sudoku to solve in the code 'solver.cpp' at line 30-54 (the sudoku is hard-coded...)

2 - Open a console/terminal in the folder where the code 'solver.cpp' is saved

3 - Compile the code with:
	$ g++ solver.cpp

4 - Run the program with:
	$ ./a.out

or (for Windows)

3 - Compile the code with:
	$ g++ -0 solver.exe solver.cpp

4 - Run the program by double-clicking on the ‘solver.exe’ that has been created

#######################################

### Example of running of the program: ###

cs-lab-no-MacBook-Air-4:desktop corentin$ g++ solver.cpp
cs-lab-no-MacBook-Air-4:desktop corentin$ ./a.out
  |   |   || 6 | 7 |   ||   |   |   | 
-   -   -    -   -   -    -   -   -
  |   |   || 4 |   | 9 ||   | 2 | 8 | 
-   -   -    -   -   -    -   -   -
  | 2 |   ||   |   |   || 3 |   |   | 
-   -   -    -   -   -    -   -   -
-   -   -    -   -   -    -   -   -
  |   |   ||   |   |   || 5 |   | 6 | 
-   -   -    -   -   -    -   -   -
  |   | 5 || 7 |   | 4 || 9 |   |   | 
-   -   -    -   -   -    -   -   -
9 |   | 1 ||   |   |   ||   |   |   | 
-   -   -    -   -   -    -   -   -
-   -   -    -   -   -    -   -   -
  |   | 2 ||   |   |   ||   | 8 |   | 
-   -   -    -   -   -    -   -   -
8 | 5 |   || 9 |   | 6 ||   |   | 1 | 
-   -   -    -   -   -    -   -   -
  |   |   ||   | 4 | 5 ||   |   |   | 
-   -   -    -   -   -    -   -   -

3 | 8 | 9 || 6 | 7 | 2 || 1 | 5 | 4 | 
-   -   -    -   -   -    -   -   -
5 | 1 | 7 || 4 | 3 | 9 || 6 | 2 | 8 | 
-   -   -    -   -   -    -   -   -
4 | 2 | 6 || 1 | 5 | 8 || 3 | 9 | 7 | 
-   -   -    -   -   -    -   -   -
-   -   -    -   -   -    -   -   -
7 | 3 | 8 || 2 | 9 | 1 || 5 | 4 | 6 | 
-   -   -    -   -   -    -   -   -
2 | 6 | 5 || 7 | 8 | 4 || 9 | 1 | 3 | 
-   -   -    -   -   -    -   -   -
9 | 4 | 1 || 5 | 6 | 3 || 8 | 7 | 2 | 
-   -   -    -   -   -    -   -   -
-   -   -    -   -   -    -   -   -
6 | 9 | 2 || 3 | 1 | 7 || 4 | 8 | 5 | 
-   -   -    -   -   -    -   -   -
8 | 5 | 4 || 9 | 2 | 6 || 7 | 3 | 1 | 
-   -   -    -   -   -    -   -   -
1 | 7 | 3 || 8 | 4 | 5 || 2 | 6 | 9 | 
-   -   -    -   -   -    -   -   -

solved

#######################################

### To do: ###

- Write an interface for the user to write the sudoku he wants to solve
- Make some speed improvements, especially about the frequency of check of the sudoku