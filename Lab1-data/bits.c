/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	x = x >> (n << 3);
	return x & 0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	int op = ~(1 << 31 >> n << 1);
	x >>= n;
	return op&x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	int mask1 = 85 | (85 << 8);
	int mask2 = 51 | (51 << 8);
	int mask3 = 15 | (15 << 8);
	int mask4 = 255;
	int op = 255 | (255 << 8);
	mask1 = mask1 | (mask1 << 16);
	mask2 = mask2 | (mask2 << 16);
	mask3 = mask3 | (mask3 << 16);
	mask4 = mask4 | (mask4 << 16);
	x = (x&mask1) + ((x >> 1)&mask1);
	x = (x&mask2) + ((x >> 2)&mask2);
	x = (x&mask3) + ((x >> 4)&mask3);
	x = (x&mask4) + ((x >> 8)&mask4);
	return (x&op) + ((x >> 16)&op);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	x = ((x >> 16) | x);
	x = ((x >> 8) | x);
	x = ((x >> 4) | x);
	x = ((x >> 2) | x);
	x = ((x >> 1) | x) & 1;
	return x^1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int shiftNumber = 32 + (~n + 1);// 32 - n
	return !(x ^ ((x << shiftNumber) >> shiftNumber));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int sign = x >> 31;
	int ans1, ans2;
	ans1 = ((x + (1 << n) + (~0)) >> n)&sign;
	ans2 = (x >> n)&(~sign);
	return ans1 + ans2;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return (~x) + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int ans = (x >> 31) & 1;
	return (ans ^ 1) & (!(!x));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int sign1 = x >> 31, sign2 = y >> 31;
	int z = y + ((~x) + 1);
	int sign = (z >> 31) & 1;
	int ans1, ans3, ans4;
	ans1 = 1 & (sign1&(~sign2));
	ans3 = (sign ^ 1)&(sign1&sign2);
	ans4 = (sign ^ 1)&((~sign1)&(~sign2));
	return ans1 + ans3 + ans4;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int bitsNumber = 0;
	bitsNumber = (!!(x >> 16)) << 4;//
	bitsNumber = bitsNumber + ((!!(x >> (bitsNumber + 8))) << 3);
	bitsNumber = bitsNumber + ((!!(x >> (bitsNumber + 4))) << 2);
	bitsNumber = bitsNumber + ((!!(x >> (bitsNumber + 2))) << 1);
	bitsNumber = bitsNumber + (!!(x >> (bitsNumber + 1)));
	//for non zero bitsNumber, it should add 0
	//for zero bitsNumber, it should subtract 1
	bitsNumber = bitsNumber + (!!bitsNumber) + (~0) + (!(1 ^ x));
	//��xΪ0ʱ������Ҫ��һ���ܵõ���ȷֵ��
	return bitsNumber;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	unsigned op = 0;
	unsigned uf1 = uf >> 23;
	unsigned uf2 = uf&((~op) >> 9);
	if ((uf1 == 0x1ff || uf1 == 0xff) && uf2)return uf;
	return uf ^ (1 << 31);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	//int x1, y, z, cnt = -1, cnt_24;
	//int flag, flag2 = 0, i;
	//unsigned e;
	//unsigned opu = 2147483648;
	//unsigned sign = 0;
	//unsigned ans1 = 1325400064;
	//if (x == opu)return ans1 | opu;
	//if (x == 0)return 0;
	//if (x < 0) {
	//	x = -x;
	//	sign = opu;
	//}
	//y = x;
	//while (y) { y >>= 1;cnt++; }
	//e = cnt + 127;
	////x = x ^ (1 << cnt);
	//z = cnt - 23;
	//if (cnt >= 23) {
	//	cnt_24 = cnt - 24;
	//	y = x >> cnt_24;
	//	x1 = x >> z;
	//	if (cnt == 23)y = 0;
	//	if (y & 1) {
	//		flag = 0;
	//		for (i = 0;i < cnt_24;i++)if (x&(1 << i)) {
	//			flag = 1;
	//			break;
	//		}
	//		if (flag || (y & 2)) x1 += 1;
	//		if (x1 & 16777216)flag2 = 1;
	//	}
	//	x = x1 & 8388607;
	//}
	//else {
	//	x <<= (22 - cnt);
	//	flag2 = 1;
	//}
	//if (flag2)e++;
	//return x | (e << 23) | sign;
	unsigned shiftLeft = 0;
	unsigned afterShift, tmp, flag;
	unsigned absX = x;
	unsigned sign = 0;
	//special case
	if (x == 0) return 0;
	//if x < 0, sign = 1000...,abs_x = -x
	if (x<0)
	{
		sign = 0x80000000;
		absX = -x;
	}
	afterShift = absX;
	//count shift_left and after_shift
	while (1)
	{
		tmp = afterShift;
		afterShift <<= 1;
		shiftLeft++;
		if (tmp & 0x80000000) break;
	}
	if ((afterShift & 0x01ff)>0x0100)
		flag = 1;
	else if ((afterShift & 0x03ff) == 0x0300)
		flag = 1;
	else
		flag = 0;

	return sign + (afterShift >> 9) + ((159 - shiftLeft) << 23) + flag;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned xf = 0xff;
	unsigned exp = (uf >> 23) & xf;
	unsigned frac;
	unsigned sign = uf&(1 << 31);
	if (exp == xf)return uf;
	if (exp) {
		if ((exp + 1) == xf)return sign | (xf << 23);
		else return uf + (1 << 23);
	}
	else {
		frac = uf&((1 << 23) - 1);
		if (frac&(1 << 22)) {
			frac = frac ^ (1 << 22);
			exp = 1;
		}
		frac = frac << 1;
		return sign | (exp << 23) | frac;
	}
}