void ins_init_mov(void)
{
	ins_add("mov~ R1,#I","~ 0 0 1 1 1 0 1 0 0 0 0 0 R1 I");
	ins_add("movs~ R1,R2","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 0 0 0 0 0 0 0 0 R2");
	ins_add("mov~ R1,R2","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 0 0 0 0 0 0 0 0 R2");
	ins_add("mvn~ R1,#I","~ 0 0 1 1 1 1 1 0 0 0 0 0 R1 I");
	ins_add("mvns~ R1,R2","~ 0 0 0 1 1 1 1 1 0 0 0 0 R1 0 0 0 0 0 0 0 0 R2");
	ins_add("mvn~ R1,R2","~ 0 0 0 1 1 1 1 0 0 0 0 0 R1 0 0 0 0 0 0 0 0 R2");
	ins_add("mov32~ R1,I","~ 0 0 1 1 1 0 1 0 0 0 0 0 R1 I");
	ins_add("mov32~ R1,NI","~ 0 0 1 1 1 1 1 0 0 0 0 0 R1 I");
}
#include "shift.c"
#include "add.c"
#include "sub.c"
#include "and.c"
#include "orr.c"
#include "eor.c"
#include "md.c"
#include "cmp.c"
#include "ldst.c"
void ins_init(void)
{
	ins_init_mov();
	ins_init_shift();
	ins_init_add();
	ins_init_sub();
	ins_init_and();
	ins_init_orr();
	ins_init_eor();
	ins_init_md();
	ins_init_cmp();
	ins_init_ldst();

	ins_add("swi~ N","~ 1 1 1 1 D");
	ins_add("bx~ R1","~ 0 0 0 1 0 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 1 R1");
	ins_add("blx~ R1","~ 0 0 0 1 0 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1 R1");
	ins_add("stm~ R1,M","~ 1 0 0 0 1 0 0 0 R1 M");
	ins_add("stmdb~ R1!,M","~ 1 0 0 1 0 0 1 0 R1 M");
	ins_add("stmda~ R1!,M","~ 1 0 0 0 0 0 1 0 R1 M");
	ins_add("stmib~ R1!,M","~ 1 0 0 1 1 0 1 0 R1 M");
	ins_add("stmia~ R1!,M","~ 1 0 0 0 1 0 1 0 R1 M");
	ins_add("ldm~ R1,M","~ 1 0 0 0 1 0 0 1 R1 M");
	ins_add("ldmdb~ R1!,M","~ 1 0 0 1 0 0 1 1 R1 M");
	ins_add("ldmda~ R1!,M","~ 1 0 0 0 0 0 1 1 R1 M");
	ins_add("ldmib~ R1!,M","~ 1 0 0 1 1 0 1 1 R1 M");
	ins_add("ldmia~ R1!,M","~ 1 0 0 0 1 0 1 1 R1 M");
}
