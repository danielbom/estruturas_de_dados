

extern inline void ellipsef( float x, float px, float py, float a, float b, float *points ) {
    points[0] = cos(x) * px * a ;
    points[1] = sin(x) * py * b ;
}

extern inline void ellipse( double x, double px, double py, double a, double b, double *points ) {
    points[0] = cos(x) * px * a ;
    points[1] = sin(x) * py * b ;
}

extern inline float rad_to_angle( double rad ) {
    // return ( rad * 180 ) / M_PI ;
    return rad * 57.29577951308232;
}

extern inline float angle_to_rad( double angle ) {
    // return ( angle * M_PI ) / 180 ;
    return angle * 0.017453292519943295;
}

extern inline float norm_vetor( float x, float y ) {
    return sqrt(x*x + y*y);
}

void unit_vetorf( float x, float y, float *points ) {
    float norm = norm_vetor( x, y );
    points[0] = x / norm;
    points[1] = y / norm;
}