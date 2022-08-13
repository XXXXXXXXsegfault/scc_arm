void gen_basic_op(struct ins *ins,char *str)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins,3,op+2);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op[1].class==1&&op[2].class==1)
	{
		if(op[0].class==1)
		{
			outs2(str);
			out_cond(ins->cond);
			outs(" ");
			out_reg(op[0].tab->reg+4);
			outs(",");
			out_reg(op[1].tab->reg+4);
			outs(",");
			out_reg(op[2].tab->reg+4);
			outs("\n");
		}
		else
		{
			outs2(str);
			out_cond(ins->cond);
			outs(" ");
			out_reg(0);
			outs(",");
			out_reg(op[1].tab->reg+4);
			outs(",");
			out_reg(op[2].tab->reg+4);
			outs("\n");
			ld_st_addr("str",0,2,op+0,ins->cond);
		}
		return;
	}
	if(op[1].class==1&&op[2].class==2)
	{
		if(op_is_valid_imm(op+2)&&strcmp(str,"mul ")
				&&strcmp(str,"udiv ")&&strcmp(str,"sdiv "))
		{
			if(op[0].class==1)
			{
				outs2(str);
				out_cond(ins->cond);
				outs(" ");
				out_reg(op[0].tab->reg+4);
				outs(",");
				out_reg(op[1].tab->reg+4);
				outs(",#");	
				op_out_const(5,op+2);
				outs("\n");
			}
			else
			{
				outs2(str);
				out_cond(ins->cond);
				outs(" ");
				out_reg(0);
				outs(",");
				out_reg(op[1].tab->reg+4);
				outs(",#");
				op_out_const(5,op+2);
				outs("\n");
				ld_st_addr("str",0,2,op+0,ins->cond);
			}
			return;
		}
	}
	mov_op(op+1,0,2,ins->cond);
	mov_op(op+2,1,2,ins->cond);
	outs2(str);
	out_cond(ins->cond);
	outs(" ");
	if(op[0].class==1)
	{
			out_reg(op[0].tab->reg+4);
			outs(",");
			out_reg(0);
			outs(",");
			out_reg(1);
			outs("\n");
	}
	else
	{
			out_reg(2);
			outs(",");
			out_reg(0);
			outs(",");
			out_reg(1);
			outs("\n");
			ld_st_addr("str",2,1,op+0,ins->cond);
	}
}
