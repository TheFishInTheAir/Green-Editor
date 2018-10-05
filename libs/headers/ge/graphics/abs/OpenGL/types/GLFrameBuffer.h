#pragma once
#include <ge/graphics/types/FrameBuffer.h>
#include <ge/graphics/abs/OpenGL/types/GLTexture.h>
#include <unordered_map>
namespace ge
{
    namespace GL
    {
        struct FrameBuffer : public ge::FrameBuffer
        {
            void init(uint32_t width, uint32_t height);

            void bind();
            void bindDefault();

            void generateBufferAttachment(FrameBufferAttachment::buffer);
            void generateTextureAttachment(FrameBufferAttachment::texture);

            ge::Texture* getTextureAttachment(FrameBufferAttachment::texture);

            uint32_t getWidth();
            uint32_t getHeight();

            void shallowDestroy();
            void deepDestroy();

            void clear();
            bool hasDepth();
            bool hasColour();

            unsigned int id;

            std::unordered_map<FrameBufferAttachment::texture, ge::GL::Texture*> textureAttachments;
            std::unordered_map<FrameBufferAttachment::buffer, uint32_t> bufferAttachments; //tbh I don't understand theese

        private:
            uint32_t width, height;

            bool _hasDepth = false;
            bool _hasColour = false;
        };
    }
}
