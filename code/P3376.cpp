#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int maxn=201;
const int maxm=2*5001;

struct Tedge
{
	int to;
	int nxt;
	long long w;
}g[maxm];

int n,m,s,t;
int h[maxn],d[maxn],cur[maxn];

void vAdd(int i,int u,int v,long long w)
{
	g[i].to=v;
	g[i].w=w;
	g[i].nxt=h[u];
	h[u]=i;
}

void bfs()
{
	int now,nxt,i;
	queue<int>q;
	memset(d,0,sizeof d);
	d[s]=1;
	q.push(s);
	while(!q.empty())
	{
		now=q.front();
		q.pop();
		//printf("%d:",now);
		for(i=h[now];i!=-1;i=g[i].nxt)
		{
			nxt=g[i].to;
			//printf(" %d",nxt);
			if(g[i].w>0&&d[nxt]==0)
			{
				d[nxt]=d[now]+1;
				q.push(nxt);
			}
		}
		//printf("\n");
	}
}

long long dfs(int id,long long now)
{
	if(id==t) return now;
	long long nRet=0,tmp;
	int &i=cur[id],nxt;
	for(;i!=-1;i=g[i].nxt)
	{
		nxt=g[i].to;
		if(d[nxt]==d[id]+1&&g[i].w>0)
		{
			tmp=dfs(nxt,min(now-nRet,g[i].w));
			if(tmp>0)
			{
				g[i].w-=tmp;
				g[i^1].w+=tmp;
				nRet+=tmp;
				if(nRet==now) break;
			}
		}
	}
	return nRet;
}

long long dinic()
{
	int i;
	long long nRet=0;
	while(1)
	{
		bfs();
		//for(i=1;i<=n;i++) printf("%d ",d[i]);
		//printf("\n");
		if(d[t]==0) return nRet;
		for(i=1;i<=n;i++) cur[i]=h[i];
		nRet+=dfs(s,1LL<<60);
		//printf("%lld\n",nRet);
	}
}

int main()
{
	int i,u,v;
	long long w;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=0;i<m*2;i++) g[i].nxt=-1;
	for(i=1;i<=n;i++) h[i]=-1;
	for(i=0;i<m*2;i+=2)
	{
		scanf("%d%d%lld",&u,&v,&w);
		vAdd(i,u,v,w);
		vAdd(i+1,v,u,0);
	}
	printf("%lld\n",dinic());
	return 0;
}
