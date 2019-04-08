/*---------------------------------------------------------------------------
  CRC У�������
      ��������ڼ���8λ��16λ��32λ CRC У�顣����ĳ�ʼ��������ָ��Ҫ����
      ��CRC��λ��������ʽ������˳�򡢳�ʼֵ������ֵ��
      ReverseΪ��ʱ��ʾ������
---------------------------------------------------------------------------*/
#include "power_crc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
UBYTE4 Crc::bits [BITSPERBYTE * 4] =
 { 0x00000001UL, 0x00000002UL, 0x00000004UL, 0x00000008UL,
   0x00000010UL, 0x00000020UL, 0x00000040UL, 0x00000080UL,
   0x00000100UL, 0x00000200UL, 0x00000400UL, 0x00000800UL,
   0x00001000UL, 0x00002000UL, 0x00004000UL, 0x00008000UL,
   0x00010000UL, 0x00020000UL, 0x00040000UL, 0x00080000UL,
   0x00100000UL, 0x00200000UL, 0x00400000UL, 0x00800000UL,
   0x01000000UL, 0x02000000UL, 0x04000000UL, 0x08000000UL,
   0x10000000UL, 0x20000000UL, 0x40000000UL, 0x80000000UL,
 } ;
//---------------------------------------------------------------------------
Crc::Crc (unsigned int BitCount,  
		  unsigned long Polynominal,
          bool Reverse,
		  unsigned long Initial, 
		  unsigned long FinalMask)	
// BitCount    : CRC Size
// Polynominal : CRC Polynomial
// Reverse     : Reversed (means shift right)
// Initial     : Initial CRC Register Value
// FinalMask   : Final CRC XOR Value
{
  BITCOUNT    = BitCount;   //У�����λ��
  POLYNOMINAL = Polynominal;//���ɶ���ʽ
  INITIAL     = Initial;    //ע����
  FINALMASK   = FinalMask;  //����
  // Mask needed to mask off redundent bits
  mask = ((1UL << (BITCOUNT - 1)) - 1UL)  | (1UL << (BITCOUNT - 1)) ;
  REVERSE = Reverse;        // Before set this property
                            // mask must be calculated
}
//---------------------------------------------------------------------------
void Crc::SetReverse(bool reverse)
{
  FREVERSE = reverse;
  if (reverse)  {
    for (unsigned int ii = 0 ; ii < MAXBYTEVALUES ; ++ ii)
      values [ii] = ReverseTableEntry (ii) ;
  }
  else  {
    for (unsigned int ii = 0 ; ii < MAXBYTEVALUES ; ++ ii)
      values [ii] = ForwardTableEntry (ii) ;
  }

}
//---------------------------------------------------------------------------
/************************************************************************/
/* ��������: Reverse (UBYTE4 value)                                     

/* ��    ��: 1.UBYTE4 value - ��Ҫ��β��������

/* �� �� ֵ: ������β���������ֵ

/* ��    ��: ��һ����ֵ��β�������� 1010 -> 0101 

/* ��    ��:ebaoqigai@sina.com

/* ��    ��: version		  purpose			 date
             1.0              create             2014.09.12
/************************************************************************/
BYTE4 Crc::Reverse (UBYTE4 value)
{
  unsigned long result = 0 ;

  for (unsigned int jj = 0 ; jj < BITCOUNT ; ++ jj)
  {
    if ((value & bits [jj]) != 0)
      result |= bits [BITCOUNT - jj - 1] ;
  }
  return result ;
}
//---------------------------------------------------------------------------
/************************************************************************/
/* ��������: ForwardTableEntry (unsigned int entryindex)                                     

/* ��    ��: 1.unsigned int entryindex - ��Ҫ��β��������

/* �� �� ֵ: ������β���������ֵ

/* ��    ��: ��һ����ֵ��β�������� 1010 -> 0101 

/* ��    ��:ebaoqigai@sina.com

/* ��    ��: version		  purpose			 date
             1.0              create             2014.09.12
/************************************************************************/
UBYTE4 Crc::ForwardTableEntry (unsigned int entryindex)
//  This function creates a CRC table entry for a non-reversed
//  CRC function.
//
//  Parameters:
//
//  entryindex: The index of the CRC table entry.
//
//  Return Value:
//
//  The value for the specified CRC table entry.
//
{

  UBYTE4 result = entryindex << (BITCOUNT - BITSPERBYTE) ;
  for (unsigned int ii = 0 ; ii < BITSPERBYTE ; ++ ii)
  {
    if ((result & bits [BITCOUNT - 1]) == 0)
      result <<= 1 ;
    else
      result = (result << 1) ^ POLYNOMINAL ;
  }
  result &= mask ;
  return result ;
}
//---------------------------------------------------------------------------
UBYTE4 Crc::ReverseTableEntry (unsigned int entryindex)
//    This function creates a CRC table entry for a reversed
//
//    CRC function.
//
//    Parameters:
//
//    entryindex: The index of the CRC table entry.
//
//    Return Value:
//
//    The value for the specified CRC table entry.
//
{
  UBYTE4 result = entryindex ;
  for (unsigned int ii = 0 ; ii < BITSPERBYTE ; ++ ii)
  {
    if ((result & 1) == 0)
      result >>= 1 ;
    else
      result = (result >> 1) ^ Reverse (POLYNOMINAL) ;
  }
  result &=  mask ;
  return result ;
}
//---------------------------------------------------------------------------
void Crc::reset (void)
{
  crc_register = INITIAL ;
}
//---------------------------------------------------------------------------
UBYTE4 Crc::value (void) const
{
  UBYTE4 result = crc_register ^ FINALMASK ;
  result &= mask ;
  return result ;
}
//---------------------------------------------------------------------------
void Crc::update (const char *buffer, unsigned int length)
//    This function updates the value of the CRC register based upon
//    the contents of a buffer.
//
//  Parameters:
//
//    buffer: The input buffer
//    length: The length of the input buffer.
//
{
  // The process for updating depends upon whether or not we are using
  // the reversed CRC form.

  if (REVERSE)
  {
    for (unsigned int ii = 0 ; ii < length ; ++ ii)
    {
      crc_register = values [(crc_register ^ buffer [ii]) & 0xFF]
                   ^ (crc_register >> 8) ;
    }
  }
  else
  {
    for (unsigned int ii = 0 ; ii < length ; ++ ii)
    {
      UBYTE4 index = ((crc_register >> (BITCOUNT - BITSPERBYTE)) ^ buffer [ii]) ;
      crc_register = values [index & 0xFF]
                   ^ (crc_register << BITSPERBYTE) ;
    }
  }
  return ;
}
//---------------------------------------------------------------------------
UBYTE4 Crc::getcrc(const char *buffer, unsigned int length)
{
  reset();
  update(buffer,length);
  return value();
}
