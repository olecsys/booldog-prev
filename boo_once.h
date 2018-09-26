#ifndef BOO_ONCE_H
#define BOO_ONCE_H

#ifndef BDOG_ATOM
#include "boo_atomic.h"
#endif
#ifndef BDOG_SLEEP
#include "boo_threading_utils.h"
#endif

typedef void (*boo_once_callback_t)(void* udata);
inline void boo_once(BDOG_ATOM* static_variable, boo_once_callback_t init, void* init_udata) {
  BDOG_ATOM_RETURN result = BDOG_ATOM_INC(static_variable);
  if(result == 1) {
    init(init_udata);
    BDOG_ATOM_EXCH(static_variable, BDOG_ATOM_MAX);
  }
  else if(result != BDOG_ATOM_MAX) {
    while(BDOG_ATOM_CMP_EXCH(static_variable, 0, 0) != BDOG_ATOM_MAX) {
      BDOG_SLEEP(1);
    }
  }
}

#endif