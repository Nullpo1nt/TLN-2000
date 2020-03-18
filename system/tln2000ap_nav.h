#ifndef _TLN2000AP_NAV_H_
#define _TLN2000AP_NAV_H_

#include "state.h"

void nav_updateDisplay(tln_sm_data_t *data);
void navReset(tln_sm_data_t *data);
void navNextTop(tln_sm_data_t *data);
void navPrevTop(tln_sm_data_t *data);
void navNextBot(tln_sm_data_t *data);
void navPrevBot(tln_sm_data_t *data);
void navDes(tln_sm_data_t *data);

#endif