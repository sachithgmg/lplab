#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
void keyw(char *p);
int i=0,id=0,kw=0,num=0,op=0;
char keys[34][10] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern",
                      "float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch",
					  "typedef","union","unsigned","void","volatile","while","printf","scanf"};
	

int main()
{
	char seps[15]= "\t\n;,(){}[]#\"<>"; 
	char oper[]="/%+-*=!&|^~<>.?";
	int j;
	j=0;
	char ch,str[25];
	char fname[50];
	FILE *f1;
	printf("\nfile name  :");
	scanf("%s",fname);
	f1=fopen(fname,"r");
	if(f1==NULL)
	{
		printf("file not found\n");
		exit(0);
	}
	while((ch=fgetc(f1))!=EOF)
	{
		for(j=0;j<=14;j++)
		{
			if(ch==oper[j])
			{
				printf("%c is an operator\n",ch);
				op++;
				str[i]='\0';
				keyw(str);
			}
		}
		for(j=0;j<=14;j++)
		{
			if(i==-1)
			break;
			if(ch==seps[j])
			{
				if(ch=='#')
				{
					while(ch!='>')
					{
						printf("%c",ch);
						ch = fgetc(f1);
					}
					printf("%c is a header file\n",ch);
					i = -1;
					break;
				}
				if(ch =='"')
				{
					do
					{
						ch = fgetc(f1);
						printf("%c ",ch);
					}while(ch!='"');
					printf("%c is an argument\n",ch);
					i = -1;
					break;
				}
				str[i]='\0';
				keyw(str);
				
		    }
		}
		if(ch==' ')
		{
			str[i++]='\0';
			keyw(str);
		}
		if(i != -1)
		{
			str[i]=ch;
			i++;
		}		
		else i=0;
	}
	printf("keywords: %d\n identifiers: %d\n operators: %d\n Numbers: %d\n",kw,id,op,num);
}
	
void keyw(char *p)
{
	int k,flag=0;
	for(k=0;k<34;k++)
	{
		if(strcmp(keys[k],p)==0)
		{
			printf("%s is a keyword \n",p);
			kw++;
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		if(isdigit(p[0]))
		{
			printf("%s is a number \n",p);
			num++;
		}
		else
		{
			if(p[0]!=13&&p[0]!=10)
			{
				if(p[0]!='\0')
				{
					printf("%s is an identifier \n",p);
					id++;
					
				}
			}
		}
	}
	i = -1;
}
