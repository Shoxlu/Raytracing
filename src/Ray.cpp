#include "Ray.h"


Ray Ray::Reflect(Hit& hit, ColorA c)
{
    Vec p = hit.normal * dot(hit.normal, dir);
    Vec new_dir = dir - p*2;
    // printf("1: %f %f %f\n2: %f %f %f\nnormal: %f %f %f\n", ray_dir_neg.x, ray_dir_neg.y, ray_dir_neg.z, dir.x, dir.y, dir.z,
    // normal.x, normal.y, normal.z);
    Ray reflectionRay(hit.hitPoint+ hit.normal * 0.001, new_dir, {255, 255, 255}, 1.0);
    return reflectionRay;
}