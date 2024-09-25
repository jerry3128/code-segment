#include <bits/stdc++.h>
#define ll long long
#define int long long
#define db long double
#define x first
#define y second
#define wdnmd const int mod=::mod;
#define eps 1e-12
#define lb(i) ((i)&(-(i)))
#define wr(x,ch) write(x),putchar(ch)
using namespace std;
typedef pair<int,char> paic;
typedef pair<int,int> pai;
typedef pair<pai,int> paii;
typedef pair<pai,pai> ppai;
typedef pair<ppai,int> ppaii;
pai operator+(const pai &x,const pai &y) {return pai(x.x+y.x,x.y+y.y);}
pai operator-(const pai &x,const pai &y) {return pai(x.x-y.x,x.y-y.y);}
#define gh() getchar()
inline long long read() {
	char ch=gh();
	long long x=0;
	char t=0;
	while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
	return t?-x:x;
}
void write(ll x) {
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar(x%10^48);
    return ;
}
const int N=5e5+5;
int l[N],r[N],v[N],lazy[N],ans[N],n,m,q,L,R,W,lc[N],rc[N];
void add(int L,int R,int W,int p) {
    if(L<=l[p]&&r[p]<=R) {lazy[p]+=W;return ;}
    lazy[lc[p]]+=lazy[p],lazy[rc[p]]+=lazy[p];
    lazy[p]=0;
    int mid=r[lc[p]];
    if(L<=mid) add(L,R,W,lc[p]);
    if(R>mid) add(L,R,W,rc[p]);
    return ;
}
signed main() {
	freopen("data.in","r",stdin);
	freopen("data.ans","w",stdout);
	n=read(),m=read(),q=read();
	for(int i=1;i<=2*n-1;i++) lc[i]=read(),rc[i]=read(),v[i]=read(),l[i]=read(),r[i]=read();
	for(int i=1;i<=m;i++) {
		L=read(),R=read(),W=read();
		add(L,R,W,1);
		for(int j=1;j<=2*n-1;j++) 
//			cout<<v[j]<<"*"<<lazy[j]<<" ",
			ans[i]+=v[j]*lazy[j];
//		cout<<"\n";
		cout<<ans[i]<<"\n";
//		if(i==8)exit(0);
//		if(i==44){
//			for(int j=1;j<=2*n-1;j++)
//				cout<<v[j]<<"*"<<lazy[j]<<"\n";
//			cout<<"\n";
//		}
	}
//	for(int i=1;i<=q;i++) {
//		int ql=read(),qr=read();
//		wr(ans[qr],'\n');
//	}
//	for(int i=1;i<=m;i++){
//		wr(ans[i],'\n');
//	}
    return 0;
}
