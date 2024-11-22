#pragma once

#include "main.hpp"
#include "3Stars/threeStars.hpp"
#include <complex>

void mosaique(sil::Image &image);

void mosaiqueMirror(sil::Image &image);

void fractalMandelbrot(sil::Image &image);

std::vector<std::vector<float>> generateBayerMatrix(int bayer_n);

void dithering(sil::Image &image);