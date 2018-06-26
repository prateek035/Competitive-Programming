//AcFreak

#include<bits/stdc++.h>
#define lint long long int 
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define endl '\n'
#define pii pair<int,int >
using namespace std;

#define MAXN  10000001

//smallest prime factor
int spf[MAXN];

void sieve()
{
	for(int i=1;i<MAXN;i++)
		spf[i]=i;

	for(int i=4;i<MAXN;i+=2)
	spf[i]=2;

	for(int i=3;i*i<MAXN;i+=2)
	{
		if(spf[i]==i)
		{
			for(int j=i*2;j<MAXN;j+=i)
			{
				if(spf[j]==j)
					spf[j]=i;
			}
		}
	}
}

vector<int > getFactorisation(int x)
{
	vector<int >ans;
	while(x!=1)
	{
		ans.pb(spf[x]);
		x/=spf[x];
	}
	return ans;
}
int main()
{
    sieve();

    int x;
    cin>>x;

    vector<int >p= getFactorisation(x);

    for(int i=0;i<p.size();i++)
    	cout<<p[i]<<" ";
    cout<<endl;
    
    return 0;
}