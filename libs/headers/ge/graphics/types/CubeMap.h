//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/graphics/enums/TextureFilterType.h>
#include <ge/graphics/enums/ColourModelType.h>
#include <ge/error/Error.h>

namespace ge
{
	struct CubeMap
	{
		std::string xp_url;
		std::string xn_url;
		
		std::string yp_url;
		std::string yn_url;

		std::string zp_url;
		std::string zn_url;
		
		int getDimension() const;

		TextureFilterType::type getFiltering();
		ColourModelType::type getColourModel();
		virtual Error setFiltering(TextureFilterType::type) = 0;

	private:
		int dim;

		TextureFilterType::type filtering;
		ColourModelType::type colourModel;

	};
}