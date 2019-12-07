#if !defined _DESC_H_
#define _DESC_H_

#include <string>

using namespace std;

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

};

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

    desc(float H, float X, float Y, string FN);
    desc(info & I, string FN);
    void repos(float X, float Y);
    void setFileName(string FN);
    string getFileName(void) { return FileName; }

    float getCentreX(void) { return CentreX; }
    float getCentreY(void) { return CentreY; }
	float getHeight(void) { return Height; }
	float getWidth(void) { return Width; }

    int getHeightPX(void) { return HeightPX; }
    int getWidthPX(void) { return WidthPX; }
    float getAspectRatio(void) { return AspectRatio; }
	int getOriginX(void) { return OriginX; }
	int getOriginY(void) { return OriginY; }
	string draw(void) { return DrawString; }

    float centre2OriginX(float centre) { return centre - (Width/2); }
	float centre2OriginY(float centre) { return centre - (Height/2); }

	bool isLandscape(void) { return HeightPX < WidthPX; }
    bool isFileFound(void) { return FileFound; }
    bool useStandardPips(void) { return !FileFound; }

};

#endif //!defined _DESC_H_
