#include<bits/stdc++.h>

using namespace std;

const int MAXS=5000005;		//sum of length of all the patterns
const int MAXC=26;			//assuming lowercase alphabet

int out[MAXS];

int f[MAXS];

int g[MAXS][MAXC];



int  buildmachine(vector<string >arr,int k)
{
	memset(out,0,sizeof(out));

	memset(g,-1,sizeof(g));

	int states=1;

	for(int i=0;i<k;i++)
	{
		string word=arr[i];

		int cstate=0;

		for(int j=0;j<word.size();j++)
		{
			int ch=word[j]-'a';

			if(g[cstate][ch]== -1)
				g[cstate][ch]=states++;

			cstate=g[cstate][ch];
		}

		out[cstate]|=(1<<i);
	}


	for(int ch=0; ch<MAXC; ++ch)
	{
		if(g[0][ch]==-1)
			g[0][ch]=0;
	}

	memset(f,-1,sizeof(f));

	queue<int >q;

	for(int ch=0;ch<MAXC;++ch)
	{
		if(g[0][ch]!=0)
		{
			f[g[0][ch]]=0;
			q.push(g[0][ch]);
		}
	}

	while(q.size())
	{
		int state=q.front();

		q.pop();

		for(int ch=0; ch<=MAXC; ++ch)
		{
			if(g[state][ch]!=-1)
			{
				int failure=f[state];
			

				while(g[failure][ch]==-1)
				{
					failure=f[failure];
				}
				failure=g[failure][ch];
				f[g[state][ch]]=failure;

				out[g[state][ch]] |=out[failure];

				q.push(g[state][ch]);
			}
		}
	}
	return states;
}

int findnextstate(int cstate,char nextinput)
{
	int answer=cstate;
	int ch=nextinput-'a';

	while(g[answer][ch]==-1)
		answer=f[answer];

	return g[answer][ch];
}

void searchwords(vector<string >arr,int k,string text)
{

	buildmachine(arr,k);

	int cstate=0;

	for(int i=0;i<text.length();++i)
	{
		cstate=findnextstate(cstate,text[i]);

		if(out[cstate]==0)
			continue;

		for(int j=0;j<k;j++)
		{
			if(out[cstate] & (1<<j))
				cout<<" word "<<arr[j]<<" appear from "<<i-arr[j].size()+1<<" to "<<i<<endl;

		}
	}
}


int main()
{
	vector<string >arr;

	
		arr.push_back("he");
		arr.push_back("she");
		arr.push_back("hers");
		arr.push_back("his");

		string text="ahishers";

		
		int k=arr.size();
	//	cout<<k<<endl;
		searchwords(arr,k,text);
	return 0;
}