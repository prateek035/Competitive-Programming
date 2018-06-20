#include<bits/stdc++.h>
#define lint long long int 
#define pb push_back
#define mp make_pair

using namespace std;

int n,m;
vector<int >adj[100005];
int val[100005];
//nxt store the tree traversal indx of the next node from parent node
//cnt variable store the total number of current chains
//chain[] store the chain index for the node i
//csz[] stores the chain size at node i
//top[] stores the topnode for the curr chain at node i
//t[] store the segmented tree
//num[] stores the euler path and node number 
//mx[] stores the maximum for a chain i


int nxt[100005],size[100005],parent[100005],chain[100005],num[100005],csz[100005];
int all,cnt=1,depth[100005],top[100005];

lint t[400005],mx[400005];

//here pr is the parent for the source node
void dfs(int src,int pr)
{
	parent[src]=pr;
	size[src]=1;

	for(int i=0;i<adj[src].size();i++)
	{
		int dest=adj[src][i];
		if(dest ==pr)
			continue;

		depth[dest]=depth[src]+1;

		dfs(dest,src);
		size[src] += size[dest];

		if(nxt[src] == -1 || size[dest] > size[nxt[src]])
		{
			nxt[src] = dest;
		}
	}
}

void hld(int src,int pr)
{
	chain[src]=cnt-1;
	num[src]=all++;

	if(!csz[cnt-1])
	{
		top[cnt-1]=src;
	}
	++csz[cnt -1];

	if(nxt[src]!=-1)
	{
		hld(nxt[src],src);
	}

	//for non special nodes...
	for(int i=0;i<adj[src].size();i++)
	{
		int dest=adj[src][i];

		if(dest==pr || dest==nxt[src])
			continue;

		++cnt;
		hld(dest,src);
	}

}

// akind of range min(max here ) query function...
lint go(int v,int tl,int tr,int l,int r)
{
	if(l> tr || r<tl)
	{
		return 0;
	}

	if(l<=tl && r>=tr)
	{
		return t[v];
	}

	int tm= (tl+tr) >>1;
	return max(go(v+v,tl,tm,l,r) ,go(v+v+1, tm+1 ,tr,l,r));
}
// crawl function here...
lint go(int a,int b)
{
	lint res=0;
	//first make the chains equal
	while(chain[a]!=chain[b])
	{
		if( depth[top[chain[a]]] < depth[top[chain[b]]] )
			swap(a,b);

		int start=top[chain[a]];

		if(num[a] == num[start]+csz[chain[a]] -1)
			res=max(res,mx[chain[a]]);
		else
			res=max(res,go(1,0,n-1,num[start],num[a]));

		a=parent[start];
	}
	//now making the depth same...
	if(depth[a]>depth[b])
		swap(a,b);

	res=max(res,go(1,0,n-1,num[a],num[b]));

	return res;
}

void upd(int v,int tl,int tr,int pos,int d)
{
	if(tl==tr)
	{
		t[v]+=d;
		return ;
	}
	int tm= (tl+tr) >>1;
	if(pos <=tm)
		upd(v+v ,tl,tm,pos,d);
	else
		upd(v+v+1,tm+1,tr,pos,d);

	t[v]=max(t[v+v],t[v+v+1]);
}

void modify(int a,int b)
{
	upd(1,0,n-1,num[a],b);

	int start=num[top[chain[a]]];
	int end=start  + csz[chain[a]] -1;
	mx[chain[a]]=go(1,0,n-1,start,end);
}

int main()
{
	cin>>n;

	for(int i=0;i<n-1;i++)
	{
		int a,b;
		cin>>a>>b;
		a--;b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	memset(nxt,-1,sizeof(nxt));
	//updating the parent information and depth information...
	dfs(0,-1);
	hld(0,-1);

	cin>>m;
	for(int i=0;i<m;i++)
	{
		char ch;
		cin>>ch;

		if(ch=='G')
		{
			int a,b;
			cin>>a>>b;
			a--;b--;
			cout<<go(a,b)<<endl;
		}
		else
		{
			int a,b;
			cin>>a>>b;
			a--;
			modify(a,b);
		}
	}
	return 0;
}