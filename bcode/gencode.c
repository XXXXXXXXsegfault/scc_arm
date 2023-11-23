int fun_stack_size;
int is_valid_imm(unsigned int imm)
{
	int x;
	x=0;
	while(x<16)
	{
		if(imm<256)
		{
			return 1;
		}
		imm=imm<<30|imm>>2;
		++x;
	}
	return 0;
}
struct operand
{
	int type;
	struct id_tab *tab;
	unsigned int value;
	char *str;
	unsigned class;
};
int op_is_reg(struct operand *op)
{
	if(!op->tab)
	{
		return 0;
	}
	if(op->tab->reg>=0&&op->tab->reg<8)
	{
		return 1;
	}
	return 0;
}
int op_is_const(struct operand *op)
{
	if(op->type==2||op->type==3)
	{
		return 1;
	}
	return 0;
}
int op_is_addr(struct operand *op)
{
	if(op->type==0)
	{
		return 1;
	}
	return 0;
}
void op_out_const(int class,struct operand *op)
{
	if(op->type==2)
	{
		out_num(class,op->value);
	}
	else if(op->type==3)
	{
		outs("@");
		outs(op->str);
	}
}
int op_is_valid_imm(struct operand *op)
{
	if(op->type!=2)
	{
		return 0;
	}
	return is_valid_imm(op->value);
}
void get_operand(struct ins *ins,int index,struct operand *ret)
{
	char *str;
	memset(ret,0,sizeof(*ret));
	if(index>=ins->count_args)
	{
		error(ins->line,"too few arguments.");
	}
	str=ins->args[index];
	ret->str=str;
	if(ret->tab=id_find(str))
	{
		if(ret->tab->class==0)
		{
			ret->type=0;
		}
		else
		{
			ret->type=1;
		}
	}
	else if(str[0]>='0'&&str[0]<='9'||str[0]=='\'')
	{
		ret->type=2;
		ret->value=const_to_num(str);
	}
	else
	{
		ret->type=3;
	}
	ret->class=0;
	if(op_is_reg(ret))
	{
		ret->class=1;
	}
	else if(op_is_const(ret))
	{
		ret->class=2;
	}
	else if(op_is_addr(ret))
	{
		ret->class=3;
	}
}
void mov_addr(int dst,int tmp,struct operand *op,char *cond)
{
	int x;
	if(op->tab->storage==0)
	{
		if(op->tab->reg>=8)
		{
			x=op->tab->reg-8;
			x=x*4+fun_stack_size;
		}
		else
		{
			x=op->tab->off;
		}
		if(is_valid_imm(x))
		{
			outs("add");
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",r12,#");
			out_num32(x);
			outs("\n");
		}
		else if(is_valid_imm(-x))
		{
			outs("sub");
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",r12,#");
			out_num32(-x);
			outs("\n");
		}
		else
		{
			outs("mov32");
			out_cond(cond);
			outs(" ");
			out_reg(tmp);
			outs(",");
			out_num32(x);
			outs("\n");

			outs("add");
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",r12,");
			out_reg(tmp);
			outs("\n");
		}
	}
	else if(op->tab->storage==2)
	{
		outs("mov32");
		out_cond(cond);
		outs(" ");
		out_reg(dst);
		outs(",@_$DATA+");
		out_num32(op->tab->off);
		outs("\n");
	}
	else if(op->tab->storage==1)
	{
		x=op->tab->off;
		x=x*4+8;
		if(is_valid_imm(x))
		{
			outs("add");
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",r12,#");
			out_num32(x);
			outs("\n");
		}
		else if(is_valid_imm(-x))
		{
			outs("sub");
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",r12,#");
			out_num32(-x);
			outs("\n");
		}
		else
		{
			outs("mov32");
			out_cond(cond);
			outs(" ");
			out_reg(tmp);
			outs(",");
			out_num32(x);
			outs("\n");

			outs("add");
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",r12,");
			out_reg(tmp);
			outs("\n");
		}
	}
}
int if_class_signed(int class)
{
	if(class&1&&class<5)
	{
		return 1;
	}
	return 0;
}
void ld_st_addr(char *ins,int dst,int tmp,struct operand *op,char *cond)
{
	int x;
	if(op->tab->storage==0)
	{
		if(op->tab->reg>=8)
		{
			x=op->tab->reg-8;
			x=x*4+fun_stack_size;
		}
		else
		{
			x=op->tab->off;
		}
		if(x>=-255&&x<255)
		{
			outs(ins);
			if(strcmp(ins,"str")&&if_class_signed(op->tab->class))
			{
				outs("s");
			}
			outs(get_type(op->tab->class));
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",[r12,#");
			if(x<0)
			{
				outs("-");
				out_num32(-x);
			}
			else
			{
				out_num32(x);
			}
			outs("]\n");
		}
		else
		{
			outs("mov32");
			out_cond(cond);
			outs(" ");
			out_reg(tmp);
			outs(",");
			out_num32(x);
			outs("\n");
			
			outs(ins);
			if(strcmp(ins,"str")&&if_class_signed(op->tab->class))
			{
				outs("s");
			}
			outs(get_type(op->tab->class));
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",[r12,");
			out_reg(tmp);
			outs("]\n");
		}
	}
	else if(op->tab->storage==2)
	{
		outs("mov32");
		out_cond(cond);
		outs(" ");
		out_reg(tmp);
		outs(",@_$DATA+");
		out_num32(op->tab->off);
		outs("\n");

		outs(ins);
		if(strcmp(ins,"str")&&if_class_signed(op->tab->class))
		{
			outs("s");
		}
		outs(get_type(op->tab->class));
		out_cond(cond);
		outs(" ");
		out_reg(dst);
		outs(",[");
		out_reg(tmp);
		outs("]\n");
	}
	else if(op->tab->storage==1)
	{
		x=op->tab->off;
		x=x*4+8;
		if(x>=-255&&x<255)
		{
			outs(ins);
			if(strcmp(ins,"str")&&if_class_signed(op->tab->class))
			{
				outs("s");
			}
			outs(get_type(op->tab->class));
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",[r12,#");
			if(x<0)
			{
				outs("-");
				out_num32(-x);
			}
			else
			{
				out_num32(x);
			}
			outs("]\n");
		}
		else
		{
			outs("mov32");
			out_cond(cond);
			outs(" ");
			out_reg(tmp);
			outs(",");
			out_num32(x);
			outs("\n");
			
			outs(ins);
			if(strcmp(ins,"str")&&if_class_signed(op->tab->class))
			{
				outs("s");
			}
			outs(get_type(op->tab->class));
			out_cond(cond);
			outs(" ");
			out_reg(dst);
			outs(",[r12,");
			out_reg(tmp);
			outs("]\n");
		}
	}
}
int opcmp(struct operand *op1,struct operand *op2)
{
	int class1,class2;
	class1=0;
	class2=0;
	if(op_is_reg(op1))
	{
		class1=1;
	}
	else if(op_is_const(op1))
	{
		class1=2;
	}
	else if(op_is_addr(op1))
	{
		class1=3;
	}
	if(op_is_reg(op2))
	{
		class2=1;
	}
	else if(op_is_const(op2))
	{
		class2=2;
	}
	else if(op_is_addr(op2))
	{
		class2=3;
	}
	if(class1!=class2)
	{
		return 1;
	}
	if(class1==0)
	{
		if(op1->tab->storage!=op2->tab->storage)
		{
			return 1;
		}
		if(op1->tab->reg!=op2->tab->reg)
		{
			return 1;
		}
		if(op1->tab->off==op2->tab->off)
		{
			return 0;
		}
	}
	else if(class1==1)
	{
		if(op1->tab->reg==op2->tab->reg)
		{
			return 0;
		}
	}
	return 1;
}
char *fun_name;
#include "mov.c"
#include "basic_op.c"
#include "div.c"
#include "mod.c"
#include "rsh.c"
#include "branch.c"
#include "ld.c"
#include "st.c"
#include "call.c"
#include "not.c"
#include "neg.c"
#include "adr.c"
void write_msg(void)
{
	struct ins *ins;
	int x;
	int num;
	char *name;
	num=1;
	ins=ins_head;
	while(ins)
	{
		x=1;
		while(x<ins->count_args)
		{
			if(ins->args[x][0]=='\"'&&strcmp(ins->args[0],"asm"))
			{
				//TODO CHANGE
				outs(".align 2\n");
				name=xstrdup("_$MSG");
				name=str_i_app(name,num);
				outs("@");
				outs(name);
				outs("\n");
				outs(".string ");
				outs(ins->args[x]);
				outs("\n");
				free(ins->args[x]);
				ins->args[x]=name;
				++num;
			}
			++x;
		}
		ins=ins->next;
	}
}
void gen_code(struct ins *ins)
{
	unsigned int size;
	int x;
	int in_asm;
	if(ins->count_args)
	{
		if(!strcmp(ins->args[0],"mov"))
		{
			gen_mov(ins);
		}
		else if(!strcmp(ins->args[0],"add"))
		{
			gen_basic_op(ins,"add ");
		}
		else if(!strcmp(ins->args[0],"sub"))
		{
			gen_basic_op(ins,"sub ");
		}
		else if(!strcmp(ins->args[0],"and"))
		{
			gen_basic_op(ins,"and ");
		}
		else if(!strcmp(ins->args[0],"orr"))
		{
			gen_basic_op(ins,"orr ");
		}
		else if(!strcmp(ins->args[0],"eor"))
		{
			gen_basic_op(ins,"eor ");
		}
		else if(!strcmp(ins->args[0],"mul"))
		{
			gen_basic_op(ins,"mul ");
		}
		else if(!strcmp(ins->args[0],"div"))
		{
			gen_div(ins);
		}
		else if(!strcmp(ins->args[0],"mod"))
		{
			gen_mod(ins);
		}
		else if(!strcmp(ins->args[0],"lsh"))
		{
			gen_basic_op(ins,"lsl ");
		}
		else if(!strcmp(ins->args[0],"rsh"))
		{
			gen_rsh(ins);
		}
		else if(!strcmp(ins->args[0],"ble"))
		{
			gen_branch(ins,"ble ","bls ","bge ","bcs ");
		}
		else if(!strcmp(ins->args[0],"bge"))
		{
			gen_branch(ins,"bge ","bcs ","ble ","bls ");
		}
		else if(!strcmp(ins->args[0],"blt"))
		{
			gen_branch(ins,"blt ","bcc ","bgt ","bhi ");
		}
		else if(!strcmp(ins->args[0],"bgt"))
		{
			gen_branch(ins,"bgt ","bhi ","blt ","bcc ");
		}
		else if(!strcmp(ins->args[0],"beq"))
		{
			gen_branch(ins,"beq ","beq ","beq ","beq ");
		}
		else if(!strcmp(ins->args[0],"bne"))
		{
			gen_branch(ins,"bne ","bne ","bne ","bne ");
		}
		else if(!strcmp(ins->args[0],"ldb"))
		{
			gen_ld(ins,1);
		}
		else if(!strcmp(ins->args[0],"ldw"))
		{
			gen_ld(ins,3);
		}
		else if(!strcmp(ins->args[0],"ldl"))
		{
			gen_ld(ins,5);
		}
		else if(!strcmp(ins->args[0],"stb"))
		{
			gen_st(ins,1);
		}
		else if(!strcmp(ins->args[0],"stw"))
		{
			gen_st(ins,3);
		}
		else if(!strcmp(ins->args[0],"stl"))
		{
			gen_st(ins,5);
		}
		else if(!strcmp(ins->args[0],"ldob"))
		{
			gen_ldo(ins,1);
		}
		else if(!strcmp(ins->args[0],"ldow"))
		{
			gen_ldo(ins,3);
		}
		else if(!strcmp(ins->args[0],"ldol"))
		{
			gen_ldo(ins,5);
		}
		else if(!strcmp(ins->args[0],"stob"))
		{
			gen_sto(ins,1);
		}
		else if(!strcmp(ins->args[0],"stow"))
		{
			gen_sto(ins,3);
		}
		else if(!strcmp(ins->args[0],"stol"))
		{
			gen_sto(ins,5);
		}
		else if(!strcmp(ins->args[0],"push"))
		{
			gen_push(ins);
		}
		else if(!strcmp(ins->args[0],"call"))
		{
			gen_call(ins);
		}
		else if(!strcmp(ins->args[0],"retval"))
		{
			gen_retval(ins);
		}
		else if(!strcmp(ins->args[0],"not"))
		{
			gen_not(ins);
		}
		else if(!strcmp(ins->args[0],"neg"))
		{
			gen_neg(ins);
		}
		else if(!strcmp(ins->args[0],"adr"))
		{
			gen_adr(ins);
		}
		else if(!strcmp(ins->args[0],"adro"))
		{
			gen_adro(ins);
		}
		else if(!strcmp(ins->args[0],"del"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			size=const_to_num(ins->args[1])*4;
			if(is_valid_imm(size))
			{
				outs("add");
				out_cond(ins->cond);
				outs(" r13,r13,#");
				out_num32(size);
				outs("\n");
			}
			else
			{
				outs("mov32");
				out_cond(ins->cond);
				outs(" r1,");
				out_num32(size);
				outs("\n");
				outs("add");
				out_cond(ins->cond);
				outs(" r13,r13,r1\n");
			}
		}
		else if(!strcmp(ins->args[0],"fun"))
		{
			int s;
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			fstart=ins;
			fun_name=ins->args[1];
			fun_stack_size=ins->stack_size;
			out_label(fun_name);
			outs("stmdb r13!,{r12,r14}\n");
			outs("mov r12,r13\n");
			if(ins->stack_size)
			{
				if(is_valid_imm(-ins->stack_size))
				{
					outs("sub r13,r13,#");
					out_num32(-ins->stack_size);
					outs("\n");
				}
				else
				{
					outs("mov32 r0,");
					out_num32(-ins->stack_size);
					outs("\nsub r13,r13,r0\n");
				}
			}
			if(ins->used_regs&0xff)
			{
				x=0;
				s=0;
				outs("stmdb r13!,");
				while(x<8)
				{
					if(ins->used_regs&1<<x)
					{
						if(s)
						{
							outs(",");
						}
						else
						{
							outs("{");
						}
						out_reg(x+4);
						s=1;
					}
					++x;
				}
				outs("}\n");
				x=0;
				while(x<8)
				{
					if(ins->used_regs&1<<x)
					{
						int val;
						if((val=ins->arg_map[x])!=-1)
						{
							val=val*4+8;
							if(val<4095)
							{
								outs("ldr ");
								out_reg(x+4);
								outs(",[r12,#");
								out_num32(val);
								outs("]\n");
							}
							else
							{
								outs("mov32 r0,");
								out_num32(val);
								outs("\n");
								outs("ldr ");
								out_reg(x+4);
								outs(",[r12,r0]\n");
							}
						}
					}
					++x;
				}
			}
		}
		else if(!strcmp(ins->args[0],"endf"))
		{
			int s;
			if(fun_name)
			{
				outs("@");
				out_label_name(fun_name);
				outs("$END\n");
				if(fstart->used_regs&0xff)
				{
					x=0;
					s=0;
					outs("ldmia r13!,");
					while(x<8)
					{
						if(fstart->used_regs&1<<x)
						{
							if(s)
							{
								outs(",");
							}
							else
							{
								outs("{");
							}
							out_reg(x+4);
							s=1;
						}
						++x;
					}
					outs("}\n");
				}
				outs("mov r13,r12\nldmia r13!,{r12,r15}\n.end_fun\n");
				fstart=0;
			}
			else
			{
				error(ins->line,"endf without fun.");
			}
			fun_name=0;
		}
		else if(!strcmp(ins->args[0],"ret"))
		{
			struct ins *p;
			p=ins->next;
			while(p)
			{
				if(p->op)
				{
					outs("b");
					out_cond(ins->cond);
					outs(" @");
					outs(fun_name);
					outs("$END\n");
					break;
				}
				if(p->count_args&&!strcmp(p->args[0],"endf"))
				{
					break;
				}
				p=p->next;
			}
		}
		else if(!strcmp(ins->args[0],"bal"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			outs("b");
			out_cond(ins->cond);
			outs(" @_$LB");
			outs(ins->args[1]);
			outs("\n");
		}
		else if(!strcmp(ins->args[0],"label"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			outs("@_$LB");
			outs(ins->args[1]);
			outs("\n");
		}
		else if(!strcmp(ins->args[0],"asm"))
		{
			if(ins->count_args<2)
			{
				error(ins->line,"too few arguments.");
			}
			out_str(ins->args[1]);
			outs("\n");
		}
	}
}
