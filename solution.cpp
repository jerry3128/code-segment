//ayanami±£””£¨ø‰∏Á±£””£¨π∑¬Ë±£””£¨MDR±£””£¨Ô±µ∂π÷±£””£¨M99±£””£¨øÀµ˘±£””
#include<bits/stdc++.h>
using namespace std;
int p1=1000000,p2=0;
char buf[1000005],wb[1000005];
int gc() {
	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
	return buf[p1++];
}
#define gc getchar
#define Loli true
#define Kon xor true
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	int c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
int n,m,q,N;
namespace T{
	int tot,sta[200005];
	struct node{
		int ch[4],fa,pre,num[2],c,prec;//chain & left/right son, father, solid chain's top node, numbers of left/right sons on a solid chain, this node is left/right son.
		long long val,laz,preval,prelaz,slaz;//value and lazy, top's lazy
		long long sval[2];//sum of left/right sons' value on current substructure, sum of lazy on current substructure.
		long long pretag,pretagtag[2],ctag;//plus tag to top, plus tag to pretag on left/right son.
		unsigned ans,tans;
	}v[400005];
	bool isroot(int x){return v[v[x].fa].ch[0]!=x&&v[v[x].fa].ch[1]!=x;}
	void add_son(int x,int t,int y) {v[x].ch[t]=y,v[y].fa=x;}
	void push_up_compress(int rt){
		if(!rt)return;
		v[rt].pre=v[rt].ch[0]?(v[rt].prec=v[v[rt].ch[0]].prec,v[rt].prelaz=v[v[rt].ch[0]].prelaz,v[rt].preval=v[v[rt].ch[0]].preval,v[v[rt].ch[0]].pre):(v[rt].prec=v[rt].c,v[rt].prelaz=v[rt].laz,v[rt].preval=v[rt].val,rt);
		
		v[rt].num[0]=v[v[rt].ch[0]].num[0]+v[v[rt].ch[1]].num[0]+(v[rt].ch[2]!=0);
		v[rt].num[1]=v[v[rt].ch[0]].num[1]+v[v[rt].ch[1]].num[1]+(v[rt].ch[3]!=0);
		v[rt].sval[0]=v[v[rt].ch[0]].sval[0]+v[v[rt].ch[1]].sval[0]+v[v[rt].ch[2]].val;
		v[rt].sval[1]=v[v[rt].ch[0]].sval[1]+v[v[rt].ch[1]].sval[1]+v[v[rt].ch[3]].val;
		v[rt].slaz=v[v[rt].ch[0]].slaz+v[v[rt].ch[1]].slaz+v[rt].laz;
		
		v[rt].ans=v[v[rt].ch[0]].ans+v[v[rt].ch[1]].ans+v[v[rt].ch[2]].ans+v[v[rt].ch[3]].ans+v[rt].laz*v[rt].val;
		v[rt].tans=v[v[rt].ch[0]].tans+v[v[rt].ch[1]].tans+v[v[rt].ch[2]].ans+v[v[rt].ch[3]].ans+(v[v[rt].ch[0]].slaz+v[rt].laz)*(v[v[rt].ch[2]].val+v[v[rt].ch[3]].val+v[v[rt].ch[1]].sval[0]+v[v[rt].ch[1]].sval[1]);
	}
	void push_up_rake(int rt){
		if(!rt)return;
		v[rt].val=v[v[rt].ch[2]].preval;
		v[rt].laz=v[v[rt].ch[2]].prelaz;
		v[rt].ans=v[v[rt].ch[2]].ans;
		v[rt].sval[0]=v[v[rt].ch[2]].sval[0];
		v[rt].sval[1]=v[v[rt].ch[2]].sval[1];
	}
	void push_up(int rt){
		rt<=N?push_up_compress(rt):push_up_rake(rt);
	}
	void push_pretag(int rt,long long val){
		if(!rt)return;
		if(rt<=N){
			v[rt].prelaz+=val,v[rt].pretag+=val,v[rt].slaz+=val;
			v[rt].ans+=v[rt].preval*val,v[rt].tans+=(v[rt].sval[0]+v[rt].sval[1])*val;
			(v[rt].pre==rt)?v[rt].laz+=val:0;
		}else{
			v[rt].pretag+=val,v[rt].laz+=val;
			v[rt].ans+=v[rt].val*val,v[rt].tans+=(v[rt].sval[0]+v[rt].sval[1])*val;
		}
//		if(rt==98)cerr<<"pretag:"<<rt<<" "<<v[rt].laz<<"\n";
	}
	void push_pretagtag(int rt,long long val[2]){
		if(!rt)return;
		v[rt].pretagtag[0]+=val[0],v[rt].pretagtag[1]+=val[1];
		v[rt].ans+=v[rt].sval[0]*val[0]+v[rt].sval[1]*val[1];
		v[rt].tans+=v[rt].sval[0]*val[0]+v[rt].sval[1]*val[1];
	}
	void push_ctag(int rt){
		if(!rt)return;
		long long tmp[2]={(v[rt].ctag?0:(v[rt].laz+(v[rt].ch[0]?v[v[rt].ch[0]].slaz+v[rt].pretag:0))), (v[rt].ctag?0:(v[rt].laz+(v[rt].ch[0]?v[v[rt].ch[0]].slaz+v[rt].pretag:0)))};
		long long tnp[2]={v[rt].pretag, v[rt].pretag};
		push_pretag(v[rt].ch[2],(v[rt].ctag?0:(v[rt].laz+(v[rt].ch[0]?v[v[rt].ch[0]].slaz+v[rt].pretag:0))));
		push_pretag(v[rt].ch[3],(v[rt].ctag?0:(v[rt].laz+(v[rt].ch[0]?v[v[rt].ch[0]].slaz+v[rt].pretag:0))));
		push_pretagtag(v[rt].ch[0],tnp);
		push_pretagtag(v[rt].ch[1],tmp);
		v[rt].ctag=1,v[rt].slaz=0,v[rt].laz=0,v[rt].prelaz=0,v[rt].pretag=0;
//		if(rt==98)cerr<<"clear:"<<rt<<" "<<v[rt].laz<<"\n";
		v[rt].ans=v[rt].tans;
	}
	void push_down_compress(int rt){
		if(v[rt].ctag)push_ctag(v[rt].ch[0]),push_ctag(v[rt].ch[1]),v[rt].ctag=0;
		if(v[rt].pretag)push_pretag(v[rt].ch[0],v[rt].pretag),v[rt].pretag=0;
		if(v[rt].pretagtag[0]||v[rt].pretagtag[1]){
			push_pretag(v[rt].ch[2],v[rt].pretagtag[0]);
			push_pretag(v[rt].ch[3],v[rt].pretagtag[1]);
			push_pretagtag(v[rt].ch[0],v[rt].pretagtag);
			push_pretagtag(v[rt].ch[1],v[rt].pretagtag);
			v[rt].pretagtag[0]=0,v[rt].pretagtag[1]=0;
		}
	}
	void push_down_rake(int rt){
		if(v[rt].pretag)push_pretag(v[rt].ch[2],v[rt].pretag),v[rt].pretag=0;
	}
	
