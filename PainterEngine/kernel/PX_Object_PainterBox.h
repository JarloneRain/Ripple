#ifndef PX_PAINTERBOX_H
#define PX_PAINTERBOX_H

#include "PX_Object.h"

typedef enum 
{
	PX_OBJECT_PAINTERBOX_TOOL_TYPE_PEN,
	PX_OBJECT_PAINTERBOX_TOOL_TYPE_ERASER,
	PX_OBJECT_PAINTERBOX_TOOL_TYPE_SPRAY,
	PX_OBJECT_PAINTERBOX_TOOL_TYPE_PAINT,
	PX_OBJECT_PAINTERBOX_TOOL_TYPE_HAND,
}PX_OBJECT_PAINTERBOX_TOOL_TYPE;


typedef struct
{
	PX_Object *widget;
	PX_Object *color_panel,*button_pen,*button_paint,*button_eraser,*button_spray,*button_hand;
	PX_Object* sliderbar_size,* sliderbar_alpha,*image_present;
	px_texture tex_Eraser, tex_Paint, tex_Pen, tex_Spray,tex_Hand;
	px_texture present;
	PX_OBJECT_PAINTERBOX_TOOL_TYPE tool_type;

}PX_Object_PainterBox;

px_float PX_Object_PainterBoxGetToolSize(PX_Object* pObject);
px_float PX_Object_PainterBoxGetToolAlpha(PX_Object* pObject);
PX_Object* PX_Object_PainterBoxCreate(px_memorypool* mp, PX_Object* Parent, px_int x, px_int y);

#endif