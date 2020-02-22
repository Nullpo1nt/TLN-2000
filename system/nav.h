#ifndef _NAV_H_
#define _NAV_H_

#include "annunciators.h"
#include "display.h"

namespace tln::nav
{

char *navGetTop();
char *navGetBot();
void nav();
void navReset();
void navNextTop();
void navPrevTop();
void navNextBot();
void navPrevBot();
void navDes();

} // namespace tln::nav

#endif