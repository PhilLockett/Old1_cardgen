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
    float CentreX;
    float CentreY;
    float Height;

public:
    info(float H, float X, float Y) : Height(H), CentreX(X), CentreY(Y) {}

    float getX(void) { return CentreX; }
    float getY(void) { return CentreY; }
    float getHeight(void) { return Height; }

    float setX(float v) { CentreX = v; }
    float setY(float v) { CentreY = v; }
    float setHeight(float v) { Height = v; }

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

