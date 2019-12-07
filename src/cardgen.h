#if !defined _CARDGEN_H_INCLUDED_
#define _CARDGEN_H_INCLUDED_

#include <string>
#include "desc.h"

using namespace std;

#if !defined ELEMENTS
#define ELEMENTS(A) (sizeof(A)/sizeof(A[0]))
#endif

#if !defined ROUND
#define ROUND(v) (int)((v) + 0.5)
#endif

// User defined.
extern int cardWidth;
extern int cardHeight;
extern string cardColour;

extern info Index;
extern info CornerPip;
extern info StandardPip;
extern info ImagePip;

extern string index;
extern string pip;
extern string face;

extern string scriptFilename;
extern string outputDirectory;
extern string refreshFilename;

extern bool keepAspectRatio;
extern float aspectRatio;

extern float cornerRadius;
extern int radius;
extern int strokeWidth;
extern int borderOffset;
extern int outlineWidth;
extern int outlineHeight;

extern int imageOffset;
extern int imageOffsetWidth;
extern int imageOffsetHeight;

extern float boarderX;
extern float boarderY;
extern float imageWidth;
extern float imageHeight;
extern int widthPX;
extern int heightPX;
extern int offsetX;
extern int offsetY;
extern float imageX;
extern float imageY;


extern int recalculate(void);
extern int init(int argc, char *argv[]);
extern int dumpCode(int argc, char *argv[]);

#endif //!defined _CARDGEN_H_INCLUDED_
