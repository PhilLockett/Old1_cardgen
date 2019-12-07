#include "cardgen.h"
#include <sys/stat.h>

// User defined.
int cardWidth  = 380;
int cardHeight = 532;
string cardColour("white");


info Index(10.5019, 8.06791, 9.83619);
info CornerPip(7.73431, 8.06791, 20.4054);
info StandardPip(18.8945, 25.3007, 18.6476);
info ImagePip(14.2857, 12.6316, 9.7744);

string index("1");
string pip("1");
string face("1");

string scriptFilename("draw.sh");
string refreshFilename("x_refresh.sh");
string outputDirectory;

bool keepAspectRatio = false;
float aspectRatio = 0.0;

float cornerRadius = 3.7594;
int radius;
int strokeWidth = 2;
int borderOffset = 1;
int outlineWidth;
int outlineHeight;

int imageOffset;
int imageOffsetWidth;
int imageOffsetHeight;

float boarderX = 14.5379;
float boarderY = 10.1364;
float imageWidth;
float imageHeight;
int widthPX;
int heightPX;
int offsetX;
int offsetY;
float imageX;
float imageY;


///////////////////////////////////////////////////////////////////////////////
//- 

int main(int argc, char *argv[])
{
    int ret = init(argc, argv);

    if (ret < 0)
    {
        return 1;
    }

    if (!ret)
    {
        dumpCode(argc, argv);

        // Ensure output scripts are executable.
        chmod(scriptFilename.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
        chmod(refreshFilename.c_str(), S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
    }

    return 0;
}
