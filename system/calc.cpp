#include "calc.h"

namespace tln::calc
{

int mode = 0;
int fuelMode = 0;

void renderCalc()
{
    switch (mode)
    {
    case 0:
        display::set("VNAV:on 125f t 105f", "a200f 29n fSMOv");
        break;
    case 1:
        display::set("FPL GS 160k  ETE 1:11", "DIST 191n    ETA 9:25");
        break;
    case 2:
        switch (fuelMode)
        {
        case 0:
            display::set("FUEL 145GAL  123 GPH", "DIST 190n    130 MPG");
            break;
        case 1:
            display::set("FUEL REMAINING  1754", "RANGE 14:15    2137n");
            break;
        case 2:
            display::set("FUEL AT ARRIVAL  535", "RESERVE  4:28   671n");
            break;
        case 3:
            display::set("TOTAL FUEL USED  412", "LEFT 198  RIGHT 214");
            break;
        case 4:
            display::set("ENGINE FUEL FLOW", "LEFT 998  RIGHT 1031");
            break;
        }
        break;
    case 3:
        display::set("PRESSURE ALT    128", "BRO 2861 IND ALT    116");
        break;
    case 4:
        display::set("DENSITY ALTITUDE 137", "OAT+19c  PRS ALT 105");
        break;
    case 5:
        display::set("TAS 145k   IAS 118k", "OAT+19c PRS ALT 105");
        break;
    case 6:
        display::set("WIND f 025d t at 28k", "TAS 153k   HDG 70d");
        break;
    case 7:
        display::set("X-WIND 16k  HEAD 19k", "RWY 31 WND 270d  25k");
        break;
    }
}

void calc()
{
    tln::annunciators::setCalcMode();

    renderCalc();
}

void calcNext()
{
    mode++;
    if (mode > 7)
    {
        mode = 0;
    }
    renderCalc();
}

void calcPrev()
{
    mode--;
    if (mode < 0)
    {
        mode = 7;
    }
    renderCalc();
}

void calcNextSub()
{
    if (mode != 2)
    {
        return;
    }

    fuelMode++;
    if (fuelMode > 4)
    {
        fuelMode = 0;
    }
    renderCalc();
}

void calcPrevSub()
{
    if (mode != 2)
    {
        return;
    }

    fuelMode--;
    if (fuelMode < 0)
    {
        fuelMode = 4;
    }
    renderCalc();
}

void calcSavePPos()
{
    display::set("PRESENT POSITION", "SAVED IN alpha");
}

} // namespace tln::calc