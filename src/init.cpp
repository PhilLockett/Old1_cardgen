// init.cpp: Command line parameter initialisation for the card generator.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "cardgen.h"

#include <iostream>


///////////////////////////////////////////////////////////////////////////////
//
//- Display help message.
//
static void help(const char * const name)
{
    cout << "Usage: " << name << " [Options]" << endl;
    cout << "  Generates the bash script \"" << scriptFilename << "\" which draws a pack of playing cards."<< endl;
    cout << endl;
    cout << "  Options:" << endl;
    cout << "\t--help \t\t\t\t\tThis help page and nothing else." << endl;
    cout << endl;
    cout << "\t-i --index directory \t\t\tSubdirectory of indices to use (default: \"" << index << "\")." << endl;
    cout << "\t-p --pip directory \t\t\tSubdirectory of pips to use (default: \"" << pip << "\")." << endl;
    cout << "\t-f --face directory \t\t\tSubdirectory of faces to use (default: \"" << face << "\")." << endl;
    cout << endl;
    cout << "\t-s --script filename \t\t\tScript filename (default: \"" << scriptFilename << "\")." << endl;
    cout << "\t-o --output directory \t\t\tOutput filename (default: same directory name as face)." << endl;
    cout << "\t-w --width integer \t\t\tCard width in pixels (default: " << cardWidth << ")." << endl;
    cout << "\t-h --height integer \t\t\tCard height in pixels (default: " << cardHeight << ")." << endl;
    cout << "\t-c --colour name \t\t\tBackground colour name (defined at: http://www.imagemagick.org/script/color.php, default: \"" << cardColour << "\")." << endl;
    cout << "\t-a --KeepAspectRatio \t\t\tKeep image Aspect Ratio (default: " << (aspectRatio ? "true" : "false") << ")." << endl;
    cout << endl;
    cout << "\t--IndexHeight value \t\t\tHeight of index as a % of card height (default: " << Index.getHeight() << ")." << endl;
    cout << "\t--IndexCentreX value \t\t\tX value of centre of index as a % of card width (default: " << Index.getX() << ")." << endl;
    cout << "\t--IndexCentreY value \t\t\tY value of centre of index as a % of card height (default: " << Index.getY() << ")." << endl;
    cout << "\t--CornerPipHeight value \t\tHeight of corner pip as a % of card height (default: " << CornerPip.getHeight() << ")." << endl;
    cout << "\t--CornerPipCentreX value \t\tX value of centre of corner pip as a % of card width (default: " << CornerPip.getX() << ")." << endl;
    cout << "\t--CornerPipCentreY value \t\tY value of centre of corner pip as a % of card height (default: " << CornerPip.getY() << ")." << endl;
    cout << "\t--StandardPipHeight value \t\tHeight of standard pip as a % of card height (default: " << StandardPip.getHeight() << ")." << endl;
    cout << "\t--StandardPipCentreX value \t\tX value of centre of standard pip as a % of card width (default: " << StandardPip.getX() << ")." << endl;
    cout << "\t--StandardPipCentreY value \t\tY value of centre of standard pip as a % of card height (default: " << StandardPip.getY() << ")." << endl;
    cout << "\t--ImageBoarderX value \t\t\tImage Boarder in X direction as a % of card width (default: " << boarderX << ")." << endl;
    cout << "\t--ImageBoarderY value \t\t\tImage Boarder in Y direction as a % of card height (default: " << boarderY << ")." << endl;
    cout << "\t--ImagePipOff \t\t\t\tDon't display image pip on the court cards." << endl;
    cout << "\t--ImagePipHeight value \t\t\tHeight of image pip as a % of card height (default: " << ImagePip.getHeight() << ")." << endl;
    cout << "\t--ImagePipCentreX value \t\tX value of centre of image pip as a % of card width relative to ImageBoarderX (default: " << ImagePip.getX() << ")." << endl;
    cout << "\t--ImagePipCentreY value \t\tY value of centre of image pip as a % of card height relative to ImageBoarderY (default: " << ImagePip.getY() << ")." << endl;
    cout << endl;
    cout << "\t--CentreX value \t\t\tShortcut for: --IndexCentreX value --CornerPipCentreX value." << endl;
    cout << "\t--Inputs value \t\t\t\tShortcut for: -f value -p value -i value." << endl;
}


