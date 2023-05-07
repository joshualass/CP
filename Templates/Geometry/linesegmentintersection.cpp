bool intersect(pair<Point,Point> first, pair<Point,Point> second) {
    ld p1x = first.first.x;
    ld p1y = first.first.y;
    ld v1x = first.second.x - first.first.x;
    ld v1y = first.second.y - first.first.y;
    ld p2x = second.first.x;
    ld p2y = second.first.y;
    ld v2x = second.second.x - second.first.x;
    ld v2y = second.second.y - second.first.y;
    if(abs(v1x*v2y - v1y*v2x) < 1e-9) {
        return false;
    }
    ld s = (p1y*v2x+p2x*v2y-p1x*v2y-p2y*v2x)/(v1x*v2y-v1y*v2x);
    ld t = (p1y*v1x+p2x*v1y-p1x*v1y-p2y*v1x)/(v1x*v2y-v1y*v2x);

    // cout << "s: " << s << "\n";
    return (-0.000000001 <= s && s <= 1.000000001) && (-0.000000001 <= t && t <= 1.000000001);
}