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
// desc.h: Interface for the info and desc classes.
//
///////////////////////////////////////////////////////////////////////////////

#if !defined _DESC_H_INCLUDED_
#define _DESC_H_INCLUDED_

#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
//- info class used to encapsulate position and size of an image.
//
class info
{
private:
    float H;
    float X;
    float Y;
    bool ChangedH;
    bool ChangedX;
    bool ChangedY;

public:
    info(float h, float x, float y) : H(h), X(x), Y(y), ChangedH(false), ChangedX(false), ChangedY(false) {}
    info(const info & a) : H(a.H), X(a.X), Y(a.Y), ChangedH(false), ChangedX(false), ChangedY(false) {}

    float getH(void) { return H; }
    float getX(void) { return X; }
    float getY(void) { return Y; }

    bool isChangedH(void) { return ChangedH; }
    bool isChangedX(void) { return ChangedX; }
    bool isChangedY(void) { return ChangedY; }

    void setH(float v) { ChangedH = true; H = v; }
    void setX(float v) { ChangedX = true; X = v; }
    void setY(float v) { ChangedY = true; Y = v; }

    friend ostream & operator<<(ostream &os, const info &A) { A.print(os); return os; }

protected:
    void print(ostream &os=cout) const;

};

///////////////////////////////////////////////////////////////////////////////
//
//- desc class used to capture image file info and image info on the canvas.
//
class desc
{
private:
    int getImageSize(void);
    int genDrawString(void);
    string DrawString;
    bool FileFound;
    int WidthPX;
    int HeightPX;
    float AspectRatio;
    int OriginX;
    int OriginY;

    float CentreX;
    float CentreY;
    float Height;
    float Width;

    string FileName;

public:

    desc(float H, float X, float Y, const string & FN);
    desc(info & I, const string & FN);
    void repos(float X, float Y);
    void setFileName(const string & FN);
    const string & getFileName(void) const { return FileName; }

    float getCentreX(void) const { return CentreX; }
    float getCentreY(void) const { return CentreY; }
    float getHeight(void) const { return Height; }
    float getWidth(void) const { return Width; }

    int getHeightPX(void) const { return HeightPX; }
    int getWidthPX(void) const { return WidthPX; }
    float getAspectRatio(void) const { return AspectRatio; }
    int getOriginX(void) const { return OriginX; }
    int getOriginY(void) const { return OriginY; }
    const string & draw(void) const { return DrawString; }

    float centre2OriginX(float centre) const { return centre - (Width/2); }
    float centre2OriginY(float centre) const { return centre - (Height/2); }

    bool isLandscape(void) const { return HeightPX < WidthPX; }
    bool isFileFound(void) const { return FileFound; }
    bool useStandardPips(void) const { return !FileFound; }

};

#endif //!defined _DESC_H_INCLUDED_

