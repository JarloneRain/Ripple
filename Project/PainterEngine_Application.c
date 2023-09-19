#include "PainterEngine_Application.h"
#include "Water.h"
#include <time.h>
PX_Application App;

#define WATER_BLUE PX_COLOR(255, 75, 175, 239)
#define DARK_WATER PX_COLOR(255, 35, 90, 120)
#define LIGHT_BLUE PX_COLOR(255, 0, 255, 255)

#define RAND_NP10 (rand() % 21 - 10)
#define RAND_NP100 (rand() % 201 - 100)
#define RAND_5_15 (rand() % 10 + 5)

int keyLayout[5][15] = {
#include "kb_layout.txt"
};
char keyName[62][10] = {
#include "kb_name.txt"
};

PX_Object *pKeyboard;
PX_Object *pKeys[62];

px_surface originalSurface;
WaterSurface waterSurface;

void NullFunc(PX_Object *pObj, PX_Object_Event e, px_void *ptr) {}
void kbWave(PX_Object *pObj, PX_Object_Event e, px_void *ptr)
{
	PushWave(&waterSurface, CreateWave(PX_Object_Event_GetCursorX(e), PX_Object_Event_GetCursorY(e),
									   RAND_5_15, RAND_5_15, 300 + RAND_NP100));
}

px_bool PX_ApplicationInitialize(PX_Application *pApp, px_int screen_width, px_int screen_height)
{
	int t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	int t = 0;
	const int in = 5;
	int keyWidth;

	srand(time(NULL));
	PX_ApplicationInitializeDefault(&pApp->runtime, screen_width, screen_height);

	waterSurface = CreateWaterSurface(20, 1.5);
	PX_SurfaceCreate(&pApp->runtime.mp_ui, pApp->runtime.surface_width, pApp->runtime.surface_height, &originalSurface);

	keyWidth = (pApp->runtime.surface_width - 16 * in) / 32;
	pKeyboard = PX_ObjectCreate(&pApp->runtime.mp_ui, PX_NULL, 0, 0, 0, pApp->runtime.surface_width, pApp->runtime.surface_height, 0);
	PX_ObjectRegisterEvent(pKeyboard, PX_OBJECT_EVENT_CURSORDOWN, kbWave, PX_NULL);

	do
	{
#define tSUM t0 + t1 + t2 + t3 + t4
		t = 3 * in;
		for (t0 = 0; t0 < 14; t0++)
		{
			pKeys[tSUM] = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, pKeyboard, t, in + 20, keyWidth * keyLayout[0][t0], 2 * keyWidth, keyName[tSUM], PX_NULL);

			PX_ObjectRegisterEvent(pKeys[tSUM], PX_OBJECT_EVENT_EXECUTE, NullFunc, PX_NULL);

			PX_Object_PushButtonSetBackgroundColor(pKeys[tSUM], WATER_BLUE);
			PX_Object_PushButtonSetCursorColor(pKeys[tSUM], DARK_WATER);

			t += keyWidth * keyLayout[0][t0] + in;
		}
		t = 3 * in;
		for (t1 = 0; t1 < 14; t1++)
		{
			pKeys[tSUM] = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, pKeyboard, t, 20 + in * 2 + 2 * keyWidth, keyWidth * keyLayout[1][t1], 2 * keyWidth, keyName[tSUM], PX_NULL);
			PX_ObjectRegisterEvent(pKeys[tSUM], PX_OBJECT_EVENT_EXECUTE, NullFunc, PX_NULL);

			PX_Object_PushButtonSetBackgroundColor(pKeys[tSUM], WATER_BLUE);
			PX_Object_PushButtonSetCursorColor(pKeys[tSUM], DARK_WATER);

			t += keyWidth * keyLayout[1][t1] + in;
		}
		t = 3 * in;
		for (t2 = 0; t2 < 13; t2++)
		{
			pKeys[tSUM] = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, pKeyboard, t, 20 + in * 3 + 4 * keyWidth, keyWidth * keyLayout[2][t2], 2 * keyWidth, keyName[tSUM], PX_NULL);
			PX_ObjectRegisterEvent(pKeys[tSUM], PX_OBJECT_EVENT_EXECUTE, NullFunc, PX_NULL);

			PX_Object_PushButtonSetBackgroundColor(pKeys[tSUM], WATER_BLUE);
			PX_Object_PushButtonSetCursorColor(pKeys[tSUM], DARK_WATER);

			t += keyWidth * keyLayout[2][t2] + in;
		}
		t = 3 * in;
		for (t3 = 0; t3 < 12; t3++)
		{
			pKeys[tSUM] = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, pKeyboard, t, 20 + in * 4 + 6 * keyWidth, keyWidth * keyLayout[3][t3], 2 * keyWidth, keyName[tSUM], PX_NULL);
			PX_ObjectRegisterEvent(pKeys[tSUM], PX_OBJECT_EVENT_EXECUTE, NullFunc, PX_NULL);

			PX_Object_PushButtonSetBackgroundColor(pKeys[tSUM], WATER_BLUE);
			PX_Object_PushButtonSetCursorColor(pKeys[tSUM], DARK_WATER);

			t += keyWidth * keyLayout[3][t3] + in;
		}
		t = 3 * in;
		for (t4 = 0; t4 < 5; t4++)
		{
			pKeys[tSUM] = PX_Object_PushButtonCreate(&pApp->runtime.mp_ui, pKeyboard, t, 20 + in * 5 + 8 * keyWidth, keyWidth * keyLayout[4][t4], 2 * keyWidth, keyName[tSUM], PX_NULL);
			PX_ObjectRegisterEvent(pKeys[tSUM], PX_OBJECT_EVENT_EXECUTE, NullFunc, PX_NULL);

			PX_Object_PushButtonSetBackgroundColor(pKeys[tSUM], WATER_BLUE);
			PX_Object_PushButtonSetCursorColor(pKeys[tSUM], DARK_WATER);

			t += keyWidth * keyLayout[4][t4] + in;
		}

#undef tSUM
	} while (0);
	return PX_TRUE;
}

px_void PX_ApplicationUpdate(PX_Application *pApp, px_dword elapsed)
{
	WaterSurfaceUpdate(&waterSurface, elapsed);
}

px_void PX_ApplicationRender(PX_Application *pApp, px_dword elapsed)
{
	px_surface *pRenderSurface = &pApp->runtime.RenderSurface;
	PX_RuntimeRenderClear(&pApp->runtime, LIGHT_BLUE);

	PX_SurfaceSetRect(&originalSurface, 0, 0, originalSurface.width, originalSurface.height, LIGHT_BLUE);
	PX_ObjectRender(&originalSurface, pKeyboard, elapsed);

	// PX_ObjectRender(pRenderSurface, pKeyboard, elapsed);
	px_point2D p;
	for (int i = 0; i < pApp->runtime.surface_width; i++)
	{
		for (int j = 0; j < pApp->runtime.surface_height; j++)
		{
			p = GetLightPoint(PX_POINT2D(i, j), &waterSurface);
			PX_SurfaceDrawPixel(pRenderSurface, i, j,
								(0 < p.x && p.x < pRenderSurface->width && 0 < p.y && p.y < pRenderSurface->height) ? originalSurface.surfaceBuffer[originalSurface.width * (int)p.y + (int)p.x] : LIGHT_BLUE);
		}
	}
}

px_void PX_ApplicationPostEvent(PX_Application *pApp, PX_Object_Event e)
{
	PX_ApplicationEventDefault(&pApp->runtime, e);

	PX_ObjectPostEvent(pKeyboard, e);
}
