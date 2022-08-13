void gen_mod(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins,3,op+2);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	mov_op(op+1,0,2,ins->cond);
	mov_op(op+2,1,2,ins->cond);
	if(op[1].class<2&&op[1].tab->class&1||
		op[2].class<2&&op[2].tab->class&1)
	{
		outs("sdiv");
		out_cond(ins->cond);
		outs(" ");
	}
	else
	{
		outs("udiv");
		out_cond(ins->cond);
		outs(" ");
	}
	out_reg(2);
	outs(",");
	out_reg(0);
	outs(",");
	out_reg(1);
	outs("\n");
	if(op[0].class==1)
	{
			outs("mls");
			out_cond(ins->cond);
			outs(" ");
			out_reg(op[0].tab->reg+4);
			outs(",r2,r1,r0\n");
	}
	else
	{
			outs("mls");
			out_cond(ins->cond);
			outs(" r0,r2,r1,r0\n");
			ld_st_addr("str",0,1,op+0,ins->cond);
	}
}
