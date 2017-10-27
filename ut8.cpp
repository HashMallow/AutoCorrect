#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef set<int> si;
typedef set<ll> sl;
typedef set<pii> sii;
typedef set<pll> sll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<string> vs;

const int inf = 1<<30;
const ll INF = (ll)1<<62;
const int mod = 1e9+7;
const int maxn = 1e5+5;

set<pair<string, int> > se;

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  string s;
  se.insert({u8"آآآ",0});
  while(cin>>s){
  	if(s[s.size()-1]=='?'||s[s.size()-1]=='.'||s[sz(s)-1]==',')
  		s.erase(sz(s)-1);
  	auto t = se.lower_bound({s,0});
  	if(t==se.end())
  		se.insert({s,1});
  	else if(t->F!=s)
  		se.insert({s,1});
  	else{
	  	int temp = t->S+1;
	  	se.erase(t);
	  	se.insert({s,temp});
	 }
  }
  for (auto u: se)
  	cout << u.F << endl;
  for (auto u: se)
    cout << u.S << endl;
  return 0;
}