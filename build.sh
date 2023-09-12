#!/bin/sh -ev
[ -x scpp ]
[ -x scc ]
[ -x bcode ]
[ -x asm ]
[ -x include ]
mkdir build
gcc scpp/main.c -o build/scpp.gcc
gcc scc/main.c -o build/scc.gcc
gcc bcode/main.c -o build/bcode.gcc
gcc asm/main.c -o build/asm.gcc
build/scpp.gcc scpp/main.c build/scpp.i
build/scpp.gcc scc/main.c build/scc.i
build/scpp.gcc bcode/main.c build/bcode.i
build/scpp.gcc asm/main.c build/asm.i
build/scc.gcc build/scpp.i build/scpp.bcode
build/scc.gcc build/scc.i build/scc.bcode
build/scc.gcc build/bcode.i build/bcode.bcode
build/scc.gcc build/asm.i build/asm.bcode
build/bcode.gcc build/scpp.bcode build/scpp.asm
build/bcode.gcc build/scc.bcode build/scc.asm
build/bcode.gcc build/bcode.bcode build/bcode.asm
build/bcode.gcc build/asm.bcode build/asm.asm
build/asm.gcc build/scpp.asm build/scpp
build/asm.gcc build/scc.asm build/scc
build/asm.gcc build/bcode.asm build/bcode
build/asm.gcc build/asm.asm build/asm
echo OK
