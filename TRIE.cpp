#include<bits/stdc++.h>

using namespace std;

struct trienode
{
	struct trienode* child [26];
	bool isEnd;
};


struct trienode *getnode()
{
	struct trienode *pnode=new trienode;

	pnode->isEnd=false;

	for(int i=0;i<26;i++)
		pnode->child[i]=NULL;

	return pnode;
}

void insert(struct trienode *root,string key)
{
	struct trienode *pnode= root;
	for(int i=0;i<key.length();i++)
	{
		int index=key[i]-'a';

		if(!pnode->child[index])
		{
			pnode->child[index]=getnode();
		}
			pnode=pnode->child[index];
		
	}
	pnode->isEnd=true;
}

bool search(struct trienode *root ,string key)
{
	struct trienode * pnode=root;

	for(int i=0;i<key.length();i++)
	{
		int index=key[i]-'a';

		if(!pnode->child[index])
			return false;

		pnode=pnode->child[index];
	}
	return (pnode!=NULL && pnode->isEnd);
}

int main()
{
	string keys[]={"the","a","there","answer","any","by","bye","their"};

	int n=sizeof(keys)/sizeof(keys[0]);

	struct trienode *root=getnode();

	for(int i=0;i<n;i++)
	{
		insert(root,keys[i]);
	}

	if(search(root,"the"))
	{
		cout<<"the found\n";
	}
	else
		cout<<"not found :(";

	if(search(root,"these"))
	{
		cout<<"these found";
	}
	else
		cout<<"not found :(";

}