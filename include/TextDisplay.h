#pragma once
#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H


#ifdef GAMEBASELIB_EXPORTS
#define GAMEBASELIB_API __declspec(dllexport)
#else
#define GAMEBASELIB_API __declspec(dllimport)
#endif

class GAMEBASELIB_API TextDisplay {
public:
    std::string text;
    float x, y;
    float intervalX, intervalY;
    std::vector<unsigned int> utf32Text;
    FT_Face face;
    size_t num_chars;
    float color[4];

    TextDisplay(const std::string& initialText, float initialX, float initialY, FT_Face ftFace);
    void change_string(const std::string& newText);
    void change_place(float newX, float newY);
    void change_interval(float newIntervalX, float newIntervalY);
    void set_color(float r, float g, float b);
    void set_color(float r, float g, float b, float a);
    void display(int windowWidth, int windowHeight);
};