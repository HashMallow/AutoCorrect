#include <bits/stdc++.h>

using namespace std;

int n, root[100][100];
double p[100], q[100], e[100][100], w[100][100];

const int inf = 1000;

void construct_bst(int i, int j){
	if(j<i)
		return;
	cout << root[i][j] << endl;
	construct_bst(i,root[i][j]-1);
	construct_bst(root[i][j]+1,j);
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
  	cin >> p[i];
  for (int i = 0; i <= n; i++)
  	cin >> q[i];
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
  				double temp = e[i][j];
  				e[i][j]=min(e[i][j],e[i][r-1]+e[r+1][j]+w[i][j]);
  				if(temp!=e[i][j])
  					root[i][j]=r;
  			}
  		}
  }
  construct_bst(1, n);
  return 0;
}