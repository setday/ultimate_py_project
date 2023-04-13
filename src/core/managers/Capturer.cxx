//
// Created by Vasya on 21.03.2023.
//
/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburs).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Capturer.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Capturer.h"
using namespace std;
int main (){
//// создание буфера кадра
//glGenFramebuffers(1, &framebuffer);
//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//// создание текстуры для буфера кадра
//glGenTextures(1, &texture);
//glBindTexture(GL_TEXTURE_2D, texture);
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
// получение дескриптора контекста устройства
HDC hdcScreen = GetDC(NULL);
int width,  height;

glfwGetFramebufferSize(window, &width, &height);
// создание битмапа для сохранения кадра
HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
HDC hdcBitmap = CreateCompatibleDC(hdcScreen);
SelectObject(hdcBitmap, hBitmap);

// копирование содержимого экрана в битмап
BitBlt(hdcBitmap, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

// получение указателя на буфер памяти с содержимым битмапа
BITMAPINFO bmpInfo = {0};
bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
bmpInfo.bmiHeader.biWidth = width;
bmpInfo.bmiHeader.biHeight = -height;
bmpInfo.bmiHeader.biPlanes = 1;
bmpInfo.bmiHeader.biBitCount = 32;
bmpInfo.bmiHeader.biCompression = BI_RGB;

unsigned char* buffer = new unsigned char[width * height * 4];
GetDIBits(hdcBitmap, hBitmap, 0, height, buffer, &bmpInfo, DIB_RGB_COLORS);

// сохранение буфера памяти в файл и освобождение ресурсов
/*saveImageToFile(buffer, width, height, "image.png");
DeleteDC(hdcBitmap);
DeleteObject(hBitmap);
ReleaseDC(NULL, hdcScreen);
delete[] buffer;
return  0;
 */
}