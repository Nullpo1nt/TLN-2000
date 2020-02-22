#include <string.h>

#include <XPLMPlugin.h>
#include "tln2000.h"

#if IBM
#include <windows.h>
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif

#ifndef XPLM301
#error This is made to be compiled against the XPLM301 SDK
#endif

// constexpr char *line1 = "/trimble2000A/cockpit/line1";
// constexpr char *line2 = "/trimble2000A/cockpit/line2";

constexpr char *annunciatorGpsStr = "/trimble2000A/annunciator/gps";
constexpr char *annunciatorWrnStr = "/trimble2000A/annunciator/wrn";
constexpr char *annunciatorAdvStr = "/trimble2000A/annunciator/adv";
constexpr char *annunciatorPtkStr = "/trimble2000A/annunciator/ptk";
constexpr char *annunciatorAprStr = "/trimble2000A/annunciator/apr";

constexpr char *annunciatorNavStr = "";
constexpr char *annunciatorWptStr = "";
constexpr char *annunciatorFplStr = "";
constexpr char *annunciatorCalcStr = "";
constexpr char *annunciatorAuxStr = "";
constexpr char *annunciatorAptVorStr = "";

constexpr char *annunciatorEntStr = "";

// Mode keys
constexpr char *keysNavStr = "/trimble2000A/keys/nav";
constexpr char *keysWptStr = "/trimble2000A/keys/wpt";
constexpr char *keysFplStr = "/trimble2000A/keys/fpl";
constexpr char *keysCalcStr = "/trimble2000A/keys/calc";
constexpr char *keysAuxStr = "/trimble2000A/keys/aux";
constexpr char *keysAptVorStr = "/trimble2000A/keys/apt_vor";

constexpr char *keysDirectStr = "/trimble2000A/keys/direct";
constexpr char *keysMsgStr = "/trimble2000A/keys/msg";
constexpr char *keysEntStr = "/trimble2000A/keys/ent";

constexpr char *keysPowerStr = "/trimble2000A/keys/power";

constexpr char *rotaryInner = "/trimble2000A/rotary/inner";
constexpr char *rotaryOuter = "/trimble2000A/rotary/outer";

int callback_pwr_cmd()
{
    tln2000::changeState(tln2000::TLN_EVENT_BTN_POWER);
}

int callback_ent_cmd()
{
    tln2000::changeState(tln2000::TLN_EVENT_BTN_ENT);
}

float flight_loop_callback(int argc, char **argv)
{
    tln2000::changeState(tln2000::TLN_EVENT_UPDATE);

    return 1.0f;
}

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc)
{
    strcpy(outName, "TLN2000Plugin");
    strcpy(outSig, "tln.pluginP");
    strcpy(outDesc, "TLN2000-Series GPS plugin");

    return 1;
}

PLUGIN_API int XPluginEnable(void) { return 1; }

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void *inParam) {}

PLUGIN_API void XPluginDisable(void) {}

PLUGIN_API void XPluginStop(void) {}
