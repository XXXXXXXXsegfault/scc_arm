struct ins
{
	char *format;
	char *encoding;
	struct ins *next;
} *ins[1021];
void ins_add(char *format,char *encoding)
{
	struct ins *node;
	char *str;
	int hash;
	node=xmalloc(sizeof(*node));
	node->format=format;
	node->encoding=encoding;
	str=read_word(&format);
	hash=name_hash(str);
	free(str);
	node->next=ins[hash];
	ins[hash]=node;
}
#include "format.c"
unsigned int ins_translate(char *input)
{
	struct ins_args args;
	struct ins *node;
	char *enc,*word;
	unsigned int ret;
	char *str;
	int hash;
	int x,l;
	str=skip_spaces(input);
	str=read_word(&str);
	hash=name_hash(str);
	x=0;
	while(x<2)
	{
		node=ins[hash];
		while(node)
		{
			if(!get_ins_args(input,node->format,&args))
			{
				if(enc=node->encoding)
				{
					ret=0;
					while(word=read_word(&enc))
					{
						if(!strcmp(word,"0"))
						{
							ret=ret<<1;
						}
						else if(!strcmp(word,"1"))
						{
							ret=ret<<1|1;
						}
						else if(!strcmp(word,"~"))
						{
							ret=ret<<4|args.cond;
						}
						else if(!strcmp(word,"R1"))
						{
							ret=ret<<4|args.regs[0];
						}
						else if(!strcmp(word,"R2"))
						{
							ret=ret<<4|args.regs[1];
						}
						else if(!strcmp(word,"R3"))
						{
							ret=ret<<4|args.regs[2];
						}
						else if(!strcmp(word,"R4"))
						{
							ret=ret<<4|args.regs[3];
						}
						else if(!strcmp(word,"I"))
						{
							ret=ret<<12|args.imm;
						}
						else if(!strcmp(word,"O"))
						{
							if(args.off<0x1000)
							{
								ret=ret<<12|args.off;
							}
						}
						else if(!strcmp(word,"M"))
						{
							ret=ret<<16|args.off;
						}
						else if(!strcmp(word,"D"))
						{
							ret=ret<<24|args.off;
						}
						else if(!strcmp(word,"Sh"))
						{
							ret=ret<<5|args.off&31;
						}
						else if(!strcmp(word,"O8"))
						{
							ret=ret<<4|args.off&0xf|args.off<<4&0xf00;
						}
						free(word);
					}
					free(str);
					return ret;
				}
			}
			node=node->next;
		}
		if((l=strlen(str))>3)
		{
			str[l-2]=0;
			hash=name_hash(str);
		}
		else
		{
			break;
		}
		++x;
	}
	free(str);
	return 0xffffffff;
}
#include "init.c"
void ins_write(void *buf,unsigned int size)
{
	unsigned char *new_ins;
	if(l->ins_len+size<=32)
	{
		memcpy(l->ins_buf2+l->ins_len,buf,size);
	}
	else if(l->ins_len<=32)
	{
		new_ins=xmalloc(l->ins_len+size);
		memcpy(new_ins,l->ins_buf2,l->ins_len);
		memcpy(new_ins+l->ins_len,buf,size);
		l->ins_buf=new_ins;
	}
	else
	{
		new_ins=xmalloc(l->ins_len+size);
		memcpy(new_ins,l->ins_buf,l->ins_len);
		free(l->ins_buf);
		memcpy(new_ins+l->ins_len,buf,size);
		l->ins_buf=new_ins;
	}
	l->ins_len+=size;
	pc+=size;
}
void ins_outc(int c)
{
	ins_write(&c,1);
}
unsigned int gen_movw(int reg,int val,int cond)
{
	unsigned int ret;
	ret=0;
	if(val>0xffff)
	{
		error(l->line,"constant out of range.");
	}
	ret=cond;
	ret=ret<<8|0x30;
	ret=ret<<4|val>>12;
	ret=ret<<4|reg;
	ret=ret<<12|val&0xfff;
	return ret;
}
unsigned int gen_movt(int reg,int val,int cond)
{
	unsigned int ret;
	ret=0;
	if(val>0xffff)
	{
		error(l->line,"constant out of range.");
	}
	ret=cond;
	ret=ret<<8|0x34;
	ret=ret<<4|val>>12;
	ret=ret<<4|reg;
	ret=ret<<12|val&0xfff;
	return ret;
}
void do_translate(void)
{
	unsigned int val,val2;
	struct ins_args args;
	if(!get_ins_args(l->str,"b~ C",&args))
	{
		val=(int)args.off-(int)pc>>2;
		val=val-2;
		if(val>0x7fffff&&val<0xff800000)
		{
			error(l->line,"branch out of range.");
		}
		val=val&0xffffff|0xa000000;
		val|=args.cond<<28;
		ins_write(&val,4);
		l->needs_recompile=1;
		return;
	}
	if(!get_ins_args(l->str,"bl~ C",&args))
	{
		val=(int)args.off-(int)pc>>2;
		val=val-2;
		if(val>0x7fffff&&val<0xff800000)
		{
			error(l->line,"branch out of range.");
		}
		val=val&0xffffff|0xb000000;
		val|=args.cond<<28;
		ins_write(&val,4);
		l->needs_recompile=1;
		return;
	}
	val=ins_translate(l->str);
	if(val!=0xffffffff)
	{
		ins_write(&val,4);
		return;
	}
	if(!get_ins_args(l->str,"movw~ R1,#C",&args))
	{
		val=gen_movw(args.regs[0],args.off,args.cond);
		ins_write(&val,4);
		return;
	}
	if(!get_ins_args(l->str,"movt~ R1,#C",&args))
	{
		val=gen_movt(args.regs[0],args.off,args.cond);
		ins_write(&val,4);
		return;
	}
	if(!get_ins_args(l->str,"mov32~ R1,C",&args))
	{
		val=gen_movw(args.regs[0],args.off&0xffff,args.cond);
		ins_write(&val,4);
		val=gen_movt(args.regs[0],args.off>>16,args.cond);
		ins_write(&val,4);
		return;
	}
	error(l->line,"unknown instruction.");
}
