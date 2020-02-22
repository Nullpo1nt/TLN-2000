#ifndef _CALC_H_
#define _CALC_H_

#include "annunciators.h"
#include "display.h"

namespace tln::calc
{
void renderCalc();
void calc();
void calcNext();
void calcPrev();
void calcNextSub();
void calcPrevSub();
void calcSavePPos();
} // namespace tln::calc

#endif