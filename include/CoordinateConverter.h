#ifndef COORDINATE_CONVERTER_H
#define COORDINATE_CONVERTER_H

#include <GLFW/glfw3.h>
#include <iostream>
class CoordinateConverter {
public:
    static void PixelToNormalized(GLFWwindow* window, float pixelX, float pixelY, float& normalizedX, float& normalizedY) {
        int windowWidth, windowHeight;

        glfwGetWindowSize(window, &windowWidth, &windowHeight);


        normalizedX = (pixelX / windowWidth) * 2 - 1;
        normalizedY = 1 - (pixelY / windowHeight) * 2;
    }

    static void NormalizedToPixel(GLFWwindow* window, float normalizedX, float normalizedY, float& pixelX, float& pixelY) {
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        pixelX = (normalizedX + 1) / 2 * windowWidth;
        pixelY = (1 - normalizedY) / 2 * windowHeight;
    }
};

#endif // COORDINATE_CONVERTER_H