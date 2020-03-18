#include "annunciators.h"

struct ANNUNCIATOR_DATA_S {
    TLN_ANNUNCIATOR gps;

    TLN_ANNUNCIATOR wrn;
    TLN_ANNUNCIATOR adv;
    TLN_ANNUNCIATOR ptk;
    // TLN_ANNUNCIATOR apr;

    TLN_ANNUNCIATOR nav;
    TLN_ANNUNCIATOR wpt;
    TLN_ANNUNCIATOR fpl;
    TLN_ANNUNCIATOR calc;
    TLN_ANNUNCIATOR aux;
    TLN_ANNUNCIATOR aptVor;

    TLN_ANNUNCIATOR direct;
    TLN_ANNUNCIATOR msg;
    TLN_ANNUNCIATOR ent;
} g_annunciators_data = {.gps = TLN_ANNUNCIATOR_OFF,

                         .wrn = TLN_ANNUNCIATOR_OFF,
                         .adv = TLN_ANNUNCIATOR_OFF,
                         .ptk = TLN_ANNUNCIATOR_OFF,
                         // .apr = TLN_ANNUNCIATOR_OFF,

                         .nav = TLN_ANNUNCIATOR_OFF,
                         .wpt = TLN_ANNUNCIATOR_OFF,
                         .fpl = TLN_ANNUNCIATOR_OFF,
                         .calc = TLN_ANNUNCIATOR_OFF,
                         .aux = TLN_ANNUNCIATOR_OFF,
                         .aptVor = TLN_ANNUNCIATOR_OFF,

                         .direct = TLN_ANNUNCIATOR_OFF,
                         .msg = TLN_ANNUNCIATOR_OFF,
                         .ent = TLN_ANNUNCIATOR_OFF};

TLN_ANNUNCIATOR getAnnunciatorGps() {
    return g_annunciators_data.gps;
}
TLN_ANNUNCIATOR getAnnunciatorWrn() {
    return g_annunciators_data.wrn;
}
TLN_ANNUNCIATOR getAnnunciatorAdv() {
    return g_annunciators_data.adv;
}
TLN_ANNUNCIATOR getAnnunciatorPtk() {
    return g_annunciators_data.ptk;
}
// TLN_ANNUNCIATOR getAnnunciatorApr() { return g_annunciators_data.; }

TLN_ANNUNCIATOR getAnnunciatorNav() {
    return g_annunciators_data.nav;
}
TLN_ANNUNCIATOR getAnnunciatorWpt() {
    return g_annunciators_data.wpt;
}
TLN_ANNUNCIATOR getAnnunciatorFpl() {
    return g_annunciators_data.fpl;
}
TLN_ANNUNCIATOR getAnnunciatorCalc() {
    return g_annunciators_data.calc;
}
TLN_ANNUNCIATOR getAnnunciatorAux() {
    return g_annunciators_data.aux;
}
TLN_ANNUNCIATOR getAnnunciatorAptVor() {
    return g_annunciators_data.aptVor;
}
TLN_ANNUNCIATOR getAnnunciatorDirect() {
    return g_annunciators_data.direct;
}
TLN_ANNUNCIATOR getAnnunciatorMsg() {
    return g_annunciators_data.msg;
}
TLN_ANNUNCIATOR getAnnunciatorEnt() {
    return g_annunciators_data.ent;
}

void setEnt(TLN_ANNUNCIATOR mode) {
    g_annunciators_data.ent = mode;
}

void enableAllAnnunciators() {
    g_annunciators_data.gps = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.wrn = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.adv = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.ptk = TLN_ANNUNCIATOR_ON;
    // g_annunciators_data.Apr = TLN_ANNUNCIATOR_ON;

    g_annunciators_data.nav = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.direct = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.msg = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.ent = TLN_ANNUNCIATOR_ON;
}
void disableAllAnnunciators() {
    g_annunciators_data.gps = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wrn = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.adv = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.ptk = TLN_ANNUNCIATOR_OFF;
    // g_annunciators_data.Apr = TLN_ANNUNCIATOR_OFF;

    g_annunciators_data.nav = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.direct = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.msg = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.ent = TLN_ANNUNCIATOR_OFF;
}

void setNavMode() {
    g_annunciators_data.nav = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_OFF;
}
void setWptMode() {
    g_annunciators_data.nav = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_OFF;
}

void setFplMode() {
    g_annunciators_data.nav = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_OFF;
}

void setCalcMode() {
    g_annunciators_data.nav = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_OFF;
}

void setAuxMode() {
    g_annunciators_data.nav = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_ON;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_OFF;
}

void setAptVorMode() {
    g_annunciators_data.nav = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.wpt = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.fpl = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.calc = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aux = TLN_ANNUNCIATOR_OFF;
    g_annunciators_data.aptVor = TLN_ANNUNCIATOR_ON;
}
