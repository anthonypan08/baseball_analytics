#include "Game.cpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    string teams[2] ={"Air","LSU"};
    Game game(teams);
 
    cout<<game.teams[1];
    ifstream readFile("input.txt");
    string s;
    
    while (readFile>>s){
       game.process_string(s);
       
       
      
       
    }
    game.process_string("END OF FILE");

    cout<<endl<<game.outs<<endl<<endl;
    return 0;
}
