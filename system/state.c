#include "state.h"

struct _tln_sm {
    tln_sm_state_t state;
    tln_sm_transition_t *transistions;
    int transistionsSize;
    void *data;
};

tln_sm_t state_new(tln_sm_state_t startingState, tln_sm_transition_t *transistions, int length, tln_sm_data_t *data) {
    tln_sm_t sm = (tln_sm_t)malloc(sizeof(struct _tln_sm));

    sm->transistions = transistions;
    sm->transistionsSize = length;
    sm->state = startingState;
    sm->data = data;

    return sm;
}

void state_update(tln_sm_t sm, tln_sm_event_t event) {
    for (int i = 0; i < sm->transistionsSize; i++) {
        tln_sm_transition_t *entry = &sm->transistions[i];

        if (sm->state == entry->state || TLN_STATE_ANY == entry->state) {
            if (event == entry->event || TLN_EVENT_ANY == entry->event) {
                if (entry->nextState != TLN_STATE_ANY) sm->state = entry->nextState;
                if (entry->stateFunction != 0) entry->stateFunction(sm->data);
                if (entry->bubble == TLN_SM_CONSUME_EVENT) return;
            }
        }
    }
}

int state_current(tln_sm_t sm) {
    return sm->state;
}