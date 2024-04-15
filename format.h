#ifndef FORMAT_H
#define FORMAT_H
#include <string>
using namespace std;

extern const string textClear;
extern const string textReset;

extern const string textBold;
extern const string textItalic;
extern const string textUnderline;
extern const string textStrikethrough;

extern const string textDefault;
extern const string textBlack;
extern const string textRed;
extern const string textGreen;
extern const string textYellow;
extern const string textBlue;
extern const string textMagenta;
extern const string textCyan;
extern const string textWhite;

extern const string bgDefault;
extern const string bgBlack;
extern const string bgRed;
extern const string bgGreen;
extern const string bgYellow;
extern const string bgBlue;
extern const string bgMagenta;
extern const string bgCyan;
extern const string bgWhite;

extern void sleep(int dur); // unit is ms
extern string setCursorPosition(int offsetY, int offsetX); // same as below
extern void fetchConsoleDimensions(int &row, int &col); // number of characters each row and column can fit, not the number of pixels

#endif