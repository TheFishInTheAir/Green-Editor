//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <graphics/enums/TextureFilterType.h>
#include <graphics/enums/ColourModelType.h>
#include <error/Error.h>

namespace ge
{
	struct CubeMap
	{
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