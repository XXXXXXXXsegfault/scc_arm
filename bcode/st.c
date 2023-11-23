void gen_st(struct ins *ins,int class)
{
	struct operand op[3];
	int reg,addr;
	int c;
	get_operand(ins,1,op+1);
	get_operand(ins,2,op+0);
	if(op[0].class==1)
	{
		reg=op[0].tab->reg+4;
		c=op[0].tab->class;
	}
	else
	{
		mov_op(op+0,0,1,ins->cond);
		reg=0;
		c=6;
	}
	if(op[1].class==1)
	{
		addr=op[1].tab->reg+4;
	}
	else
	{
		mov_op(op+1,1,2,ins->cond);
		addr=1;
	}
	if(class-1>>1>c-1>>1)
	{
		if(c-1>>1!=1)
		{
			outs("and");
			out_cond(ins->cond);
			outs(" ");
			out_reg(reg);
			outs(",");
			out_reg(reg);
			outs(",#0xff\n");
		}
		else
		{
			outs("movw");
			out_cond(ins->cond);
			outs(" r2,#0xffff\n");
			outs("and");
			out_cond(ins->cond);
			outs(" ");
			out_reg(reg);
			outs(",");
			out_reg(reg);
			outs(",r2\n");
		}
	}
	outs("str");
	outs(get_type(class));
	out_cond(ins->cond);
	outs(" ");
	out_reg(reg);
	outs(",[");
	out_reg(addr);
	outs("]\n");
}
void gen_sto(struct ins *ins,int class)
{
	struct operand op[3];
	int reg,addr;
	int c,s;
	get_operand(ins,1,op+1);
	get_operand(ins,2,op+0);
	get_operand(ins,3,op+2);
	if(op[2].class!=2)
	{
		error(ins->line,"invalid op.");
	}
	if(op[0].class==1)
	{
		reg=op[0].tab->reg+4;
		c=op[0].tab->class;
	}
	else
	{
		mov_op(op+0,0,1,ins->cond);
		reg=0;
		c=6;
	}
	if(op[1].class==1)
	{
		addr=op[1].tab->reg+4;
	}
	else
	{
		mov_op(op+1,1,2,ins->cond);
		addr=1;
	}
	if(class-1>>1>c-1>>1)
	{
		if(c-1>>1!=1)
		{
			outs("and");
			out_cond(ins->cond);
			outs(" ");
			out_reg(reg);
			outs(",");
			out_reg(reg);
			outs(",#0xff\n");
		}
		else
		{
			outs("movw");
			out_cond(ins->cond);
			outs(" r2,#0xffff\n");
			outs("and");
			out_cond(ins->cond);
			outs(" ");
			out_reg(reg);
			outs(",");
			out_reg(reg);
			outs(",r2\n");
		}
	}
	s=0;
	if(op[2].value>=256||op[2].value<0)
	{
		s=1;
		outs("mov32");
		out_cond(ins->cond);
		outs(" r3,");
		out_num32(op[2].value);
		outs("\n");
	}
	outs("str");
	outs(get_type(class));
	out_cond(ins->cond);
	outs(" ");
	out_reg(reg);
	outs(",[");
	out_reg(addr);
	outs(",");
	if(s)
	{
		outs("r3");
	}
	else
	{
		outs("#");
		out_num32(op[2].value);
	}
	outs("]\n");
}
