#include "annunciators.h"

namespace tln::annunciators
{

TLN_ANNUNCIATOR gps = TLN_ANNUNCIATOR_OFF;

TLN_ANNUNCIATOR wrn = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR adv = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR ptk = TLN_ANNUNCIATOR_OFF;
// TLN_ANNUNCIATOR apr = TLN_ANNUNCIATOR_OFF;

TLN_ANNUNCIATOR nav = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR wpt = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR fpl = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR calc = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR aux = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR aptVor = TLN_ANNUNCIATOR_OFF;

TLN_ANNUNCIATOR direct = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR msg = TLN_ANNUNCIATOR_OFF;
TLN_ANNUNCIATOR ent = TLN_ANNUNCIATOR_OFF;

TLN_ANNUNCIATOR getAnnunciatorGps()
{
    return gps;
}
TLN_ANNUNCIATOR getAnnunciatorWrn()
{
    return wrn;
}
TLN_ANNUNCIATOR getAnnunciatorAdv()
{
    return adv;
}
TLN_ANNUNCIATOR getAnnunciatorPtk()
{
    return ptk;
}
// TLN_ANNUNCIATOR getAnnunciatorApr() { return ; }

TLN_ANNUNCIATOR getAnnunciatorNav()
{
    return nav;
}
TLN_ANNUNCIATOR getAnnunciatorWpt()
{
    return wpt;
}
TLN_ANNUNCIATOR getAnnunciatorFpl()
{
    return fpl;
}
TLN_ANNUNCIATOR getAnnunciatorCalc()
{
    return calc;
}
TLN_ANNUNCIATOR getAnnunciatorAux()
{
    return aux;
}
TLN_ANNUNCIATOR getAnnunciatorAptVor()
{
    return aptVor;
}
TLN_ANNUNCIATOR getAnnunciatorDirect()
{
    return direct;
}
TLN_ANNUNCIATOR getAnnunciatorMsg()
{
    return msg;
}
TLN_ANNUNCIATOR getAnnunciatorEnt()
{
    return ent;
}

void setEnt(TLN_ANNUNCIATOR mode)
{
    ent = mode;
}

void enableAllAnnunciators()
{
    gps = TLN_ANNUNCIATOR_ON;
    wrn = TLN_ANNUNCIATOR_ON;
    adv = TLN_ANNUNCIATOR_ON;
    ptk = TLN_ANNUNCIATOR_ON;
    // Apr = TLN_ANNUNCIATOR_ON;

    nav = TLN_ANNUNCIATOR_ON;
    wpt = TLN_ANNUNCIATOR_ON;
    fpl = TLN_ANNUNCIATOR_ON;
    calc = TLN_ANNUNCIATOR_ON;
    aux = TLN_ANNUNCIATOR_ON;
    aptVor = TLN_ANNUNCIATOR_ON;
    direct = TLN_ANNUNCIATOR_ON;
    msg = TLN_ANNUNCIATOR_ON;
    ent = TLN_ANNUNCIATOR_ON;
}
void disableAllAnnunciators()
{
    gps = TLN_ANNUNCIATOR_OFF;
    wrn = TLN_ANNUNCIATOR_OFF;
    adv = TLN_ANNUNCIATOR_OFF;
    ptk = TLN_ANNUNCIATOR_OFF;
    // Apr = TLN_ANNUNCIATOR_OFF;

    nav = TLN_ANNUNCIATOR_OFF;
    wpt = TLN_ANNUNCIATOR_OFF;
    fpl = TLN_ANNUNCIATOR_OFF;
    calc = TLN_ANNUNCIATOR_OFF;
    aux = TLN_ANNUNCIATOR_OFF;
    aptVor = TLN_ANNUNCIATOR_OFF;
    direct = TLN_ANNUNCIATOR_OFF;
    msg = TLN_ANNUNCIATOR_OFF;
    ent = TLN_ANNUNCIATOR_OFF;
}

void setNavMode()
{
    nav = TLN_ANNUNCIATOR_ON;
    wpt = TLN_ANNUNCIATOR_OFF;
    fpl = TLN_ANNUNCIATOR_OFF;
    calc = TLN_ANNUNCIATOR_OFF;
    aux = TLN_ANNUNCIATOR_OFF;
    aptVor = TLN_ANNUNCIATOR_OFF;
}
void setWptMode()
{
    nav = TLN_ANNUNCIATOR_OFF;
    wpt = TLN_ANNUNCIATOR_ON;
    fpl = TLN_ANNUNCIATOR_OFF;
    calc = TLN_ANNUNCIATOR_OFF;
    aux = TLN_ANNUNCIATOR_OFF;
    aptVor = TLN_ANNUNCIATOR_OFF;
}

void setFplMode()
{
    nav = TLN_ANNUNCIATOR_OFF;
    wpt = TLN_ANNUNCIATOR_OFF;
    fpl = TLN_ANNUNCIATOR_ON;
    calc = TLN_ANNUNCIATOR_OFF;
    aux = TLN_ANNUNCIATOR_OFF;
    aptVor = TLN_ANNUNCIATOR_OFF;
}

void setCalcMode()
{
    nav = TLN_ANNUNCIATOR_OFF;
    wpt = TLN_ANNUNCIATOR_OFF;
    fpl = TLN_ANNUNCIATOR_OFF;
    calc = TLN_ANNUNCIATOR_ON;
    aux = TLN_ANNUNCIATOR_OFF;
    aptVor = TLN_ANNUNCIATOR_OFF;
}

void setAuxMode()
{
    nav = TLN_ANNUNCIATOR_OFF;
    wpt = TLN_ANNUNCIATOR_OFF;
    fpl = TLN_ANNUNCIATOR_OFF;
    calc = TLN_ANNUNCIATOR_OFF;
    aux = TLN_ANNUNCIATOR_ON;
    aptVor = TLN_ANNUNCIATOR_OFF;
}

void setAptVorMode()
{
    nav = TLN_ANNUNCIATOR_OFF;
    wpt = TLN_ANNUNCIATOR_OFF;
    fpl = TLN_ANNUNCIATOR_OFF;
    calc = TLN_ANNUNCIATOR_OFF;
    aux = TLN_ANNUNCIATOR_OFF;
    aptVor = TLN_ANNUNCIATOR_ON;
}

} // namespace tln::annunciators