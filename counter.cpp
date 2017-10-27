#include <bits/stdc++.h>


using namespace std;

int cnt, n;

struct Integer{
	int k;
	Integer(int _k){
		k = _k;
	}
};

bool operator <(Integer a, Integer b){
	cnt++;
	cerr << a.k << ' ' << b.k << endl;
	return a.k < b.k;
}

Integer a[100] = Integer(0);

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++){
  	int temp;
  	cin >> temp;
  	a[i].k = temp;
  }
  sort(a,a+n);
  cout << cnt;
  return 0;
}