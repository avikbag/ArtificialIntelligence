Docs for ab3433_minimaxPlayer.java

ab3433_minimaxPlayer is the name assigned to this object. 
a value needs to be associated with it, which corresponds
to the depth limit of how deep the recursion needs to go 
for the minimax function to pull out the best possible 
move.

public int minimax is a recursive function that goes to 
the depth level assigned by the constructor and pulls out
the value that corresponds to the best possible move and 
also updates what this move is in a OthelloMove object.

public OthelloMove getMove is the function primarily 
called upon by the object in main. This will return 
the best possible move available for the given player 
in the current state.

Player 0 wins when the score of the final state is a positive value
Player 1 wins when the score of the final state is a negative value