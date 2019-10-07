function [result] = mandelbrot(c, stop)

z = c;
result = 0;

while(abs(z) <= 2 && result < stop - 1)
    z = z^2 + c;
    result = result + 1;
end

