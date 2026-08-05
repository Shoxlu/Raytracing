#include <RayTracing.h>
#include <cstdio>
#include <chrono>
#define DEPTH_REFLECT 0



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
    Hit dummy;
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
                Trace(ray, scene, DEPTH_REFLECT, dummy);
            // auto duration = std::chrono::duration<double, std::micro>(
            // std::chrono::high_resolution_clock::now() - start);
            // traceCallCount++;
            // traceTotalTimeUs += duration.count();
            // traceAverageTimeUs = traceTotalTimeUs / traceCallCount;
        }
    }
    // printf("Total: %f, Avg: %f, N: %u\n", traceTotalTimeUs/1000, traceAverageTimeUs/1000, traceCallCount);
}

ColorA RayTracer::Trace(Ray &ray, Scene &scene, int depth, Hit& res)
{
    ColorA color(0, 0, 0, 0);
    double closest_t = std::numeric_limits<double>::max();
    Object* closest_b = nullptr;
    bool hit_flag = false;
    Hit best_hit;
    best_hit.distance = closest_t;
    for(Object* obj: scene.objects)
    {
        Object& b = *obj;
        Hit current_hit;
        if(b.Intersect(ray, current_hit) && best_hit.distance > current_hit.distance)
        {
            hit_flag = true;
            best_hit = current_hit;
            closest_b = &b;
            // hit.reflection_coeff = b.reflexion;
            //printf("closest now %f, t %f\n", closest_t, t);
        }
    }
    if(closest_b)
    {
        Object& b = *closest_b;
        double k = b.reflexion;
        ColorA lightColor = {ComputeLighting(best_hit, scene), 255};
        color = MixColorsSub(ray, best_hit.hitPoint, b.color, b.brightness, b.reflexion)*lightColor;
        if(depth == 0)
        {
            return color;
        }
        Ray reflectionRay = ray.Reflect(best_hit, color);
        Hit next_hit;
        ColorA color2 = Trace(reflectionRay, scene, depth-1, next_hit);
        color = color2*k+color*(1-k);
    }

    res = best_hit;

    return color;
}

bool RayTracer::isOccluded(Ray& ray, float distance, Scene& scene, double& transmission)
{
    for(Object* obj: scene.objects)
    {
        Object& b = *obj;
        Hit t;
        if(b.Intersect(ray, t))
        {
            
            return t.distance <= distance;
        }
    }
    return false;
}

Color RayTracer::ComputeLighting(Hit& hit, Scene& scene)
{
    Color lightcolor;
    for(Light& l: scene.lights)
    {
        Vec toLight = l.position - hit.hitPoint;
        float distance = toLight.dist();

        Vec direction = normalize(toLight);
        Ray shadowRay(hit.hitPoint+hit.normal*0.001f, direction);

        double factor = 1.0;
        isOccluded(shadowRay, distance, scene, factor);

        Vec lightDirection = -normalize(hit.hitPoint-l.position);
        lightcolor += l.color*std::max(dot(hit.normal, lightDirection),0.0)*factor;
    }
    float r = lightcolor.r/255.0;
    float g = lightcolor.g/255.0;
    float b = lightcolor.b/255.0;
    return lightcolor;
}

ColorA RayTracer::MixColorsSub(Ray& ray,Vec hitPoint, ColorA& color, double brightness, double reflexion)
{
    ColorA mixedColor;
    mixedColor.r = std::min(255.0, (ray.color.r/255.0 * ray.brightness * color.r/255.0)*255);
    mixedColor.g = std::min(255.0, (ray.color.g/255.0 * ray.brightness * color.g/255.0)*255);
    mixedColor.b = std::min(255.0, (ray.color.b/255.0 * ray.brightness * color.b/255.0)*255);
    mixedColor.a = 255;
    return mixedColor;
}