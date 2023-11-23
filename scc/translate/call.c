void calculate_call(struct syntax_tree *root,struct expr_ret *ret)
{
	int x;
	struct syntax_tree *type,*decl,*decl1;
	struct expr_ret result,func;
	char *name,*new_name;
	char *stk_tmpname;
	if(stkoverflowprot_state)
	{
		stk_tmpname=mktmpname();
		c_write("local u32 ",10);
		c_write(stk_tmpname,strlen(stk_tmpname));
		c_write("\ncall ",6);
		c_write(stk_tmpname,strlen(stk_tmpname));
		c_write(" __stackdepth_inc\n",18);
	}
	calculate_expr(root->subtrees[0],&func);
	deref_ptr(&func,root->line,root->col);
	if(!is_function(func.decl))
	{
		if(!is_pointer_array(func.decl))
		{
			error(root->line,root->col,"calling a non-function.");
		}
		decl=decl_next(func.decl);
		syntax_tree_release(func.decl);
		func.decl=decl;
		if(!is_function(func.decl))
		{
			error(root->line,root->col,"calling a non-function.");
		}
	}
	decl1=get_decl_type(func.decl);
	if(decl1->count_subtrees-1>>1!=root->count_subtrees-1)
	{
		error(root->line,root->col,"numbers of arguments did not match.");
	}
	x=root->count_subtrees;
	while(x>1)
	{
		--x;
		calculate_expr(root->subtrees[x],&result);
		deref_ptr(&result,root->subtrees[x]->line,root->subtrees[x]->col);
		if(if_type_compat(result.type,result.decl,decl1->subtrees[x*2-1],decl1->subtrees[x*2],1))
		{
			error(root->line,root->col,"incompatible type.");
		}
		c_write("push ",5);
		if(result.is_const)
		{
			name=str_i_app(0,result.value);
		}
		else
		{
			name=xstrdup(get_decl_id(result.decl));
		}
		c_write(name,strlen(name));
		c_write("\n",1);
		free(name);
		expr_ret_release(&result);
	}
	new_name=mktmpname();
	type=syntax_tree_dup(func.type);
	decl=decl_next(func.decl);
	decl1=get_decl_type(decl);
	if(!strcmp(decl1->name,"Identifier"))
	{
		free(decl1->value);
		decl1->value=new_name;
	}
	else
	{
		free(decl1->subtrees[0]->value);
		decl1->subtrees[0]->value=new_name;
	}
	add_decl(type,decl,0,0,0,1);
	c_write("call ",5);
	c_write(new_name,strlen(new_name));
	c_write(" ",1);
	name=get_decl_id(func.decl);
	c_write(name,strlen(name));
	c_write("\n",1);

	if(root->count_subtrees>1)
	{
		c_write("del ",4);
		name=str_i_app(0,root->count_subtrees-1);
		c_write(name,strlen(name));
		c_write("\n",1);
		free(name);
	}


	ret->type=type;
	ret->decl=decl;
	ret->is_const=0;
	ret->is_lval=0;
	ret->needs_deref=0;

	expr_ret_release(&func);
	if(stkoverflowprot_state)
	{
		c_write("call ",5);
		c_write(stk_tmpname,strlen(stk_tmpname));
		c_write(" __stackdepth_dec\n",18);
		free(stk_tmpname);
	}
}
