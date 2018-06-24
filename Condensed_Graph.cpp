//AcFreak


//Belw code is solution to the problem CF Round #490 div-3
// Implement using condensed Graph technique
//Along with Strongly Connected Component..

#include<bits/stdc++.h>
#define lint long long int 
#define mp make_pair
#define pb push_back
#define pii pair<int,int >
#define plii pair<lint,lint >
using namespace std;

//g->original graph.........cg->condensed graph
//_g->transposed graph

vector<lint >g[5005],cg[5005],_g[5005];

vector<lint >order,component(5005);
vector<bool>visited(5005);
void dfs1(lint src)
{
    visited[src]=true;
    for(lint i=0;i<g[src].size();i++)
    {
        if(!visited[g[src][i]])
            dfs1(g[src][i]);
    }
    order.pb(src);

}
void dfs2(lint src,lint val)
{
     visited[src]=true;
    for(lint i=0;i<_g[src].size();i++)
    {
        if(!visited[_g[src][i]])
            dfs2(_g[src][i],val);
    }
    component[src]=val;
}
void dfs3(lint src)
{
    visited[src]=true;
    for(lint i=0;i<cg[src].size();i++)
    {
        if(!visited[cg[src][i]])
            dfs3(cg[src][i]);
    }
}

int main()
{
    lint n,m,s;
    cin>>n>>m>>s;
    s--;

    vector<plii>Edges(m);

    lint i,j;
    for(i=0;i<m;i++)
    {
        lint a,b;
        cin>>a>>b;
        a--;b--;
        Edges[i].first=a;Edges[i].second=b;

        g[a].pb(b);
        _g[b].pb(a);
    }
    visited.assign(n,false);
    for(i=0;i<n;i++)
    {
        if(!visited[i])
            dfs1(i);
    }
    

     visited.assign(n,false);
     lint temp=0;
     for(i=n-1;i>=0;i--)
     {
           lint vt=order[i];
        if(!visited[vt])
        {
            dfs2(vt,temp);
            temp++;
        }
       
     }
     
    /* 
     for(i=0;i<n;i++)
     cout<<component[i]<<" ";
     cout<<endl;
     */
     
     s=component[s];

     for(i=0;i<m;i++)
     {
        lint a,b;
        a=component[Edges[i].first];
        b=component[Edges[i].second];

        if(a!=b)
            cg[a].pb(b);
     }
     
    /* 
     for(i=0;i<temp;i++)
     {
           for(j=0;j<cg[i].size();j++)
           cout<<cg[i][j]<<"  ";
           cout<<"ends here"<<endl;
           cout<<endl;
     }
     */
     
     

     lint count=0;
    visited.assign(n,false);
    dfs3(s);
    for(i=0;i<temp;i++)
        {
            if(!visited[i])
            {
                count++;
                dfs3(i);
            }
        }

        cout<<count<<endl;



    return 0;
}