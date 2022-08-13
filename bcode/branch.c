char *cond_neg(char *cond)
{
	if(!strcmp(cond,"beq "))
	{
		return "bne ";
	}
	else if(!strcmp(cond,"bne "))
	{
		return "beq ";
	}
	else if(!strcmp(cond,"bcc "))
	{
		return "bcs ";
	}
	else if(!strcmp(cond,"bcs "))
	{
		return "bcc ";
	}
	else if(!strcmp(cond,"bls "))
	{
		return "bhi ";
	}
	else if(!strcmp(cond,"bhi "))
	{
		return "bls ";
	}
	else if(!strcmp(cond,"ble "))
	{
		return "bgt ";
	}
	else if(!strcmp(cond,"bge "))
	{
		return "blt ";
	}
	else if(!strcmp(cond,"bgt "))
	{
		return "ble ";
	}
	else if(!strcmp(cond,"blt "))
	{
		return "bge ";
	}
}
char *cond_neg2(char *cond)
{
	if(!strcmp(cond,"beq"))
	{
		return "bne";
	}
	else if(!strcmp(cond,"bne"))
	{
		return "beq";
	}
	else if(!strcmp(cond,"ble"))
	{
		return "bgt";
	}
	else if(!strcmp(cond,"bge"))
	{
		return "blt";
	}
	else if(!strcmp(cond,"bgt"))
	{
		return "ble";
	}
	else if(!strcmp(cond,"blt"))
	{
		return "bge";
	}
}
int if_cond_same(struct ins *ins,struct ins *ins2)
{
	struct operand op[3];
	struct operand op2[3];
	int s1,s2;
	if(strcmp(ins2->args[0],cond_neg2(ins->args[0])))
	{
		return 0;
	}
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins2,1,op2+0);
	get_operand(ins2,2,op2+1);
	if(op[0].class<2&&op[0].tab->class&1||
			op[1].class<2&&op[1].tab->class&1)
	{
		s1=1;
	}
	else
	{
		s1=0;
	}
	if(op2[0].class<2&&op2[0].tab->class&1||
			op2[1].class<2&&op2[1].tab->class&1)
	{
		s2=1;
	}
	else
	{
		s2=0;
	}
	if(s1==s2)
	{
		return 1;
	}
	return 0;
}
int if_cond_same2(struct ins *ins,struct ins *ins2)
{
	struct operand op[3];
	struct operand op2[3];
	int s1,s2;
	if(strcmp(ins2->args[0],ins->args[0]))
	{
		return 0;
	}
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	get_operand(ins2,1,op2+0);
	get_operand(ins2,2,op2+1);
	if(op[0].class<2&&op[0].tab->class&1||
			op[1].class<2&&op[1].tab->class&1)
	{
		s1=1;
	}
	else
	{
		s1=0;
	}
	if(op2[0].class<2&&op2[0].tab->class&1||
			op2[1].class<2&&op2[1].tab->class&1)
	{
		s2=1;
	}
	else
	{
		s2=0;
	}
	if(s1==s2)
	{
		return 1;
	}
	return 0;
}
int if_label_same(struct ins *ins,char *name)
{
	while(ins->count_args>=2&&!strcmp(ins->args[0],"label"))
	{
		if(!strcmp(ins->args[1],name))
		{
			return 1;
		}
		ins=ins->next;
	}
	return 0;
}
int gen_branch2(struct ins *ins,char *op_1,char *op_2,char *op_3,char *op_4)
{
	struct ins *p,*p1;
	int n,s,x;
	int reg1,reg2;
	struct operand op[3];
	char *label;
	n=0;
	s=0;
	p=ins->next;
	label=ins->args[3];
	while(p&&p!=fend)
	{
		if(p->args[0]&&!strcmp(p->args[0],"label"))
		{
			if(if_label_same(p,label))
			{
				break;
			}
			else
			{
				return 1;
			}
		}
		if(p->op==4||p->op==9||p->op==10)
		{
			p1=p->next;
			while(p1&&p1!=fend&&!p1->op)
			{
				if(p1->count_args>=2&&!strcmp(p1->args[0],"label")&&if_label_same(p1,label))
				{
					p=p1;
					break;
				}
				p1=p1->next;
			}
			if(!(p1&&p1!=fend&&!p1->op))
			{
				return 1;
			}
		}
		if(p->op==7)
		{
			if(s)
			{
				return 1;
			}
			else if(if_cond_same(ins,p))
			{
				n=0;
			}
			else
			{
				return 1;
			}
		}
		if(p->op)
		{
			++n;
		}
		if(n==5)
		{
			return 1;
		}
		if(p->op==8)
		{
			if(!s)
			{
				p1=p->next;
				while(p1&&p1!=fend&&!p1->op)
				{
					if(p1->count_args>=2&&!strcmp(p1->args[0],"label")&&if_label_same(p1,label))
					{
						n=0;
						s=1;
						label=p->args[1];
					}
					p1=p1->next;
				}
				if(!(p1&&p1!=fend&&!p1->op))
				{
					return 1;
				}
			}
			else
			{
				return 1;
			}
		}
		p=p->next;
	}
	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==1&&op[1].class==2)
	{
		if(op_is_valid_imm(op+1))
		{
			outs("cmp");
			out_cond(ins->cond);
			outs(" ");
			out_reg(op[0].tab->reg+4);
			outs(",#");
			op_out_const(5,op+1);
			outs("\n");
			p1=ins->next;
			while(p1&&p1!=p)
			{
				if(op[0].tab->class&1)
				{
					p1->cond=op_1;
				}
				else
				{
					p1->cond=op_2;
				}
				if(p1->op==8)
				{
					op_1=cond_neg(op_1);
					op_2=cond_neg(op_2);
					p1->op=0;
					p1->count_args=0;
				}
				p1=p1->next;
			}
			return 0;
		}
	}
	if(op[0].class==1)
	{
		reg1=op[0].tab->reg+4;
	}
	else
	{
		mov_op(op+0,0,2,ins->cond);
		reg1=0;
	}
	if(op[1].class==1)
	{
		reg2=op[1].tab->reg+4;
	}
	else
	{
		mov_op(op+1,1,2,ins->cond);
		reg2=1;
	}
	outs("cmp");
	out_cond(ins->cond);
	outs(" ");
	out_reg(reg1);
	outs(",");
	out_reg(reg2);
	outs("\n");
	p1=ins->next;
	while(p1&&p1!=p)
	{
		if(op[0].class<2&&op[0].tab->class&1||
				op[1].class<2&&op[1].tab->class&1)
		{
			p1->cond=op_1;
		}
		else
		{
			p1->cond=op_2;
		}
		if(p1->op==8)
		{
			op_1=cond_neg(op_1);
			op_2=cond_neg(op_2);
			p1->op=0;
			p1->count_args=0;
		}
		p1=p1->next;
	}
	return 0;
}

