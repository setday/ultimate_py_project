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
#include <windows.h>
#include <opencv2/opencv.hpp>
void Capturer(int num_frames);
#endif // CAPTURER_H
#include "Capturer.h"

void Capturer(int num_frames) {
  HDC hdcScreen = GetDC(NULL);
  int screen_width = GetSystemMetrics(SM_CXSCREEN);
  int screen_height = GetSystemMetrics(SM_CYSCREEN);

  cv::VideoWriter writer("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(screen_width, screen_height));

  if (!writer.isOpened()) {
    std::cerr << "Error opening video file" << std::endl;
    return;
  }

  for (int i = 0; i < num_frames; i++) {
    cv::Mat frame(screen_height, screen_width, CV_8UC4);
    if (!BitBlt(frame.data, 0, 0, screen_width, screen_height, hdcScreen, 0, 0, SRCCOPY)) {
      std::cerr << "Error copying screen content to Mat" << std::endl;
      writer.release();
      ReleaseDC(NULL, hdcScreen);
      return;
    }
    cv::cvtColor(frame, frame, cv::COLOR_BGRA2RGB);
    writer.write(frame);
  }
  writer.release();
  ReleaseDC(NULL, hdcScreen);
}
