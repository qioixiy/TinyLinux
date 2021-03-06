#ifndef _I386_CURRENT_H
#define _I386_CURRENT_H

#include <abyon/thread_info.h>
struct task_struct;

static inline struct task_struct *get_current(void){
  return current_thread_info()->task;
}
#define current get_current()
#endif
