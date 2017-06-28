#include <string>
#include <iostream>
#include <deque>
#include <unordered_map>

using namespace std;

class Game{



deque<string> buffer;



class keyword{
    string key;
    
public:
    string getKey(){return key;}
    keyword(string in):key(in){}
    keyword(){}
    
    bool operator()(string in){
        for (int i=0;i<in.length();++i){
            if (!(in[i]>='A' && in [i] <='Z' || in[i] >='a' && in[i]<='z')){
               in=in.substr(0,i)+in.substr(i+1,in.length());
               --i;
            }
        }
        
        return in==key;
    }    

};
deque<keyword> keywords_array;

public:
   int outs;
   int score [2];
   string teams[2];
   string bases[3];
   bool is_name;
   bool team;
   unordered_map<string,int> equivalences;
   Game(string teams_in[2]):is_name(false),outs(0){
       for (int i=0;i<2;++i){
           teams[i]=*(teams_in+i);
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
	
	
    keyword out ("out"); keywords_array.push_back(out);
    //keyword swinging ("out"); keywords_array.push_back(swinging);
    keyword popped("popped"); keywords_array.push_back(popped);
    keyword double_play("double"); keywords_array.push_back(double_play);
    
    keyword walked ("walked"); keywords_array.push_back(walked);
    keyword reached ("reached"); keywords_array.push_back(reached);
    keyword singled ("singled"); keywords_array.push_back(singled);
    keyword doubled ("doubled"); keywords_array.push_back(doubled);
    keyword tripled ("tripled"); keywords_array.push_back(tripled);
    keyword homered ("homered"); keywords_array.push_back(homered);
    
    
    
    keyword advanced ("advanced"); keywords_array.push_back(advanced); 
    keyword stole ("stole"); keywords_array.push_back(stole);          
    keyword caught ("caught"); keywords_array.push_back(caught);
    
    keyword scored ("scored"); keywords_array.push_back(scored);
    keyword second ("second"); keywords_array.push_back(second);
    keyword third ("third"); keywords_array.push_back(third);
    
    
    
    equivalences.insert(pair <string,int> ("singled",0));
    equivalences.insert(pair <string,int> ("doubled",1));
    equivalences.insert(pair <string,int> ("tripled",2));
    equivalences.insert(pair <string,int> ("walked",0));
    equivalences.insert(pair <string,int> ("reached",0));
    
    
    equivalences.insert(pair <string,int> ("second",1));
    equivalences.insert(pair <string,int> ("third",2));
    

   }
   string get_player(int start){
       
       
       for (int i=start;;++i){
          if (buffer[i][0]>='A' && buffer[i][0]<='Z'){
             return buffer[i];
             
          }
       }
       return ""; 
      
   }
   void update_bases(int i,string player){
       cout<<i<<player<<endl;
       bases[i]=player;
   
       
   }

   void calc_situation(){
    	for (int i=buffer.size()-1;i>0;--i){
	       for (int j=0;j<keywords_array.size();++j){
		    if (keywords_array[j](buffer[i])==true && j>=0 && j<=2){
		         
		         outs++;
		        
		    }else if (keywords_array[j](buffer[i])==true && j>=3 && j<=7){
		        
		         update_bases(equivalences[keywords_array[j].getKey()],get_player(i));
		    }
		    
		    
	       }
	}
   }
   void calc_base_out(){
   
   }
   
   void process_string(string s){
   
        if (s==teams[0] || s==teams[1] || s== "END OF FILE"){
            calc_situation();
	    buffer.clear();
	    team=!team;
        }
        if (is_name){
           is_name=false;
           buffer[0]=buffer[0]+" "+s.substr(0,s.length()-1);
        }else{
		    for (int i=0;i<s.length();++i){
		       
		       if (s[i]==',' && s[0]>='A' && s[0]<='Z'){
		            is_name=true;
		           
		            break;
		       }
		  
		      
		    }
		   
		    
		    buffer.push_front(s);
		    
		    
		}
        
       // return s;
    }
};