	void out(int x){
		cerr<<"index: "<<x<<"\n";
		cerr<<"laz: "<<v[x].laz<<"\n";
		cerr<<"slaz: "<<v[x].slaz<<"\n";
		cerr<<"ch[2]->preval: "<<v[v[x].ch[2]].val<<"\n";
		cerr<<"sval[0]: "<<v[x].sval[0]<<"\n";
		cerr<<"ch[3]->preval: "<<v[v[x].ch[3]].val<<"\n";
		cerr<<"sval[1]: "<<v[x].sval[1]<<"\n";
//		cerr<<"tans: "<<v[x].tans<<"\n";
		cerr<<"\n";
	}
	
	void push_down(int rt){
		rt<=N?push_down_compress(rt):push_down_rake(rt);
	}
	int son(int p,int x){
		if(v[p].ch[0]==x)return 0;
		if(v[p].ch[1]==x)return 1;
		if(v[p].ch[2]==x)return 2;
		if(v[p].ch[3]==x)return 3;
		puts("Error"),exit(233);
	}
	void rot(int x) {
		int p=v[x].fa,g=v[p].fa,d=(v[p].ch[1]==x);
		if(g)v[g].ch[son(g,p)]=x;
		v[x].fa=g,add_son(p,d,v[x].ch[!d]),add_son(x,!d,p);
		push_up(p),push_up(x);
	}
	void pre_push_down(int x) {
		if(!isroot(x))pre_push_down(v[x].fa);
		push_down(x);
	}
	void splay(int x) {
		pre_push_down(x);
		while(!isroot(x)) {
			int p=v[x].fa,g=v[p].fa;
			if(!isroot(p))rot(p==v[g].ch[0]^x==v[p].ch[0]?x:p);
			rot(x);
		}
		push_up(x);
	}
	void local_splay(int x,int d) {
		int goal=v[x].fa;
		push_down(x);
		while(v[x].ch[d])x=v[x].ch[d],push_down(x);
		while(!isroot(x)&&v[x].fa!=goal)rot(x);push_up(x);
	}
	void erase(int x){v[sta[++sta[0]]=x]=node();}
	int new_node(){return sta[0]?sta[sta[0]--]:++tot;}
	void ins(int x,int y){
		if(!y)return;
		int t=new_node();
		add_son(t,0,v[x].ch[2|v[y].prec]),add_son(t,2,y);
		push_up(t),v[x].ch[1]=0,add_son(x,2|v[y].prec,t),push_up(x);
	}
	void del(int x,int y){
		if(!y)return;
		splay(v[y].fa);int t=v[x].ch[2|v[y].prec];
		push_down(t),add_son(x,1,v[t].ch[2]);
		if(v[t].ch[0])local_splay(v[t].ch[0],1),add_son(v[t].ch[0],1,v[t].ch[1]),v[x].ch[2|v[y].prec]=v[t].ch[0];
		else push_down(v[t].ch[1]),v[x].ch[2|v[y].prec]=v[t].ch[1];
		erase(t),t=v[x].ch[2|v[y].prec],v[t].fa=x,push_up(t);
	}
	int access(int x){
		int y=x,ret=x,stot=0;
		static int s[200005];
		splay(s[++stot]=x),x=v[x].fa;
		for(;x;y=x,x=v[x].fa)
			splay(x),s[++stot]=x=v[x].fa,splay(x),push_up(ret=x);
		
		for(int i=stot;i>=1;i--){
			ins(s[i],v[s[i]].ch[1]),del(s[i],s[i-1]),push_up(s[i]),s[i-1]?splay(s[i-1]):void();
		}
		return ret;
	}
	void link(int x,int y){
		if(!y)return;
		access(x),splay(x),splay(y),add_son(x,1,y),push_up(x);
	}
	long long out(){
		long long res=0;
		for(int i=1;i<=tot;i++)
			for(int j=1;j<=tot;j++)
				push_down(j);
		
		for(int i=1;i<=2*n-1;i++)
//			cout<<T::v[i].val<<"*"<<T::v[i].laz<<" ",
			res+=T::v[i].val*T::v[i].laz;
//		cout<<"\n";
		return res;
	}
	long long out1(){
		long long res=0;
		for(int i=1;i<=tot;i++)
			for(int j=1;j<=tot;j++)
				pre_push_down(j);
		
		for(int i=1;i<=2*n-1;i++)
			cout<<T::v[i].val<<"*"<<T::v[i].laz<<"\n",
			res+=T::v[i].val*T::v[i].laz;
		cout<<"\n";
		return res;
	}
}
int l[200005],r[200005],p[200005];
map<int,int> mp[200005];
set<int> lset[200005],rset[200005];
int main() {
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=getint(),m=getint(),q=getint(),T::tot=2*n-1,N=2*n-1;
	for(int i=1;i<=(n<<1)-1;i++){
		int ls=getint(),rs=getint();
		T::v[ls].c=0,T::v[rs].c=1,T::access(i),T::v[i].val=getint(),T::push_up(i),p[ls]=i,p[rs]=i;
		l[i]=getint(),r[i]=getint(),T::link(i,ls),T::link(i,rs);
		mp[l[i]][r[i]]=i,lset[l[i]].insert(r[i]),rset[r[i]].insert(l[i]);
	}
	for(int i=1;i<=m;i++){
		int L=getint(),R=getint();
		long long tag=getint();
		int lnode = mp[L][*--lset[L].upper_bound(R)];
		int rnode = mp[*  rset[R].lower_bound(L)][R];
		
		if(lnode == rnode){
			if(lnode == 1)T::access(1),T::v[1].laz+=tag,T::push_up(1);
			else T::access(p[lnode]),T::splay(p[lnode]),T::push_ctag(p[lnode]),T::push_down(p[lnode]),T::push_pretag(T::v[p[lnode]].ch[2|T::v[lnode].c],tag),T::push_up(p[lnode]);
		}else{
			
			int lca=(T::access(lnode),T::access(rnode));
			long long ltag[2]={0, tag}, rtag[2]={tag, 0}, iltag[2]={0, -tag}, irtag[2]={-tag, 0};
			if(T::v[lnode].c==0)T::access(lnode),T::splay(lnode),T::v[lnode].laz+=tag,T::push_up(lnode);
			if(T::v[rnode].c==1)T::access(rnode),T::splay(rnode),T::v[rnode].laz+=tag,T::push_up(rnode);
			lnode=p[lnode], rnode=p[rnode];

//			if(i==44)T::access(98),T::splay(98),cerr<<T::v[T::v[98].ch[0]].slaz<<"\n";
						
			T::access(lnode),T::splay(lnode),T::push_ctag(lnode),T::push_pretagtag(lnode,ltag),T::access(lca),T::splay(lca),T::push_pretagtag(lca,iltag);
			T::access(rnode),T::splay(rnode),T::push_ctag(rnode),T::push_pretagtag(rnode,rtag),T::access(lca),T::splay(lca),T::push_pretagtag(lca,irtag);
		}
//		cout<<T::out()<<"\n";
//		T::out();
//		if(i==44)cout<<T::out()<<"\n",exit(233);
		T::splay(1),wrt(T::v[1].ans),pc('\n');
		
	}
	fwrite(wb,1,p2,stdout);
	return Loli Kon;
}
