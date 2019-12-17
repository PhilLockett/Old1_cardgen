/*  cardgen - a playing card image generator.

    Copyright 2019 Philip Lockett.

    This file is part of cardgen.

    cardgen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cardgen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cardgen.  If not, see <https://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////
//
// cardgen.h: Common interfaces for the card generator.
//
///////////////////////////////////////////////////////////////////////////////

#if !defined _CARDGEN_H_INCLUDED_
#define _CARDGEN_H_INCLUDED_

#include <string>
#include "desc.h"

using namespace std;

#if !defined ELEMENTS
#define ELEMENTS(A) (sizeof(A)/sizeof(A[0]))
#endif

#if !defined ROUND
#define ROUND(v) (int)((v) + 0.5)
#endif

///////////////////////////////////////////////////////////////////////////////
//
//- Global variables.
//

// User defined.
extern int cardWidth;
extern int cardHeight;
extern string cardColour;

extern info Index;
extern info CornerPip;
extern info StandardPip;
extern info ImagePip;

extern string index;
extern string pip;
extern string face;

extern string scriptFilename;
extern string outputDirectory;
extern string refreshFilename;

extern bool keepAspectRatio;
extern float aspectRatio;

extern float cornerRadius;
extern int radius;
extern int strokeWidth;
extern int borderOffset;
extern int outlineWidth;
extern int outlineHeight;

extern int imageOffset;
extern int imageOffsetWidth;
extern int imageOffsetHeight;

extern float boarderX;
extern float boarderY;
extern float imageWidth;
extern float imageHeight;
extern int widthPX;
extern int heightPX;
extern int offsetX;
extern int offsetY;
extern float imageX;
extern float imageY;


///////////////////////////////////////////////////////////////////////////////
//
//- Common functions.
//
extern int recalculate(void);
extern int init(int argc, char *argv[]);
extern int generateScript(int argc, char *argv[]);

#endif //!defined _CARDGEN_H_INCLUDED_

