# Example: a Connect Four engine

In this section I will show an example of two Connect Four engines:
* One uses 2D array data structure
* The second uses a Bitboard data structure

## The structures we need

Only two structures will be useful:
* `Move`: represent a move of the game
* `State`: represent a state of the game (player to play and board representation)

## The methods we need

To write a basic game engine, the methods we will need to write are:
* `void play(State * state, Move move)`: plays a move by directly modifying the state
* `EndGame isEnd(State state)`: to know if the game is finished or not and what is the result
* `vector<Move*> getMoves(State state)`: return the available moves for current player

And now let's code !

# First version: 2D vectors engine

# Second version: Bitboard engine
