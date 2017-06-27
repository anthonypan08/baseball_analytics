#include <string>
#include <iostream>

using namespace std;

class Game{
const static int BUFFER_SIZE=10;
const static int KEYWORD_NUM=11;

string buffer[BUFFER_SIZE];


class keyword{
    string key;
public:
    keyword(string in):key(in){}
    keyword(){}
    
    bool operator()(string in){
        return in==key;
    }    

};

keyword keywords_array[KEYWORD_NUM];

public:
   int outs;
   int score [2];
   string teams[2];
   string bases[3];
   bool is_name;
   bool team;
   Game(string teams_in[2]):is_name(false){
       for (int i=0;i<2;++i){
           teams[i]=teams_in[i];
       }
       
       const static double BASE_OUT_SCORE [8][3]={
        {0.461, 0.243, 0.095},
	{0.831,0.489, 	0.214},
	{1.068, 0.644, 	0.305},
 	{1.373, 0.908, 	0.343},
 	{1.426, 0.865, 	0.413},
 	{1.798 ,1.140, 	0.471},
 	{1.920 ,1.352, 	0.570},
	{2.282, 1.520 ,	0.73}};
	
	
    keyword out ("out"); keywords_array[0]=out;
    keyword popped("popped"); keywords_array[1]=popped;
    keyword double_play("double"); keywords_array[2]=double_play;
    
    keyword singled ("singled"); keywords_array[3]=singled;
    keyword doubled ("doubled"); keywords_array[4]=doubled;
    keyword tripled ("tripled"); keywords_array[5]=tripled;
    keyword homered ("homered"); keywords_array[6]=homered;
    
    
    
    keyword advanced ("advanced"); keywords_array[7]=advanced;
    keyword stole ("stole"); keywords_array[8]=stole;
    keyword caught ("caught"); keywords_array[9]=caught;
    
    keyword scored ("scored"); keywords_array[10]=scored;
    
    
   }
   string get_player(){
       
       
       for (int i=0;i<BUFFER_SIZE;++i){
          if (buffer[i][0]>='A' && buffer[i][0]<='Z'){
             return buffer[i];
             
          }
       }
       return ""; 
      
   }
   void update_bases(int i,string player){
       cout<<player<<endl;
       bases[i]=player;
   }
   void update_situation(){
       for (int i=0;i<KEYWORD_NUM;++i){
            if (keywords_array[i](buffer[0])==true && i>=0 && i<=2){
                 outs++;
            }else if (keywords_array[i](buffer[0])==true && i>=3 && i<=5){
                
                 update_bases(i-3,get_player());
            }
            
            
       }
   }
   void calc_base_out(){
   
   }
   
   void process_string(string s){
        if (is_name){
           is_name=false;
           buffer[0]=buffer[0]+s;
        }else{
		    for (int i=0;i<s.length();++i){
		       
		       if (s[i]==',' && s[0]>='A' && s[0]<='Z'){
		            is_name=true;
		           
		            break;
		       }
		  
		      
		    }
		   
		    for (int i=BUFFER_SIZE-1;i>0;--i){
		        buffer[i]=buffer[i-1];          
		    }
		    buffer[0]=s;
		    
		    update_situation();
		    if (s[s.length()-1]=='.' && s != "LOB."){
		        calc_base_out();
		    }
		}
        
       // return s;
    }
};
