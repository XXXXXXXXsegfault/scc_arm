void ins_init_ldst(void)
{
	ins_add("ldr~ R1,[R2]","~ 0 1 0 1 1 0 0 1 R2 R1 0 0 0 0 0 0 0 0 0 0 0 0");
	ins_add("str~ R1,[R2]","~ 0 1 0 1 1 0 0 0 R2 R1 0 0 0 0 0 0 0 0 0 0 0 0");
	ins_add("str~ R1,[R2,#-O]!","~ 0 1 0 1 0 0 1 0 R2 R1 O");
	ins_add("str~ R1,[R2,#-O]","~ 0 1 0 1 0 0 0 0 R2 R1 O");
	ins_add("str~ R1,[R2,#O]!","~ 0 1 0 1 1 0 1 0 R2 R1 O");
	ins_add("str~ R1,[R2,#O]","~ 0 1 0 1 1 0 0 0 R2 R1 O");
	ins_add("ldr~ R1,[R2,#-O]!","~ 0 1 0 1 0 0 1 1 R2 R1 O");
	ins_add("ldr~ R1,[R2,#-O]","~ 0 1 0 1 0 0 0 1 R2 R1 O");
	ins_add("ldr~ R1,[R2,#O]!","~ 0 1 0 1 1 0 1 1 R2 R1 O");
	ins_add("ldr~ R1,[R2,#O]","~ 0 1 0 1 1 0 0 1 R2 R1 O");
	ins_add("ldr~ R1,[R2,R3]","~ 0 1 1 1 1 0 0 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("ldr~ R1,[R2,R3]!","~ 0 1 1 1 1 0 1 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("str~ R1,[R2,R3]","~ 0 1 1 1 1 0 0 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("str~ R1,[R2,R3]!","~ 0 1 1 1 1 0 1 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("ldr~ R1,[R2],R3","~ 0 1 1 0 1 0 0 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("str~ R1,[R2],R3","~ 0 1 1 0 1 0 0 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("ldr~ R1,[R2],#O","~ 0 1 0 0 1 0 0 1 R2 R1 O");
	ins_add("ldr~ R1,[R2],#-O","~ 0 1 0 0 0 0 0 1 R2 R1 O");
	ins_add("str~ R1,[R2],#O","~ 0 1 0 0 1 0 0 0 R2 R1 O");
	ins_add("str~ R1,[R2],#-O","~ 0 1 0 0 0 0 0 0 R2 R1 O");


	ins_add("ldrb~ R1,[R2]","~ 0 1 0 1 1 1 0 1 R2 R1 0 0 0 0 0 0 0 0 0 0 0 0");
	ins_add("strb~ R1,[R2]","~ 0 1 0 1 1 1 0 0 R2 R1 0 0 0 0 0 0 0 0 0 0 0 0");
	ins_add("strb~ R1,[R2,#-O]!","~ 0 1 0 1 0 1 1 0 R2 R1 O");
	ins_add("strb~ R1,[R2,#-O]","~ 0 1 0 1 0 1 0 0 R2 R1 O");
	ins_add("strb~ R1,[R2,#O]!","~ 0 1 0 1 1 1 1 0 R2 R1 O");
	ins_add("strb~ R1,[R2,#O]","~ 0 1 0 1 1 1 0 0 R2 R1 O");
	ins_add("ldrb~ R1,[R2,#-O]!","~ 0 1 0 1 0 1 1 1 R2 R1 O");
	ins_add("ldrb~ R1,[R2,#-O]","~ 0 1 0 1 0 1 0 1 R2 R1 O");
	ins_add("ldrb~ R1,[R2,#O]!","~ 0 1 0 1 1 1 1 1 R2 R1 O");
	ins_add("ldrb~ R1,[R2,#O]","~ 0 1 0 1 1 1 0 1 R2 R1 O");
	ins_add("ldrb~ R1,[R2,R3]","~ 0 1 1 1 1 1 0 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("ldrb~ R1,[R2,R3]!","~ 0 1 1 1 1 1 1 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("strb~ R1,[R2,R3]","~ 0 1 1 1 1 1 0 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("strb~ R1,[R2,R3]!","~ 0 1 1 1 1 1 1 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("ldrb~ R1,[R2],R3","~ 0 1 1 0 1 1 0 1 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("strb~ R1,[R2],R3","~ 0 1 1 0 1 1 0 0 R2 R1 0 0 0 0 0 0 0 0 R3");
	ins_add("ldrb~ R1,[R2],#O","~ 0 1 0 0 1 1 0 1 R2 R1 O");
	ins_add("ldrb~ R1,[R2],#-O","~ 0 1 0 0 0 1 0 1 R2 R1 O");
	ins_add("strb~ R1,[R2],#O","~ 0 1 0 0 1 1 0 0 R2 R1 O");
	ins_add("strb~ R1,[R2],#-O","~ 0 1 0 0 0 1 0 0 R2 R1 O");


	ins_add("ldrh~ R1,[R2]","~ 0 0 0 1 1 1 0 1 R2 R1 0 0 0 0 1 0 1 1 0 0 0 0");
	ins_add("strh~ R1,[R2]","~ 0 0 0 1 1 1 0 0 R2 R1 0 0 0 0 1 0 1 1 0 0 0 0");
	ins_add("strh~ R1,[R2,#-O8]!","~ 0 0 0 1 0 1 1 0 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("strh~ R1,[R2,#-O8]","~ 0 0 0 1 0 1 0 0 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("strh~ R1,[R2,#O8]!","~ 0 0 0 1 1 1 1 0 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("strh~ R1,[R2,#O8]","~ 0 0 0 1 1 1 0 0 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("ldrh~ R1,[R2,#-O8]!","~ 0 0 0 1 0 1 1 1 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("ldrh~ R1,[R2,#-O8]","~ 0 0 0 1 0 1 0 1 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("ldrh~ R1,[R2,#O8]!","~ 0 0 0 1 1 1 1 1 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("ldrh~ R1,[R2,#O8]","~ 0 0 0 1 1 1 0 1 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("ldrh~ R1,[R2,R3]","~ 0 0 0 1 1 0 0 1 R2 R1 0 0 0 0 1 0 1 1 R3");
	ins_add("ldrh~ R1,[R2,R3]!","~ 0 0 0 1 1 0 1 1 R2 R1 0 0 0 0 1 0 1 1 R3");
	ins_add("strh~ R1,[R2,R3]","~ 0 0 0 1 1 0 0 0 R2 R1 0 0 0 0 1 0 1 1 R3");
	ins_add("strh~ R1,[R2,R3]!","~ 0 0 0 1 1 0 1 0 R2 R1 0 0 0 0 1 0 1 1 R3");
	ins_add("ldrh~ R1,[R2],R3","~ 0 0 0 0 1 0 0 1 R2 R1 0 0 0 0 1 0 1 1 R3");
	ins_add("strh~ R1,[R2],R3","~ 0 0 0 0 1 0 0 0 R2 R1 0 0 0 0 1 0 1 1 R3");
	ins_add("ldrh~ R1,[R2],#O8","~ 0 0 0 0 1 1 0 1 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("ldrh~ R1,[R2],#-O8","~ 0 0 0 0 0 1 0 1 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("strh~ R1,[R2],#O8","~ 0 0 0 0 1 1 0 0 R2 R1 0 0 0 0 1 0 1 1 O8");
	ins_add("strh~ R1,[R2],#-O8","~ 0 0 0 0 0 1 0 0 R2 R1 0 0 0 0 1 0 1 1 O8");


	ins_add("ldrsb~ R1,[R2]","~ 0 0 0 1 1 1 0 1 R2 R1 0 0 0 0 1 1 0 1 0 0 0 0");
	ins_add("ldrsb~ R1,[R2,#-O8]!","~ 0 0 0 1 0 1 1 1 R2 R1 0 0 0 0 1 1 0 1 O8");
	ins_add("ldrsb~ R1,[R2,#-O8]","~ 0 0 0 1 0 1 0 1 R2 R1 0 0 0 0 1 1 0 1 O8");
	ins_add("ldrsb~ R1,[R2,#O8]!","~ 0 0 0 1 1 1 1 1 R2 R1 0 0 0 0 1 1 0 1 O8");
	ins_add("ldrsb~ R1,[R2,#O8]","~ 0 0 0 1 1 1 0 1 R2 R1 0 0 0 0 1 1 0 1 O8");
	ins_add("ldrsb~ R1,[R2,R3]","~ 0 0 0 1 1 0 0 1 R2 R1 0 0 0 0 1 1 0 1 R3");
	ins_add("ldrsb~ R1,[R2,R3]!","~ 0 0 0 1 1 0 1 1 R2 R1 0 0 0 0 1 1 0 1 R3");
	ins_add("ldrsb~ R1,[R2],R3","~ 0 0 0 0 1 0 0 1 R2 R1 0 0 0 0 1 1 0 1 R3");
	ins_add("ldrsb~ R1,[R2],#O8","~ 0 0 0 0 1 1 0 1 R2 R1 0 0 0 0 1 1 0 1 O8");
	ins_add("ldrsb~ R1,[R2],#-O8","~ 0 0 0 0 0 1 0 1 R2 R1 0 0 0 0 1 1 0 1 O8");


	ins_add("ldrsh~ R1,[R2]","~ 0 0 0 1 1 1 0 1 R2 R1 0 0 0 0 1 1 1 1 0 0 0 0");
	ins_add("ldrsh~ R1,[R2,#-O8]!","~ 0 0 0 1 0 1 1 1 R2 R1 0 0 0 0 1 1 1 1 O8");
	ins_add("ldrsh~ R1,[R2,#-O8]","~ 0 0 0 1 0 1 0 1 R2 R1 0 0 0 0 1 1 1 1 O8");
	ins_add("ldrsh~ R1,[R2,#O8]!","~ 0 0 0 1 1 1 1 1 R2 R1 0 0 0 0 1 1 1 1 O8");
	ins_add("ldrsh~ R1,[R2,#O8]","~ 0 0 0 1 1 1 0 1 R2 R1 0 0 0 0 1 1 1 1 O8");
	ins_add("ldrsh~ R1,[R2,R3]","~ 0 0 0 1 1 0 0 1 R2 R1 0 0 0 0 1 1 1 1 R3");
	ins_add("ldrsh~ R1,[R2,R3]!","~ 0 0 0 1 1 0 1 1 R2 R1 0 0 0 0 1 1 1 1 R3");
	ins_add("ldrsh~ R1,[R2],R3","~ 0 0 0 0 1 0 0 1 R2 R1 0 0 0 0 1 1 1 1 R3");
	ins_add("ldrsh~ R1,[R2],#O8","~ 0 0 0 0 1 1 0 1 R2 R1 0 0 0 0 1 1 1 1 O8");
	ins_add("ldrsh~ R1,[R2],#-O8","~ 0 0 0 0 0 1 0 1 R2 R1 0 0 0 0 1 1 1 1 O8");

	ins_add("ldrex~ R1,[R2]","~ 0 0 0 1 1 0 0 1 R2 R1 1 1 1 1 1 0 0 1 1 1 1 1");
	ins_add("strex~ R1,R2,[R3]","~ 0 0 0 1 1 0 0 0 R3 R1 1 1 1 1 1 0 0 1 R2");
}
