Programming Assignment #3

Part A
  For this part of the assignment, a simple heuristic is used. In other words, a h(n) was used to get the best possible result from this. The heuristic h(n) function used was the manhattan distance for the master block from it's current position to the target position. 

Part B
  For this part, we used a proper a* search method with both h(n) and g(n). In this case, i have decided to stick with the heuristic function as used in the earlier part, and along with that a g(n), which represented the occurences of any element with a value other than 2 to have a cost associated with it. Example, if a block 2 is surrounded by empty blocks(block 0), then the g(n) would be zero, whereas if there were elements around it, there would be an increase of 1 per block surrounding the master block (block 2). The reason for using this function is because the more empty spaces we have around the master block, we are promoting the chance of finding empty spots for the master block to move. The more often the master block can stay in motion will improve performance and the liklihood of encountering a optimal solution. 
