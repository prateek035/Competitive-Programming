//code here is writtten for kmp search algorithm
//lps is longest proper prefix which is also a suffix

#include<bits/stdc++.h>

using namespace std;


void computeLPS(string& pattern,int m,vector<int>& lps)
{
	int len=0;

	lps[0]=0;

	int i=1;
	while(i<m)
	{
		if(pattern[i]==pattern[len])
		{
			len++;
			lps[i]=len;
			i++;
		}
		else
		{
			if(len!=0)
			{
				len=lps[len-1];
			}
			else
			{
				lps[i]=0;
				i++;
			}
		}
	}
}


void KMPSearch(string& pattern,string& text)
{
	int m=pattern.size();
	int n=text.size();

	
	vector<int >lps(m);
	
	computeLPS(pattern,m,lps);

	int i=0,j=0;

	while(i<n)
	{
		if(pattern[j]==text[i])
		{
			i++;
			j++;
		}
		if(j==m)
		{
			cout<<"hurrah !! ,pattern found at "<<i-j<<endl;
			j=lps[j-1];
		}

		else if(i<n && pattern[j]!=text[i])
		{
			if(j!=0)
				j=lps[j-1];
			else
				i=i+1;
		}
	}
}



int main()
{
	string text="ababdabacdababcababababcabab";

	string pattern="ababcabab";

	KMPSearch(pattern,text);
	return 0;
}