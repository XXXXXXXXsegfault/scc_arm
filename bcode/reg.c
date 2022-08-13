struct reg_map
{
	unsigned int *bitmap;
	struct reg_map *next;
	unsigned int uses;
	unsigned int n;
} *reg_map_head,*reg_map_end;
unsigned int count_reg_maps;
struct reg_map *new_reg_map(void)
{
	struct reg_map *node;
	int size;
	size=current_line/32+1;
	node=xmalloc(sizeof(*node));
	node->bitmap=xmalloc(size*4);
	memset(node->bitmap,0,size*4);
	node->next=0;
	node->uses=0;
	node->n=count_reg_maps;
	if(reg_map_head)
	{
		reg_map_end->next=node;
	}
	else
	{
		reg_map_head=node;
	}
	reg_map_end=node;
	++count_reg_maps;
	return node;
}
void reg_map_release(void)
{
	struct reg_map *node;
	while(node=reg_map_head)
	{
		reg_map_head=node->next;
		free(node->bitmap);
		free(node);
	}
	reg_map_end=0;
	count_reg_maps=0;
}
void reg_map_sort(void)
{
	int s;
	struct reg_map *p,*node,*t;
	do
	{
		s=0;
		p=0;
		node=reg_map_head;
		if(node)
		{
			while(node->next)
			{
				if(node->next->uses>node->uses)
				{
					t=node->next;
					node->next=t->next;
					t->next=node;
					if(p)
					{
						p->next=t;
					}
					else
					{
						reg_map_head=t;
					}
					s=1;
					p=t;
				}
				else
				{
					p=node;
					node=node->next;
				}
			}
		}
	}
	while(s);
}
unsigned int get_reg_index(unsigned int n)
{
	unsigned int reg;
	struct reg_map *node;
	reg=0;
	node=reg_map_head;
	while(node)
	{
		if(node->n==n)
		{
			break;
		}
		node=node->next;
		++reg;
	}
	return reg;
}

void init_def_use(void)
{
	struct ins *node;
	char *str;
	struct id_list *id;
	int x;
	unsigned a;
	a=1;
	node=fstart;
	while(node&&node!=fend)
	{
		id=id_list_head;
		x=0;
		while(id)
		{
			if(node->op==1||node->op==11||node->op==12)
			{

				if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valdef[0]|=a<<x;
				}
			}
			else if(node->op==2||node->op==13||node->op==14||node->op==17)
			{
				if(id->num==node->var_num[2])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valdef[0]|=a<<x;
				}
			}
			else if(node->op==15)
			{
				if(id->num==node->var_num[2])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valdef[0]|=a<<x;
				}
			}
			else if(node->op==16)
			{
				if(id->num==node->var_num[2])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valuse[0]|=a<<x;
				}
			}
			else if(node->op==3)
			{
				if(id->num==node->var_num[0])
				{
					node->valuse[0]|=a<<x;
				}
			}
			else if(node->op==4)
			{
				if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valdef[0]|=a<<x;
				}
			}
			else if(node->op==5)
			{
				if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valuse[0]|=a<<x;
				}
			}
			else if(node->op==6)
			{
				if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valdef[0]|=a<<x;
				}
			}
			else if(node->op==7)
			{
				if(id->num==node->var_num[1])
				{
					node->valuse[0]|=a<<x;
				}
				else if(id->num==node->var_num[0])
				{
					node->valuse[0]|=a<<x;
				}
			}
			else if(node->op==9)
			{
				if(id->num==node->var_num[0])
				{
					node->valuse[0]|=a<<x;
				}
			}
			++x;
			id=id->next;
		}
		node=node->next;
	}
}
void calculate_df(void)
{
	struct ins *ins;
	unsigned int s;
	unsigned int old_in[4];
	ins=fstart;
	while(ins&&ins!=fend)
	{
		ins->valin[0]=0;
		ins=ins->next;
	}
	do
	{
		s=0;
		ins=fstart;
		while(ins&&ins!=fend)
		{
			ins->valout[0]=0;
			if(ins->next&&ins->next!=fend&&ins->op!=8&&ins->op!=9&&ins->op!=10)
			{
				ins->valout[0]|=ins->next->valin[0];
			}
			if(ins->branch)
			{
				ins->valout[0]|=ins->branch->valin[0];
			}
			old_in[0]=ins->valin[0];
			ins->valin[0]=ins->valuse[0]|ins->valout[0]&~ins->valdef[0];
			s|=old_in[0]^ins->valin[0];
			ins=ins->next;
		}
	}
	while(s);
}
unsigned int *gen_var_map(int index)
{
	int size;
	unsigned int *ret;
	int x;
	struct ins *ins;
	unsigned a;
	a=1;
	size=current_line-current_line%32+32;
	ret=xmalloc(size/8);
	memset(ret,0,size/8);
	x=fline;
	ins=fstart;
	while(ins&&ins!=fend)
	{
		if((ins->valin[0]|ins->valdef[0])&a<<index)
		{
			ret[x/32]|=1<<x%32;
		}
		++x;
		ins=ins->next;
	}
	return ret;
}
int if_reg_available(struct reg_map *rmap,unsigned int *vmap)
{
	int size,x,n;
	size=current_line/32+1;
	x=fline/32;
	n=fend_line/32+1;
	while(x<size&&x<n)
	{
		if(rmap->bitmap[x]&vmap[x])
		{
			return 0;
		}
		++x;
	}
	return 1;
}
void use_reg(struct reg_map *rmap,unsigned int *vmap)
{
	int size,x,n;
	size=current_line/32+1;
	x=fline/32;
	n=fend_line/32+1;
	while(x<size&&x<n)
	{
		rmap->bitmap[x]|=vmap[x];
		++x;
	}
	++rmap->uses;
}
void get_reg(void)
{
	struct ins *ins;
	struct id_list *id;
	struct id_tab *tab;
	unsigned int *map;
	struct reg_map *rmap;
	int x,s;
	ins=fstart;
	while(ins&&ins!=fend)
	{
		ins->valdef[0]=0;
		ins->valuse[0]=0;
		ins=ins->next;
	}
	init_def_use();
	calculate_df();
	x=0;
	id=id_list_head;
	while(id)
	{
		s=0;
		tab=id_tab_find(local_id,id->name);
		if(!tab)
		{
			tab=id_tab_find(args_id,id->name);
			s=1;
		}
		map=gen_var_map(x);
		rmap=reg_map_head;
		while(rmap)
		{
			if(if_reg_available(rmap,map))
			{
				if(!s||(rmap->n>=8||fstart->arg_map[rmap->n]==-1))
				{
					break;
				}
			}
			rmap=rmap->next;
		}
		if(!rmap)
		{
			rmap=new_reg_map();
		}
		if(fstart&&(rmap->n<8||!s))
		{
			tab->reg=rmap->n;
			if(tab->reg<8)
			{
				fstart->used_regs|=1<<tab->reg;
			}
			if(s)
			{
				fstart->arg_map[tab->reg]=tab->off;
			}
			use_reg(rmap,map);
		}
		free(map);
		reg_map_sort();
		++x;
		id=id->next;
	}
	id_list_release();
}
