#include <util.h>
#include <ge/graphics/GraphicsCore.h>

float getRelativeHeight(float h)
{
	int winW, winH;
	ge::GraphicsCore::ctx->window->getSize(&winW, &winH);
	return h*winW; //NOTE: nuklear only scales by width
}

struct nk_rect getRelativeRect(float x, float y, float w, float h)
{
	int winW, winH;
	ge::GraphicsCore::ctx->window->getSize(&winW, &winH);
	return nk_rect(x*winW, y*winW, w*winW, h*winW); //NOTE: nuklear only scales by width
}

struct nk_rect getRelativeRect_WIN(float x, float y, float w, float h)
{
	int winW, winH;
	ge::GraphicsCore::ctx->window->getSize(&winW, &winH);
	return nk_rect(x*winW, y*winH, w*winW, h*winH); //NOTE: nuklear only scales by width
}
