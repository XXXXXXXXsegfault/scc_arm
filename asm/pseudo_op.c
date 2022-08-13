void parse_pseudo_op(char *str)
{
	char *word,*p,c;
	unsigned int val;
	if(str_match(&str,"string"))
	{
		word=read_word(&str);
		if(*word!='\"')
		{
			error(l->line,"expected string after \'.string\'.");
		}
		p=word+1;
		while(*p!='\"')
		{
			p=sgetc(p,&c);
			ins_outc(c);
		}
		free(word);
		ins_outc(0);

	}
	else if(str_match(&str,"entry"))
	{
		l->needs_recompile=1;
		entry=pc;
	}
	else if(str_match(&str,"datasize"))
	{
		word=read_word(&str);
		if(word)
		{
			data_size=const_to_num(word);
			free(word);
		}
	}
	else if(str_match(&str,"byte"))
	{
		do
		{
			if(parse_const(&str,&val)==-1)
			{
				error(l->line,"invalid constant expression.");
			}
			ins_write(&val,1);
		}
		while(str_match(&str,","));
	}
	else if(str_match(&str,"word"))
	{
		do
		{
			if(parse_const(&str,&val)==-1)
			{
				error(l->line,"invalid constant expression.");
			}
			ins_write(&val,2);
		}
		while(str_match(&str,","));
	}
	else if(str_match(&str,"long"))
	{
		do
		{
			if(parse_const(&str,&val)==-1)
			{
				error(l->line,"invalid constant expression.");
			}
			ins_write(&val,4);
		}
		while(str_match(&str,","));
	}
	else if(str_match(&str,"align"))
	{
		word=read_word(&str);
		if(word)
		{
			val=const_to_num(word);
			if(val<16)
			{
				while((1<<val)-1&pc)
				{
					ins_outc(0);
				}
				l->needs_recompile=1;
			}
		}
	}
	else if(!str_match(&str,"end_fun"))
	{
		error(l->line,"unknown pseudo-op.");
	}
}
