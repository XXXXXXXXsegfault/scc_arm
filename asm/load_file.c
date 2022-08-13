struct line
{
	char *str;
	unsigned int line;
	unsigned char *ins_buf;
	unsigned char ins_buf2[32];
	unsigned int ins_len;
	unsigned int ins_pos;
	unsigned int needs_recompile;
	struct line *next;
} *lines_head;
void load_file(void)
{
	char *str;
	struct line *l,*end;
	end=NULL;
	while(str=read_line())
	{
		l=xmalloc(sizeof(*l));
		memset(l,0,sizeof(*l));
		l->str=str;
		l->line=current_line;
		l->next=NULL;
		if(end)
		{
			end->next=l;
		}
		else
		{
			lines_head=l;
		}
		end=l;
	}
}

