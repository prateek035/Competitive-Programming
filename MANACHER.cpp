
//LPS is the longest pallindromic subsequence...
//lps[i] stores the longest pallindromic subsequence at index i
#include<bits/stdc++.h>

using namespace std;
int lps[100005];

void LPS(string name)
{
	int n=name.length();

	if(n==0)
		return;

	n=2*n+1;
	lps[0]=0;
	lps[1]=1;

	int center=1;	//center position
	int centerR=2;	//center right position
	int i=0;			//current right position
	int iMirror;		//current left position
	int expand=-1;
	int diff=-1;
	int maxLPS=0;
	int maxlpsCenter=0;
	int start=-1;
	int end=-1;

	for(i=2;i<n;i++)
	{
		iMirror=2*center-i;
		expand=0;
		diff=centerR-i;

		if(diff>0)
		{
			if(lps[iMirror]<diff)
			{
				lps[i]=lps[iMirror];	//case1
			}
			else if(lps[iMirror]==diff && i==n-1)
			{
				lps[i]=lps[iMirror];	//case2
			}
			else if(lps[iMirror]==diff && i<n-1)
			{
				lps[i]=lps[iMirror];	//case3
				expand=1;			//expansion needed
			}
			else if(lps[iMirror]>diff)
			{
				lps[i]=diff;
				expand=1;		//expansion needed
			}
		}
		else
		{
			lps[i]=0;
			expand=1;		//expansion needed
		}

		if(expand==1)
		{
			while(((i+lps[i]) <n && (i-lps[i]) >0 )&&( ((i+lps[i]+1) %2 ==0) || (name[(i+lps[i] +1)/2]==name[(i-lps[i] -1)/2])))
			{
				lps[i]++;
			}
		}

		if(lps[i]>maxLPS)
		{
			maxLPS=lps[i];
			maxlpsCenter=i;
		}

		if(i+lps[i]> centerR)
		{
			center=i;
			centerR=i+lps[i];
		}
	}
	start=(maxlpsCenter-maxLPS)/2;
	end=start+maxLPS -1;

	cout<<"LPS of string " <<name<<"  "<<endl;
	for(i=start;i<=end;i++)
		cout<<name[i];
	cout<<endl;
}

int main()
{
	string name;
	cin>>name;

	LPS(name);

	return 0;
}