#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include "TextDisplay.h"
#include "Text.h"
#include <functional>
#include <memory>
#include <array>

class GameMain;

class GAMEBASELIB_API Button : public GameObject {
public:
    Button(GameMain* gameMain, float x, float y, float width, float height, const std::string& text, FT_Face face);
    ~Button() override = default;

    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;

    void SetOnClickHandler(std::function<void()> handler);
    void SetText(const std::string& text);

    void SetNormalColor(float r, float g, float b);
    void SetHoverColor(float r, float g, float b);
    void SetPressedColor(float r, float g, float b);
    void SetTextColor(float r, float g, float b);
    void SetTextCenterByTextSize(float w, float h);
    void SetTextPosition(float textX, float textY);

protected:
    GameMain* gameMain;
    float x, y, width, height;  // これらはピクセル座標
    std::shared_ptr<Text> textDisplay;
    std::function<void()> onClickHandler;
    bool isHovered;
    bool isPressed;

    std::array<float, 3> normalColor;
    std::array<float, 3> hoverColor;
    std::array<float, 3> pressedColor;
    std::array<float, 3> textColor;
    float textwidth;
    float textheight;

    virtual void UpdateTextPosition();
    virtual bool IsPointInside(float px, float py) const;
    virtual void RenderBackground();
    virtual void RenderText();
};

#endif // BUTTON_H