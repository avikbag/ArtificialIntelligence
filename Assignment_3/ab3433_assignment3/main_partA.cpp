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

vector <tuple<Puzzle, int> > visited;
vector <tuple<Puzzle, int> > unexpanded;
vector <tuple<Puzzle, Puzzle, tuple<int, char> > > path; // Child -> Parent -> tuple of dir and element
map<char, string> conv;

bool check_exists(vector< tuple<Puzzle, int> > p, Puzzle c)
{
  for (int i = 0; i < p.size(); i++)
  {
    if (c.compare(get<0>(p[i])) == true)
      return true;
  }
  return false;
}
void removeElem(Puzzle p, vector<tuple <Puzzle, int> > &src)
{
  int temp;
  for(int i =0; i < src.size(); i++)
  {
    if (get<0>(src[i]).compare(p))
    {
      src.erase(src.begin() + i);
      break;
    }
  }
}

void backtrace(Puzzle p)
{
  Puzzle temp = p;
  vector <int> elements;
  vector <char> moves;
  for(int i=path.size()-1; i >= 0; i--)
  {
    if(temp.compare(get<0>(path[i])))
    {
      elements.push_back(get<0>(get<2>(path[i])));
      moves.push_back(get<1>(get<2>(path[i])));
      temp = get<1>(path[i]);
    }
  }
  for (int j = elements.size() - 1; j >= 0; j--)
  {
    cout << "Element: " << elements[j] << " Move: " << conv[moves[j]] << endl;
  }
}

Puzzle aStarMan(Puzzle root) // pass in root node to search for a star path using manhattan as heuristic
{
  visited.clear();
  path.clear();
  unexpanded.clear();

  vector<int> elements = root.elementList();
  vector<char> moves;
  visited.push_back(make_tuple(root, root.manhattanMaster()));
  Puzzle temp = root;
  Puzzle tempSt;
  int min = 100000;
  
  while(!temp.checkStateCompletion())
  {
    for(int i = 0; i< elements.size(); i++)
    {
      moves = temp.moveList(elements[i]);
      for(int j = 0; j < moves.size(); j++)
      {
        tempSt = temp;
        tempSt.applyMove(elements[i], moves[j]);
        if (!check_exists(visited, tempSt))
        {
          path.push_back(make_tuple(tempSt, temp, make_tuple(elements[i], moves[j])));
          visited.push_back(make_tuple(tempSt, tempSt.manhattanMaster()));
          unexpanded.push_back(make_tuple(tempSt, tempSt.manhattanMaster()));
        }  
      }
    }
    removeElem(temp, unexpanded);
    //cout << check_exists(unexpanded, temp);
    min = 1000000;
    for(int i = 0; i < unexpanded.size(); i++) // Heuristic value check for minimum
    {
      if(min >= get<1>(unexpanded[i]))
      {
        min = get<1>(unexpanded[i]);
        temp = get<0>(unexpanded[i]);
      }
    }
  }
  return temp;
}

int main()
{
  conv['u'] = "UP";
  conv['d'] = "DOWN";
  conv['l'] = "LEFT";
  conv['r'] = "RIGHT";
  
  Puzzle temp;
  ifstream input0("SBP-level0.txt");
  Puzzle pz0(input0);
  input0.close();

  ifstream input1("SBP-level1.txt");
  Puzzle pz1(input1);
  input1.close();
  
  ifstream input2("SBP-level2.txt");
  Puzzle pz2(input2);
  input2.close();

  ifstream input3("SBP-level3.txt");
  Puzzle pz3(input3);
  input3.close();
  
  
  cout << "---------------------------------------" << endl;
  cout << "----------- Solved using A* -----------" << endl;
  cout << "---------------------------------------" << endl;
      
  cout << "------------ Initial State ------------" << endl;
  cout << "--------------- Level0 ----------------" << endl;
  pz0.printState();
  cout << "---------------------------------------" << endl;
  
  temp = aStarMan(pz0);
  cout << "------------ Solution State -----------" << endl;
  temp.printState();
  cout << "------ Moves to reach solution --------" << endl;
  backtrace(temp);
  
  
  cout << "------------ Initial State ------------" << endl;
  cout << "--------------- Level1 ----------------" << endl;
  pz1.printState();
  cout << "---------------------------------------" << endl;
  
  temp = aStarMan(pz1);
  cout << "------------ Solution State -----------" << endl;
  temp.printState();
  cout << "------ Moves to reach solution --------" << endl;
  backtrace(temp);


  cout << "------------ Initial State ------------" << endl;
  cout << "--------------- Level2 ----------------" << endl;
  pz2.printState();
  cout << "---------------------------------------" << endl;
  
  temp = aStarMan(pz2);
  cout << "------------ Solution State -----------" << endl;
  temp.printState();
  cout << "------ Moves to reach solution --------" << endl;
  backtrace(temp);
  
  
  cout << "------------ Initial State ------------" << endl;
  cout << "--------------- Level3 ----------------" << endl;
  pz3.printState();
  cout << "---------------------------------------" << endl;
  
  temp = aStarMan(pz3);
  cout << "------------ Solution State -----------" << endl;
  temp.printState();
  cout << "------ Moves to reach solution --------" << endl;
  backtrace(temp);
  
  return 0;
}
