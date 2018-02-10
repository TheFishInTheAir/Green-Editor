//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once
namespace ge
{
    namespace ColourModelType
    {
        typedef enum
        {

			///Single Channel
			BW		= 0x0000,
			
			///Double Channel
			BWA		= 0x1000,

			///Three Channel
            RGB     = 0x2000,
            BGR     = 0x2001,

			///Four Channel
            ARGB    = 0x3002,
            RGBA    = 0x3003,
            ABGR    = 0x3004,
            BGRA    = 0x3005,
            /*CMYK,
            ACMYK,
            CMYKA,*/

        } type;

        //TODO: function to check if model has alpha

    }
}