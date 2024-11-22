#include "twoStars.hpp"

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