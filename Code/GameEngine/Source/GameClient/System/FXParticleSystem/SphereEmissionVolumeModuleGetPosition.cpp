// cl: /O1 /arch:SSE /G7 /ICode/Libraries/Include/Lib
// Sphere emission-volume callback: native 0x0055D48C..0x0055D50D.
// Target evidence: constructor 0x003AC087 installs primary table 0x0081C7B8;
// slot 7 selects this 129-byte RET20 body. The callback reads hollow +0x20
// and radius +0x24, calls random 0x00234111 and unit-vector 0x003AFA64.
// WB 0x0141B180 (fxpsemitterspherevolumemodule.cpp:86) corroborates the
// algorithm and by-value coordinate result. This scoped ABI view spells its
// hidden output pointer explicitly; the four other scalar arguments are unused.
// Donor semantic lead: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe,
// game/GameEngine/Source/GameClient/System/FXParticleSystem/
// SphereEmissionVolumeModuleGetPosition.cpp. Receiver prefix is unmodeled.
#include "Coord3D.h"

float __cdecl GetGameClientRandomValueReal(float, float, char *, int);
Coord3D *__cdecl Rva003AFA64FillUnitVector(Coord3D *);

class SphereEmissionVolumeModuleAbiView {
public:
    Coord3D *getPosition(Coord3D *out, float, float, float, float);
private:
    unsigned char prefix[0x20];
    bool hollow;
    unsigned char alignment[3];
    float radius;
};

Coord3D *SphereEmissionVolumeModuleAbiView::getPosition(
    Coord3D *out, float, float, float, float)
{
    char *source = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterspherevolumemodule.cpp";
    float scale = hollow ? radius :
        GetGameClientRandomValueReal(0.0f, radius, source, 86);
    Coord3D scratch;
    Coord3D unit = *Rva003AFA64FillUnitVector(&scratch);
    // Observe the copied coordinates before multiplying, as in retail's
    // three consecutive MOVSS loads. No volatile object layout is asserted.
    volatile Coord3D &v = unit;
    float x = v.x, y = v.y, z = v.z;
    out->x = x * scale;
    out->y = y * scale;
    out->z = z * scale;
    return out;
}
