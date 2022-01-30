#include<bits/stdc++.h>
using namespace std;

const int maxn=200010;

char s[maxn],t[2000010];
int cnt,eid[maxn],fail[maxn],trie[maxn][26],nAns[maxn],fa[maxn],indeg[maxn],vis[maxn];

void vInsert(int id)
{
	int i,len=strlen(s+1),r=0;
	for(i=1;i<=len;i++)
	{
		int &nd=trie[r][s[i]-'a'];
		if(nd==0) nd=++cnt;
		r=nd;
	}
	if(!eid[r]) eid[r]=id;
	fa[id]=eid[r];
}

void vFail()
{
	int i,now;
	queue<int>q;
	for(i=0;i<26;i++) if(trie[0][i]) q.push(trie[0][i]);
	while(!q.empty())
	{
		now=q.front();
		q.pop();
		for(i=0;i<26;i++)
		{
			int &nxt=trie[now][i];
			if(nxt)
			{
				indeg[fail[nxt]=trie[fail[now]][i]]++;
				q.push(nxt);
			}
			else nxt=trie[fail[now]][i];
		}
	}
}

void vQuery()
{
	int i,j,len=strlen(t+1),rt=0;
	for(i=1;i<=len;i++) nAns[rt=trie[rt][t[i]-'a']]++;
}

int main()
{
	int i,n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		vInsert(i);
	}
	vFail();
	scanf("%s",t+1);
	vQuery();
	queue<int>q;
	for(i=0;i<=cnt;i++) if(!indeg[i]) q.push(i);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		vis[eid[now]]=nAns[now];
		int nxt=fail[now];
		indeg[nxt]--;
		nAns[nxt]+=nAns[now];
		if(!indeg[nxt]) q.push(nxt);
	}
	for(i=1;i<=n;i++) printf("%d\n",vis[fa[i]]);
	return 0;
}
