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
	freopen("data.in","w",stdout);
	srand(chrono::system_clock().now().time_since_epoch().count());
	int n=100,m=100,q=100;
	printf("%d %d %d\n",n,m,q);
	dfs(1,n);
	for(int i=1;i<=2*n-1;i++) printf("%d %d %d %d %d\n",lc[i],rc[i],v[i],l[i],r[i]);
	for(int i=1;i<=m;i++) {
		int l=random(n),r=random(n),v=random(1000);
		if(l>r) swap(l,r);
		printf("%d %d %d\n",l,r,v);
	}
	for(int i=1;i<=q;i++) {
		int l=random(m),r=random(m);
		if(l>r) swap(l,r);
		printf("%d %d\n",l,r);
	}
	return 0;
}
