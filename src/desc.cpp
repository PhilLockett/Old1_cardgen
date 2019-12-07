#include "cardgen.h"
#include "desc.h"


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <err.h>
#include <sstream>

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

int desc::genDrawString(void)
{
    stringstream outputStream;
    outputStream  << "\t-draw \"image over " << OriginX << ',' << OriginY << ' ' << ROUND(getWidth()) << ',' << ROUND(getHeight()) << " '" << FileName << "'\" \\" << endl;
    DrawString = outputStream.str();

    return 0;
}

desc::desc(float H, float X, float Y, string FN)
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

desc::desc(info & I, string FN)
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

void desc::repos(float X, float Y)
{
    CentreX = X * cardWidth / 100;
    CentreY = Y * cardHeight / 100;
    OriginX = ROUND(centre2OriginX(CentreX));
    OriginY = ROUND(centre2OriginY(CentreY));
    genDrawString();
}

void desc::setFileName(string FN)
{
    FileName = FN;
    getImageSize();
    Width   = Height * WidthPX / HeightPX;
    OriginX = ROUND(centre2OriginX(CentreX));
    genDrawString();
}
