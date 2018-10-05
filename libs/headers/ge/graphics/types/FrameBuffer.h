#pragma once
#include <cstdint>
#include <ge/graphics/enums/FrameBufferAttachment.h>
#include <ge/graphics/types/Texture.h>
namespace ge
{
    struct FrameBuffer
    {
        virtual void bind() = 0;
        virtual void bindDefault() = 0;
        
        virtual void generateBufferAttachment(FrameBufferAttachment::buffer) = 0;
        virtual void generateTextureAttachment(FrameBufferAttachment::texture) = 0;
        
        virtual Texture* getTextureAttachment(FrameBufferAttachment::texture) = 0;

        virtual uint32_t getWidth() = 0;
        virtual uint32_t getHeight() = 0;

        virtual void shallowDestroy() = 0;
        virtual void deepDestroy() = 0;

        virtual void clear() = 0;
        virtual bool hasDepth() = 0;
        virtual bool hasColour() = 0;
    };
}