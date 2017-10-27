#include <bits/stdc++.h>

using namespace std;

#define sz(x) ((int)(x).size())


char arr[4][30]={{'\0'},{'\0','q','w','e','r','t','y','u','i','o','p','[',']'},{'\0','a','s','d','f','g','h','j','k','l',';','\''},{'\0','z','x','c','v','b','n','m',','}};

string s1 = "qwertyuiop[]asdfghjkl;'zxcvbnm,";
string s2 = u8"ضصثقفغعهخحجچشسیبلاتنمکگظطزرذدپو";

int n, cnt;
string str[1000], g[1000];
vector<char> adj[40];
map <string,char> m1;
map <char,string> m2;

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

string substring_2(string s, int i){
  string str=u8"";
  str+=s[i];
  str+=s[i+1];
  return str;
}

string convert_to_EN(string str, int start){
  string s = "";
  for (int i = start; i < str.size();i+=2)
    s+=m1[substring_2(str,i)];
  return s;
}

string convert_to_FA(string str){
  string s = u8"";
  for (int i = 0; i <str.size();i++)
    s+=m2[str[i]];
  return s;
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

int main(){
  int n = 37;
  int start = 3;
  init();
  for (int i = 0; i < n; i++){
    string s;
    cin >> s;
    cerr << i << endl;
    str[i]=convert_to_EN(s,start);
    start = 0;
  }
  int t = n;
  for (int i = 0; i < t; i++){
    int r1 = rand()%n;
    int r2 = rand()%sz(str[r1]);
    int r3 = rand()%(sz(adj[chartoInd(str[r1][r2])]));
    char c = str[r1][r2];
    str[r1][r2] = adj[chartoInd(str[r1][r2])][r3];
    g[i] = convert_to_FA(str[r1]);
    str[r1][r2] = c;
  }
//  for (int i = 0; i < t; i++)
  //  cout << g[i] << endl;
  for (int i = 0; i < t; i++)
  //  for (int j =0; j < rand()%10; j++)
      cout << g[i] << endl;

}