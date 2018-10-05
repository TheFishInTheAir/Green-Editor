//
// Created by Ethan Breit on 2017-12-23.
//

#pragma once

#include <ge/error/Error.h>
#include <ge/graphics/types/ShaderGroup.h>


namespace ge
{
	struct Scene;


    namespace ShaderLoader
    {

        Error loadShader(std::string path, ShaderGroup**);

		Error loadShader(std::string path, ShaderGroup**, Scene*);


		Error LoadRealShader(std::string path);


    }
}
