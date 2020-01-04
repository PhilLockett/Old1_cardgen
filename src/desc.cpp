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
// desc.cpp: Implementation for the info and desc classes.
//
///////////////////////////////////////////////////////////////////////////////

#include "cardgen.h"
#include "desc.h"

#include <arpa/inet.h>
#include <sstream>
#include <fstream>


///////////////////////////////////////////////////////////////////////////////
//
//- print function for info class.
//
void info::print(ostream &os) const
{
    os << H << "\t(" << X << ", " << Y << ")";
}



///////////////////////////////////////////////////////////////////////////////
//
//- Get the image size from the .png file.
//
bool desc::isValidPNG(const char * const buffer)
{
    const uint8_t magic[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
    for (int i = 0; i < sizeof(magic); ++i)
    {
        if ((uint8_t)buffer[i] != magic[i])
            return false;
    }

    return true;
}

int desc::getImageSize(void)
{
    FileFound = false;
    WidthPX = 1;
    HeightPX = 1;
    AspectRatio = 1;

//- Open the binary file.
    ifstream file(FileName, ifstream::in|ifstream::binary);

    if (!file.is_open())
    {
        return 1;
    }

//- Success. Read header data.
    char buffer[28];

    file.read(buffer, 24);
    if ((file) && (isValidPNG(buffer)))
    {
        FileFound = true;
        WidthPX = htonl(*(uint32_t *)(buffer+16));
        HeightPX = htonl(*(uint32_t *)(buffer+20));
        AspectRatio = float(WidthPX) / HeightPX;
    }

    file.close();

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//- Set up "DrawString"" for drawing the .png file with the correct size and position.
//
int desc::genDrawString(void)
{
    if ((Height == 0) || (Width == 0))
    {
        DrawString = "";	// Don't draw anything here.

        return 0;
    }

    stringstream outputStream;
    outputStream  << "\t-draw \"image over " << OriginX << ',' << OriginY << ' ' << ROUND(Width) << ',' << ROUND(Height) << " '" << FileName << "'\" \\" << endl;
    DrawString = outputStream.str();

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//- Constructors.
//
desc::desc(float H, float X, float Y, const string & FN)
: FileName(FN), FileFound(false)
{
    getImageSize();
    Height  = H * cardHeight / 100;
    Width   = Height * WidthPX / HeightPX;
    CentreX = X * cardWidth / 100;
    CentreY = Y * cardHeight / 100;
    OriginX = ROUND(centre2OriginX(CentreX));
    OriginY = ROUND(centre2OriginY(CentreY));
    genDrawString();
}

desc::desc(info & I, const string & FN)
: FileName(FN), FileFound(false)
{
    getImageSize();
    Height  = I.getH() * cardHeight / 100;
    Width   = Height * WidthPX / HeightPX;
    CentreX = I.getX() * cardWidth / 100;
    CentreY = I.getY() * cardHeight / 100;
    OriginX = ROUND(centre2OriginX(CentreX));
    OriginY = ROUND(centre2OriginY(CentreY));
    genDrawString();
}


///////////////////////////////////////////////////////////////////////////////
//
//- Reposition image and adjust internal values.
//
void desc::repos(float X, float Y)
{
    CentreX = X * cardWidth / 100;
    CentreY = Y * cardHeight / 100;
    OriginX = ROUND(centre2OriginX(CentreX));
    OriginY = ROUND(centre2OriginY(CentreY));
    genDrawString();
}


///////////////////////////////////////////////////////////////////////////////
//
//- Change image file image and adjust internal values.
//
void desc::setFileName(const string & FN)
{
    FileName = FN;
    getImageSize();
    Width   = Height * WidthPX / HeightPX;
    OriginX = ROUND(centre2OriginX(CentreX));
    genDrawString();
}

