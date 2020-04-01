# Downturn: CMSC 15200 Final Project
> _The game Downturn was created by a computer science instructor at a prestigious university in the midwestern United States. You may not have heard of it before; it has regrettably remained obscure, and licensing revenue has been profoundly disappointing thus far. In fact, its creator just hopes to be able to use an unsigned int to store the net revenue from the game someday._ – Professor Matthew Wachs

The final project for UChicago's Intro to Computer Science II course. The program can store the game board in two different ways: with a matrix (two-dimensional array) or a more compact bits representation.

Like Connect Four, players take alternating turns. In a turn, a given player can either drop a piece in one, not-fully-occupied, column; or make one rotation, 90 degrees in either direction.

The objective of the game is to get a number of pieces of your color in a row, either horizontally, vertically, or diagonally. Just like the game board can be different dimensions, the number of pieces in a row required to win is configurable.

The game is made interesting by the fact that the implications of turns and falls may not be obvious to a player, so their opponent may be able to put pieces into positions where they will fall into a line without their opponent realizing and being able to take countermeasures.

## Demonstration
This is a sample board with 5 rows and 4 columns, empty at the start of the game.
```
  0123

0 ....
1 ....
2 ....
3 ....
4 ....
```
Black drops a piece in column 0.
```
  0123

0 ....
1 ....
2 ....
3 ....
4 *...
```
White drops a piece in column 2.
```
  0123

0 ....
1 ....
2 ....
3 ....
4 *.o.
```
Black drops another piece in column 0.
```
  0123

0 ....
1 ....
2 ....
3 *...
4 *.o.
```
White drops a piece in column 0 as well.
```
  0123

0 ....
1 ....
2 o...
3 *...
4 *.o.
```
Black rotates the board CW.
```
  01234

0 .....
1 .....
2 *....
3 o*o..
```
etc. etc.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. Have fun!

### Run
1. Clone this repo into your folder of choice.
    ```
    $ git clone https://github.com/jackandthebean/downturn.git
    ```
2. Change directories.
    ```
    $ cd downturn/proj2
    ```
3. Compile the program.
    ```
    $ make
    ```
4. Run the program, specifying desired width, height, winning-run length, and game storing method (`-m` for matrix representation, `-b` for bits representation).
    ```
    $ ./play -w 4 -h 5 -r 4 -m
    ```

### Play
* Enter a column label to drop a piece into that column.
* Enter `<` to rotate the board counterclockwise, `>` to rotate the board clockwise.
* Game is over when one of the players has the requisite number of pieces in a row or the game is a draw and the board is full.

## Built With
* [Atom](https://atom.io/) – open-source text editor
* [Clang](https://clang.llvm.org/) – compiler front-end for the C language family
