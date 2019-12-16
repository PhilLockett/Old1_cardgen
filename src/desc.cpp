// desc.cpp: Implementation for the info and desc classes.
//
///////////////////////////////////////////////////////////////////////////////

#include "cardgen.h"
#include "desc.h"


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <err.h>
#include <sstream>


///////////////////////////////////////////////////////////////////////////////
//
//- print function for info class.
//
void info::print(ostream &os) const
{
    os << Height << "\t(" << CentreX << ", " << CentreY << ")";
}

///////////////////////////////////////////////////////////////////////////////
//
//- Get the image size from the .png file.
//
int desc::getImageSize(void)
{
    int ret = 1;
    int fd;
    uint32_t h, w;

    WidthPX = 1;
    HeightPX = 1;
    AspectRatio = 1;
    FileFound = false;

    if ((fd = open(FileName.c_str(), O_RDONLY)) != -1)
    {
        if (lseek(fd, 16, SEEK_SET) != -1)
        {
            if (read(fd, &w, 4) == 4)
            {
                if (read(fd, &h, 4) == 4)
                {
                    WidthPX = htonl(w);
                    HeightPX = htonl(h);
                    AspectRatio = float(WidthPX) / HeightPX;
                    ret = 0;
                    FileFound = true;
                }
            }
        }

        close(fd);
    }

    return ret;
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
    Height  = I.getHeight() * cardHeight / 100;
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

