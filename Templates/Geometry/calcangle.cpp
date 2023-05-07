ld calcAngle(Point a, Point b, Point c) {
    ld v1x = a.x - b.x;
    ld v1y = a.y - b.y;
    ld v2x = c.x - b.x;
    ld v2y = c.y - b.y;
    ld magv1 = sqrt(v1x*v1x+v1y*v1y);
    ld magv2 = sqrt(v2x*v2x+v2y*v2y);
    ld theta = acosl((v1x*v2x+v1y*v2y)/(magv1*magv2));
    return theta;
}