struct stream
{
	unsigned char data[4084];
	int size;
	struct stream *next;
} *stream_start,*stream_end;
int stream_in_pos;
void stream_putc(int c)
{
	struct stream *node;
	if(stream_end&&stream_end->size<4084)
	{
		stream_end->data[stream_end->size]=c;
		++stream_end->size;
		return;
	}
	node=xmalloc(sizeof(*node));
	node->data[0]=c;
	node->size=1;
	node->next=0;
	if(stream_end)
	{
		stream_end->next=node;
	}
	else
	{
		stream_start=node;
	}
	stream_end=node;
}
int stream_getc(void)
{
	int c;
	struct stream *node;
	if(stream_start==0)
	{
		return -1;
	}
	c=(unsigned int)stream_start->data[stream_in_pos];
	++stream_in_pos;
	if(stream_in_pos>=stream_start->size)
	{
		stream_in_pos=0;
		node=stream_start;
		stream_start=stream_start->next;
		free(node);
	}
	return c;
}
