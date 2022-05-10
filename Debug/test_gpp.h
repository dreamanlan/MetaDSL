@@delimiter(script, "={:=", "=:}=");
@@code
={:=
[[13]]
int
main ()
{

  struct index_st
  {
    unsigned char type;
    unsigned char num;
    unsigned int len;
  };
=:}=;
@@if(1)
{
	@@code
	={:=

  typedef struct index_st index_t;
  int x,y;
  x = offsetof(struct index_st, len);
  y = offsetof(index_t, num)

  ;
	=:}=;
};
@@code
={:=
  return 0;
};

=:}=;
@@define(definexxx 1);
@@code
={:=


abc(()abcd);
=:}=;
