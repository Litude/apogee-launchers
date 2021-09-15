#ifndef APGTEXT_H
#define APGTEXT_H

#define TEXT_LAYOUT_TRADITIONAL 0
#define TEXT_LAYOUT_MODERN 1

void showTextFile(const char* path, const char* title);
void showTextFiles(const char* title, const char* separator, ...);
void showTextBuffer(char* buffer, int bufferSize, const char* title);
void setStyle(int newTextStyle, int newLegendStyle, int layout);
void storeTextStyle();
void restoreTextStyle();

#endif
