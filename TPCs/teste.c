unsigned char computePoint(double x, double y)
{
    int iterations = 0;
    double zi = 0;
    double zr = 0;
    while ((zr * zr + zi * zi < 4.0) && (iterations < 255))
    {
        double nr = zr * zr - zi * zi + x;
        double ni = 2 * zr * zi + y;
        zi = ni;
        zr = nr;
        iterations++;
    }
    return iterations;
}