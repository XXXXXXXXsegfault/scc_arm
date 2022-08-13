void ins_init_eor(void)
{
	ins_add("eor~ R1,R2,R3","~ 0 0 0 0 0 0 1 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("eor~ R1,R2,R3,lsl #O","~ 0 0 0 0 0 0 1 0 R2 R1 Sh 0 0 0 R3");
	ins_add("eor~ R1,R2,R3,lsr #O","~ 0 0 0 0 0 0 1 0 R2 R1 Sh 0 1 0 R3");
	ins_add("eor~ R1,R2,R3,asr #O","~ 0 0 0 0 0 0 1 0 R2 R1 Sh 1 0 0 R3");
	ins_add("eor~ R1,R2,R3,ror #O","~ 0 0 0 0 0 0 1 0 R2 R1 Sh 1 1 0 R3");
	ins_add("eor~ R1,R2,R3,lsl R4","~ 0 0 0 0 0 0 1 0 R2 R1 R4 0 0 0 1 R3");
	ins_add("eor~ R1,R2,R3,lsr R4","~ 0 0 0 0 0 0 1 0 R2 R1 R4 0 0 1 1 R3");
	ins_add("eor~ R1,R2,R3,asr R4","~ 0 0 0 0 0 0 1 0 R2 R1 R4 0 1 0 1 R3");
	ins_add("eor~ R1,R2,R3,ror R4","~ 0 0 0 0 0 0 1 0 R2 R1 R4 0 1 1 1 R3");
	ins_add("eors~ R1,R2,R3","~ 0 0 0 0 0 0 1 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("eors~ R1,R2,R3,lsl #O","~ 0 0 0 0 0 0 1 1 R2 R1 Sh 0 0 0 R3");
	ins_add("eors~ R1,R2,R3,lsr #O","~ 0 0 0 0 0 0 1 1 R2 R1 Sh 0 1 0 R3");
	ins_add("eors~ R1,R2,R3,asr #O","~ 0 0 0 0 0 0 1 1 R2 R1 Sh 1 0 0 R3");
	ins_add("eors~ R1,R2,R3,ror #O","~ 0 0 0 0 0 0 1 1 R2 R1 Sh 1 1 0 R3");
	ins_add("eors~ R1,R2,R3,lsl R4","~ 0 0 0 0 0 0 1 1 R2 R1 R4 0 0 0 1 R3");
	ins_add("eors~ R1,R2,R3,lsr R4","~ 0 0 0 0 0 0 1 1 R2 R1 R4 0 0 1 1 R3");
	ins_add("eors~ R1,R2,R3,asr R4","~ 0 0 0 0 0 0 1 1 R2 R1 R4 0 1 0 1 R3");
	ins_add("eors~ R1,R2,R3,ror R4","~ 0 0 0 0 0 0 1 1 R2 R1 R4 0 1 1 1 R3");
	ins_add("eor~ R1,R2,#I","~ 0 0 1 0 0 0 1 0 R2 R1 I");
	ins_add("eors~ R1,R2,#I","~ 0 0 1 0 0 0 1 1 R2 R1 I");
}
