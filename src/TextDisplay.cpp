#include "TextDisplay.h"
#include <codecvt>
#include <locale>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>


static void normalize(float windowWidth, float windowHeight, float pixelX, float pixelY, float& normalizedX, float& normalizedY) {
    normalizedX = (pixelX / windowWidth) * 2 - 1;
    normalizedY = 1 - (pixelY / windowHeight) * 2;
}



// UTF-8 std::string を UTF-32 unsigned int vector に変換する関数
std::vector<unsigned int> convertUtf8ToUtf32(const std::string& utf8Str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32 = converter.from_bytes(utf8Str);
    return std::vector<unsigned int>(utf32.begin(), utf32.end());
}

TextDisplay::TextDisplay(const std::string& initialText, float initialX, float initialY, FT_Face ftFace)
    : x(initialX), y(initialY), face(ftFace) {
    change_string(initialText);
    set_color(1.0f, 1.0f, 1.0f);
}

void TextDisplay::change_string(const std::string& newText) {
    text = newText;
    utf32Text.clear();

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32 = converter.from_bytes(text);

    for (char32_t c : utf32) {
        unsigned int c_int = static_cast<unsigned int>(c);
        if (c_int == static_cast<unsigned int>('\n')) {
            utf32Text.push_back(static_cast<unsigned int>('\n'));
        }
        else {
            utf32Text.push_back(c_int);
        }
    }

    num_chars = utf32Text.size();
}

void TextDisplay::change_place(float newX, float newY) {
    x = newX;
    y = newY;
}

void TextDisplay::change_interval(float newIntervalX, float newIntervalY) {
    intervalX = newIntervalX;
    intervalY = newIntervalY;
}

void TextDisplay::display(int windowWidth, int windowHeight) {
    glColor4f(color[0], color[1], color[2], color[3]);


    float normalizedX, normalizedY;
    normalize(windowWidth, windowHeight, x, y, normalizedX, normalizedY);

    float localX = normalizedX;
    float localY = normalizedY;
    float lineHeight = (face->size->metrics.height >> 6) * (intervalY / (float)windowHeight);



    for (size_t i = 0; i < num_chars; ++i) {
        if (utf32Text[i] == static_cast<unsigned int>('\n')) {
            localX = normalizedX;  // X座標をリセット
            localY -= lineHeight;  // Y座標を1行分下げる
            continue;
        }

        if (FT_Load_Char(face, utf32Text[i], FT_LOAD_RENDER)) {
            fprintf(stderr, "Failed to load character\n");
            continue;
        }

        // 透過度含めて４成分のためその分のバッファ
        std::vector<unsigned char> colored_buffer(face->glyph->bitmap.rows * face->glyph->bitmap.width * 4);
        for (unsigned int row = 0; row < face->glyph->bitmap.rows; ++row) {
            for (unsigned int col = 0; col < face->glyph->bitmap.width; ++col) {
                unsigned char value = face->glyph->bitmap.buffer[(face->glyph->bitmap.rows - 1 - row) * face->glyph->bitmap.width + col];
                unsigned int idx = (row * face->glyph->bitmap.width + col) * 4;
                colored_buffer[idx] = static_cast<unsigned char>(color[0] * 255);
                colored_buffer[idx + 1] = static_cast<unsigned char>(color[1] * 255);
                colored_buffer[idx + 2] = static_cast<unsigned char>(color[2] * 255);
                colored_buffer[idx + 3] = value;  // アルファ値として使用
            }
        }

        glRasterPos2f(localX, localY); // Update position for each character

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glDrawPixels(
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            colored_buffer.data()
        );

        // Advance the localX offset for the next character
        localX += (face->glyph->advance.x >> 6) * (intervalX / (float)windowWidth); // Adjust scaling factor as needed
    }
}

void TextDisplay::set_color(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = 1.0f;
}

void TextDisplay::set_color(float r, float g, float b, float a) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}