#include <Vector.h>

double dot(Vec v1, Vec v2)
{
    return v1.dot(v2);
}


Vec normalize(Vec v)
{
    return v/v.dist();
}