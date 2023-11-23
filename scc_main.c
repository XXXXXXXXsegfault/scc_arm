#include "include/lib.c"
#include "include/stream.c"
int fdi,fdo;
namespace scc_front;
#include "scc/main.c"
namespace scc_back;
#include "bcode/main.c"
namespace;
int main(int argc,char **argv)
{
	if(argc<3)
	{
		return 1;
	}
	fdi=open(argv[1],0,0);
	if(fdi<0)
	{
		return 1;
	}
	fdo=open(argv[2],578,0644);
	if(fdo<0)
	{
		return 1;
	}
	scc_front__scc_run();
	scc_back__bcode_run();
	close(fdi);
	close(fdo);
	return 0;
}
