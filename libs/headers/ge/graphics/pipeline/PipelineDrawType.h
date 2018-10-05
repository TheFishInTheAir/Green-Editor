#pragma once
namespace ge
{
    namespace PipelineDrawType
    {
        typedef enum
        {
            Default,
            GUI,
            PostProcessing,
            DepthMap,
            Final_Blit
            
            

        } type;
    }
    namespace PipelineState
    {
        typedef enum
        {
            NotRendering,
            Render,
            PostRender
        } type;
    }
}