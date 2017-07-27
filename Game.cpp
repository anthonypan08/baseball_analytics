#include <string>
#include <iostream>
#include <deque>
#include <unordered_map>

using namespace std;

class Game {

  deque<string> buffer;

  class keyword {
    string key;

  public:
    string getKey() {
      return key;
    }
    keyword(string in) :
        key(in) {
    }
    keyword() {
    }

    bool operator()(string in) {
      for (int i = 0; i < in.length(); ++i) {
        if (!(in[i] >= 'A' && in[i] <= 'Z'
            || in[i] >= 'a' && in[i] <= 'z')) {
          in = in.substr(0, i) + in.substr(i + 1, in.length());
          --i;
        }
      }

      return in == key;
    }

  };

  class is_player {
  public:
    bool operator ()(string s, char a, char b) {
      return s[0] >= a && s[0] <= b;
    }
  };

  template<typename Pred>
  class comparator {
    char upper, lower;

    Pred function;
  public:
    comparator(char upper_in, char lower_in) :
        upper(upper_in), lower(lower_in) {
    }

    //comparator (string target){string target};
    bool operator ()(string in) {
      return function(in, upper, lower);
    }
  };
  deque<keyword> keywords_array;

public:

  int outs;
  int score[2];
  string teams[2];
  string bases[3];
  string bases_duplicate[3];
  //string batter;
  bool is_name;
  int team;
  bool new_batter;

  unordered_map<string, int> equivalences;
  comparator<is_player> is_player_comp = comparator<is_player>('A', 'Z');

  Game(string teams_in[2]) :
      is_name(false), outs(0), team(0) {
    for (int i = 0; i < 2; ++i) {
      teams[i] = *(teams_in + i);
      score[i] = 0;
    }

    const static double BASE_OUT_SCORE[8][3] = { { 0.461, 0.243, 0.095 }, {
        0.831, 0.489, 0.214 }, { 1.068, 0.644, 0.305 }, { 1.373, 0.908,
        0.343 }, { 1.426, 0.865, 0.413 }, { 1.798, 1.140, 0.471 }, {
        1.920, 1.352, 0.570 }, { 2.282, 1.520, 0.73 } };

    keyword out("out");
    keywords_array.push_back(out);
    //keyword swinging ("out"); keywords_array.push_back(swinging);
    keyword popped("popped");
    keywords_array.push_back(popped);
    keyword double_play("double");
    keywords_array.push_back(double_play);
    keyword caught("caught");
    keywords_array.push_back(caught);

    keyword advanced("advanced");
    keywords_array.push_back(advanced);
    keyword stole("stole");
    keywords_array.push_back(stole);
    keyword pinch_ran("ran");
    keywords_array.push_back(pinch_ran);

    ///////////////////////////////////////////////////////////////////
    //keywords array below must also be in equivalences array
    keyword walked("walked");
    keywords_array.push_back(walked);
    keyword hbp("pitch");
    keywords_array.push_back(hbp);
    keyword reached("reached");
    keywords_array.push_back(reached);
    keyword singled("singled");
    keywords_array.push_back(singled);
    keyword doubled("doubled");
    keywords_array.push_back(doubled);
    keyword tripled("tripled");
    keywords_array.push_back(tripled);

    keyword homered("homered");
    keywords_array.push_back(homered);

    keyword scored("scored");
    keywords_array.push_back(scored);

    keyword second("second");
    keywords_array.push_back(second);
    keyword third("third");
    keywords_array.push_back(third);

    equivalences.insert(pair<string, int>("singled", 0));
    equivalences.insert(pair<string, int>("hit", 0));
    equivalences.insert(pair<string, int>("doubled", 1));
    equivalences.insert(pair<string, int>("tripled", 2));
    equivalences.insert(pair<string, int>("walked", 0));
    equivalences.insert(pair<string, int>("reached", 0));

    equivalences.insert(pair<string, int>("second", 1));
    equivalences.insert(pair<string, int>("third", 2));

    equivalences.insert(pair<string, int>("homered", 3));
    equivalences.insert(pair<string, int>("scored", 3));

  }

  string look_player(int start, int direction) {

    for (int i = start;; i = i + direction) {
      if (is_player_comp(buffer[i])) {
        return buffer[i];
      }
    }
  }

  bool is_legit_out(int start, int direction) {
    for (int i = start + 1;; i = i + direction) {
      if (keywords_array[0](buffer[i])) {
        return false;
      }

      if (is_player_comp(buffer[i])) {
        return true;
      }
    }

  }

  string get_player(int start) {

    string player = look_player(start, 1);

    if (is_legit_out(start, 1) == false) {
      outs--;
    }

    for (int j = 0; j < 3; ++j) {

      if (bases[j] == player) {
        break;
      }
      if (j == 2)
        new_batter = true;
    }
    return player;

    return "";

  }

  int get_bases(int start) {

    for (int i = start;; --i) {
      for (int j = keywords_array.size() - equivalences.size();
          j < keywords_array.size(); ++j) {
        if (keywords_array[j](buffer[i])) {
          return equivalences[keywords_array[j].getKey()];

        } else if (is_player_comp(buffer[i])) {
          for (int k = 0; k < 3; ++k) {
            if (bases[k] == buffer[i])
              return k;
          }

        }
      }
    }
    return 0;

  }

  void clean_bases(string player) {
    for (int i = 0; i < 3; ++i) {
      if (bases_duplicate[i] == player)
        bases_duplicate[i] = "";
    }
  }
  void assign_bases(int base, string player) {

    if (base <= 2)
      bases_duplicate[base] = player;
    else {

      score[team]++;
      clean_bases(player);

    }

  }
  void update_bases() {
    for (int i = 0; i < 3; ++i) {
      bases[i] = bases_duplicate[i];

    }

    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 3; ++j) {
        if (bases[i] == bases[j])
          bases[i] = "";
      }

    }
  }

  void reset() {
    for (int i = 0; i < 3; ++i) {
      bases[i] = "";
      bases_duplicate[i] = "";
    }
    buffer.clear();
    team = (team + 1) % 2;

  }

  void calc_situation() {

    for (int i = buffer.size() - 1; i >= 0; --i) {

      for (int j = 0; j < keywords_array.size(); ++j) {

        if (keywords_array[j](buffer[i]) == true && j >= 0 && j <= 3) {

          clean_bases(get_player(i));
          outs++;
          break;

        } else if (keywords_array[j](buffer[i]) == true && j >= 4
            && j <= 14) {

          assign_bases(get_bases(i), get_player(i));
          break;
        }

      }

      if (buffer[i][buffer[i].length() - 1] == '.' && new_batter) {

        update_bases();

        for (int i = 0; i < 3; ++i) {
          cout << bases[i] << endl;
        }
        cout << outs << endl;
        cout << score[0] << endl;
        cout << score[1] << endl;
        cout << teams[team] << endl;
        cout << "============" << endl;
        new_batter = false;

      }

    }

  }
  void calc_base_out() {

  }

  void process_string(string s) {

    if (is_name) {
      is_name = false;
      buffer[0] = buffer[0] + " " + s.substr(0, s.length() - 1);
    } else {
      for (int i = 0; i < s.length(); ++i) {

        if (s[i] == ',' && is_player_comp(s)) {
          is_name = true;

          break;
        }

      }

      buffer.push_front(s);

    }

    for (int i = 0; i < s.length(); ++i) {
      s[i] = tolower(s[i]);
    }
    //find
    if (s.find("run") != string::npos) {

      
      calc_situation();
      reset();

    }

    // return s;
  }
};
