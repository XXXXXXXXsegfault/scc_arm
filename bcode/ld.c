void gen_ld(struct ins *ins,int class)
{
	struct operand op[3];
	int reg,dst;
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op[1].class==1)
	{
		reg=op[1].tab->reg+4;
	}
	else
	{
		mov_op(op+1,0,1,ins->cond);
		reg=0;
	}
	if(op[0].class==1)
	{
		dst=op[0].tab->reg+4;
	}
	else
	{
		dst=0;
	}
	outs("ldr");
	if(if_class_signed(op[0].tab->class))
	{
		outs("s");
	}
	outs(get_type(class));
	out_cond(ins->cond);
	outs(" ");
	out_reg(dst);
	outs(",[");
	out_reg(reg);
	outs("]\n");
	if(op[0].class==0)
	{
		ld_st_addr("str",0,1,op+0,ins->cond);
	}
}
void gen_ldo(struct ins *ins,int class)
{
	struct operand op[3];
	int reg,dst;
	int s;
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins,3,op+2);
	if(op[0].class==2||op[0].class==3||op[2].class!=2)
	{
		error(ins->line,"invalid op.");
	}
	if(op[1].class==1)
	{
		reg=op[1].tab->reg+4;
	}
	else
	{
		mov_op(op+1,0,1,ins->cond);
		reg=0;
	}
	if(op[0].class==1)
	{
		dst=op[0].tab->reg+4;
	}
	else
	{
		dst=0;
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
	outs("ldr");
	if(if_class_signed(op[0].tab->class))
	{
		outs("s");
	}
	outs(get_type(class));
	out_cond(ins->cond);
	outs(" ");
	out_reg(dst);
	outs(",[");
	out_reg(reg);
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
	if(op[0].class==0)
	{
		ld_st_addr("str",0,1,op+0,ins->cond);
	}
}
