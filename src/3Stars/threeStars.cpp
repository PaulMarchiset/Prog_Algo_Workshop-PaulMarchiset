#include "threeStars.hpp"

void circus(sil::Image &image)
{
    int rayon{100};
    int centreX{image.width() / 2};
    int centreY{image.height() / 2};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            double calculus{pow(x - centreX, 2) + pow(y - centreY, 2)};
            if (calculus <= pow(rayon, 2))
            {
                image.pixel(x, y) = glm::vec3{1};
            };
        }
    }
}

void disque(sil::Image &image)
{
    int rayon{100};
    int centreX{image.width() / 2};
    int centreY{image.height() / 2};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            double calculus{pow(x - centreX, 2) + pow(y - centreY, 2)};
            if (calculus < pow(rayon, 2) && calculus > pow(rayon - 10, 2))
            {
                image.pixel(x, y) = glm::vec3{1};
            };
        }
    }
}

void animationCircle(sil::Image &image)
{
    int rayon{100};
    int frames{24};

    for (int i{0}; i <= frames; i++)
    {
        sil::Image new_image{image.width(), image.height()};

        int centreX{(image.width() / frames) * i};

        int centreY{image.height() / 2};
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                double calculus{pow(x - centreX, 2) + pow(y - centreY, 2)};
                if (calculus < pow(rayon, 2))
                {
                    new_image.pixel(x, y) = glm::vec3{1};
                    image.pixel(x, y) = glm::vec3{1};
                };
            }
        }
        //     if (i == 0) {
        //         // generate text "saucisse" on the first frame with opencv
        //         cv::Mat mat(image.height(), image.width(), CV_8UC3);

        //         for (int x{0}; x < image.width(); x++)
        //         {
        //             for (int y{0}; y < image.height(); y++)
        //             {
        //                 mat.at<cv::Vec3b>(y, x)[0] = image.pixel(x, y).b * 255;
        //                 mat.at<cv::Vec3b>(y, x)[1] = image.pixel(x, y).g * 255;
        //                 mat.at<cv::Vec3b>(y, x)[2] = image.pixel(x, y).r * 255;
        //             }
        //         }
        //         cv::putText(mat, "saucisse", cv::Point(10, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        //         cv::imwrite("output/animation/animation_cercle_" + std::to_string(i) + ".jpg", mat);

        // }

        new_image.save("output/animation/animation_cercle_" + std::to_string(i) + ".jpg");
    }
}

void rosace(sil::Image &image)
{

    int rayon{100};
    int centreX{image.width() / 2};
    int centreY{image.height() / 2};
    float pi{3.14159f};

    int circusNumber{0};
    std::cout << "Combien de cercles voulez-vous ?" << std::endl;
    std::cin >> circusNumber;

    for (int i{0}; i < circusNumber; i++)
    {
        int randomColor{rand() % 3};
        int newCentreX{centreX + static_cast<int>(rayon * cos(i * pi / (circusNumber / 2)))};
        int newCentreY{centreY + static_cast<int>(rayon * sin(i * pi / (circusNumber / 2)))};

        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                double calculus{pow(x - newCentreX, 2) + pow(y - newCentreY, 2)};
                if (calculus < pow(rayon, 2) && calculus > pow(rayon - 5, 2))
                {
                    switch (randomColor)
                    {
                    case 0:
                        image.pixel(x, y).r = 1;
                        break;
                    case 1:
                        image.pixel(x, y).g = 1;
                        break;
                    case 2:
                        image.pixel(x, y).b = 1;
                        break;
                    default:
                        image.pixel(x, y) = glm::vec3{1};
                        break;
                    }
                };
            }
        }
    }
}

