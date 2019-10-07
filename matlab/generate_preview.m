zoom = 1;
offset_x = 0;
offset_y = 0;
data_preview = zeros(VGA_VERTICAL_RESOLUTION, VGA_HORIZONTAL_RESOLUTION);
screen_preview = zeros(VGA_VERTICAL_RESOLUTION, VGA_HORIZONTAL_RESOLUTION, 3);
for y=1:VGA_VERTICAL_RESOLUTION
    for x=1:VGA_HORIZONTAL_RESOLUTION
        i = (x - (VGA_HORIZONTAL_RESOLUTION/2))/(VGA_VERTICAL_RESOLUTION/2)*zoom + offset_x;
        j = ((VGA_VERTICAL_RESOLUTION/2) - y)/(VGA_VERTICAL_RESOLUTION/2)*zoom + offset_y;
        data_preview(y, x) = mandelbrot(complex(i,j), MAX_ITERATIONS);
        screen_preview(y, x, :) = palette_norm(data_preview(y, x) + 1, :);
    end
end

figure(1)
imshow(screen_preview)

figure(2)
surf(data_preview(1:16:end, 1:16:end))
colormap(palette_norm)
colorbar
