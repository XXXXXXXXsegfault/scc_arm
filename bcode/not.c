void gen_not(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op[0].class==1&&op[1].class==1)
	{
		outs("mvn");
		out_cond(ins->cond);
		outs(" ");
		out_reg(op[0].tab->reg+4);
		outs(",");
		out_reg(op[1].tab->reg+4);
		outs("\n");
		return;
	}
	mov_op(op+1,0,1,ins->cond);
	if(op[0].class==1)
	{
		outs("mvn");
		out_cond(ins->cond);
		outs(" ");
		out_reg(op[0].tab->reg+4);
		outs(",r0\n");
	}
	else
	{
		outs("mvn");
		out_cond(ins->cond);
		outs(" r0,r0\n");
		mov_addr(1,2,op+0,ins->cond);
		outs("str");
		outs(get_type(op[0].tab->class));
		out_cond(ins->cond);
		outs(" r0,[r1]\n");
	}	
}
