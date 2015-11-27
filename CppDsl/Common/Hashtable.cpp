#include "Hashtable.h"

UINT CalcStringHashCode(const CHAR *str)
{
	UINT h=0;
	const UCHAR* p;
	for(p=(const UCHAR*)str; 0!=(*p); ++p)
		h = 31 * h + (*p);
	return h;
}

UINT HashtableBase::PrepareAddIndex(const ISlotKey& key)
{
	UINT count = GetSlotCount();
	if(0==count)
		return INVALID_HASH_INDEX;
	UINT incr = 1;
	UINT c = ToIndex(count,key.GetHashCode(),incr);
	for( UINT i=0; i<count; ++i, c = ( c + incr ) % count )
	{
		if( GetSlot(c).GetStatus() == IDTS_USED )
		{
			continue;
		}
		GetSlot(c).SetStatus(IDTS_USED);
		return c;
	}
	return INVALID_HASH_INDEX;
}

UINT HashtableBase::Find( const ISlotKey& key ) const
{
	UINT count = GetSlotCount();
	if(0==count)
		return INVALID_HASH_INDEX;
	UINT incr = 1;
	UINT c = ToIndex(count,key.GetHashCode(),incr);
	for( UINT i=0; i<count; ++i, c = ( c + incr ) % count )
	{
		UINT v = GetSlot(c).GetStatus();
		if( v == IDTS_EMPTY )
		{
			return INVALID_HASH_INDEX;
		}
		else if( v == IDTS_REMOVED )
		{
			continue;
		}

		if( key.KeyEqual(c) )
		{
			return c;
		}
	}
	return INVALID_HASH_INDEX;
}

UINT HashtableBase::Remove( const ISlotKey& key )
{	
	UINT c = Find(key);
	if(INVALID_HASH_INDEX==c)
		return INVALID_HASH_INDEX;
	ISlot& slot=GetSlot(c);
	slot.Cleanup();
	slot.SetStatus(IDTS_REMOVED);
	return c;
}

VOID HashtableBase::Cleanup( VOID )
{
	UINT count = GetSlotCount();
	for( UINT i=0; i<count; ++i )
	{
		ISlot& slot = GetSlot(i);
		slot.Cleanup();
	}
}

UINT HashtableBase::GetPrime(UINT code)
{
	//»ù´¡ËØÊý±í
	static UINT primes[] = 
	{
		3, 7, 11, 0x11, 0x17, 0x1d, 0x25, 0x2f, 0x3b, 0x47, 0x59, 0x6b, 0x83, 0xa3, 0xc5, 0xef, 
		0x125, 0x161, 0x1af, 0x209, 0x277, 0x2f9, 0x397, 0x44f, 0x52f, 0x63d, 0x78b, 0x91d, 0xaf1, 0xd2b, 0xfd1, 0x12fd, 
		0x16cf, 0x1b65, 0x20e3, 0x2777, 0x2f6f, 0x38ff, 0x446f, 0x521f, 0x628d, 0x7655, 0x8e01, 0xaa6b, 0xcc89, 0xf583, 0x126a7, 0x1619b, 
		0x1a857, 0x1fd3b, 0x26315, 0x2dd67, 0x3701b, 0x42023, 0x4f361, 0x5f0ed, 0x72125, 0x88e31, 0xa443b, 0xc51eb, 0xec8c1, 0x11bdbf, 0x154a3f, 0x198c4f, 
		0x1ea867, 0x24ca19, 0x2c25c1, 0x34fa1b, 0x3f928f, 0x4c4987, 0x5b8b6f, 0x6dda89
    };
	INT l=0;
	INT h=sizeof(primes)/sizeof(UINT) - 1;
	if(primes[h]>code)
	{
		while(l<h)
		{
			INT m=(l+h)/2;
			UINT prime=primes[m];
			if(prime<code)
				l=m+1;
			else if(prime==code)
				return prime;
			else
				h=m;
		}
		return primes[h];
	}
	else
	{
		for (UINT i = (code | 1); i < MAX_HASH_INDEX_VALUE; i += 2)
		{
			if (TRUE == IsPrime(i))
			{
				return i;
			}
		}
	}
    return code;
}

UINT HashtableBase::ToIndex(UINT hashSize,UINT code,UINT& incr)
{
	if(0==hashSize || 1==hashSize)
		return INVALID_HASH_INDEX;
    UINT num = (UINT) (code & MAX_HASH_INDEX_VALUE);
    incr = 1 + ((UINT) (((num >> 5) + 1) % (hashSize - 1)));
    return num % hashSize;
}

BOOL HashtableBase::IsPrime(UINT val)
{
	if((val & 1) == 0)
	{
		return (val == 2);
	}
	UINT num = (UINT)sqrt((DOUBLE)val);
	for(UINT i = 3; i <= num; i += 2)
	{
		if((val % i) == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}