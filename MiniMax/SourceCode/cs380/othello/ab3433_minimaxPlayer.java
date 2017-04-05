/*
 * Author: Avik Bag
 * Class : CS 380
 * Term  : Spring 2016
 * Prof. : Marcello Balduccini
 * 
 * Date Created: 18th May 2016
 */

// Package used
package cs380.othello;

import java.util.*;

public class ab3433_minimaxPlayer extends OthelloPlayer
{
  int depth_limit;
  public ab3433_minimaxPlayer(int limit)
  {
    depth_limit = limit;
  }

  OthelloMove finalMove = new OthelloMove(0, 0, 0);
  public int minimax(OthelloState state, int depth)
  {
    int max, min;
    int index;
    List<OthelloMove> available_moves = state.generateMoves();
    List<Integer> scores = new LinkedList<Integer>();
    List<OthelloMove> moves = new LinkedList<OthelloMove>();
    OthelloState temp = new OthelloState(8);
    

    // Finding the score associated to every end state 
    // after applying every possible move available
    if (available_moves.size() == 0 || depth >= depth_limit)
    {
      return state.score();
    }
    // Keep track of depth reached
    depth++;
    for(int i = 0; i < available_moves.size(); i++)
    {
      temp = state.applyMoveCloning(available_moves.get(i));
      scores.add(minimax(temp, depth));
      moves.add(available_moves.get(i));
    }
    // Now figuring out whether to use min or max
    // Player 0 -> max
    // Player 1 -> min
    if (state.nextPlayerToMove == 0) // This means it's currently Player 1
    {
      max = Collections.max(scores);
      index = scores.indexOf(max);
      finalMove = moves.get(index);
      return scores.get(index);
    }
    else if (state.nextPlayerToMove == 1)
    {
      min = Collections.min(scores);
      index = scores.indexOf(min);
      finalMove = moves.get(index);
      return scores.get(index);
    }
    return 0;
  }
  public OthelloMove getMove(OthelloState state)
  {
    int res = minimax(state, 0);
    return finalMove;
  }
}
