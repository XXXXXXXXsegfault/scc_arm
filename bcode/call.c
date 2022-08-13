void gen_push(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	if(op[0].class==1)
	{
		outs("str");
		out_cond(ins->cond);
		outs(" ");
		out_reg(op[0].tab->reg+4);
		outs(",[r13,#-4]!\n");
	}
	else
	{
		mov_op(op+0,0,1,ins->cond);
		outs("str");
		out_cond(ins->cond);
		outs(" ");
		out_reg(0);
		outs(",[r13,#-4]!\n");
	}
}
void gen_call(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op[1].class==2)
	{
		outs("bl");
		out_cond(ins->cond);
		outs(" ");
		op_out_const(6,op+1);
		outs("\n");
	}
	else
	{
		mov_op(op+1,0,1,ins->cond);
		outs("blx");
		out_cond(ins->cond);
		outs(" r0\n");
	}
	if(op[0].tab->unused)
	{
		return;
	}
	if(op[0].class==1)
	{
		outs("mov");
		out_cond(ins->cond);
		outs(" ");
		out_reg(op[0].tab->reg+4);
		outs(",r0\n");
	}
	else
	{
		ld_st_addr("str",0,1,op+0,ins->cond);
	}
}
void gen_retval(struct ins *ins)
{
	struct operand op[3];
	struct ins *p;
	if(!fun_name)
	{
		error(ins->line,"ret outside of function.");
	}
	get_operand(ins,1,op+0);
	mov_op(op+0,0,1,ins->cond);
	p=ins->next;
	while(p)
	{
		if(p->op)
		{
			break;
		}
		if(p->count_args&&!strcmp(p->args[0],"endf"))
		{
			return;
		}
		p=p->next;
	}

	outs("b");
	out_cond(ins->cond);
	outs(" ");
	outs("@");
	outs(fun_name);
	outs("$END\n");
}
