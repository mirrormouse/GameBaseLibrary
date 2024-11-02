#include "Button.h"
#include "Rectangle.h"
#include "GameMain.h"
#include "CoordinateConverter.h"
#include <GLFW/glfw3.h>
#include <iostream>

Button::Button(GameMain* gameMain, float x, float y, float width, float height, const std::string& text, FT_Face face)
    : GameObject(0), gameMain(gameMain), x(x), y(y), width(width), height(height), isHovered(false), isPressed(false) {
    textDisplay = std::make_shared<Text>(gameMain, text, 0, 0, gameMain->getFace()); // 位置は後で更新
    // デフォルトの色を設定
    normalColor = { 0.7f, 0.7f, 1.0f };
    hoverColor = { 0.8f, 0.8f, 1.0f };
    pressedColor = { 0.5f, 0.5f, 1.0f };
    textColor = { 0.0f, 0.0f, 1.0f };
    textwidth = 8.0f;
    textheight = 48.0f;

    UpdateTextPosition();
}

void Button::Start() {
    // 初期化が必要な場合はこれを継承
}

void Button::Update() {
    double mouseX, mouseY;
    gameMain->GetInputManager().GetMousePosition(mouseX, mouseY);

    isHovered = IsPointInside(mouseX, mouseY);

    
    if (isHovered && gameMain->GetInputManager().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        if (!isPressed) {
            isPressed = true;
            if (onClickHandler) {
                onClickHandler();
            }
        }
    }
    else {
        isPressed = false;
    }
}

void Button::FixedUpdate() {
    // 固定更新が必要な場合はこれを継承
}

void Button::Draw() {

    RenderBackground();
    RenderText();
}

void Button::SetOnClickHandler(std::function<void()> handler) {
    onClickHandler = std::move(handler);
}

void Button::SetText(const std::string& text) {
    textDisplay->SetText(text);
    UpdateTextPosition();
}

void Button::SetTextPosition(float textX, float textY) {
    textDisplay->SetPosition(textX, textY);
}
void Button::SetTextCenterByTextSize(float w, float h) {
    textwidth = w; textheight = h;
    UpdateTextPosition();
}

void Button::UpdateTextPosition() {
    float textX = x + (width - textDisplay->GetText().length() * textwidth) / 2;
    float textY = y + (height - textheight) / 2;
    textDisplay->SetPosition(textX, textY);

}

bool Button::IsPointInside(float px, float py) const {

    return px >= x && px <= x + width && py >= y && py <= y + height;
}

void Button::RenderBackground() {

    const auto& color = isPressed ? pressedColor : (isHovered ? hoverColor : normalColor);
    float c[3] = {color[0],color[1],color[2]};
    Point p{ x, y };
    Rectangle blockRect(gameMain, p, width, height, c);
    blockRect.Draw();
}

void Button::RenderText() {
    textDisplay->Draw();
}

void Button::SetNormalColor(float r, float g, float b) { normalColor = { r, g, b }; }
void Button::SetHoverColor(float r, float g, float b) { hoverColor = { r, g, b }; }
void Button::SetPressedColor(float r, float g, float b) { pressedColor = { r, g, b }; }
void Button::SetTextColor(float r, float g, float b) { textColor = { r, g, b }; }
