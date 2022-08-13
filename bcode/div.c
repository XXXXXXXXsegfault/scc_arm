void gen_div(struct ins *ins)
{
	struct operand op[3];
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins,3,op+2);
	if(op[0].class==2||op[0].class==3)
	{
		error(ins->line,"invalid op.");
	}
	if(op[1].class<2&&op[1].tab->class&1||
		op[2].class<2&&op[2].tab->class&1)
	{
		gen_basic_op(ins,"sdiv ");
	}
	else
	{
		gen_basic_op(ins,"udiv ");
	}
}
