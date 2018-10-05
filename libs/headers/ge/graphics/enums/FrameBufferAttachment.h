#pragma once
namespace ge
{
    namespace FrameBufferAttachment
    {
        typedef enum
        {
            Colour = 0x00,
            Depth   = 0x10, //I really don't know what the detail of this map is...
            Depth16 = 0x11,
            Depth24 = 0x12,
            Depth32 = 0x13,
        } texture;
        typedef enum
        {
            Depth24_Stencil8,//TODO: add others
            
        } buffer;
    }
}