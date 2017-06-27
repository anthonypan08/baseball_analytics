#include "Game.cpp"
#include <iostream>
#include <fstream>

using namespace std;
int main(){
    string teams[2] ={"a","b"};
    Game game(teams);
 
    
    ifstream readFile("input.txt");
    string s;
    int i=0;
    while (readFile>>s){
       game.process_string(s);
     
      
       
    }
    cout<<endl<<endl<<i<<endl;
    return 0;
}
