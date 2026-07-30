#include <RayTracing.h>
#include <cstdio>
float theta = 0;
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

    Light l{{cos(theta)*40, 0, sin(theta)*40}, {255, 255, 255}};
    scene.lights.push_back(l);
    for(size_t y = 0; y < image.height; y++)
    {
        for(size_t x = 0; x < image.width; x++)
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


            image.pixels[y*image.width+x] =
                Trace(ray, scene);
        }
    }
    theta+= rad(2);
    scene.lights.pop_back();
}

ColorA RayTracer::Trace(Ray &ray, Scene &scene)
{
    ColorA color(0, 0, 0, 255);
    float closest_t = std::numeric_limits<float>::max();
    Ball b({0.3, 0.2, 0}, {255, 0, 0, 255}, 1.0, 1.0, 10.0);
    double t;
    if(Intersect(ray, b, t))
    {
        //printf("%f, %f\n", ray.dir.x, ray.dir.y);
        Vec hitPoint = ray.start + ray.dir*t;
        Vec normal = normalize(hitPoint - b.pos);
        ColorA lightColor = {ComputeLighting(hitPoint, normal, scene), 255};
        return MixColorsSub(ray, hitPoint, b.color, b.brightness, b.reflexion)*lightColor;
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