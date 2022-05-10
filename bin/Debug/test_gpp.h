@@delimiter(script, "={:=", "=:}=");
@@code
={:=
[[13]]
int
main ()
{
    //fdafdsa

    /*fdafa
    fdafads
    fdasfa
    */

   //-----12345-----

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
	@@define("ABC abc
fdef");
	@@code
	={:=


	=:}=;
	@@define("DEF abc(abc)");
	@@code
	={:=


	=:}=;
	@@define(XXX1 > 2 ? 1 : 0);
	@@code
	={:=


	=:}=;
};
@@code
={:=
  return 0;
};

=:}=;
@@define(xxx 1);
@@code
={:=


abc(()abcd);
=:}=;
