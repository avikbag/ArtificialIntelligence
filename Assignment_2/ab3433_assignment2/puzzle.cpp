#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <algorithm>
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
    Puzzle(vector< vector<int> > src);
    Puzzle(ifstream& file);
    
    // Method to print out given state
    int width() const ;
    int height() const;
    bool empty();
    int at(int i, int j) const;
    void printState() const;
    // State clone;
    vector<vector<int> > stateClone();
    // Check completion of state;
    bool checkStateCompletion();
    // List valid moves individual pieces can make;
    vector<char> moveList(int piece);
    void allMoveList();
    void applyMove(int piece, char dir);
    void normalize();
    void swapIdx(int idx1,int idx2) ;
    bool compare( vector< vector<int> > src )const;
    bool compare(const Puzzle& p )const;
    vector<int> elementList();
    bool operator<(const Puzzle& other) const;
};



Puzzle::Puzzle(){};
Puzzle::Puzzle(vector< vector<int> > src)
{
  _y = src.size();
  _x = src[0].size();
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
Puzzle::Puzzle(ifstream& file)
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
int Puzzle::width() const 
{
  return _x;
}
int Puzzle::height() const
{
  return _y;
}
bool Puzzle::empty()
{
  if (_x == 1 && _y == 1)
    return true;
  else 
    return false;
}
int Puzzle::at(int i, int j) const
{
  return _state[i][j];
}
void Puzzle::printState() const
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
vector<vector<int> > Puzzle::stateClone()
{
  _state_clone = _state;
  return _state;
}
// Check completion of state
bool Puzzle::checkStateCompletion()
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
vector<char> Puzzle::moveList(int piece)
{
  vector<char> moveList;
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
    moveList.push_back('u');
  if(down == true)
    moveList.push_back('d');
  if(left == true)
    moveList.push_back('l');
  if(right == true)
    moveList.push_back('r');
  return moveList;
} 
void Puzzle::allMoveList()
{
  vector<char> temp;
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
void Puzzle::applyMove(int piece, char dir)
{
  bool valid = false;
  int prev = 0;
  vector < vector<int> > temp = _state;
  //locale loc;
  //dir = toupper(dir, loc);
  vector <char> moves = moveList(piece);
  if (dir == 'u' || dir == 'd' ||dir == 'l' ||dir == 'r'){
    for (int i = 0; i < moves.size(); i++)
    {
      if (dir == moves[i])
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
            if(dir == 'u')
            {
              _state[i-1][j] = _state[i][j];
              _state[i][j] = 0;
            }
            if(dir == 'd')
            {
              _state[i+1][j] = _state[i][j];
              _state[i][j] = 0;
            }
            if(dir == 'l')
            {
              _state[i][j-1] = _state[i][j];
              
              _state[i][j] = 0;
            }
            if(dir == 'r')
            {
              _state[i][j+1] = _state[i][j];
              if (prev == 0)
              {
                _state[i][j] = 0;
                prev = -1;
              }

            }
          }
        }
      }
    }
  }
}
void Puzzle::normalize()
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
void Puzzle::swapIdx(int idx1,int idx2) 
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
bool Puzzle::compare( vector< vector<int> > src ) const 
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

bool Puzzle::compare(const Puzzle& p ) const
{
  if (p.width() != _x || p.height() != _y)
  {
    return false;
  }
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
vector<int> Puzzle::elementList()
{
  vector <int> temp;
  for (int i = 0; i < _y; i++)
  {
    for (int j = 0; j < _x; j++)
    {
      if (_state[i][j] != -1 && _state[i][j]!=1 && _state[i][j]!=0)
      {  
        if(find(temp.begin(), temp.end(), _state[i][j]) == temp.end())
          temp.push_back(_state[i][j]);
      }
    }
  }
  return temp;
}
bool Puzzle::operator<(const Puzzle& p) const 
{
  if (compare(p) == true)
  {
    return false;
  }
  return true;
}
