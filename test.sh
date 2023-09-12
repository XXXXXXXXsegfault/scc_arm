#!/bin/sh -ev
[ -x scpp ]
[ -x scc ]
[ -x bcode ]
[ -x asm ]
[ -x include ]
build/scpp scpp/main.c build/scpp.i
build/scpp scc/main.c build/scc.i
build/scpp bcode/main.c build/bcode.i
build/scpp asm/main.c build/asm.i
build/scc build/scpp.i build/scpp.bcode
build/scc build/scc.i build/scc.bcode
build/scc build/bcode.i build/bcode.bcode
build/scc build/asm.i build/asm.bcode
build/bcode build/scpp.bcode build/scpp.asm
build/bcode build/scc.bcode build/scc.asm
build/bcode build/bcode.bcode build/bcode.asm
build/bcode build/asm.bcode build/asm.asm
build/asm build/scpp.asm build/scpp.test
build/asm build/scc.asm build/scc.test
build/asm build/bcode.asm build/bcode.test
build/asm build/asm.asm build/asm.test
cmp build/scpp build/scpp.test
cmp build/scc build/scc.test
cmp build/bcode build/bcode.test
cmp build/asm build/asm.test
echo OK
