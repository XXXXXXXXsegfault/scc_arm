#include "../include/lib.c"
int fdi,fdo,fde;
unsigned int current_line;
void error(int line,char *msg)
{
	char *str;
	str=xstrdup("line ");
	str=str_i_app(str,line);
	str=str_s_app(str,": error: ");
	str=str_s_app(str,msg);
	str=str_c_app(str,'\n');
	write(2,str,strlen(str));
	exit(2);
}
int name_hash(char *str)
{
	unsigned int hash;
	hash=0;
	while(*str)
	{
		hash=(hash<<11|hash>>21)+*str;
		++str;
	}
	return hash%1021;
}
int readc(void)
{
	static unsigned char buf[65536];
	static int x,n;
	int n1,c;
	if(x==n)
	{
		n1=read(fdi,buf,65536);
		if(n1<=0)
		{
			return -1;
		}
		n=n1;
		x=0;
	}
	c=buf[x];
	++x;
	return c;
}
char *read_line(void)
{
	char *str;
	int c;
	str=0;
	while((c=readc())!=-1)
	{
		if(c=='\n')
		{
			if(str==0)
			{
				str=xstrdup(" ");
			}
			break;
		}
		str=str_c_app(str,c);
	}
	++current_line;
	return str;
}
#include "load_file.c"
#include "read_word.c"
struct line *l;
int stage;
unsigned int pc;
unsigned int entry;
#define data_addr 0x2000000
unsigned int data_size;
#include "label.c"
#include "ins/ins.c"
#include "elf.c"
#include "pseudo_op.c"

int main(int argc,char **argv)
{
	char *str;
	struct ins *node;
	struct label *lb;
	int s;
	unsigned int old_size;
	if(argc<3)
	{
		return 1;
	}
	fde=-1;
	if(argc>=4)
	{
		fde=open(argv[3],578,0644);
	}
	fdi=open(argv[1],0,0);
	if(fdi<0)
	{
		return 1;
	}
	fdo=open(argv[2],578,0755);
	if(fdo<0)
	{
		return 1;
	}
	load_file();
	ins_init();
	l=lines_head;
	entry=0x10074;
	pc=0x10074;
	while(l)
	{
		if(l->str[0]=='@')
		{
			label_tab_add(l->str+1);
			l->needs_recompile=1;
		}
		else if(l->str[0]=='.')
		{
			parse_pseudo_op(l->str+1);
		}
		else
		{
			do_translate();
		}
		l=l->next;
	}
	stage=1;
	do
	{
		s=0;
		l=lines_head;
		pc=0x10074;
		while(l)
		{
			if(l->needs_recompile)
			{
				old_size=l->ins_len;
				free(l->ins_buf);
				l->ins_buf=NULL;
				l->ins_len=0;
				if(l->str[0]=='@')
				{
					lb=label_tab_find(l->str+1);
					if(lb)
					{
						if(lb->value!=pc)
						{
							s=1;
						}
						lb->value=pc;
					}
				}
				else if(l->str[0]=='.')
				{
					parse_pseudo_op(l->str+1);
				}
				else
				{
					do_translate();
				}
				if(l->ins_len!=old_size)
				{
					s=1;
				}
			}
			else
			{
				pc+=l->ins_len;
			}
			l=l->next;
		}
	}
	while(s);
	mkelf();
	return 0;
}
