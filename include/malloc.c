/*
 * NOTE: This implementation has no multithreading support.
 *
 * */

#define MALLOC_MAGIC 0xe38859e8
#define MALLOC_MAGIC2 0x8b62ea66
#define MALLOC_TABLEN 1021
unsigned int __malloc_count_del;
struct __malloc_zone
{
	unsigned int magic;
	unsigned char start_color;
	unsigned char end_color;
	unsigned char color;
	unsigned char used;
	unsigned int *block_links;
	unsigned int size;
	struct __malloc_zone *start_left;
	struct __malloc_zone *start_right;
	struct __malloc_zone *start_parent;
	struct __malloc_zone *end_left;
	struct __malloc_zone *end_right;
	struct __malloc_zone *end_parent;
	struct __malloc_zone *left;
	struct __malloc_zone *right;
	struct __malloc_zone *parent;
};
#define RBTREE_TYPE struct __malloc_zone
#define RBTREE_CMP(n1,n2) ((n1)->size>(n2)->size||(n1)->size==(n2)->size&&(unsigned int)(n1)>(unsigned int)(n2))
#define RBTREE_LEFT left
#define RBTREE_RIGHT right
#define RBTREE_PARENT parent
#define RBTREE_COLOR color
#define RBTREE_INSERT __malloc_zone_size_add
#define RBTREE_DELETE __malloc_zone_size_del
#include "templates/rbtree.c"
#define RBTREE_TYPE struct __malloc_zone
#define RBTREE_CMP(n1,n2) ((unsigned int)(n1)>(unsigned int)(n2))
#define RBTREE_LEFT start_left
#define RBTREE_RIGHT start_right
#define RBTREE_PARENT start_parent
#define RBTREE_COLOR start_color
#define RBTREE_INSERT __malloc_zone_start_add
#define RBTREE_DELETE __malloc_zone_start_del
#include "templates/rbtree.c"
#define RBTREE_TYPE struct __malloc_zone
#define RBTREE_CMP(n1,n2) ((unsigned int)(n1)+(n1)->size>(unsigned int)(n2)+(n2)->size)
#define RBTREE_LEFT end_left
#define RBTREE_RIGHT end_right
#define RBTREE_PARENT end_parent
#define RBTREE_COLOR end_color
#define RBTREE_INSERT __malloc_zone_end_add
#define RBTREE_DELETE __malloc_zone_end_del
#include "templates/rbtree.c"
char *__current_brk;
unsigned int __heap_size;
void *__set_heap_size(unsigned int size)
{
	char *new_brk,*old_brk;
	if(__current_brk==0)
	{
		__current_brk=brk(0);
	}
	old_brk=__current_brk+__heap_size;
	new_brk=brk(__current_brk+size);
	if(new_brk==old_brk&&size!=__heap_size)
	{
		return 0;
	}
	__heap_size=size;
	return old_brk;
}

