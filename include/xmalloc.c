void *xmalloc(unsigned int size)
{
	void *ptr;
	ptr=malloc(size);
	if(ptr==NULL)
	{
		write(2,"FATAL: cannot allocate memory\n",30);
		exit(2);
	}
	return ptr;
}
unsigned int __str_size(unsigned int size)
{
	unsigned int a;
	a=16;
	while(a<size)
	{
		a=a*5>>2;
	}
	return a;
}
char *xstrdup(char *str)
{
	unsigned int l;
	char *new_str;
	l=strlen(str);
	new_str=xmalloc(__str_size(l+1));
	memcpy(new_str,str,l+1);
	return new_str;
}

char *str_c_app(char *s,int c)
{
	char *new_str;
	unsigned int l,l1,l2;
	if(s==0)
	{
		new_str=xmalloc(16);
		new_str[0]=c;
		new_str[1]=0;
	}
	else
	{
		l=strlen(s);
		l1=__str_size(l+1);
		l2=__str_size(l+2);
		if(l1==l2)
		{
			new_str=s;
			new_str[l]=c;
			new_str[l+1]=0;
		}
		else
		{
			new_str=xmalloc(l2);
			memcpy(new_str,s,l);
			new_str[l]=c;
			new_str[l+1]=0;
			free(s);
		}
	}
	return new_str;
}
char *str_c_app2(char *s,int off,int c)
{
	char *new_str;
	int l,l1,l2;
	if(s==0)
	{
		new_str=xmalloc(16);
		new_str[0]=c;
		new_str[1]=0;
	}
	else
	{
		l=strlen(s+off)+off;
		l1=__str_size(l+1);
		l2=__str_size(l+2);
		if(l1==l2)
		{
			new_str=s;
			new_str[l]=c;
			new_str[l+1]=0;
		}
		else
		{
			new_str=xmalloc(l2);
			memcpy(new_str,s,l);
			new_str[l]=c;
			new_str[l+1]=0;
			free(s);
		}
	}
	return new_str;
}
char *str_s_app(char *s,char *s2)
{
	while(*s2)
	{
		s=str_c_app(s,*s2);
		s2=s2+1;
	}
	return s;
}
char *str_i_app(char *s,unsigned int n)
{
	unsigned int a;
	a=1000000000;
	int c;
	if(n==0)
	{
		return str_c_app(s,'0');
	}
	while(a>n)
	{
		a/=10;
	}
	while(a)
	{
		c=n/a;
		n%=a;
		a/=10;
		s=str_c_app(s,c+'0');
	}
	return s;
}
