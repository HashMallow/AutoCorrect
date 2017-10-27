#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

#define F first
#define S second

using namespace std;

const int inf = 1e6;
const int maxn = 1000;

char arr[5][30]={{'\0'},{'\0','q','w','e','r','t','y','u','i','o','p','[',']'},{'\0','a','s','d','f','g','h','j','k','l',';','\''},{'\0','z','x','c','v','b','n','m',','},{'\0'}};
string s1 = "qwertyuiop[]asdfghjkl;'zxcvbnm,";
string s2 = u8"ضصثقفغعهخحجچشسیبلاتنمکگظطزرذدپو";

int n=37, root[maxn][maxn];
long long cnt;
string str[1000];
set<string> correct_words, mark, mark2;
set<pair<string, long double> > wrong_words[maxn], t;
long double p[maxn], q[maxn], e[maxn][maxn], w[maxn][maxn];
map<string,int> corNum;
map <string,char> m1;
map <char,string> m2;
vector<char> adj[35];
set<string> ans;

int dist(string s1, string s2){
  int temp = 0;
  for(int i = 0; i < s1.size(); i++)
    if(s1[i]!=s2[i])
      temp++;
    return temp;
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

set<pair<string, long double> > generate_words_v2(string s, long double x){
  set<pair<string, long double> > v;
  for (int i = 0; i < s.size(); i++)
    for (auto u:adj[chartoInd(s[i])]){
      if(u!='\0'){
        char c = s[i];
        s[i]=u;
        if(mark.find(s)==mark.end()){
          mark.insert(s);
          v.insert({s,x*0.75/(long double)(adj[chartoInd(s[i])].size())});
        }
        s[i]=c;
      }
    }
  for(int i = 0; i < s.size()-1;i++){
    swap(s[i],s[i+1]);
    if(mark.find(s)!=mark.end()){
      mark.insert(s);
      v.insert({s,x*0.25});
    }
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

class BST{
private:
  struct node{
    string k;
    bool c;
    set<string> s;
    node *l;
    node *r;
    node *p;
  };
public:
  node *root;
  BST(){root=NULL;}
  bool isEmpty() const { return root==NULL; }
  void preorder(node*);
  void inorder(node*);
  void postorder(node*);
  void insert(string);
  void remove(string);
  bool find(string);
  void completion(string);
  void correct(string);
  void transplant(node*,node*);
  node* minimum(node*);
};

void BST::preorder(node *n){
    if(n != NULL)
    {
      cout<<" "<<n->k<<" ";
        if(n->l) preorder(n->l);
        if(n->r) preorder(n->r);
    }
    else return;
}
void BST::inorder(node *n){
    if(n != NULL)
    {
        if(n->l) inorder(n->l);
        cout<<" "<<n->k<<" ";
        if(n->r) inorder(n->r);
    }
    else return;
}
void BST::postorder(node *n){
    if(n != NULL)
    {
        if(n->l) postorder(n->l);
        if(n->r) postorder(n->r);
        cout<<" "<<n->k<<" ";
    }
    else return;
}
void BST::insert(string v){
  node* n = new node;
  n->k=v;
  n->c = 1;
  n->l=NULL;
  n->r=NULL;
  n->p=NULL;
  node *y;
  y = NULL;
  if (isEmpty())
    root = n;
  else{
    node* x;
    x = root;
    while(x){
      y=x;
      if(v<x->k)
        x=x->l;
      else
        x=x->r;
    }
    n->p=y;
    if(v<y->k)
      y->l=n;
    else
      y->r=n;
  }
}

bool BST::find(string v){
    bool found = false;
    if(isEmpty()) {
        cout<<" This Tree is empty! "<<endl;
        return false;
    }
    
    node* x;
    x = root;
    
    while(x != NULL){
      if(x->k == v){
        found = true;
        break;
       }
      else{
        cnt++;
        if(v>x->k) x = x->r;
        else x = x->l;
      }
    }
    if(found==false)
      return false;
    else
      return found&x->c;
}

void BST::completion(string v){
    bool found = false;
    if(isEmpty()) {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    node* x;
    x = root;
    while(x != NULL){
      if(x->k == v){
          found = true;
          break;
      }
      else{
          if(v>x->k) x = x->r;
          else x = x->l;
      }
    }
    if(x->c==1){
      int temp = corNum[x->k];
      if(x->l==NULL){
          node* n = new node;
          if(wrong_words[temp-1].begin()!=wrong_words[temp-1].end())
            n->k=wrong_words[temp-1].begin()->F;
          else n->k="";
          n->l=NULL;
          n->r=NULL;
          n->c = 0;
          n->p=x;
          x->l=n;
          if(wrong_words[temp-1].begin()!=wrong_words[temp-1].end())
            for (auto u: wrong_words[temp-1])
              n->s.insert(u.F);
      }
      if(x->r==NULL){
          node* n = new node;
          if(wrong_words[temp].begin()!=wrong_words[temp].end())
            n->k=wrong_words[temp].begin()->F;
          else n->k="";
          n->l=NULL;
          n->c=0;
          n->r=NULL;
          n->p=x;
          x->r=n;
          if(wrong_words[temp].begin()!=wrong_words[temp].end())
            for (auto u: wrong_words[temp])
              n->s.insert(u.F);
      }
    }
}
void BST::correct(string str){
  if(!str.size())
    return;
  set<string> v = generate_words(str);
  for(auto u:v)
    if(find(u))
      ans.insert(u);
}

void BST::remove(string v){
    bool found = false;
    if(isEmpty()) {
        cerr <<" This Tree is empty! "<<endl;
        return;
    }
    node* x;
    x = root;
    while(x != NULL){
         if(x->k == v){
            found = true;
            break;
         }
         else{
             if(v>x->k) x = x->r;
             else x = x->l;
         }
    }
    if(!found){
        cout<<" Data not found! "<<endl;
        return;
    }
    if(x->l==NULL){
        transplant(x,x->r);
      }
    else if(x->r==NULL){
      transplant(x,x->l);
    }
    else{
      node *y;
      y = minimum(x->r);
      if(y->p!=x){
        if(y->r){
          transplant(y,y->r);
          y->r=x->r;
          y->r->p=y;
        }
      }
      transplant(x,y);
      y->l=x->l;
      if(y->l)
        y->l->p=y;
    }
    delete x;
}

void BST::transplant(node* u, node* v){
  if(u->p==NULL)
    root = v;
  else if(u==u->p->l)
    u->p->l=v;
  else u->p->r=v;
  if(v!=NULL)
    v->p=u->p;
}

BST::node* BST::minimum(node* r){
  node* x = r;
  while(x->l!=NULL)
    x=x->l;
  return x;
}

void construct_BST(int i, int j, BST *b){
  if(j<i)
    return;
  auto t = correct_words.begin();
  for (int k = 0; k < root[i][j]-1;k++)
    ++t;
  b->insert(*t);
  construct_BST(i,root[i][j]-1, b);
  construct_BST(root[i][j]+1,j, b);
}

void compute_Optimal_BST(BST *b){
  for (int i = 0; i <= n+1; i++)
    w[i][i-1]=q[i-1];
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      w[i][j]=w[i][j-1]+p[j]+q[j];
  for (int i = 1; i <= n+1; i++){
    e[i][i-1]=q[i-1];
    for (int j = i; j <= n;j++)
      e[i][j]=inf;
  }
  for (int l = 1; l <= n; l++){
        for (int i = 1; i<=n-l+1; i++){
          int j = i+l-1;
        for (int r = i; r <= j; r++){
          long double temp = e[i][j];
          e[i][j]=min(e[i][j],e[i][r-1]+e[r+1][j]+w[i][j]);
          if(temp!=e[i][j])
            root[i][j]=r;
        }
      }
  }
  construct_BST(1, n, b);
}

void compute_q(){
  for (int i = 0; i <= n; i++)
    for (auto u: wrong_words[i])
      q[i]+=u.S;
}

void init(BST *b){
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
  int start = 3;
  for (int i = 1; i <= n; i++)
    cin >> str[i];//it should be persian
  for(int i = 1; i <= n; i++)
    cin >> p[i];
  for(int i = 1; i <= n; i++){
    string str1 = convert_to_EN(str[i], start);
    corNum[str1]=i;
    correct_words.insert(str1);
    auto v = generate_words_v2(str1,p[i]);
    for (auto u: v){
      if(mark2.find(u.F)==mark2.end()){
        mark2.insert(u.F);
        t.insert(u);
      }
    }
    start = 0;
  }
  int temp = 0;
  for (auto u:t)
    if(corNum[u.F])
      temp++;
    else
      wrong_words[temp].insert(u);
  compute_q();
  compute_Optimal_BST(b);
  for(auto str:correct_words)
    b->completion(str);
}

int main(){
  BST b;
  init(&b);
  int nt; 
  cin >> nt;
  for (int i = 0; i < nt; i++){
   // cerr << i << endl;
    string st;
    cin >> st;
    st = convert_to_EN(st,0);
    if(b.find(st))
      cout << "It's OK\n";
    else{
      b.correct(st);
      int mn = inf;
      string res;
      for(auto u: ans){
        if(dist(u,st)<mn){
          mn = dist(u,st);
          res = u;
        }
      }
      cout << "Did you mean " << convert_to_FA(res) << "?\n";
      cout << "Other Suggestions:"; 
      for (auto u:ans)
        if(u!=res)
          cout << convert_to_FA(u) << ' ';
      cout << endl;
    }
    ans.clear();
  }
  cout << cnt << endl;
  return 0;
}