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
