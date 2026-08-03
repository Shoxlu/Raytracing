#include <Object.h>


Object::Object(Vec p,ColorA c, double r, double b): pos(p), color(c), reflexion(r), brightness(b)
{

}


Ball::Ball(Vec p, ColorA c, double r , double b, double rad):Object(p, c, r, b), radius(rad)
{

}
Ball::Ball(Vec p, Color c, double r , double b, double rad):Object(p, {c.r, c.g, c.b, 255}, r, b), radius(rad)
{

}


bool Ball::Intersect(const Ray& ray, Hit& hit)
{
     Vec oc = ray.start -pos;

    double a = dot(ray.dir, ray.dir);
    double b = 2.0f * dot(oc, ray.dir);
    double c = dot(oc, oc) - radius*radius;

    double delta = b*b - 4*a*c;

    if(delta < 0)
        return false;

    hit.distance = (-b - sqrt(delta)) / (2*a);

    return hit.distance > 0;
}