#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int maxn=5001;
const int maxm=2*50001;

struct Tedge
{
	int to;
	int nxt;
	int w;
	int f;
}g[maxm];

int n,m,s,t,nAns,nAnsf;
int h[maxn],d[maxn];
bool inq[maxn],vis[maxn]; 

void vAdd(int i,int u,int v,int w,int f)
{
	g[i].to=v;
	g[i].w=w;
	g[i].f=f;
	g[i].nxt=h[u];
	h[u]=i;
}

void spfa()
{
	int now,nxt,i;
	queue<int>q;
	memset(inq,false,sizeof inq);
	for(i=1;i<=n;i++) d[i]=1<<30;
	q.push(s);
	d[s]=0;
	inq[s]=true;
	while(!q.empty())
	{
		now=q.front();
		q.pop();
		inq[now]=false;
		for(i=h[now];i!=-1;i=g[i].nxt)
		{
			nxt=g[i].to;
			if(g[i].w>0&&d[nxt]>d[now]+g[i].f)
			{
				d[nxt]=d[now]+g[i].f;
				if(!inq[nxt])
				{
					inq[nxt]=true;
					q.push(nxt);
				}
			}
		}
	}
}

int dfs(int id,int now)
{
	if(id==t) return now;
	vis[id]=true;
	int i,nxt,nRet=0,tmp;
	for(i=h[id];i!=-1;i=g[i].nxt)
	{
		nxt=g[i].to;
		if(d[nxt]==d[id]+g[i].f&&g[i].w>0&&!vis[nxt])
		{
			tmp=dfs(nxt,min(now-nRet,g[i].w));
			if(tmp>0)
			{
				g[i].w-=tmp;
				g[i^1].w+=tmp;
				nRet+=tmp;
				nAnsf+=tmp*g[i].f;
				if(nRet==now) break;
			}
		}
	}
	return nRet;
}

int main()
{
	int i,u,v,w,f;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=0;i<m*2;i++) g[i].nxt=-1;
	for(i=1;i<=n;i++) h[i]=-1;
	for(i=0;i<m*2;i+=2)
	{
		scanf("%d%d%d%d",&u,&v,&w,&f);
		vAdd(i,u,v,w,f);
		vAdd(i+1,v,u,0,-f);
	}
	while(1)
	{
		spfa();
		if(d[t]==1<<30) break;
		memset(vis,false,sizeof vis);
		nAns+=dfs(s,1<<30);
	}
	printf("%d %d\n",nAns,nAnsf);
	return 0;
}
