#include <bits/stdc++.h>

using namespace std;


char arr[4][30]={{'\0'},{'\0','q','w','e','r','t','y','u','i','o','p','[',']'},{'\0','a','s','d','f','g','h','j','k','l',';','\''},{'\0','z','x','c','v','b','n','m',','}};

string s1 = "qwertyuiop[]asdfghjkl;'zxcvbnm,";
string s2 = u8"ضصثقفغعهخحجچشسیبلاتنمکگظطزرذدپو";

struct myString{
  string str;
  myString(string _str){
    str = _str;
  }
};

int n, cnt;
vector<char> adj[40];
map <string,char> m1;
map <char,string> m2;
set<myString> s;

bool operator <(myString s1, myString s2){
  cnt++;
  return s1.str < s2.str;
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

set<myString> generate_words(string s){
  set<myString> v;
  for (int i = 0; i < s.size(); i++)
    for (auto u:adj[chartoInd(s[i])]){
      if(u!='\0'){
        char c = s[i];
        s[i]=u;
        myString s1 = myString(s);
        v.insert(s1);
        s[i]=c;
      }
    }
  for(int i = 0; i < s.size()-1;i++){
    swap(s[i],s[i+1]);
    myString s1 = myString(s);
    cerr << s1.str << endl;
    v.insert(s1);
    swap(s[i],s[i+1]);
  }
  return v;
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
	
	init();
	int n=37;
	int start = 3;
	for (int i = 0; i < n; i++){
		string s1;
		cin >> s1;
		s1 = convert_to_EN(s1,start);
    myString ms1 = myString(s1);
		s.insert(ms1);
		start=0;
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++){
		string str;
		cin >> str;
    str = convert_to_EN(str,start);
    myString mstr = myString(str);
		set<myString> st = generate_words(str);
		for (auto u:st)
			if(s.find(u)!=s.end())
				cout << convert_to_FA(u.str) << endl;
	}
  cout << cnt;
}