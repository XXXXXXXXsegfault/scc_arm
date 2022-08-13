void ins_init_cmp(void)
{
	ins_add("cmp~ R1,#I","~ 0 0 1 1 0 1 0 1 R1 0 0 0 0 I");
	ins_add("cmp~ R1,R2","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 0 0 0 0 0 0 0 0 R2");
	ins_add("cmp~ R1,R2,lsl #O","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 Sh 0 0 0 R2");
	ins_add("cmp~ R1,R2,lsr #O","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 Sh 0 1 0 R2");
	ins_add("cmp~ R1,R2,asr #O","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 Sh 1 0 0 R2");
	ins_add("cmp~ R1,R2,ror #O","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 Sh 1 1 0 R2");
	ins_add("cmp~ R1,R2,lsl R3","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 R3 0 0 0 1 R2");
	ins_add("cmp~ R1,R2,lsr R3","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 R3 0 0 1 1 R2");
	ins_add("cmp~ R1,R2,asr R3","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 R3 0 1 0 1 R2");
	ins_add("cmp~ R1,R2,ror R3","~ 0 0 0 1 0 1 0 1 R1 0 0 0 0 R3 0 1 1 1 R2");
	ins_add("tst~ R1,#I","~ 0 0 1 1 0 0 0 1 R1 0 0 0 0 I");
	ins_add("tst~ R1,R2","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 0 0 0 0 0 0 0 0 R2");
	ins_add("tst~ R1,R2,lsl #O","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 Sh 0 0 0 R2");
	ins_add("tst~ R1,R2,lsr #O","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 Sh 0 1 0 R2");
	ins_add("tst~ R1,R2,asr #O","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 Sh 1 0 0 R2");
	ins_add("tst~ R1,R2,ror #O","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 Sh 1 1 0 R2");
	ins_add("tst~ R1,R2,lsl R3","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 R3 0 0 0 1 R2");
	ins_add("tst~ R1,R2,lsr R3","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 R3 0 0 1 1 R2");
	ins_add("tst~ R1,R2,asr R3","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 R3 0 1 0 1 R2");
	ins_add("tst~ R1,R2,ror R3","~ 0 0 0 1 0 0 0 1 R1 0 0 0 0 R3 0 1 1 1 R2");
}
