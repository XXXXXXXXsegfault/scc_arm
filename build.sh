#!/bin/sh -ev
mkdir -p build
bin/scpp scpp/main.c build/scpp.i
bin/scpp scc_main.c build/scc.i
bin/scpp asm/main.c build/asm.i
bin/scc build/scpp.i build/scpp.asm
bin/scc build/scc.i build/scc.asm
bin/scc build/asm.i build/asm.asm
bin/asm build/scpp.asm build/scpp
bin/asm build/scc.asm build/scc
bin/asm build/asm.asm build/asm
