//
// Created by Ethan Breit on 2017-08-10.
//

#pragma once

namespace ge
{
    namespace ReadableMemType
    {

        typedef enum
        {
            OTHER,
            FUNCTION,
            BOOLEAN,
            INTEGER,
            UNSIGNED_INTEGER,
            FLOAT,
            UNSIGNED_FLOAT,
            DOUBLE,
            UNSIGNED_DOUBLE,
            STRING
        } type;

    }
}
