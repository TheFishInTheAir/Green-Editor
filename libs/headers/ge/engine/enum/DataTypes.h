#pragma once
#include <json/json.hpp>
namespace ge
{
    namespace DataType
    {
        enum type
        {

            STRING,

            BOOL,

            INT,

            FLOAT,
            DOUBLE,

            FVEC2,
            FVEC3,
            FVEC4,

            FMAT2,
            FMAT3,
            FMAT4,

            QUAT,

            SHADER,
            SHADER_GROUP,

			AUDIO_CLIP,

            MESH_DATA,
            MATERIAL,

            TEXTURE,
            CUBEMAP,

            COLOUR3, //vec3 but with a nice UI
            COLOUR4  //vec4 but with a nice UI
        };

        nlohmann::json serialize(type, void*);
        void copy(type, void* src, void* dest);
        //void* deserialize(nlohmann::json);
        void deserialize(nlohmann::json, type, void*);

    }
}