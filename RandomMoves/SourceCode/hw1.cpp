#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
using namespace std;

class Puzzle
{
  private:
    int _x;
    int _y;
    vector< vector<int> > _state;
    vector< vector<int> > _state_clone;

  
  public:
    // Constructors
    Puzzle();
    Puzzle(vector< vector<int> > src)
    {
      _x = src.size();
      _y = src[0].size();
      vector<int> temp;
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          temp.push_back(src[i][j]);
        }
        _state.push_back(temp);
        temp.clear();
      }
    }
    Puzzle(ifstream& file)
    {
      string str, token;
      vector<int> temp;
      bool check = false;
      while(getline(file, str))
      {
        istringstream ss(str);
        if (check == false){
          _x = int(str[0] - '0');
          _y = int(str[2] - '0');

          check = true;
        }
        else{
          while (getline(ss, token, ','))
          {
            //cout << stoi(token) << endl;
            temp.push_back(stoi(token));
          }
          _state.push_back(temp);
          temp.clear();
        }
      }
      _y = _state.size();
      file.close();
    }
    
    // Method to print out given state
    int at(int i, int j) const
    {
      return _state[i][j];
    }
    void printState()
    {
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          cout << setw(2);
          cout << _state[i][j] << "  ";
        }
        cout << endl;
      }
    }
    // State clone
    vector<vector<int> > stateClone()
    {
      _state_clone = _state;
      return _state;
    }
    // Check completion of state
    bool checkStateCompletion()
    {
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          if (_state[i][j] == -1)
          {
            return false;
          }
        }
      }
      return true;
    }
    // List valid moves individual pieces can make
    vector<string> moveList(int piece)
    {
      vector<string> moveList;
      bool up = true;
      bool down = true;
      bool left = true;
      bool right = true;

      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          if(_state[i][j] == piece)
          {
            if(_state[i][j-1] == piece || _state[i][j-1] == 0 || ( piece == 2 && _state[i][j-1] == -1))
              left = left && true;
            else
              left = left && false;
            
            if(_state[i][j+1] == piece || _state[i][j+1] == 0 || ( piece == 2 && _state[i][j+1] == -1))
              right = right && true;
            else
              right = right && false;
            
            if(_state[i-1][j] == piece || _state[i-1][j] == 0 || ( piece == 2 && _state[i-1][j] == -1))
              up = up && true;
            else
              up = up && false;
            
            if(_state[i+1][j] == piece || _state[i+1][j] == 0 || ( piece == 2 && _state[i+1][j] == -1))
              down = down && true;
            else
              down = down && false;
          }
        }
      }
      if(up == true)
        moveList.push_back("UP");
      if(down == true)
        moveList.push_back("DOWN");
      if(left == true)
        moveList.push_back("LEFT");
      if(right == true)
        moveList.push_back("RIGHT");
      return moveList;
    } 
    void allMoveList()
    {
      vector<string> temp;
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          if (_state[i][j] != -1 && _state[i][j]!=1 && _state[i][j]!=0 )
          {
            temp = moveList(_state[i][j]);
            cout << "Moves available for piece " << _state[i][j] << " ";
            if (temp.size() == 0)
              cout << "no moves available" << endl;
            else{
              for (int i = 0; i< temp.size(); i++)
              {
                cout << temp[i] << ", ";
              }
              cout << endl;
            }
          }
        }
      }
    }
    void applyMove(int piece, string dir)
    {
      bool valid = false;
      vector < vector<int> > temp = _state;
      //locale loc;
      //dir = toupper(dir, loc);
      vector <string> moves = moveList(piece);
      if (dir.size() != 0){
        for (int i = 0; i < moves.size(); i++)
        {
          if (dir.compare(moves[i]) == 0)
          {
            valid = true;
            break;
          }
        }
        if (valid == false)
          cout << "Invalid move" << endl;
        else
        {
          for (int i = 0; i < _y; i++)
          {
            for (int j = 0; j < _x; j++)
            {
              if(temp[i][j] == piece)
              {
                if(dir.compare("UP") == 0)
                {
                  _state[i-1][j] = _state[i][j];
                  _state[i][j] = 0;
                }
                if(dir.compare("DOWN") == 0)
                {
                  _state[i+1][j] = _state[i][j];
                  _state[i][j] = 0;
                }
                if(dir.compare("LEFT") == 0)
                {
                  _state[i][j-1] = _state[i][j];
                  _state[i][j] = 0;
                }
                if(dir.compare("RIGHT") == 0)
                {
                  _state[i][j+1] = _state[i][j];
                  _state[i][j] = 0;
                }
              }
            }
          }
        }
      }
    }
    void normalize()
    {
      int nextIdx = 3;
      int i;
      int j;

      for(i = 0;i < _y;i++) 
      {
        for(j = 0;j < _x;j++) 
        {
          if (_state[i][j]==nextIdx) 
          {
            nextIdx++;
          } 
          else if (_state[i][j] > nextIdx) 
          {
            swapIdx(nextIdx,_state[i][j]);
            nextIdx++;
          }
        }
      }
    }
    void swapIdx(int idx1,int idx2) 
    {
      int i;
      int j;
      for(i = 0;i < _y;i++) 
      {
        for(j = 0;j < _x;j++) 
        {
          if (_state[i][j]==idx1) 
          {
            _state[i][j]=idx2;
          } 
          else if (_state[i][j]==idx2) 
          {
            _state[i][j]=idx1;
          }
        }
      }
    }
    bool compare( vector< vector<int> > src )
    {
      
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          if (_state[i][j] != src[i][j])
            return false;
        }
      }
      return true;
    }

    bool compare(const Puzzle& p )
    {
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          if (_state[i][j] != p.at(i,j))
            return false;
        }
      }
      return true;
    }
    vector<int> elementList()
    {
      vector <int> temp;
      for (int i = 0; i < _y; i++)
      {
        for (int j = 0; j < _x; j++)
        {
          if (_state[i][j] != -1 && _state[i][j]!=1 && _state[i][j]!=0 )
            temp.push_back(_state[i][j]);
        }
      }
      return temp;
    }
};


