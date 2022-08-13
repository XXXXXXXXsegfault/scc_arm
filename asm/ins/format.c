int parse_num(char **str,unsigned int *result)
{
	char *old_str,*word;
	int s;
	struct label *label;
	old_str=*str;
	*str=skip_spaces(*str);
	s=0;
	if(**str=='-')
	{
		++*str;
		s=1;
	}
	if(**str=='@')
	{
		//label
		++*str;
		word=read_word(str);
		if(!strcmp(word,"_$DATA"))
		{
			free(word);
			if(s)
			{
				*result=-data_addr;
			}
			else
			{
				*result=data_addr;
			}
			return 0;
		}
		else
		{
			label=label_tab_find(word);
			if(stage)
			{
				if(label)
				{
					free(word);
					*result=label->value;
					if(s)
					{
						*result=-*result;
					}
					return 0;
				}
				error(l->line,"label undefined.");
			}
			else
			{
				l->needs_recompile=1;
			}
		}
		free(word);
		return -2;
	}
	else if(**str>='0'&&**str<='9'||**str=='\'')
	{
		*result=const_to_num(*str);
		word=read_word(str);
		free(word);
	}
	else
	{
		*str=old_str;
		return -1;
	}
	if(s)
	{
		*result=-*result;
	}
	return 0;
}
int parse_const(char **str,unsigned int *result)
{
	unsigned int num;
	int ret,s,s1;
	char *old_str;
	old_str=*str;
	s=0;
	s1=0;
	*result=0;
	while(1)
	{
		ret=parse_num(str,&num);
		if(ret==-1)
		{
			*str=old_str;
			return -1;
		}
		if(ret==-2)
		{
			s=1;
		}
		if(s1)
		{
			*result-=num;
		}
		else
		{
			*result+=num;
		}
		*str=skip_spaces(*str);
		if(**str=='+')
		{
			s1=0;
			++*str;
		}
		else if(**str=='-')
		{
			s1=1;
			++*str;
		}
		else
		{
			break;
		}
	}
	if(s)
	{
		*result=0;
	}
	return 0;
}
int str_match(char **pstr,char *str)
{
	int l;
	char *old_str;
	old_str=*pstr;
	l=strlen(str);
	*pstr=skip_spaces(*pstr);
	if(strncmp(*pstr,str,l))
	{
		*pstr=old_str;
		return 0;
	}
	*pstr+=l;
	return 1;
}
int parse_reg(char **str)
{
	if(str_match(str,"r0"))
	{
		return 0;
	}
	if(str_match(str,"r10"))
	{
		return 10;
	}
	if(str_match(str,"r11"))
	{
		return 11;
	}
	if(str_match(str,"r12"))
	{
		return 12;
	}
	if(str_match(str,"r13"))
	{
		return 13;
	}
	if(str_match(str,"r14"))
	{
		return 14;
	}
	if(str_match(str,"r15"))
	{
		return 15;
	}
	if(str_match(str,"r1"))
	{
		return 1;
	}
	if(str_match(str,"r2"))
	{
		return 2;
	}
	if(str_match(str,"r3"))
	{
		return 3;
	}
	if(str_match(str,"r4"))
	{
		return 4;
	}
	if(str_match(str,"r5"))
	{
		return 5;
	}
	if(str_match(str,"r6"))
	{
		return 6;
	}
	if(str_match(str,"r7"))
	{
		return 7;
	}
	if(str_match(str,"r8"))
	{
		return 8;
	}
	if(str_match(str,"r9"))
	{
		return 9;
	}
	if(str_match(str,"sp"))
	{
		return 13;
	}
	if(str_match(str,"lr"))
	{
		return 14;
	}
	if(str_match(str,"pc"))
	{
		return 15;
	}
	return -1;
}
int imm_shifts(unsigned int *imm)
{
	int x;
	x=0;
	while(x<16)
	{
		if(*imm<0x100)
		{
			return x;
		}
		*imm=*imm<<2|*imm>>30;
		++x;
	}
	return -1;
}
int parse_const_nolabel(char **str,unsigned int *result)
{
	unsigned int num;
	*str=skip_spaces(*str);
	if(**str>='0'&&**str<='9'||**str=='\'')
	{
		num=const_to_num(*str);
		free(read_word(str));
		*result=num;
		return 0;
	}
	else
	{
		return -1;
	}
}
unsigned int parse_cond(char **input)
{
	if(str_match(input,"eq"))
	{
		return 0;
	}
	else if(str_match(input,"ne"))
	{
		return 1;
	}
	else if(str_match(input,"cs"))
	{
		return 2;
	}
	else if(str_match(input,"hs"))
	{
		return 2;
	}
	else if(str_match(input,"cc"))
	{
		return 3;
	}
	else if(str_match(input,"lo"))
	{
		return 3;
	}
	else if(str_match(input,"mi"))
	{
		return 4;
	}
	else if(str_match(input,"pl"))
	{
		return 5;
	}
	else if(str_match(input,"vs"))
	{
		return 6;
	}
	else if(str_match(input,"vc"))
	{
		return 7;
	}
	else if(str_match(input,"hi"))
	{
		return 8;
	}
	else if(str_match(input,"ls"))
	{
		return 9;
	}
	else if(str_match(input,"ge"))
	{
		return 10;
	}
	else if(str_match(input,"lt"))
	{
		return 11;
	}
	else if(str_match(input,"gt"))
	{
		return 12;
	}
	else if(str_match(input,"le"))
	{
		return 13;
	}
	else if(str_match(input,"al"))
	{
		return 14;
	}
	return 14;
}
int parse_map(char **input)
{
	int val,reg;
	if(!str_match(input,"{"))
	{
		return -1;
	}
	val=0;
	do
	{
		reg=parse_reg(input);
		if(reg<0)
		{
			return -1;
		}
		val|=1<<reg;
	}
	while(str_match(input,","));
	if(!str_match(input,"}"))
	{
		return -1;
	}
	return val;
}
struct ins_args
{
	unsigned char regs[4];
	unsigned int imm;
	unsigned int off;
	unsigned int cond;
};
int get_ins_args(char *input,char *format,struct ins_args *args)
{
	char *word;
	int val,s;
	args->cond=14;
	s=l->needs_recompile;
	while(word=read_word(&format))
	{
		if(!strcmp(word,"~"))
		{
			args->cond=parse_cond(&input);
		}
		else if(!strcmp(word,"R1"))
		{
			if((args->regs[0]=parse_reg(&input))>15)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"R2"))
		{
			if((args->regs[1]=parse_reg(&input))>15)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"R3"))
		{
			if((args->regs[2]=parse_reg(&input))>15)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"R4"))
		{
			if((args->regs[3]=parse_reg(&input))>15)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"I"))
		{
			if(parse_const_nolabel(&input,&args->imm)<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
			if((val=imm_shifts(&args->imm))<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
			args->imm|=val<<8;
		}
		else if(!strcmp(word,"NI"))
		{
			if(parse_const_nolabel(&input,&args->imm)<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
			args->imm=~args->imm;
			if((val=imm_shifts(&args->imm))<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
			args->imm|=val<<8;
		}
		else if(!strcmp(word,"N"))
		{
			if(parse_const_nolabel(&input,&args->off)<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"O"))
		{
			if(parse_const_nolabel(&input,&args->off)<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
			if(args->off>4095)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"O8"))
		{
			if(parse_const_nolabel(&input,&args->off)<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
			if(args->off>255)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"C"))
		{
			if(parse_const(&input,&args->off)<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!strcmp(word,"M"))
		{
			if((args->off=parse_map(&input))<0)
			{
				free(word);
				l->needs_recompile=s;
				return 1;
			}
		}
		else if(!str_match(&input,word))
		{
			free(word);
			l->needs_recompile=s;
			return 1;
		}
		free(word);
	}
	input=skip_spaces(input);
	if(*input!=0)
	{
		l->needs_recompile=s;
		return 1;
	}

	return 0;
}
