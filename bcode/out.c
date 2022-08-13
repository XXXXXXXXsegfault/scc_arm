char outc_buf[65536];
int outc_x;
void outc(char c)
{
	int n;
	if(outc_x==65536)
	{
		write(fdo,outc_buf,outc_x);
		outc_x=0;
	}
	outc_buf[outc_x]=c;
	++outc_x;
}
void out_flush(void)
{
	if(outc_x)
	{
		write(fdo,outc_buf,outc_x);
	}
}
void outs(char *str)
{
	while(*str)
	{
		outc(*str);
		++str;
	}
}
void outs2(char *str)
{
	if(!*str)
	{
		return;
	}
	while(str[1])
	{
		outc(*str);
		++str;
	}
}
void out_label(char *label)
{
	outs("@");
	outs(label);
	outs("\n");
}
void out_label_name(char *label)
{
	outs(label);
}
void out_reg(int reg)
{
	outc('r');
	if(reg<10)
	{
		outc('0'+reg);
	}
	else
	{
		outc('1');
		outc('0'+reg-10);
	}
}
void out_num32(unsigned int n)
{
	char *str;
	str=str_i_app(0,n);
	outs(str);
	free(str);
}
void out_num16(unsigned int n)
{
	out_num32(n&0xffff);
}
void out_num8(unsigned int n)
{
	out_num32(n&0xff);
}
void out_num(int class,unsigned int n)
{
	if(class==1||class==2)
	{
		out_num8(n);
	}
	else if(class==3||class==4)
	{
		out_num16(n);
	}
	else if(class==5||class==6)
	{
		out_num32(n);
	}
}
char *sgetc(char *str,char *ret)
{
	int x;
	if(str[0]=='\\')
	{
		if(str[1]=='\\')
		{
			*ret='\\';
			return str+2;
		}
		else if(str[1]=='n')
		{
			*ret='\n';
			return str+2;
		}
		else if(str[1]=='t')
		{
			*ret='\t';
			return str+2;
		}
		else if(str[1]=='v')
		{
			*ret='\v';
			return str+2;
		}
		else if(str[1]=='r')
		{
			*ret='\r';
			return str+2;
		}
		else if(str[1]=='\'')
		{
			*ret='\'';
			return str+2;
		}
		else if(str[1]=='\"')
		{
			*ret='\"';
			return str+2;
		}
		else if(str[1]=='\?')
		{
			*ret='\?';
			return str+2;
		}
		else if(str[1]>='0'&&str[1]<='7')
		{
			x=1;
			*ret=0;
			while(str[x]>='0'&&str[x]<='7')
			{
				*ret=(*ret<<3)+(str[x]-'0');
				++x;
			}
			return str+x;
		}
		else if(str[1]=='x')
		{
			x=2;
			*ret=0;
			while(1)
			{
				if(str[x]>='0'&&str[x]<='9')
				{
					*ret=*ret*16+(str[x]-'0');
				}
				else if(str[x]>='A'&&str[x]<='F')
				{
					*ret=*ret*16+(str[x]-'A'+10);
				}
				else if(str[x]>='a'&&str[x]<='f')
				{
					*ret=*ret*16+(str[x]-'a'+10);
				}
				else
				{
					break;
				}
				++x;
			}
			return str+x;
		}
		else
		{
			*ret='\\';
			return str+1;
		}
	}
	else
	{
		*ret=str[0];
		return str+1;
	}
}
void out_str(char *str)
{
	char c[2];
	c[1]=0;
	str=str+1;
	while(*str&&*str!='\"')
	{
		str=sgetc(str,c);
		outs(c);
	}
}
char *get_type(int class)
{
	if(class==1||class==2)
	{
		return "b";
	}
	if(class==3||class==4)
	{
		return "h";
	}
	return "\0";
}
void out_cond(char *cond)
{
	if(!cond)
	{
		return;
	}
	if(!strcmp(cond,"beq "))
	{
		outs("ne");
	}
	else if(!strcmp(cond,"bne "))
	{
		outs("eq");
	}
	else if(!strcmp(cond,"bcc "))
	{
		outs("cs");
	}
	else if(!strcmp(cond,"bcs "))
	{
		outs("cc");
	}
	else if(!strcmp(cond,"bls "))
	{
		outs("hi");
	}
	else if(!strcmp(cond,"bhi "))
	{
		outs("ls");
	}
	else if(!strcmp(cond,"bcs "))
	{
		outs("cc");
	}
	else if(!strcmp(cond,"ble "))
	{
		outs("gt");
	}
	else if(!strcmp(cond,"bge "))
	{
		outs("lt");
	}
	else if(!strcmp(cond,"bgt "))
	{
		outs("le");
	}
	else if(!strcmp(cond,"blt "))
	{
		outs("ge");
	}
}
