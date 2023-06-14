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


#ifndef CAPTURER_H
#define CAPTURER_H
#endif // CAPTURER_H
#include "Capturer.h"
#include <bits/stdc++.h>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define ll long long
const ll INF = 10e17;
const int window_width = 800;
const int window_height = 600;
const char* video_file_name = "output.avi";
const int frame_rate = 30;
const int num_frames = 10;
using namespace std;
void capturer(const char* video_file_name, int window_width, int window_height, int frame_rate, int num_frames)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGL Video Capture", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    ofstream video_file(video_file_name, ios::binary);
    if (!video_file.good()) {
        cerr << "Error opening video file" << '\n';
        return;
    }
    char aviHeader[] = { 'R', 'I', 'F', 'F', 0x00, 0x00, 0x00, 0x00, 'A', 'V', 'I', ' ', 'L', 'I', 'S', 'T', 0x00, 0x00, 0x00, 0x00, 'h', 'd', 'r', 'l', 'a', 'v', 'i', 'h', 0x00, 0x00, 0x00, 0x48, 'L', 'E', 'D', 'I', 'X', '2', '5', '6', '0', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 's', 't', 'r', 'l', 's', 't', 'r', 'h', 0x00, 0x00, 0x00, 0x38, 'v', 'i', 'd', 's', 'm', 's', 'w', 's', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 's', 't', 'r', 'f', 0x00, 0x00, 0x00, 0x28, 'L', 'E', 'D', 'I', 'X', '2', '5', '6', '1', 0x00, 0x00, 0x00, (char)screen_width, (char)(screen_width >> 8), (char)(screen_width >> 16), (char)(screen_width >> 24), (char)screen_height, (char)(screen_height >> 8), (char)(screen_height >> 16), (char)(screen_height >> 24), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (char)frame_rate, 0x00, (char)num_frames, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    video_file.write(aviHeader, sizeof(aviHeader));
    int aviDataSizePos = (int)video_file.tellp();
    for (int i = 0; i < num_frames; i++) {
        vector<unsigned char> bitmapData(screen_width * screen_height * 3);
        glReadPixels(0, 0, screen_width, screen_height, GL_RGB, GL_UNSIGNED_BYTE, &bitmapData[0]);
        char frameHeader[] = { '0', '0', 'd', 'c', 0x00, 0x00, 0x00, 0x00, (char)screen_width, (char)(screen_width >> 8), (char)(screen_width >> 16), (char)(screen_width >> 24), (char)screen_height, (char)(screen_height >> 8), (char)(screen_height >> 16), (char)(screen_height >> 24), 0x01, 0x00, 0x18, 0x00 };
        video_file.write(frameHeader, sizeof(frameHeader));
        video_file.write((char*)&bitmapData[0], bitmapData.size());
    }
    int aviDataSize = (int)video_file.tellp() - aviDataSizePos - 4;
    video_file.seekp(aviDataSizePos, ios::beg);
    video_file.write((char*)&aviDataSize, 4);
    char aviFileSize[] = { 'R', 'I', 'F', 'F', 0x00, 0x00, 0x00, 0x00, 'A', 'V', 'I', ' ', 0x00, 0x00, 0x00, 0x00, 'L', 'I', 'S', 'T', 0x00, 0x00, 0x00, 0x00, 'm', 'o', 'v', 'i' };
    int aviFileSizePos = 0;
    video_file.write(aviFileSize, sizeof(aviFileSize));
    aviFileSizePos = (int)video_file.tellp();
    video_file.write((char*)&aviDataSize, 4);
    video_file.close();
    glfwDestroyWindow(window);
    glfwTerminate();
}
