#include <sil/sil.hpp>
#include <iostream>
#include "../lib/random.hpp"

void onlyGreen(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

void swapColor(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
}

void blackWhite(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float luminance{0.2126f * image.pixel(x, y).r + 0.7152f * image.pixel(x, y).g + 0.0722f * image.pixel(x, y).b};
            image.pixel(x, y) = glm::vec3{luminance};
        }
    }
}

void invertColor(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = 1.f - image.pixel(x, y);
        }
    }
}

void gradientBlack(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
}

void caac(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            int newX{image.width() - 1 - x};
            int newY{image.height() - 1 - y};
            image.pixel(newX, y) = image.pixel(x, y);
        }
    }
}

void mirrorImage(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int newX{image.width() - 1 - x};
            std::swap(image.pixel(x, y), image.pixel(newX, y));
        }
    }
}

void noise(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            switch (random_int(0, 3))
            {
            case 0:
                image.pixel(x, y).r = image.pixel(x, y).r + (rand() % 2) / 2.f;
                break;
            case 1:
                image.pixel(x, y).g = image.pixel(x, y).g + (rand() % 2) / 2.f;
                break;
            case 2:
                image.pixel(x, y).b = image.pixel(x, y).b + (rand() % 2) / 2.f;
                break;

            default:
                break;
            };
        }
    }
}

void rotate90(sil::Image &image)
{
    int new_width{image.height()};
    int new_height{image.width()};
    sil::Image new_image{new_width, new_height};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(new_width - 1 - y, x) = image.pixel(x, y);
        }
    }
    new_image.save("output/rotate90.png");
}

void rgb_split(sil::Image &image)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int blueX{x - 30};
            int redX{x + 30};

            if (blueX < 0)
            {
                blueX = 0;
            }
            else if (redX >= image.width())
            {
                redX = image.width() - 1;
            }
            new_image.pixel(redX, y).r = image.pixel(x, y).r;
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            new_image.pixel(blueX, y).b = image.pixel(x, y).b;
        }
    }
    new_image.save("output/rgb_split.png");
}

void surexp(sil::Image &image)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(x, y).g = pow(image.pixel(x, y).g, 0.75);
            new_image.pixel(x, y).r = pow(image.pixel(x, y).r, 0.75);
            new_image.pixel(x, y).b = pow(image.pixel(x, y).b, 0.75);
        }
    }
    new_image.save("output/surexp.jpg");
}

void sousexp(sil::Image &image)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(x, y).r = pow(image.pixel(x, y).r, 1.1);
            new_image.pixel(x, y).g = pow(image.pixel(x, y).g, 1.1);
            new_image.pixel(x, y).b = pow(image.pixel(x, y).b, 1.1);
        }
    }
    new_image.save("output/sousexp.jpg");
}

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

void mosaique(sil::Image &image)
{

    int rows{5};
    int cols{5};

    sil::Image new_image{image.width() * 5, image.height() * 5};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {
                    new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                }
            }
        }
    }

    new_image.save("output/mosaique.png");
}

void mosaiqueMirror(sil::Image &image)
{
    int rows{5};
    int cols{5};

    sil::Image new_image{image.width() * 5, image.height() * 5};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {
                    int newX{image.width() - 1 - x};
                    int newY{image.height() - 1 - y};

                    if (i % 2 == 1 && j % 2 == 1)
                    {
                        new_image.pixel(newX + i * image.width(), newY + j * image.height()) = image.pixel(x, y);
                    }
                    else if (i % 2 == 1)
                    {
                        new_image.pixel(newX + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                    }
                    else if (j % 2 == 1)
                    {
                        new_image.pixel(x + i * image.width(), newY + j * image.height()) = image.pixel(x, y);
                    }
                    else
                    {
                        new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                    }
                }
            }
        }
    }

    new_image.save("output/mosaiqueMirror.png");
}

void water(sil::Image &image)
{
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int waterX{random_int(0, 10)};
            int waterY{random_int(0, 10)};

            if (x + waterX >= image.width())
            {
                new_image.pixel(x, y) = image.pixel(x, y);
            }
            else if (y + waterY >= image.height())
            {
                new_image.pixel(x, y) = image.pixel(x, y);
            }
            else
            {
                new_image.pixel(x, y) = image.pixel(x + waterX, y + waterY);
            }
        }
    }

    new_image.save("output/water.png");
}

void glitch(sil::Image &image)
{
    int numberGlitch{random_int(10, 50)};

    for (int i = 0; i < numberGlitch; i++)
    {
        int rectangleWidth = rand() % 20;
        int rectangleHeight = rand() % 20;

        if (rectangleWidth > image.width() || rectangleHeight > image.height())
            continue;

        int positionRectangleX1 = rand() % (image.width() - rectangleWidth);
        int positionRectangleY1 = rand() % (image.height() - rectangleHeight);

        int positionRectangleX2 = rand() % (image.width() - rectangleWidth);
        int positionRectangleY2 = rand() % (image.height() - rectangleHeight);

        for (int x = 0; x < rectangleWidth; x++)
        {
            for (int y = 0; y < rectangleHeight; y++)
            {
                std::swap(image.pixel(positionRectangleX1 + x, positionRectangleY1 + y), image.pixel(positionRectangleX2 + x, positionRectangleY2 + y));
            }
        }
    }
}

int main()
{
    sil::Image image{"images/logo.png"};
    mosaiqueMirror(image);
    image.save("output/pouet.png");
}