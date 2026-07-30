#include <RayTracing.h>
#include <cstdio>
#include <chrono>

void RayTracer::Render(Image &image, Scene &scene)
{

    Camera &camera = scene.camera;
    glm::vec3 forward = glm::normalize(camera.cameraFront);

    glm::vec3 right =
        glm::normalize(
            glm::cross(forward, camera.cameraUp));

    glm::vec3 up =
        glm::cross(right, forward);


    double aspect =
        image.width / (float)image.height;

    double scale =
        tan(glm::radians(camera.fov * 0.5f));

    // size_t traceCallCount = 0;
    // double traceTotalTimeUs = 0.0;
    // double traceAverageTimeUs = 0.0;
    #pragma omp parallel for collapse(2)
    for(int y = 0; y < image.height; y++)
    {
        for(int x = 0; x < image.width; x++)
        {
            double u = (x + 0.5) / image.width;
            double v = (y + 0.5) / image.height;


            float px =
                (2*u - 1) * aspect * scale;

            float py =
                (1 - 2*v) * scale;


            glm::vec3 dir =
                glm::normalize(
                    forward
                    + px * right
                    + py * up
                );

            Ray ray(camera.cameraPos, dir);

            // auto start = std::chrono::high_resolution_clock::now();
            image.pixels[y*image.width+x] =
                Trace(ray, scene);
            // auto duration = std::chrono::duration<double, std::micro>(
            // std::chrono::high_resolution_clock::now() - start);
            // traceCallCount++;
            // traceTotalTimeUs += duration.count();
            // traceAverageTimeUs = traceTotalTimeUs / traceCallCount;
        }
    }
    // printf("Total: %f, Avg: %f, N: %u\n", traceTotalTimeUs/1000, traceAverageTimeUs/1000, traceCallCount);
}

ColorA RayTracer::Trace(Ray &ray, Scene &scene)
{

    ColorA color(0, 0,0, 255);
    double closest_t = std::numeric_limits<double>::max();
    Ball closest_b({0, 0, 0}, {0, 0, 0, 0});
    bool hit = false;
    for(Ball& b: scene.objects)
    {
        double t;
        if(Intersect(ray, b, t))
        {
            if(closest_t > t)
            {
                hit = true;
                closest_t = t;
                closest_b = b;
                //printf("closest now %f, t %f\n", closest_t, t);
            }
        }
    }
    if(hit)
    {
        double t= closest_t;
        Ball& b = closest_b;
        Vec hitPoint = ray.start + ray.dir*t;
        Vec normal = normalize(hitPoint - b.pos);
        ColorA lightColor = {ComputeLighting(hitPoint, normal, scene), 255};
        color = MixColorsSub(ray, hitPoint, b.color, b.brightness, b.reflexion)*lightColor;
    }

    

    return color;
}

Color RayTracer::ComputeLighting(Vec hitPoint,Vec normal, Scene& scene)
{
    Color lightcolor;
    for(Light& l: scene.lights)
    {
        Vec lightDirection = -normalize(hitPoint-l.position);
        lightcolor += l.color*std::max( dot(normal, lightDirection),0.0);
    }
    float r = lightcolor.r/255.0;
    float g = lightcolor.g/255.0;
    float b = lightcolor.b/255.0;
    return lightcolor;
}

bool RayTracer::Intersect(
    const Ray& ray,
    const Ball& sphere,
    double& t)
{
    Vec oc = ray.start - sphere.pos;

    double a = dot(ray.dir, ray.dir);
    double b = 2.0f * dot(oc, ray.dir);
    double c = dot(oc, oc) - sphere.radius*sphere.radius;

    double delta = b*b - 4*a*c;

    if(delta < 0)
        return false;

    t = (-b - sqrt(delta)) / (2*a);

    return t > 0;
}

ColorA RayTracer::MixColorsSub(Ray& ray,Vec hitPoint, ColorA& color, double brightness, double reflexion)
{
    ColorA mixedColor;
    mixedColor.r = std::min(255.0, (ray.color.r/255.0 * ray.brightness * color.r/255.0 * reflexion)*255);
    mixedColor.g = std::min(255.0, (ray.color.g/255.0 * ray.brightness * color.g/255.0 * reflexion)*255);
    mixedColor.b = std::min(255.0, (ray.color.b/255.0 * ray.brightness * color.b/255.0 * reflexion)*255);
    mixedColor.a = 255;
    return mixedColor;
}