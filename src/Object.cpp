#include <Object.h>
#include <iostream>


Object::Object(Vec p,ColorA c, double r, double b, double t): pos(p), color(c), reflexion(r), brightness(b), transparency(t)
{

}


Ball::Ball(Vec p, ColorA c, double r , double b, double rad, double t):Object(p, c, r, b, t), radius(rad)
{

}
Ball::Ball(Vec p, Color c, double r , double b, double rad, double t):Object(p, {c.r, c.g, c.b, 255}, r, b, t), radius(rad)
{

}


bool Ball::Intersect(const Ray& ray, Hit& hit)
{
     Vec oc = ray.start -pos;

    double a = dot(ray.dir, ray.dir);
    double b = 2.0f * dot(oc, ray.dir);
    double c = dot(oc, oc) - radius*radius;

    double delta = b*b - 4*a*c;

    if(delta < 0 )
        return false;
    hit.distance = (-b - sqrt(delta)) / (2*a);
    if(hit.distance > 0)
    {
        hit.distance = (-b - sqrt(delta)) / (2*a);
        hit.hitPoint = ray.start + ray.dir*hit.distance;
        hit.normal = normalize( hit.hitPoint - pos);
        return true;
    }
    

    return false;
}

Wall::Wall(Vec center, ColorA color, Vec size, Vec normal, double r, double b, double t): Object(center, color, r, b, t), size(size), normal(normalize(normal))
{
}

Wall::Wall(Wall &w) : Object(w.pos, w.color, w.reflexion, w.brightness, w.transparency), size(w.size), normal(w.normal)
{

}

bool Wall::IsPointInRectangle(const Vec &point) const
{
    Vec diff = point - pos;
    return abs(diff.x) <= size.x / 2.0 && abs(diff.y) <= size.y / 2.0;
}

bool Wall::Intersect(const Ray &ray, Hit &result)
{

    // normal.x * (x-pos.x) + normal.y * (y-pos.y) + normal.z * (z-pos.z) = 0;
    // normal.x * x + normal.y * y + normal.z * z = <normal, pos>;
    // x,y,z = ray.dir*t;
    // normal.x * ray.dir.x*t + normal.y * ray.dir.y*t + normal.z * ray.dir.z*t = <normal, pos>;
    // t*(normal.x * ray.dir.x + normal.y * ray.dir.y + normal.z * ray.dir.z) = <normal, pos>;
    // t = <normal,pos>/<normal, ray.dir>;
    double distance = dot(normal, ray.dir) != 0 ? dot(normal, pos-ray.start)/dot(normal, ray.dir): 10000000;
    //printf("%f\n", distance);
    //printf("Vec: %f %f %f\n%f\n",p.x, p.y, p.z, distance);
    Vec hitpoint = ray.start + ray.dir*distance ;
    if(distance >= 0 && dot(ray.dir, normal) != 0.0 && IsPointInRectangle(hitpoint))
    {
        // <e1, normal> = 0 <=> e1.x*normal.x + e1.y*normal.y + e1.z*normal.z = 0 <= e1 = (normal.y, -normal.x, 0) or (normal.z,0, -normal.x)
        
        result.distance = distance;
        result.hitPoint = hitpoint;
        result.normal = normal;
        return true;
    }
    return false;
}
