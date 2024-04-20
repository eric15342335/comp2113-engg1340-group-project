/**
 * @file format.h
 * @author Prismatiscence
 * @brief Terminal text formatting header.
 */
#ifndef FORMAT_H
#define FORMAT_H
#include <string>

extern const std::string textClear;
extern const std::string textReset;

extern const std::string textBold;
extern const std::string textItalic;
extern const std::string textUnderline;
extern const std::string textStrikethrough;

extern const std::string textDefault;
extern const std::string textBlack;
extern const std::string textRed;
extern const std::string textGreen;
extern const std::string textYellow;
extern const std::string textBlue;
extern const std::string textMagenta;
extern const std::string textCyan;
extern const std::string textWhite;

extern const std::string bgDefault;
extern const std::string bgBlack;
extern const std::string bgRed;
extern const std::string bgGreen;
extern const std::string bgYellow;
extern const std::string bgBlue;
extern const std::string bgMagenta;
extern const std::string bgCyan;
extern const std::string bgWhite;

/** @brief Mimic Python time.sleep() */
class time {
    public:
        /** @param dur unit is ms. */
        static void sleep(int dur);
};
/** Parameters are the same as `fetchConsoleDimensions();` */
extern std::string setCursorPosition(int offsetY, int offsetX);

/** number of characters each row and column can fit, not the number of pixels. */
extern void fetchConsoleDimensions(int & row, int & col);

#endif