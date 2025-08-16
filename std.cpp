#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define int long long
#define N 1005
int n,m,hed[N],tal[N],wt[N],nxt[N],cnte,f[N][1<<10];
void de(int u,int v,int w) {tal[++cnte]=v,wt[cnte]=w,nxt[cnte]=hed[u],hed[u]=cnte;}
std::queue<std::pair<int,int> > q;
signed main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0),std::cout.tie(0);
	std::cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++) std::cin>>u>>v>>w,de(u,v,w);
	q.push({1,0});
	f[1][0]=1;
	while(!q.empty())
	{
		int u=q.front().first,t=q.front().second;
		q.pop();
		for(int i=hed[u];i;i=nxt[i]) if(!f[tal[i]][t^wt[i]]) f[tal[i]][t^wt[i]]=1,q.push({tal[i],t^wt[i]});
	}
	for(int i=0;i<(1<<10);i++) if(f[n][i]) return std::cout<<i,0;
	std::cout<<-1;
}