void gen_branch(struct ins *ins,char *op_1,char *op_2,char *op_3,char *op_4)
{
	struct operand op[3];
	int reg1,reg2;
	if(!ins->no_branch_optimize&&!gen_branch2(ins,op_1,op_2,op_3,op_4))
	{
		return;
	}

	get_operand(ins,1,op+0);
	get_operand(ins,2,op+1);
	if(op[0].class==1&&op[1].class==2)
	{
		if(op_is_valid_imm(op+1))
		{
			outs("cmp");
			out_cond(ins->cond);
			outs(" ");
			out_reg(op[0].tab->reg+4);
			outs(",#");
			op_out_const(5,op+1);
			outs("\n");
			if(op[0].tab->class&1)
			{
				outs(op_1);
			}
			else
			{
				outs(op_2);
			}
			outs("@_$LB");
			outs(ins->args[3]);
			outs("\n");
			return;
		}
	}
	if(op[0].class==1)
	{
		reg1=op[0].tab->reg+4;
	}
	else
	{
		mov_op(op+0,0,2,ins->cond);
		reg1=0;
	}
	if(op[1].class==1)
	{
		reg2=op[1].tab->reg+4;
	}
	else
	{
		mov_op(op+1,1,2,ins->cond);
		reg2=1;
	}
	outs("cmp");
	out_cond(ins->cond);
	outs(" ");
	out_reg(reg1);
	outs(",");
	out_reg(reg2);
	outs("\n");
	if(op[0].class<2&&op[0].tab->class&1||
			op[1].class<2&&op[1].tab->class&1)
	{
		outs(op_1);
	}
	else
	{
		outs(op_2);
	}
	outs("@_$LB");
	outs(ins->args[3]);
	outs("\n");
}
