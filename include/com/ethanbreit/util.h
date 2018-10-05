#pragma once
#include <nuklear.h>

struct nk_rect getRelativeRect(float x, float y, float w, float h);
struct nk_rect getRelativeRect_WIN(float x, float y, float w, float h);
float getRelativeHeight(float h);