#include <RayTracing.h>

void RayTracer::Render(Image &image, Scene &scene)
{
    for (size_t i = 0; i < image.width; i++)
    {
        for (size_t j = 0; j < image.height; j++)
        {
            image.pixels[i * image.height + j] = ColorA(255, 0, 0, 255);
        }
    }
}
