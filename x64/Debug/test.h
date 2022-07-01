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
#if 1
  typedef struct index_st index_t;
  int x,y;
  x = offsetof(struct index_st, len);
  y = offsetof(index_t, num)

  ;
#endif  
  return 0;
};

#define xxx 1

abc(()abcd);