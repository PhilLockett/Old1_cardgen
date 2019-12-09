// dump.cpp: Card generation script generator.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "cardgen.h"
#include "desc.h"


///////////////////////////////////////////////////////////////////////////////
//
//- Internal variables.
//
static const char* suits[]     = { "C", "D", "H", "S" };
static const char* alts[]      = { "S", "H", "D", "C" };
static const char* cards[]     = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

static const char* suitNames[]     = { "Clubs", "Diamonds", "Hearts", "Spades" };
static const char* cardNames[]     = { "Joker", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

static string suit;
static string alt;
static string card;


///////////////////////////////////////////////////////////////////////////////
//
//- Genarate the blank card string used as a template for each card.
//
static string genStartString(void)
{
    stringstream outputStream;
    outputStream  << "convert -size " << cardWidth << "x" << cardHeight << " xc:transparent  \\" << endl;
    outputStream  << "\t-fill '" << cardColour << "' -stroke black -strokewidth " << strokeWidth << " -draw 'roundRectangle " << borderOffset << ',' << borderOffset << ' ' << outlineWidth << ',' << outlineHeight << ' ' << radius << ',' << radius << "' \\" << endl;

    return outputStream.str();
}


///////////////////////////////////////////////////////////////////////////////
//
//- Generate the string for drawing the pips on the card. This is a two pass
//  process. The second pass is after the image is rotated.
//
static string drawStandardPips(int pass, int card, const string & FileName)
{
    stringstream outputStream;
    desc pipD(StandardPip, FileName);

    if (pass == 1)
    {
        if ((card == 2) || (card == 3) || (card == 12) || (card == 13))
        {
            pipD.repos(50, StandardPip.getY());
            outputStream  << pipD.draw();
        }

        if (card >= 4)
        {
            pipD.repos(StandardPip.getX(), StandardPip.getY());
            outputStream  << pipD.draw();

            pipD.repos(100-StandardPip.getX(), StandardPip.getY());
            outputStream  << pipD.draw();
        }

        if ((card == 8) || (card > 10))
        {
            pipD.repos(50, (50+StandardPip.getY())/2);
            outputStream  << pipD.draw();
        }

        if (card >= 9)
        {
            pipD.repos(StandardPip.getX(), StandardPip.getY()+(100-StandardPip.getY()-StandardPip.getY())/3);
            outputStream  << pipD.draw();

            pipD.repos(100-StandardPip.getX(), StandardPip.getY()+(100-StandardPip.getY()-StandardPip.getY())/3);
            outputStream  << pipD.draw();
        }

        if (card == 10)
        {
            pipD.repos(50, StandardPip.getY()+(100-StandardPip.getY()-StandardPip.getY())/6);
            outputStream  << pipD.draw();
        }
    }
    else
    if (pass == 2)
    {
        if ((card == 1) || (card == 3) || (card == 5) || (card == 9) || (card == 11) || (card == 13))
        {
            pipD.repos(50, 50);
            outputStream  << pipD.draw();
        }

        if ((card == 2) || (card == 3) || (card == 12) || (card == 13))
        {
            pipD.repos(50, StandardPip.getY());
            outputStream  << pipD.draw();
        }

        if (card >= 4)
        {
            pipD.repos(StandardPip.getX(), StandardPip.getY());
            outputStream  << pipD.draw();

            pipD.repos(100-StandardPip.getX(), StandardPip.getY());
            outputStream  << pipD.draw();
        }

        if ((card == 6) || (card == 7) || (card == 8))
        {
            pipD.repos(StandardPip.getX(), 50);
            outputStream  << pipD.draw();

            pipD.repos(100-StandardPip.getX(), 50);
            outputStream  << pipD.draw();
        }

        if ((card == 7) || (card == 8) || (card > 10))
        {
            pipD.repos(50, (50+StandardPip.getY())/2);
            outputStream  << pipD.draw();
        }

        if (card >= 9)
        {
            pipD.repos(StandardPip.getX(), StandardPip.getY()+(100-StandardPip.getY()-StandardPip.getY())/3);
            outputStream  << pipD.draw();

            pipD.repos(100-StandardPip.getX(), StandardPip.getY()+(100-StandardPip.getY()-StandardPip.getY())/3);
            outputStream  << pipD.draw();
        }

        if (card == 10)
        {
            pipD.repos(50, StandardPip.getY()+(100-StandardPip.getY()-StandardPip.getY())/6);
            outputStream  << pipD.draw();
        }
    }

    return outputStream.str();
}


///////////////////////////////////////////////////////////////////////////////
//
//- Generate the string for drawing the image on the card. Usually used for the
//  court cards. Numerous internal variables need to be recalculated if the
//  aspect ratio of the image is to be maintained, otherwise the image is
//  stretched to fill the card.
//
static string drawImage(const desc & faceD, const string & FileName)
{
    stringstream outputStream;
    int x = offsetX;
    int y = offsetY;
    int w = widthPX;
    int h = heightPX;
    float scale = 1;

    if (faceD.isLandscape())
    {
        if (keepAspectRatio)
        {
            aspectRatio = float(widthPX) / heightPX;
            if (faceD.getAspectRatio() < aspectRatio)
            {
                // Use heightPX to redefine view port size.
                scale = (float)heightPX / faceD.getHeightPX();
                w = ROUND(scale * faceD.getWidthPX()) + 1;
                x = (cardWidth - w)/2;
            }
            else
            {
                // Use widthPX to redefine view port size.
                scale = (float)widthPX / faceD.getWidthPX();
                h = ROUND(scale * faceD.getHeightPX());
                y = (cardHeight/2) - h;
            }
        }
    }
    else
    {
        h = 2*heightPX;
        if (keepAspectRatio)
        {
            aspectRatio = (float)widthPX / (2*heightPX);
            if (faceD.getAspectRatio() < aspectRatio)
            {
                // Use 2*heightPX to redefine view port size.
                scale = (float)(heightPX * 2) / faceD.getHeightPX();
                w = ROUND(scale * faceD.getWidthPX());
                x = (cardWidth - w)/2;
            }
            else
            {
                // Use widthPX to redefine view port size.
                scale = (float)widthPX / faceD.getWidthPX();
                h = ROUND(scale * faceD.getHeightPX());
                y = (cardHeight - h)/2;
            }
        }
    }

    outputStream << "\t-draw \"image over " << x << ',' << y << ' ' << w << ',' << h << " '" << faceD.getFileName() << "'\" \\" << endl;

//- Pip Filename is only supplied for court cards if they need pips adding.
    desc pipD(ImagePip, FileName);
    if (pipD.isFileFound() && ImagePip.getHeight())
    {
        outputStream << "\t-draw \"image over " << pipD.getOriginX()+x << ',' << pipD.getOriginY()+y << ' ' << ROUND(pipD.getWidth()) << ',' << ROUND(pipD.getHeight()) << " '" << FileName << "'\" \\" << endl;
        outputStream << "\t-rotate 180 \\" << endl;
        outputStream << "\t-draw \"image over " << pipD.getOriginX()+x << ',' << pipD.getOriginY()+y << ' ' << ROUND(pipD.getWidth()) << ',' << ROUND(pipD.getHeight()) << " '" << FileName << "'\" \\" << endl;
        outputStream << "\t-rotate 180 \\" << endl;
    }

    return outputStream.str();
}


///////////////////////////////////////////////////////////////////////////////
//
//- Joker drawing routines - a bit messy, but gets the job done.
//
static int drawImageMagickJoker(ofstream & file, const string & fileName)
{
    string startString = genStartString();

    string faceFile = string("boneyard/ImageMagick_logo.svg.png");
    desc faceD(95, 50, 50, faceFile);

    string headerFile = string("boneyard/ImageMagickUsage.png");
    desc headerD(4, 50, 10, headerFile);
    string footerFile = string("boneyard/ImageMagickURL.png");
    desc footerD(3, 50, 90, footerFile);

    file << startString;
    file << drawImage(faceD, "");
    file << headerD.draw();
    file << footerD.draw();
    file << "\t+dither -colors 256 \\" << endl;
    file << "\tcards/" << outputDirectory << "/" << fileName << ".png" << endl;
    file << endl;

    return 1;
}

static int drawDefaultJoker(ofstream & file, const string & fileName)
{
    string startString = genStartString();
    string currentCardColour = cardColour;
    cardColour = "white";

    string faceFile = string("boneyard/ImageMagick_logo.svg.png");
    desc faceD(95, 50, 50, faceFile);

    startString = genStartString();
    faceFile = string("boneyard/Back.png");
    faceD.setFileName(faceFile);
    file << startString;
    file << drawImage(faceD, "");
    file << "\t+dither -colors 256 \\" << endl;
    file << "\tcards/" << outputDirectory << "/" << fileName << ".png" << endl;
    file << endl;

    cardColour = currentCardColour;

    return 1;
}


static int drawJoker(int fails, ofstream & file, int suit)
{
    file << "# Draw the " << suitNames[suit] << " " << cardNames[0] << " as file " << suits[suit] << cardNames[0] << ".png" << endl;

    string fileName = string(suits[suit]) + cardNames[0];
    string faceFile = string("faces/") + face + "/" + fileName + ".png";
    desc faceD(95, 50, 50, faceFile);
    if (faceD.isFileFound())
    {
        string startString = genStartString();

        file << startString;
        file << drawImage(faceD, "");
        file << "\t+dither -colors 256 \\" << endl;
        file << "\tcards/" << outputDirectory << "/" << fileName << ".png" << endl;
        file << endl;

        return 0;
    }

    // Got here so, Joker image file not found, so generate card.
    switch (fails)
    {
    case 0:
    case 2:
        drawImageMagickJoker(file, fileName);
        break;

    default:
        drawDefaultJoker(file, fileName);
        break;
    }

    return 1;
}


///////////////////////////////////////////////////////////////////////////////
//
//- The bulk of the script generation work.
//
int generateScript(int argc, char *argv[])
{
    ofstream file(scriptFilename.c_str());

//- Open the script file for writing.
    if (!file)
    {
        cerr << "Can't open output file " << scriptFilename << " - aborting!" << endl;

        return 1;
    }

//- Generate the initial preamble of the script.
    file << "#!/bin/sh" << endl;
    file << endl;
    file << "# This file was generated as \"" << scriptFilename << "\" using the following command:" << endl;
    file << "#" << endl;
    file << "#  ";
    for (int i = 0; i < argc; ++i)
    {
        file << argv[i] << ' ';
    }
    file << endl;
    file << "#" << endl;
    file << endl;
    file << "# Make the directories."  << endl;
    file << "mkdir -p cards"  << endl;
    file << "mkdir -p cards/" << outputDirectory << endl;

    file << endl;
    file << "# Generate the refresh script."  << endl;
    file << "cat <<EOM >cards/" << outputDirectory  << "/" << refreshFilename << endl;
    file << "#!/bin/sh" << endl;
    file << endl;
    file << "# This file was generated using the following " << argv[0] << " command." << endl;
    file << "#" << endl;
    file << "cd ../../" << endl;
    for (int i = 0; i < argc; ++i)
    {
        file << argv[i] << ' ';
    }
    file << endl;
    file << "./" << scriptFilename << endl;
    file << "EOM" << endl;
    file << endl;


//- Initial blank card string used as a template for each card.
    string startString = genStartString();

//- Generate all the playing cards.
    for (int s = 0; s < ELEMENTS(suits); ++s)
    {
        suit    = string(suits[s]);
        alt     = string(alts[s]);

        string pipFile = string("pips/") + pip + "/" + suit + "S.png";      // Try small pip file first.
        desc pipD(CornerPip, pipFile);
        if (!pipD.isFileFound())
        {
            // Small pip file not found, so use standard pip file.
            pipFile = string("pips/") + pip + "/" + suit + ".png";
            pipD.setFileName(pipFile);
        }

        for (int c = 1; c < ELEMENTS(cards); ++c)
        {
            card = string(cards[c]);

            string indexFile = string("indices/") + index + "/" + suit + card + ".png";
            desc indexD(Index, indexFile);
            if (!indexD.isFileFound())
            {
                // Index for suit file not found, so use alternate index file.
                indexFile = string("indices/") + index + "/" + alt + card + ".png";
                indexD.setFileName(indexFile);
            }

            string faceFile = string("faces/") + face + "/" + suit + card + ".png";
            desc faceD(imageHeight, imageX, imageY, faceFile);

            string drawFace;

//- If the face directory does not have the needed image file, use standard pips.
            pipFile = string("pips/") + pip + "/" + suit + ".png";      // Use standard pip file.
            if (faceD.useStandardPips())
            {
                drawFace = drawStandardPips(1, c, pipFile);
            }
            else
            {
                drawFace = drawImage(faceD, c > 10 ? pipFile : "");
            }


//- Write to output file.
            file << "# Draw the " << cardNames[c] << " of " << suitNames[s] << " as file " << suit << card << ".png." << endl;
            file << startString;

            if ((faceD.useStandardPips()) || (faceD.isFileFound() && faceD.isLandscape()))
            {
                file << drawFace;			// Draw either half of the pips or one of the landscape images.
            }
            file << indexD.draw();			// Draw index.
            file << pipD.draw();			// Draw corner pip.

            file << "\t-rotate 180 \\" << endl;

            if (faceD.useStandardPips())
            {
                drawFace = drawStandardPips(2, c, pipFile);
            }
            file << drawFace;				// Draw either the rest of the pips or the needed image.
            file << indexD.draw();			// Draw index.
            file << pipD.draw();			// Draw corner pip.

            file << "\t+dither -colors 256 \\" << endl;
            file << "\tcards/" << outputDirectory << "/" << suit << card << ".png" << endl;

            file << endl;
        }
    }


//- Add the Jokers using narrower boarders.
    boarderX = 7;
    boarderY = 5;
    recalculate();

    int fails = 0;
    for (int s = 0; s < ELEMENTS(suits); ++s)
    {
        fails += drawJoker(fails, file, s);
    }

    file << "echo Output created in cards/" << outputDirectory << "/" << endl;
    file << endl;

    return 0;
}


