#pragma once
#include <engine/global_settings.pre>
namespace ge
{
	namespace LightType
	{

		typedef enum {
			Point = LIGHT_POINT,
			Directional = LIGHT_DIRECTIONAL,
			Spot = LIGHT_SPOT

		} type;
		
	}
}