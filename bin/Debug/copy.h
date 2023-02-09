@@delimiter(script, "={:=", "=:}=");
[[13]]int main()
{
	struct index_st
	{
		unsigned char type;
		unsigned char num;
		unsigned int len;
	};
	typedef struct index_st index_t;
	int x,
	y;
	x "=" offsetof(struct index_st, len);
	y "=" offsetof(index_t, num);
	return 0;
};
abc(()abcd);
