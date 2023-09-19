#include "./PainterEngine_Startup.h"

#define MU_R 0.025
#define MU_T 0.002

#define MEM_OPTI

#ifdef MEM_OPTI
#define MEM_WIDTH 400
#define MEM_HEIGHT 150
#endif

typedef struct Wave
{
  float X, Y;
  float A;
  float L;
  int T0;
  int T;
} Wave;

#define WAVE_SIZE 10
typedef struct WaterSurface
{
  Wave Waves[WAVE_SIZE];
  float Height;
  float N;
  int Index;
#ifdef MEM_OPTI
  float PointHeight[MEM_WIDTH + 5][MEM_HEIGHT + 5];
#endif
} WaterSurface;
WaterSurface CreateWaterSurface(float height, float N);
Wave CreateWave(float x, float y, float A, float l, int T);
void PushWave(WaterSurface *pWS, Wave wave);
void WaterSurfaceUpdate(WaterSurface *pWS, px_dword elapsed);

px_point2D GetLightPoint(px_point2D i, WaterSurface *pWS);