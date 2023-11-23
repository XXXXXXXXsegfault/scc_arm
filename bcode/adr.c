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
void gen_adro(struct ins *ins)
{
	struct operand op[3];
	int s;
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins,3,op+2);
	if(op[0].class==2||op[0].class==3||
			op[1].class==1||op[1].class==2||op[2].class!=2)
	{
		error(ins->line,"invalid op.");
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
	if(op[0].class==1)
	{
		mov_addr(op[0].tab->reg+4,0,op+1,ins->cond);
		outs("add");
		out_cond(ins->cond);
		outs(" ");
		out_reg(op[0].tab->reg+4);
		outs(",");
		out_reg(op[0].tab->reg+4);
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
		outs("\n");
	}
	else
	{
		mov_addr(0,0,op+1,ins->cond);
		outs("add");
		out_cond(ins->cond);
		outs(" r0,r0,");
		if(s)
		{
			outs("r3");
		}
		else
		{
			outs("#");
			out_num32(op[2].value);
		}
		outs("\n");
		ld_st_addr("str",0,1,op+0,ins->cond);
	}
}
