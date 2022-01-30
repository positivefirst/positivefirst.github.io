#include<bits/stdc++.h>
using namespace std;

const int maxn=100010;

struct Tedge
{
	int t,nxt;
}g[maxn*2];

int cnt=0,n;
int h[maxn],f[maxn],d[maxn],sz[maxn],son[maxn],nid[maxn],top[maxn];

void vEdge(int i,int f,int t)
{
	g[i].t=t;
	g[i].nxt=h[f];
	h[f]=i;
}

void dfs1(int id,int fa)
{
	int i,to;
	f[id]=fa;
	d[id]=d[fa]+1;
	sz[id]=1;
	for(i=h[id];i;i=g[i].nxt)
	{
		to=g[i].t;
		if(to==fa) continue;
		dfs1(to,id);
		sz[id]+=sz[to];
		if(sz[to]>sz[son[id]]) son[id]=to;
	}
}

void dfs2(int id,int t)
{
	nid[id]=++cnt;
	top[id]=t;
	if(son[id])
	{
		int i,to;
		dfs2(son[id],t);
		for(i=h[id];i;i=g[i].nxt)
		{
			to=g[i].t;
			if(to!=f[id]&&to!=son[id]) dfs2(to,to);
		}
	}
}
//////////////////////////////////////////
struct node
{
	int l,r,len,sum,all;
}t[maxn*2];

void vBuild(node &rt,int l,int r)
{
	rt.all=-1;
	rt.len=r-l+1;
	if(l==r) return;
	int mid=(l+r)/2;
	vBuild(t[rt.l=++cnt],l,mid);
	vBuild(t[rt.r=++cnt],mid+1,r);
	rt.sum=t[rt.l].sum+t[rt.r].sum;
}

void vPushDown(node &rt)
{
	node &l=t[rt.l],&r=t[rt.r];
	if(rt.all!=-1)
	{
		l.all=r.all=rt.all;
		l.sum=l.all*l.len;
		r.sum=r.all*r.len;
		rt.all=-1;
	}
}

void vCover(node &rt,int l,int r,int L,int R,int val)
{
	if(l==L&&r==R)
	{
		rt.all=val;
		rt.sum=val*rt.len;
		return;
	}
	vPushDown(rt);
	int mid=(l+r)/2;
	if(R<=mid) vCover(t[rt.l],l,mid,L,R,val);
	else if(L>mid) vCover(t[rt.r],mid+1,r,L,R,val);
	else vCover(t[rt.l],l,mid,L,mid,val),vCover(t[rt.r],mid+1,r,mid+1,R,val);
	rt.sum=t[rt.l].sum+t[rt.r].sum;
}

int nQuery(node &rt,int l,int r,int L,int R)
{
	if(l==L&&r==R) return rt.sum;
	vPushDown(rt);
	int mid=(l+r)/2;
	if(R<=mid) return nQuery(t[rt.l],l,mid,L,R);
	if(L>mid) return nQuery(t[rt.r],mid+1,r,L,R);
	return nQuery(t[rt.l],l,mid,L,mid)+nQuery(t[rt.r],mid+1,r,mid+1,R);
}
////////////////////////////////////////
void vCoverTree(int x,int y,int val)
{
	int tx=top[x],ty=top[y];
	while(tx!=ty)
	{
		if(d[tx]<d[ty]) swap(x,y),swap(tx,ty);
		vCover(t[1],1,n,nid[tx],nid[x],val);
		x=f[tx];
		tx=top[x];
	}
	if(nid[x]>nid[y]) swap(x,y);
	vCover(t[1],1,n,nid[x],nid[y],val);
}

int nQueryTree(int x,int y)
{
	int tx=top[x],ty=top[y],ret=0;
	while(tx!=ty)
	{
		if(d[tx]<d[ty]) swap(x,y),swap(tx,ty);
		ret+=nQuery(t[1],1,n,nid[tx],nid[x]);
		x=f[tx];
		tx=top[x];
	}
	if(nid[x]>nid[y]) swap(x,y);
	return ret+nQuery(t[1],1,n,nid[x],nid[y]);
}

int main()
{
	int i,m,u;
	char opt[15];
	scanf("%d",&n);
	for(i=2;i<=n;i++)
	{
		scanf("%d",&u);
		vEdge(i*2-1,i,u+1);
		vEdge(i*2,u+1,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	cnt=1;
	vBuild(t[1],1,n);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s%d",opt,&u);
		u++;
		if(opt[0]=='i')
		{
			printf("%d\n",d[u]-nQueryTree(1,u));
			vCoverTree(1,u,1);
		}
		else
		{
			printf("%d\n",nQuery(t[1],1,n,nid[u],nid[u]+sz[u]-1));
			vCover(t[1],1,n,nid[u],nid[u]+sz[u]-1,0);
		}
	}
	return 0;
}
