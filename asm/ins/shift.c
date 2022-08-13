void ins_init_shift(void)
{
	ins_add("lsl~ R1,R2,R3","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 R3 0 0 0 1 R2");
	ins_add("lsr~ R1,R2,R3","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 R3 0 0 1 1 R2");
	ins_add("asr~ R1,R2,R3","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 R3 0 1 0 1 R2");
	ins_add("ror~ R1,R2,R3","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 R3 0 1 1 1 R2");
	ins_add("lsl~ R1,R2,#O","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 Sh 0 0 0 R2");
	ins_add("lsr~ R1,R2,#O","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 Sh 0 1 0 R2");
	ins_add("asr~ R1,R2,#O","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 Sh 1 0 0 R2");
	ins_add("ror~ R1,R2,#O","~ 0 0 0 1 1 0 1 0 0 0 0 0 R1 Sh 1 1 0 R2");
	ins_add("lsls~ R1,R2,R3","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 R3 0 0 0 1 R2");
	ins_add("lsrs~ R1,R2,R3","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 R3 0 0 1 1 R2");
	ins_add("asrs~ R1,R2,R3","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 R3 0 1 0 1 R2");
	ins_add("rors~ R1,R2,R3","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 R3 0 1 1 1 R2");
	ins_add("lsls~ R1,R2,#O","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 Sh 0 0 0 R2");
	ins_add("lsrs~ R1,R2,#O","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 Sh 0 1 0 R2");
	ins_add("asrs~ R1,R2,#O","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 Sh 1 0 0 R2");
	ins_add("rors~ R1,R2,#O","~ 0 0 0 1 1 0 1 1 0 0 0 0 R1 Sh 1 1 0 R2");
}
