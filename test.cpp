#include <bits/stdc++.h>

using namespace std;

char arr[4][30]={{'\0'},{'\0','q','w','e','r','t','y','u','i','o','p','[',']'},{'\0','a','s','d','f','g','h','j','k','l',';','\''},{'\0','z','x','c','v','b','n','m',','}};

string s1 = "qwertyuiop[]asdfghjkl;'zxcvbnm,";
string s2 = u8"ضصثقفغعهخحجچشسیبلاتنمکگظطزرذدپو";

int n;
set<string> t;
vector<char> adj[40];
map <string,char> m1;
map <char,string> m2;

string substring_2(string s, int i){
  string str=u8"";
  str+=s[i];
  str+=s[i+1];
  return str;
}

int chartoInd(char c){
      int t;
      switch(c){
      case '[':
           t=26;
            break;
        case ']':
          t =27;
            break;
        case ';':
          t =28;
            break;
        case '\'':
          t =29;
            break;
        case ',':
          t =30;
            break;
        default:
            t = (int)(c-'a');
  }
  return t;
}

void init(){
  for (int i = 1; i < 4; i++)
    for (int j = 1; j < 20; j++)
      if(arr[i][j]!='\0'){
         vector<char> vs= {arr[i][j],arr[i][j-1],arr[i][j+1], arr[i-1][j+1], arr[i+1][j-1],arr[i-1][j],arr[i+1][j]};
         for (auto u: vs)
           adj[chartoInd(arr[i][j])].push_back(u);
      }
  for (int i = 0; i < s2.size();i+=2){
    m1[substring_2(s2,i)]=s1[i/2];
    m2[s1[i/2]]=substring_2(s2,i);
  }
}

string convert_to_EN(string str, int st){
  string s = "";
  cerr << str.size() << endl;
  for (int i = st; i <str.size();i+=2)
    s+=m1[substring_2(str,i)];
 // cerr << s << s.size() << endl;
  return s;
}

string convert_to_FA(string str){
  string s = u8"";
  for (int i = 0; i <str.size();i++)
    s+=m2[str[i]];
  return s;
}

set<string> generate_words(string s){
  set<string> v;
  for (int i = 0; i < s.size(); i++)
    for (auto u:adj[chartoInd(s[i])]){
      if(u!='\0'){
        char c = s[i];
        s[i]=u;
        v.insert(s);
        s[i]=c;
      }
    }
  for(int i = 0; i < s.size()-1;i++){
    swap(s[i],s[i+1]);
    v.insert(s);
    swap(s[i],s[i+1]);
  }
    return v;
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  int start = 3;
  n = 5;
  for (int i = 0; i < n; i++){
    string s;
    cin >> s;
    s = convert_to_EN(s,start);
    //cout << s << endl;
    set<string> v = generate_words(s);
  	for (auto u: v)
  		t.insert(u);
    start = 0;
  }
  int temp;
  for (int i = 0; i < n; i++)
    cin >> temp;
  cerr << temp;
  for (auto u: t)
  	cout << convert_to_FA(u) << endl;
  return 0;
}
