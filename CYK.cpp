#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<algorithm>
#include<cassert>
using namespace std;
#define max 100
string grammar[max][max];
string dpr[max];
int p,np;

inline int lchomsky(string s)
{
	if(s.length()==1 && s[0]>='A'&& s[0]<='Z')
	return 1;
	else return 0;
}
inline int rchomsky(string s)
{
	if(s.length()==1 && s[0]>='a' && s[0]<='z')
	return 1;
	if(s.length()==2 && s[0]>='A' && s[0]<='Z' && s[1]>='A' && s[1]<='Z')
	return 1;
	return 0;
}
inline void break_grammar(string s)
{
	int i;
	p=0;
	while(s.length())
	{
		i=s.find("|");
		if(i>s.length())
		{
			dpr[p++]=s;
			s="";
		}
		else
		{
			dpr[p++]=s.substr(0,i);
			s=s.substr(i+1,s.length());
		}
	}
}
inline string concat(string a,string b)
{
	int i;
	string r=a;
	for(i=0;i<b.length();i++)
	if(r.find(b[i])>r.length())
	r+=b[i];
	return (r);
}
inline string search_prod(string p)
{
	int j,k;
	string r="";
	for(j=0;j<np;j++)
	{
		k=1;
		while(grammar[j][k]!="")
		{
			if(grammar[j][k]==p)
			{
				r=concat(r,grammar[j][0]);
			}
			k++;
		}
	}
	return r;
}
inline string gen_combo(string a,string b)
{
	int i,j;
	string pri=a,re="";
	for(i=0;i<a.length();i++)
	{
		for(j=0;j<b.length();j++)
		{
			pri="";
			pri=pri+a[i]+b[j];
			re=re+search_prod(pri);
		}
	}
	return re;
}
int main()
{
	string str,start,r,st,pr;
	int pt,i,j,k,l;
	cout<<"Enter the start symbol ";
	cin>>start;
	cout<<"Enter the number of production ";
	cin>>np;
	for(i=0;i<np;i++)
	{
		cin>>str;
		pt=str.find("->");
		grammar[i][0]=str.substr(0,pt);
		
		if(!lchomsky(grammar[i][0]))
		{
			cout<<"The grammar is not in CNF \n";
			return -1;
		}
		str=str.substr(pt+2,str.length());
		break_grammar(str);
		for(int j=0;j<p;j++)
		{
			grammar[i][j+1]=dpr[j];
			if(!rchomsky(dpr[j]))
			{
				cout<<"The grammar is not in CNF \n";
				return -1;
			}
		}
	}
	string matrix[max][max],s;
	cout<<"Enter string to be checked ";
	cin>>st;
	for(i=0;i<st.length();i++)
	{
		r="";
		s="";
		s=s+st[i];
		for(j=0;j<np;j++)
		{
			k=1;
			while(grammar[j][k]!="")
			{
				if(grammar[j][k]==s)
				{
					r=concat(r,grammar[j][0]);
				}
				k++;
			}
		}
	
		matrix[i][i]=r;
	}
	int m,n;
	for(k=1;k<st.length();k++)
	{
		for(j=k;j<st.length();j++)
		{
			r="";
			for(l=j-k;l<j;l++)
			{
				pr=gen_combo(matrix[j-k][l],matrix[l+1][j]);
				r=concat(r,pr);
			}
			matrix[j-k][j]=r;
		}
	}
	for(i=0;i<st.length();i++)
	{
		k=0;
		l=str.length()-i-1;
		for(j=l;j<st.length();j++)
		{
			cout<<setw(3)<<matrix[k++][j]<<" ";
		}
		cout<<endl;
	}
	int f=0;
	for(i=0;i<start.length();i++)
	{
		if(matrix[0][st.length()-1].find(start[i])<=matrix[0][st.length()-1].length())
		{
			cout<<"String can be generated\n";
			return 0;
		}
		cout<<"String cant be generated\n";
		return 0;
		
	}
		}

