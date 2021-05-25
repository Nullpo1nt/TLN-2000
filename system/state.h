#ifndef _STATE_H_
#define _STATE_H_

#include <stdlib.h>

#define TLN_STATE_ANY 0
#define TLN_USER_STATES_START 100

#define TLN_EVENT_ANY 0
#define TLN_USER_EVENTS_START 100

typedef enum { TLN_SM_CONSUME_EVENT = 0, TLN_SM_BUBBLE_EVENT } tln_sm_bubbling_t;

typedef int tln_sm_state_t;
typedef int tln_sm_event_t;

typedef struct tln_sm_data tln_sm_data_t;
typedef void tln_sm_func_t(tln_sm_data_t *data);

typedef struct tln_statetransitions {
    tln_sm_state_t state;
    tln_sm_event_t event;
    tln_sm_state_t nextState;
    void (*stateFunction)(tln_sm_data_t *data);  // Optional function called when this state is entered
    tln_sm_bubbling_t bubble;
} tln_sm_transition_t;

typedef struct _tln_sm *tln_sm_t;

tln_sm_t state_new(tln_sm_state_t initialState, tln_sm_transition_t *transitionTable, int tableSize,
                   tln_sm_data_t *data);

void state_update(tln_sm_t, tln_sm_event_t);

tln_sm_state_t state_current(tln_sm_t);

#endif  // _STATE_H_