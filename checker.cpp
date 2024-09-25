#include <bits/stdc++.h>
#define ll long long
using namespace std;
int random(int x) {
	return 1ll*rand()*rand()%x+1;
}
const int N=1e5+5;
int tot,lc[N],rc[N],v[N],l[N],r[N];
int dfs(int l,int r) {
	int p=++tot;
	::l[p]=l,::r[p]=r,v[p]=random(1000);
	if(l<r) {
		int mid=random(r-l)+l-1;
		lc[p]=dfs(l,mid);
		rc[p]=dfs(mid+1,r);
	}
	return p;
}
int main() {
	int Ti=1000;
	while(Ti--){
		system("Î´ÃüÃû3.exe");
		system("Î´ÃüÃû2.exe");
		system("solution.exe");
		if(system("fc data.out data.ans"))break;
	}
	return 0;
}
