void ins_init_md(void)
{
	ins_add("mul~ R1,R2,R3","~ 0 0 0 0 0 0 0 0 R1 0 0 0 0 R3 1 0 0 1 R2");
	ins_add("mls~ R1,R2,R3,R4","~ 0 0 0 0 0 1 1 0 R1 R4 R3 1 0 0 1 R2");
	ins_add("udiv~ R1,R2,R3","~ 0 1 1 1 0 0 1 1 R1 1 1 1 1 R3 0 0 0 1 R2");
	ins_add("sdiv~ R1,R2,R3","~ 0 1 1 1 0 0 0 1 R1 1 1 1 1 R3 0 0 0 1 R2");
}
