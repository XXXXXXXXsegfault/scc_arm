void mov_op(struct operand *op,int dst,int tmp,char *cond)
{
	if(op[0].class==3)
	{
		mov_addr(dst,tmp,op,cond);
	}
	else if(op[0].class==2)
	{
		outs("mov32");
		out_cond(cond);
		outs(" ");
		out_reg(dst);
		outs(",");
		op_out_const(5,op);
		outs("\n");
	}
	else if(op[0].class==0)
	{
		ld_st_addr("ldr",dst,tmp,op,cond);
	}
	else if(op[0].class==1)
	{
		outs("mov");
		out_cond(cond);
		outs(" ");
		out_reg(dst);
		outs(",");
		out_reg(op[0].tab->reg+4);
		outs("\n");
	}
}
void gen_mov(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op[0].class==1)
	{
		if(op[1].class==3)
		{
			mov_addr(op[0].tab->reg+4,0,op+1,ins->cond);
		}
		else if(op[1].class==0)
		{
			ld_st_addr("ldr",op[0].tab->reg+4,1,op+1,ins->cond);
		}
		else if(op[1].class==1)
		{
			outs("mov");
			out_cond(ins->cond);
			outs(" ");
			out_reg(op[0].tab->reg+4);
			outs(",");
			out_reg(op[1].tab->reg+4);
			outs("\n");
		}
		else
		{
			outs("mov32");
			out_cond(ins->cond);
			outs(" ");
			out_reg(op[0].tab->reg+4);
			outs(",");
			op_out_const(5,op+1);
			outs("\n");
		}
	}
	else
	{
		if(op[1].class==3)
		{
			mov_addr(0,0,op+1,ins->cond);
		}
		else if(op[1].class==0)
		{
			ld_st_addr("ldr",0,1,op+1,ins->cond);
		}
		else if(op[1].class==1)
		{
			outs("mov");
			out_cond(ins->cond);
			outs(" ");
			out_reg(0);
			outs(",");
			out_reg(op[1].tab->reg+4);
			outs("\n");
		}
		else
		{
			outs("mov32");
			out_cond(ins->cond);
			outs(" ");
			out_reg(0);
			outs(",");
			op_out_const(5,op+1);
			outs("\n");
		}
		mov_addr(1,2,op+0,ins->cond);
		outs("str");
		outs(get_type(op[0].tab->class));
		out_cond(ins->cond);
		outs(" r0,[r1]\n");
	}
}
