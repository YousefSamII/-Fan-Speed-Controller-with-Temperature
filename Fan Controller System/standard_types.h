/****************************************************
 * Module: Common Types Abstraction
 *
 * File Name: standard_types.h
 *
 *  Description: Standard Types for AVR in C
 *
 *  Author: Yousef Samy
 *
 ****************************************************/

/* To Avoid Duplicate File*/
#ifndef STANDARD_TYPES_H_
#define STANDARD_TYPES_H_
/* Create Boolean Data Type*/
typedef unsigned char boolean;
/*Boolean Values */
#ifndef FALSE
#define FALSE 			(0u)
#endif
#ifndef TRUE
#define TRUE 			(1u)
#endif

#define LOGIC_HIGH		(1u)
#define LOGIC_LOW		(0u)

#define NULL_Ptr		((void*)0)

typedef unsigned long uint32;							/* 0 : 4294967295*/
typedef signed long sint32 ;							/* +2147483648 : - 2147483647*/
typedef unsigned short uint16;							/* 0 : 65536*/
typedef signed short sint16;							/* +32768 : - 32767*/
typedef unsigned char uint8;							/* 0:255*/
typedef signed int sint8;								/* +128: -127*/
typedef unsigned long long uint64;						/*  0 : 1.844*10^19 */
typedef signed long long sint64;						/* 9.22*10^18 : -(9.22*10^18-1) */
typedef float 	 float32;
typedef double   float64;

#endif /* STANDARD_TYPES_H_ */
