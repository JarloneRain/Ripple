#include <math.h>
#include <stdlib.h>
#include "Water.h"
#include "PainterEngine_Startup.h"

#define RANDX rand() % 400
#define RANDY rand() % 150
#define _2PI 6.2831853072f

Wave CreateWave(float x, float y, float A, float l, int T)
{
  Wave w;
  w.X = x;
  w.Y = y;
  w.A = A;
  w.L = l;
  w.T0 = 0;
  w.T = T;
  return w;
}

WaterSurface CreateWaterSurface(float height, float N)
{
  WaterSurface ws;
  ws.Height = height;
  ws.Index = 0;
  ws.N = 1.5;
  for (size_t k = 0; k < WAVE_SIZE; k++)
  {
    ws.Waves[k] = CreateWave(RANDX, RANDY, 10, 20, 100);
  }
  return ws;
}

float getWaveOffset(Wave *pW, float r, int t, float v)
{
  return t * v > r ? pW->A * sinf(_2PI * (r / pW->L - t * 1.0 / pW->T)) /
                         expf(MU_R * r + MU_T * (t - r / v))
                   : 0;
}

void WaterSurfaceUpdate(WaterSurface *pWS, px_dword elapsed)
{
  for (int k = 0; k < WAVE_SIZE; k++)
  {
    pWS->Waves[k].T0 -= elapsed;
  }
#ifdef MEM_OPTI
  for (int i = 0; i <= MEM_WIDTH; i++)
  {
    for (int j = 0; j <= MEM_HEIGHT; j++)
    {
      pWS->PointHeight[i][j] = pWS->Height;
    }
  }

  float r;
  float v;
  int t;
  Wave *pW;
  for (int k = 0; k < WAVE_SIZE; k++)
  {
    pW = &pWS->Waves[k];
    t = -pW->T0;
    v = pW->L / pW->T;
    for (int i = 0; i <= MEM_WIDTH; i++)
    {
      for (int j = 0; j <= MEM_HEIGHT; j++)
      {
        r = sqrt((i - pW->X) * (i - pW->X) + (j - pW->Y) * (j - pW->Y));
        pWS->PointHeight[i][j] += getWaveOffset(pW, r, t, v);
      }
    }
  }
#endif
}

float getWaterHeight(WaterSurface *pWS, float x, float y)
{
#ifdef MEM_OPTI
  if (0 < x && x < MEM_WIDTH + 2 && 0 < y && y < MEM_HEIGHT + 2)
  {
    return pWS->PointHeight[(int)x][(int)y];
  }
  return pWS->Height;
#else
  float h = pWS->Height;
  Wave *pW;
  float r;
  float v;
  int t;
  for (int k = 0; k < WAVE_SIZE; k++)
  {
    pW = &pWS->Waves[k];
    t = -pW->T0;
    v = pW->L / pW->T;
    r = sqrt((x - pW->X) * (x - pW->X) + (y - pW->Y) * (y - pW->Y));

    h += getWaveOffset(pW, r, t, v);
  }
  return h;
#endif
}

void PushWave(WaterSurface *pWS, Wave wave)
{
  pWS->Waves[pWS->Index++] = wave;
  pWS->Index %= WAVE_SIZE;
}

px_point2D GetLightPoint(px_point2D i, WaterSurface *pWS)
{
  px_point2D r;
  float h = getWaterHeight(pWS, i.x + 0.1, i.y + 0.1);
  float a = h - getWaterHeight(pWS, i.x + 1.1, i.y),
        b = h - getWaterHeight(pWS, i.x, i.y + 1.1);
  float n = pWS->N;
  float t = (sqrt(n * n * n * n + (n * n - 1) * (a * a + b * b - n * n)) - n * n) /
            (a * a + b * b - n * n);
  r.x = i.x + a * t * h;
  r.y = i.y + b * t * h;
  return r;
}