struct __malloc_zone *__malloc_start_tab[MALLOC_TABLEN],*__malloc_end_tab[MALLOC_TABLEN],*__malloc_zone_root;
void __malloc_zone_start_tab_add(struct __malloc_zone *node)
{
	unsigned int addr;
	int hash;
	addr=(unsigned int)node;
	hash=(addr>>16|addr<<16)%MALLOC_TABLEN;
	__malloc_zone_start_add(__malloc_start_tab+hash,node);
}
void __malloc_zone_end_tab_add(struct __malloc_zone *node)
{
	unsigned int addr;
	int hash;
	addr=(unsigned int)node+node->size;
	hash=(addr>>16|addr<<16)%MALLOC_TABLEN;
	__malloc_zone_end_add(__malloc_end_tab+hash,node);
}
void __malloc_zone_start_tab_del(struct __malloc_zone *ptr)
{
	unsigned int addr;
	int hash;
	addr=(unsigned int)ptr;
	hash=(addr>>16|addr<<16)%MALLOC_TABLEN;
	__malloc_zone_start_del(__malloc_start_tab+hash,ptr);
}
void __malloc_zone_end_tab_del(struct __malloc_zone *ptr)
{
	unsigned int addr;
	int hash;
	addr=(unsigned int)ptr+ptr->size;
	hash=(addr>>16|addr<<16)%MALLOC_TABLEN;
	__malloc_zone_end_del(__malloc_end_tab+hash,ptr);
}
struct __malloc_zone *__malloc_zone_start_tab_find(void *ptr)
{
	unsigned int addr;
	int hash;
	struct __malloc_zone *node;
	addr=(unsigned int)ptr;
	hash=(addr>>16|addr<<16)%MALLOC_TABLEN;
	node=__malloc_start_tab[hash];
	while(node&&(unsigned int)node!=addr)
	{
		if((unsigned int)node>addr)
		{
			node=node->start_left;
		}
		else
		{
			node=node->start_right;
		}
	}
	return node;
}
struct __malloc_zone *__malloc_zone_end_tab_find(void *ptr)
{
	unsigned int addr;
	int hash;
	struct __malloc_zone *node;
	addr=(unsigned int)ptr;
	hash=(addr>>16|addr<<16)%MALLOC_TABLEN;
	node=__malloc_end_tab[hash];
	while(node&&(unsigned int)node+node->size!=addr)
	{
		if((unsigned int)node+node->size>addr)
		{
			node=node->end_left;
		}
		else
		{
			node=node->end_right;
		}
	}
	return node;
}
struct __malloc_zone *__malloc_zone_size_find(unsigned int size)
{
	struct __malloc_zone *node,*p;
	node=__malloc_zone_root;
	p=0;
	while(node)
	{
		if(node->size>=size)
		{
			p=node;
			node=node->left;
		}
		else
		{
			node=node->right;
		}
	}
	return p;
}
void __malloc_error(void)
{
	write(2,"invalid pointer or corruption detected.\n",40);
	while(1)
	{
		asm ".long 0xffffffff"
	}
}
void __malloc_zone_add(struct __malloc_zone *node)
{
	if(node->magic!=MALLOC_MAGIC)
	{
		__malloc_error();
	}
	node->used=0;
	__malloc_zone_size_add(&__malloc_zone_root,node);
	__malloc_zone_start_tab_add(node);
	__malloc_zone_end_tab_add(node);
}
void __malloc_zone_del(struct __malloc_zone *node)
{
	if(node->magic!=MALLOC_MAGIC)
	{
		__malloc_error();
	}
	node->used=0;
	__malloc_zone_size_del(&__malloc_zone_root,node);
	__malloc_zone_start_tab_del(node);
	__malloc_zone_end_tab_del(node);
}
void *__malloc(unsigned int size)
{
	unsigned int size1,size2;
	struct __malloc_zone *zone,*new_zone;
	int hash;
	int type;
	void *ret;
	if(size==0)
	{
		return 0;
	}
	size1=((size-1>>4)+1<<4)+32;
	if(size1<80)
	{
		size1=80;
	}
	zone=__malloc_zone_size_find(size1);
	if(zone==0)
	{
		if(size1<0x1000)
		{
			size2=0x10000;
		}
		else if(size1<0x8000)
		{
			size2=0x20000;
		}
		else
		{
			size2=size1*4;
		}
		size2=(size2-1>>12)+1<<12;
		if(!(zone=__set_heap_size(__heap_size+size2)))
		{
			size2=size1;
			size2=(size2-1>>12)+1<<12;
			if(!(zone=__set_heap_size(__heap_size+size2)))
			{
				return 0;
			}
		}
		zone->size=size2;
		zone->magic=MALLOC_MAGIC;
	}
	else
	{
		__malloc_zone_del(zone);
	}
	ret=(char *)zone+16;
	if(size1>zone->size)
	{
		__malloc_error();
	}
	if(size1+128<zone->size)
	{
		new_zone=(void *)((char *)zone+size1);
		new_zone->magic=MALLOC_MAGIC;
		new_zone->size=zone->size-size1;
		__malloc_zone_add(new_zone);
		zone->size=size1;
	}
	zone->used=1;
	return ret;
}
struct __malloc_cache
{
	unsigned int bmp;
	struct __malloc_cache *next;
	struct __malloc_cache *prev;
	unsigned int index;
} *__malloc_cache_tab[140],*__malloc_cache_tab2[140];
struct __malloc_cache2
{
	unsigned int magic;
	unsigned int mbz;
	struct __malloc_cache *block;
	unsigned int index;
};
unsigned int __malloc_cache_num[140];
int __malloc_cache_index_get(unsigned int size,unsigned int *size1)
{
	int x;
	x=0;
	*size1=4;
	while(*size1<<5<size)
	{
		*size1=(*size1*9>>3)+1;
		++x;
	}
	*size1<<=5;
	return x;
}
void __free(struct __malloc_zone *zone)
{
	struct __malloc_zone *start,*end;
	__malloc_zone_add(zone);
	if(start=__malloc_zone_end_tab_find(zone))
	{
		__malloc_zone_del(zone);
		__malloc_zone_del(start);
		start->size+=zone->size;
		__malloc_zone_add(start);
		zone=start;
	}
	if(end=__malloc_zone_start_tab_find((char *)zone+zone->size))
	{
		__malloc_zone_del(zone);
		__malloc_zone_del(end);
		zone->size+=end->size;
		__malloc_zone_add(zone);
	}
	if((char *)zone+zone->size==__current_brk+__heap_size&&zone->size>=32768)
	{
		__malloc_zone_del(zone);
		__set_heap_size(__heap_size-zone->size);
	}
}
void free(void *ptr)
{
	struct __malloc_zone *zone;
	struct __malloc_cache2 *cache2;
	struct __malloc_cache *cache;
	int x;
	if(!ptr)
	{
		return;
	}
	zone=(void *)((char *)ptr-16);
	if(zone->magic==MALLOC_MAGIC2)
	{
		cache2=(void *)zone;
		cache2->magic=0;
		cache=cache2->block;
		x=cache->index;
		if(cache->bmp==0xffffffff)
		{
			cache->next=__malloc_cache_tab[x];
			cache->prev=0;
			if(__malloc_cache_tab[x])
			{
				__malloc_cache_tab[x]->prev=cache;
			}
			__malloc_cache_tab[x]=cache;
		}
		cache->bmp&=~(1<<cache2->index);
		if(cache->bmp!=0)
		{
			return;
		}
		if(cache->prev)
		{
			cache->prev->next=cache->next;
		}
		else
		{
			__malloc_cache_tab[x]=cache->next;
		}
		if(cache->next)
		{
			cache->next->prev=cache->prev;
		}
		if(__malloc_cache_num[x]<4)
		{
			cache->next=__malloc_cache_tab2[x];
			__malloc_cache_tab2[x]=cache;
			++__malloc_cache_num[x];
			return;
		}
		zone=(void *)((char *)cache-16);
	}
	if(zone->used!=1)
	{
		__malloc_error();
	}
	__free(zone);
}
void *malloc(unsigned int size)
{
	int x,x1;
	struct __malloc_cache *ptr;
	struct __malloc_cache2 *ptr2;
	unsigned int size1;
	x=__malloc_cache_index_get(size+16,&size1);
	if(ptr=__malloc_cache_tab[x])
	{
		x1=0;
		while(ptr->bmp&1<<x1)
		{
			++x1;
			if(x1==32)
			{
				__malloc_error();
			}
		}
		if((ptr->bmp|=1<<x1)==0xffffffff)
		{
			if(ptr->next)
			{
				ptr->next->prev=0;
			}
			__malloc_cache_tab[x]=ptr->next;
		}
		ptr2=(void *)((char *)(ptr+1)+size1*x1);
		ptr2->magic=MALLOC_MAGIC2;
		ptr2->block=ptr;
		ptr2->index=x1;
		ptr2->mbz=0;
		return ptr2+1;
	}
	if(ptr=__malloc_cache_tab2[x])
	{
		__malloc_cache_tab2[x]=ptr->next;
		--__malloc_cache_num[x];
		ptr->bmp=1;
		ptr->index=x;
		ptr->next=__malloc_cache_tab[x];
		ptr->prev=0;
		if(__malloc_cache_tab[x])
		{
			__malloc_cache_tab[x]->prev=ptr;
		}
		__malloc_cache_tab[x]=ptr;
		ptr2=(void *)((char *)(ptr+1));
		ptr2->magic=MALLOC_MAGIC2;
		ptr2->block=ptr;
		ptr2->index=0;
		ptr2->mbz=0;
		return ptr2+1;
	}
	if(ptr=__malloc(size1*32+16))
	{
		ptr->bmp=1;
		ptr->index=x;
		ptr->next=__malloc_cache_tab[x];
		ptr->prev=0;
		if(__malloc_cache_tab[x])
		{
			__malloc_cache_tab[x]->prev=ptr;
		}
		__malloc_cache_tab[x]=ptr;
		ptr2=(void *)((char *)(ptr+1));
		ptr2->magic=MALLOC_MAGIC2;
		ptr2->block=ptr;
		ptr2->index=0;
		ptr2->mbz=0;
		return ptr2+1;
	}
	return __malloc(size);
}
#undef MALLOC_TABLEN
#undef MALLOC_MAGIC
#undef MALLOC_MAGIC2
