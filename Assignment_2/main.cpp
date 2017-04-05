#include "puzzle.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <queue>
#include <stack>
#include <map>
#include <tuple>
#include <ctime>
using namespace std;

bool check_exists(vector<Puzzle> p, Puzzle c)
{
  for (int i = 0; i < p.size(); i++)
  {
    if (c.compare(p[i]) == true)
      return true;
  }
  return false;
}
map<char, string> conv;

void bfs_path(Puzzle p)
{
  queue<vector<Puzzle> > tracker;
  vector<Puzzle> path;
  vector<Puzzle> temp_path;
  vector<Puzzle> visited;
  
  vector<int> elements;
  
  queue<vector<int> > tracker_elements;
  vector<int> path_elements;
  vector<int> temp_path_elements;
  
  vector<char> moves;
  
  queue<vector<char> > tracker_moves;
  vector<char> path_moves;
  vector<char> temp_path_moves;
  
  Puzzle vertex;
  Puzzle temp;
  temp_path.push_back(p);
  tracker.push(temp_path);
  temp_path.clear();
  tracker_moves.push(vector<char>());
  tracker_elements.push(vector<int>());

  while(tracker.empty() == false)
  {

    path = tracker.front();
    tracker.pop();
    vertex = path.back();
      
    path_moves = tracker_moves.front();
    tracker_moves.pop();
      
    path_elements = tracker_elements.front();
    tracker_elements.pop();

    
    elements = vertex.elementList();

    if (vertex.checkStateCompletion() == true)
    {
      cout << "---------------------------------------" << endl;
      cout << "---------- Solved using bfs! ----------" << endl;
      cout << "---------------------------------------" << endl;
      vertex.printState();
      cout << "Path to target : " << endl;
      for (int k = 0; k < path_moves.size(); k++)
        cout << path_elements[k] << ", " << conv[path_moves[k]] << endl;
      break;
    }
    else if (check_exists(visited, vertex) == false)
    {
      elements = vertex.elementList();
      for (int i =0; i < elements.size(); i++)
      {
        moves = vertex.moveList(elements[i]);
        for (int j=0; j < moves.size(); j++)
        {
          temp = vertex.stateClone();
          temp.applyMove(elements[i], moves[j]);
          temp_path = path;
          temp_path.push_back(temp);
          tracker.push(temp_path);
          
          temp_path_moves = path_moves;
          temp_path_moves.push_back(moves[j]);
          tracker_moves.push(temp_path_moves);
          
          temp_path_elements = path_elements;
          temp_path_elements.push_back(elements[i]);
          tracker_elements.push(temp_path_elements);
          
        }
      }
      visited.push_back(vertex);
    }
  }
}

vector<Puzzle> visited;
vector<int> elements_stack;
vector<char> moves_stack;
bool complete = false;
void dfs_path(Puzzle src)
{
  visited.push_back(src);
  Puzzle vertex = src.stateClone();
  vector<int> elements = vertex.elementList();
  vector<char> moves;
  Puzzle temp;
  if (src.checkStateCompletion() == true)
  {
    cout << "---------------------------------------" << endl;
    cout << "---------- Solved using dfs! ----------" << endl;
    cout << "---------------------------------------" << endl;

    src.printState();
    cout << "Path to solution from initial state" << endl;
    for(int k = 0; k < elements_stack.size(); k++)
    {
      cout << elements_stack[k] << ", " << conv[moves_stack[k]] << endl;
    }
    complete = true;
  }
  else{
    for (int i =0; i < elements.size(); i++)
    {
      moves = vertex.moveList(elements[i]);
      for (int j=0; j < moves.size(); j++)
      {
        if (complete == true)
        {
          break;
        }
        //cout << i << j << elements[i] << moves[j]<< endl;
        temp = vertex.stateClone();
        temp.applyMove(elements[i], moves[j]);
        if (check_exists(visited, temp) == false)
        {
          elements_stack.push_back(elements[i]);
          moves_stack.push_back(moves[j]);
          dfs_path(temp);
        }
      }
    }
    elements_stack.pop_back();
    moves_stack.pop_back();
  }
}
map<int, tuple<int, char>> trace;
void dls(Puzzle src, int depth, vector<Puzzle> &visited_list)
{
  visited_list.push_back(src);
  Puzzle vertex = src.stateClone();
  vector<int> elements = vertex.elementList();
  vector<char> moves;
  Puzzle temp;
  if (src.checkStateCompletion() == true)
  {
    cout << "---------------------------------------" << endl;
    cout << "-Solved using iterative deepening dfs!-" << endl;
    cout << "---------------------------------------" << endl;
      vertex.printState();
      cout << "Path to target : " << endl;
    for(int k = trace.size(); k >depth; k--)
    {
      cout << get<0>(trace[k]) << ", " << conv[get<1>(trace[k])] << endl;
    }
    complete = true;
  }
  else if (depth > 0){
    for (int i =0; i < elements.size(); i++)
    {
      moves = vertex.moveList(elements[i]);
      for (int j=0; j < moves.size(); j++)
      {
        if (complete == true)
        {
          break;
        }
        temp = vertex.stateClone();
        //temp.printState();
        temp.applyMove(elements[i], moves[j]);
        if (check_exists(visited_list, temp) == false)
        { 
          trace[depth] = make_tuple(elements[i], moves[j]);
          dls(temp, depth-1, visited_list);
        }
      }
    }
  }
}
void IDDFS(Puzzle p)
{
  complete = false;
  vector<Puzzle> visited_list;
  for(int d =1; d < 50; d++)
  {
    dls(p, d, visited_list);
    if (complete == true)
    {
      cout << "done" << endl;
      break;
    }
    visited_list.clear();
  }
}


int main()
{
  conv['u'] = "UP";
  conv['d'] = "DOWN";
  conv['l'] = "LEFT";
  conv['r'] = "RIGHT";
  clock_t begin, end;
  double res;

  ifstream file1("SBP-level0.txt");
  Puzzle pz = file1;
  cout << "---------------------------------------" << endl;
  cout << "------------- Initial State -----------" << endl;
  cout << "---------------------------------------" << endl;
  pz.printState();
  begin = clock();
  bfs_path(pz);
  end = clock();
  res = double(end-begin)/CLOCKS_PER_SEC;
  cout << "\nTotal time taken for reaching solution : " << res << " seconds" << endl;
  
  begin = clock();
  dfs_path(pz);
  end = clock();
  res = double(end-begin)/CLOCKS_PER_SEC;
  cout << "\nTotal time taken for reaching solution : " << res << " seconds" << endl;
  
  begin = clock();
  IDDFS(pz);
  end = clock();
  res = double(end-begin)/CLOCKS_PER_SEC;
  cout << "\nTotal time taken for reaching solution : " << res << " seconds" << endl;
  
  return 0;
}