int main()
{
  vector<int> inner(5, 1);
  vector< vector<int> > test;
  vector<int> temp;
  vector<string> options;
  string move;

  ifstream input("SBP-test-not-normalized.txt");
  int element;
  Puzzle pz1(input);
  //test = pz.stateClone();
  //cout << "comlare test" << pz.compare(test) << endl;
  cout << "_______________________________________________________" << endl;
  cout << "____________Normalization Test with Sample_____________" << endl;
  cout << "_______________________________________________________" << endl;
  cout << "Not Normalized State" << endl;
  pz1.printState();
  pz1.normalize();
  cout << "Normalized State" << endl;
  pz1.printState();
  

  cout << endl;
  int n = 1;
  
  ifstream walk("SBP-level3.txt");
  Puzzle pz(walk);
  cout << "_______________________________________________________" << endl;
  cout << "____________Random Walk Test with Sample 3_____________" << endl;
  cout << "_______________________________________________________" << endl;
  
  cout << "Initial State" << endl;
  pz.printState();
  pz.normalize();
  while (n <= 3)
  {
    temp = pz.elementList();
    element = temp[int(rand() % temp.size())];
    cout << "Element: " << element << endl;
    options = pz.moveList(element);

    if (options.size() != 0){
      move = options[int(rand() % options.size())];
      cout << "Move Executed : " << move << " on element: " << element << endl;
      pz.applyMove(element, move);
    }
    else{
      cout << "Move not available for the selected piece" << endl;
    }
    pz.normalize();
    pz.printState();
    n++;
  }
  cout << ((pz.checkStateCompletion() == 0)? "fail":"pass") << endl;
  return 0;
}
