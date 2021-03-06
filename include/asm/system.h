/*
 * include/asm/system.h  
 * Copyright (C) <2014>  <@RKX1209>
 */

#ifndef __ASM_SYSTEM_H
#define __ASM_SYSTEM_H

/* Operation of special registes */
#define read_cr0()({ \
  unsigned int __ret; \
  __asm__ __volatile__( \
  "movl %%cr0,%0\n\t" \
  :"=r" (__ret)); \
  __ret; \
})

#define write_cr0(x) \
	__asm__ __volatile__("movl %0,%%cr0": :"r" (x));

#define read_cr2()({ \
  unsigned int __ret; \
  __asm__ __volatile__( \
  "movl %%cr2,%0\n\t" \
  :"=r" (__ret)); \
  __ret; \
})

#define write_cr2(x) \
	__asm__ __volatile__("movl %0,%%cr2": :"r" (x));

#define read_cr3()({ \
  unsigned int __ret; \
  __asm__ __volatile__( \
  "movl %%cr3,%0\n\t" \
  :"=r" (__ret)); \
  __ret; \
})

#define write_cr3(x) \
	__asm__ __volatile__("movl %0,%%cr3": :"r" (x));

#define read_cr4()({ \
  unsigned int __ret; \
  __asm__ __volatile__( \
  "movl %%cr4,%0\n\t" \
  :"=r" (__ret)); \
  __ret; \
})

#define write_cr4(x) \
	__asm__ __volatile__("movl %0,%%cr4": :"r" (x));

/* Write memory barrier */
#define wmb() __asm__ __volatile__("sfence");
#define smp_wmb() wmb()

/* Enable Interupt (set IF = 1) */
#define local_irq_enable() __asm__ __volatile__("sti": : :"memory")
#define local_irq_save(x) __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (x): /* no input */ :"memory")

#define switch_to(prev,next,last) do{ \
  unsigned long esi,edi; \
__asm__ __volatile__("pushfl\n\t"\
		     "pushl %%ebp\n\t" \
		     "movl %%esp,%0\n\t" \
		     "movl %5,%%esp\n\t" \
		     "movl $1f,%1\n\t"\
		     "pushl %6\n\t" \
		     "jmp __switch_to\n" \
		     "1:\t" \
		     "popl %%ebp\n\t" \
		     "popfl" \
		     :"=m" (prev->thread.esp),"=m" (prev->thread.eip), \	
		      "=a" (last),"=S" (esi),"=D" (edi)	\
		     :"m" (next->thread.esp),"m" (next->thread.eip), \
		      "2" (prev), "d" (next)); \
}while(0)
#endif
