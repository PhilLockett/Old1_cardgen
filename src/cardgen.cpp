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
// cardgen.h: Entry point for the card generator.
//
///////////////////////////////////////////////////////////////////////////////

#include "cardgen.h"
#include <sys/stat.h>

///////////////////////////////////////////////////////////////////////////////
//
//- Global variables.
//

// User defined.
int cardWidth  = 380;
int cardHeight = 532;
string cardColour("white");


info Index(10.5, 8.07, 9.84);
info CornerPip(7.5, 8.07, 20.41);
info StandardPip(18.5, 25.7, 18.65);
info ImagePip(14.29, 12.63, 9.77);

string index("1");
string pip("1");
string face("1");

string scriptFilename("draw.sh");
string refreshFilename("x_refresh.sh");
string outputDirectory;

bool keepAspectRatio = false;

float cornerRadius = 3.76;
int radius;
int strokeWidth = 2;
int borderOffset = 1;
int outlineWidth;
int outlineHeight;

float boarderX = 14.54;
float boarderY = 10.14;
float originalImageWidth = 100 - (2 * boarderX);
float originalImageHeight = 50 - boarderY;
int originalWidthPX  = ROUND(originalImageWidth * cardWidth / 100);
int originalHeightPX = ROUND(originalImageHeight * cardHeight / 100);

float imageWidth;
float imageHeight;
int widthPX;
int heightPX;
int offsetX;
int offsetY;
float imageX;
float imageY;


///////////////////////////////////////////////////////////////////////////////
//
//- Entry point.
//
int main(int argc, char *argv[])
{
//- Get the command line parameters.
    int ret = init(argc, argv);

    if (ret < 0)
    {
        return 1;
    }

//- If all is well, generate the script.
    if (!ret)
    {
        generateScript(argc, argv);

        // Ensure output scripts are executable.
        chmod(scriptFilename.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
    }

    return 0;
}

