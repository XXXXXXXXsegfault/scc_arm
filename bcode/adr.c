void gen_adr(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==2||op[0].class==3||
			op[1].class==1||op[1].class==2)
	{
		error(ins->line,"invalid op.");
	}
	if(op[0].class==1)
	{
		mov_addr(op[0].tab->reg+4,0,op+1,ins->cond);
	}
	else
	{
		mov_addr(0,0,op+1,ins->cond);
		ld_st_addr("str",0,1,op+0,ins->cond);
	}
}
