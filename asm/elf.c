struct elf_header
{
	unsigned char ident[16];
	unsigned short int type;
	unsigned short int machine;
	unsigned int version;
	unsigned int entry;
	unsigned int phoff;
	unsigned int shoff;
	unsigned int flags;
	unsigned short int ehsize;
	unsigned short int phentsize;
	unsigned short int phnum;
	unsigned short int shentsize;
	unsigned short int shnum;
	unsigned short int shstrndx;
} elf_header;
struct elf_program_header
{
	unsigned int type;
	unsigned int offset;
	unsigned int vaddr;
	unsigned int paddr;
	unsigned int filesz;
	unsigned int memsz;
	unsigned int flags;
	unsigned int align;
};
char outc_buf[65536];
int outc_x;
void outc(char c)
{
	int n;
	if(outc_x==65536)
	{
		write(fdo,outc_buf,outc_x);
		outc_x=0;
	}
	outc_buf[outc_x]=c;
	++outc_x;
}
void out_flush(void)
{
	if(outc_x)
	{
		write(fdo,outc_buf,outc_x);
	}
}
void c_write(char *buf,int size)
{
	while(size)
	{
		outc(*buf);
		++buf;
		--size;
	}
}

void out_pos(unsigned int pos)
{
	int x;
	char *str;
	str="0123456789ABCDEF";
	x=32;
	while(x)
	{
		x-=4;
		write(fde,str+(pos>>x&0xf),1);
	}
}
void mkelf(void)
{
	struct elf_program_header phead[2];
	unsigned int addr,size;
	unsigned int pos;
	memcpy(&elf_header,"\x7f\x45\x4c\x46\x01\x01\x01",7);
	elf_header.type=2;
	elf_header.machine=0x28;
	elf_header.version=1;
	elf_header.phoff=0x34;
	elf_header.ehsize=0x34;
	elf_header.phentsize=0x20;
	elf_header.phnum=2;
	elf_header.shentsize=0x28;
	elf_header.flags=0x5000200;
	elf_header.entry=entry;
	write(fdo,&elf_header,0x34);
	phead[0].type=1;
	phead[0].flags=0x5;
	phead[0].offset=0;
	phead[0].vaddr=0x10000;
	phead[0].paddr=0x10000;
	phead[0].filesz=pc-0x10000;
	phead[0].memsz=pc-0x10000;
	phead[0].align=0x1000;
	phead[1].type=1;
	phead[1].flags=0x6;
	phead[1].offset=0;
	phead[1].vaddr=0x2000000;
	phead[1].paddr=0x2000000;
	phead[1].filesz=0;
	phead[1].memsz=data_size;
	phead[1].align=0x1000;
	write(fdo,phead,sizeof(phead));
	l=lines_head;
	pos=0x10074;
	while(l)
	{
		if(l->ins_len<=32)
		{
			c_write(l->ins_buf2,l->ins_len);
		}
		else
		{
			c_write(l->ins_buf,l->ins_len);
		}
		if(fde>=0)
		{
			out_pos(pos);
			write(fde,": ",2);
			write(fde,l->str,strlen(l->str));
			write(fde,"\n",1);
		}
		pos+=l->ins_len;
		l=l->next;
	}
	out_flush();
}