void glitch(sil::Image &image)
{
    int numberGlitch{random_int(10, 250)};

    for (int i = 0; i < numberGlitch; i++)
    {
        int rectangleWidth{rand() % 20};
        int rectangleHeight{rand() % 20};

        if (rectangleWidth > image.width() || rectangleHeight > image.height())
            continue;

        int positionRectangleX1{rand() % (image.width() - rectangleWidth)};
        int positionRectangleY1{rand() % (image.height() - rectangleHeight)};

        int positionRectangleX2{rand() % (image.width() - rectangleWidth)};
        int positionRectangleY2{rand() % (image.height() - rectangleHeight)};

        for (int x = 0; x < rectangleWidth; x++)
        {
            for (int y = 0; y < rectangleHeight; y++)
            {
                std::swap(image.pixel(positionRectangleX1 + x, positionRectangleY1 + y), image.pixel(positionRectangleX2 + x, positionRectangleY2 + y));
            }
        }
    }
}

float luminance(glm::vec3 const &color)
{
    return 0.2126f * color.r + 0.7152f * color.g + 0.0722f * color.b;
}

void pixelSorting(sil::Image &image)
{
    for (int y{0}; y < image.height(); y++)
    {
        int rectangleSize{random_int(0, 70)};
        int x{random_int(0, image.width() - rectangleSize)};

        for (int i{x}; i < image.width() - rectangleSize; i++)
        {
            std::sort(image.pixels().begin(), image.pixels().end(), [](glm::vec3 const &color1, glm::vec3 const &color2)
                      { return luminance(color1) < luminance(color2); });
        }
    }
}


void rgb_to_lab(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            double X{0.4124564 * image.pixel(x, y).r + 0.3575761 * image.pixel(x, y).g + 0.1804375 * image.pixel(x, y).b};
            double Y{0.2126729 * image.pixel(x, y).r + 0.7151522 * image.pixel(x, y).g + 0.0721750 * image.pixel(x, y).b};
            double Z{0.0193339 * image.pixel(x, y).r + 0.1191920 * image.pixel(x, y).g + 0.9503041 * image.pixel(x, y).b};

            double Xn{0.964221};
            double Yn{1.0};
            double Zn{0.825211};

            double fx = X / Xn;
            double fy = Y / Yn;
            double fz = Z / Zn;

            if (fx > pow(6.0 / 29.0, 3))
            {
                fx = pow(fx, 1.0 / 3.0);
            }
            else
            {
                fx = (1.0 / 3.0) * pow(29.0 / 6.0, 2) * fx + (4.0 / 29.0);
            }

            if (fy > pow(6.0 / 29.0, 3))
            {
                fy = pow(fy, 1.0 / 3.0);
            }
            else
            {
                fy = (1.0 / 3.0) * pow(29.0 / 6.0, 2) * fy + (4.0 / 29.0);
            }

            if (fz > pow(6.0 / 29.0, 3))
            {
                fz = pow(fz, 1.0 / 3.0);
            }
            else
            {
                fz = (1.0 / 3.0) * pow(29.0 / 6.0, 2) * fz + (4.0 / 29.0);
            }

            double L = 116 * fy - 16;
            double a = 500 * (fx - fy);
            double b = 200 * (fy - fz);

            double epsilon{216 / 24389};
            double kappa{24389 / 27};

            double fy2 = (L + 16) / 116;
            double fx2 = a / 500 + fy2;
            double fz2 = fy2 - b / 200;

            double X2{fx2 > epsilon ? Xn * pow(fx2, 3) : Xn * ((116 * fx2 - 16) / kappa)};
            double Y2{L > kappa * epsilon ? Yn * pow(fy2, 3) : Yn * (L / kappa)};
            double Z2{fz2 > epsilon ? Zn * pow(fz2, 3) : Zn * ((116 * fz2 - 16) / kappa)};

            double R = 3.2404542 * X2 - 1.5371385 * Y2 - 0.4985314 * Z2;
            double G = -0.9692660 * X2 + 1.8760108 * Y2 + 0.0415560 * Z2;
            double B = 0.0556434 * X2 - 0.2040259 * Y2 + 1.0572252 * Z2;

            image.pixel(x, y) = glm::vec3{R, G, B};
        }
    }
}

void colorGradient(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float gradient = static_cast<float>(x) / static_cast<float>(image.width() - 1);
            image.pixel(x, y) = glm::vec3{1.f - gradient, gradient, 0.f};
        }
    }
    rgb_to_lab(image);
}