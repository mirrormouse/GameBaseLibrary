#include "Line.h"
#include <cmath>

Line::Line(GameMain* gameMain, const Point& startPoint, const Point& endPoint, const float color[3], float thickness)
    : Shape(gameMain, {startPoint, endPoint}, color), thickness(thickness)
{
    UpdateLineVertices();
}

void Line::SetStartPoint(const Point& point)
{
    pixelVertices[0] = point;
    UpdateLineVertices();
}

void Line::SetEndPoint(const Point& point)
{
    pixelVertices[1] = point;
    UpdateLineVertices();
}

void Line::SetThickness(float thickness)
{
    this->thickness = thickness;
    UpdateLineVertices();
}

void Line::UpdateLineVertices()//�n�_�ƏI�_�����ƂɁA�ג�����`�Ƃ��ĉ���
{
    Point start = pixelVertices[0];
    Point end = pixelVertices[1];

    //���̕���
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    //���̒���
    float length = std::sqrt(dx * dx + dy * dy);

    //start,end�͒Z�ӂ̒��_�Ȃ��߁A��`�̒��_�܂ł̕���thickness�̔���
    float nx;
    float ny;

    if (length < 0.0001f) {//�������ɒ[�ɒZ���ꍇ�A�`�悵�Ȃ�
        nx = 0;
        ny = 0;
    }
    else {
        nx = -dy / length * (thickness / 2.0f);
        ny = dx / length * (thickness / 2.0f);
    }




    // 4�̒��_��ݒ�
    std::vector<Point> newVertices = {
        Point{start.x + nx, start.y + ny},  // ����
        Point{end.x + nx, end.y + ny},      // �E��
        Point{end.x - nx, end.y - ny},      // �E��
        Point{start.x - nx, start.y - ny}   // ����
    };

    pixelVertices = newVertices;

    
}
