#include "Text.h"
#include "GameMain.h"
#include "CoordinateConverter.h"
#include <GLFW/glfw3.h>

Text::Text(GameMain* gameMain, const std::string& text, float x, float y, FT_Face face, float interval)
    : GameObject(0), gameMain(gameMain) {

    textDisplay = std::make_unique<TextDisplay>(text, x, y, face);
    SetColor(1.0f, 1.0f, 1.0f);  // �f�t�H���g�̐F�𔒂ɐݒ�

    int windowWidth, windowHeight;
    glfwGetWindowSize(gameMain->GetWindow(), &windowWidth, &windowHeight);

    textDisplay->change_interval(interval * windowWidth, interval * windowHeight);
    textContent = text;
}

void Text::Start() {
    // ���������K�v�ȏꍇ�͂�����p��
}

void Text::Update() {
    // �X�V���K�v�ȏꍇ�͂�����p��
}

void Text::FixedUpdate() {
    // �Œ�X�V���K�v�ȏꍇ�͂�����p��
}

void Text::Draw() {

    int windowWidth, windowHeight;
    glfwGetWindowSize(gameMain->GetWindow(), &windowWidth, &windowHeight);

    // �e�L�X�g�̕`��O�Ƀu�����f�B���O��ݒ�
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textDisplay->display(windowWidth, windowHeight);
    // �u�����f�B���O�𖳌����i�I�v�V�����j
    glDisable(GL_BLEND);
}

void Text::SetText(const std::string& text) {


    textDisplay->change_string(text);
    textContent = text;
}

void Text::SetPosition(float x, float y) {

    textDisplay->change_place(x, y);
}

void Text::SetColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
    textDisplay->set_color(r, g, b);
}

void Text::SetInterval(float x, float y) {
    textDisplay->change_interval(x, y);
}

std::string Text::GetText() {
    return textContent;
}