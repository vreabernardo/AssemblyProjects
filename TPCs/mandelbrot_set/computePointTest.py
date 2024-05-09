def compute(nx, ny, xmin, ymin, xmax, ymax):
    delta_x = (xmax - xmin) / nx
    delta_y = (ymax - ymin) / ny
    
    for y in range(ny):
        y_value = ymin + delta_y * y
        for x in range(nx):
            x_value = xmin + delta_x * x
            v = compute_point(x_value, y_value)  
            print(v)

# unsigned char computePoint( double x, double y)
def compute_point(x, y):
    iterations = 0
    zi = 0
    zr = 0
    
    while ((zr*zr + zi*zi < 4.0) and (iterations < 255)):
        nr = zr*zr - zi*zi + x
        ni = 2*zr*zi + y
        zi = ni
        zr = nr
        iterations+=1
    
    return iterations

def main():
    compute(10, 10, -1, -1, 1, 1)

if __name__ == "__main__":
    main()