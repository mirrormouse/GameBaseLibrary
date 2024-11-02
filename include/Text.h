#ifndef TEXT_H
#define TEXT_H

#include "GameObject.h"
#include "TextDisplay.h"
#include <memory>
#include <string>

class GameMain;

class GAMEBASELIB_API Text : public GameObject {
public:
    Text(GameMain* gameMain, const std::string& text, float x, float y, FT_Face face, float interval = 0.0022f);
    ~Text() override = default;

    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;

    void SetText(const std::string& text);
    void SetPosition(float x, float y);
    void SetColor(float r, float g, float b);
    void SetInterval(float intervalX, float intervalY);
    std::string GetText();

private:
    std::unique_ptr<TextDisplay> textDisplay;
    GameMain* gameMain;
    float color[3];
    std::string textContent;
};

#endif // TEXT_H