///////////////////////////////////////////////////////////////////////////////
//
//- Process command line parameters with help from getopt_long().
//
static int parseCommandLine(int argc, char *argv[])
{
    while (1)
    {
        int option_index = 0;
        int optchr;

        static struct option long_options[] = {
            {"width",   required_argument,0,'w'},
            {"height",  required_argument,0,'h'},
            {"colour",  required_argument,0,'c'},

            {"index",   required_argument,0,'i'},
            {"pip",     required_argument,0,'p'},
            {"face",    required_argument,0,'f'},

            {"script",  required_argument,0,'s'},
            {"output",  required_argument,0,'o'},
            {"help",    no_argument,0,0},
            {"KeepAspectRatio",  no_argument,0,'a'},

            {"IndexHeight", required_argument,0,1},
            {"IndexCentreX", required_argument,0,2},
            {"IndexCentreY", required_argument,0,3},

            {"CornerPipHeight", required_argument,0,4},
            {"CornerPipCentreX", required_argument,0,5},
            {"CornerPipCentreY", required_argument,0,6},

            {"StandardPipHeight", required_argument,0,7},
            {"StandardPipCentreX", required_argument,0,8},
            {"StandardPipCentreY", required_argument,0,9},

            {"ImageBoarderX", required_argument,0,10},
            {"ImageBoarderY", required_argument,0,11},
            {"ImagePipOff", no_argument,0,12},
            {"ImagePipHeight", required_argument,0,13},
            {"ImagePipCentreX", required_argument,0,14},
            {"ImagePipCentreY", required_argument,0,15},

            {"CentreX", required_argument,0,16},
            {"Inputs", required_argument,0,17},
            {0,0,0,0}
        };

        optchr = getopt_long(argc, argv ,"w:h:c:i:p:f:s:o:a", long_options, &option_index);
        if (optchr == -1)
            return 0;

        switch (optchr)
        {
            case 'w': cardWidth = atoi(optarg);         break;
            case 'h': cardHeight = atoi(optarg);        break;
            case 'c': cardColour = string(optarg);      break;

            case 'i': index = string(optarg);           break;
            case 'p': pip = string(optarg);             break;
            case 'f': face = string(optarg);            break;

            case 's': scriptFilename = string(optarg);  break;
            case 'o': outputDirectory = string(optarg); break;

            case 'a': keepAspectRatio = true;           break;

            case 1:   Index.setHeight(atof(optarg));    break;
            case 2:   Index.setX(atof(optarg));         break;
            case 3:   Index.setY(atof(optarg));         break;

            case 4:   CornerPip.setHeight(atof(optarg));break;
            case 5:   CornerPip.setX(atof(optarg));     break;
            case 6:   CornerPip.setY(atof(optarg));     break;

            case 7:   StandardPip.setHeight(atof(optarg));break;
            case 8:   StandardPip.setX(atof(optarg));   break;
            case 9:   StandardPip.setY(atof(optarg));   break;

            case 10:  boarderX = atof(optarg);          break;
            case 11:  boarderY = atof(optarg);          break;
            case 12:  ImagePip.setHeight(0);            break;
            case 13:  ImagePip.setHeight(atof(optarg)); break;
            case 14:  ImagePip.setX(atof(optarg));      break;
            case 15:  ImagePip.setY(atof(optarg));      break;

            case 16:
                Index.setX(atof(optarg));
                CornerPip.setX(atof(optarg));
                break;

            case 17:
                index = string(optarg);
                pip   = string(optarg);
                face  = string(optarg);
                break;

            case 0:
                help(argv[0]);

                return 1;

            default:
                help(argv[0]);

                return -1;
        }//end switch
    }//end while

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
//- Recalculate internal values using command line input.
//
int recalculate(void)
{
    int ret = 0;

//- Card outline values in pixels.
    radius = ROUND(cornerRadius * cardHeight / 100);
    outlineWidth = cardWidth-borderOffset-1;
    outlineHeight = cardHeight-borderOffset-1;

//- Card face image values in pixels.
    imageOffset = 60;
    imageOffsetWidth = cardWidth-imageOffset-imageOffset;
    imageOffsetHeight = (cardHeight/2)-imageOffset+1;

    imageWidth  = 100 - (2 * boarderX);
    imageHeight = 50 - boarderY;
    widthPX     = ROUND(imageWidth * cardWidth / 100);
    heightPX    = ROUND(imageHeight * cardHeight / 100);
    offsetX     = ROUND(boarderX * cardWidth / 100);
    offsetY     = ROUND(boarderY * cardHeight / 100);

    imageX      = 50;
    imageY      = boarderY + (imageHeight / 2);

//- If "outputDirectory" isn't explicitly set, use "face".
    if (!outputDirectory.length())
    {
        outputDirectory = face;
    }

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
//
//- Initailise using command line input and recalculated internal values.
//
int init(int argc, char *argv[])
{
    int ret = 0;

//- Adjust value for nicer result.
    Index.setHeight(10.0);          /* Height of index (as a % of card height). */
    CornerPip.setHeight(7.0);       /* Height of corner pip (as a % of card height). */
    StandardPip.setHeight(18.0);    /* Height of standard pip (as a % of card height). */
    ImagePip.setHeight(14.2);       /* Height of image pip (as a % of card height). */

//- Process command line input.
    ret = parseCommandLine(argc, argv);
    if (!ret)
    {
        recalculate();
    }

    return ret;
}

