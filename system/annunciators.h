#ifndef _ANNUNCIATORS_H_
#define _ANNUNCIATORS_H_

typedef enum { TLN_ANNUNCIATOR_OFF = 0, TLN_ANNUNCIATOR_ON = 1, TLN_ANNUNCIATOR_BLINK = 2 } TLN_ANNUNCIATOR;

TLN_ANNUNCIATOR getAnnunciatorGps();
TLN_ANNUNCIATOR getAnnunciatorWrn();
TLN_ANNUNCIATOR getAnnunciatorAdv();
TLN_ANNUNCIATOR getAnnunciatorPtk();
// TLN_ANNUNCIATOR getAnnunciatorApr();
TLN_ANNUNCIATOR getAnnunciatorNav();
TLN_ANNUNCIATOR getAnnunciatorWpt();
TLN_ANNUNCIATOR getAnnunciatorFpl();
TLN_ANNUNCIATOR getAnnunciatorCalc();
TLN_ANNUNCIATOR getAnnunciatorAux();
TLN_ANNUNCIATOR getAnnunciatorAptVor();
TLN_ANNUNCIATOR getAnnunciatorDirect();
TLN_ANNUNCIATOR getAnnunciatorMsg();
TLN_ANNUNCIATOR getAnnunciatorEnt();

void enableAllAnnunciators();
void disableAllAnnunciators();

void setEnt(TLN_ANNUNCIATOR mode);

void setNavMode();
void setWptMode();
void setFplMode();
void setCalcMode();
void setAuxMode();
void setAptVorMode();

#endif