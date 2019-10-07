palette_size = MAX_ITERATIONS;

base_colors_y(1,:) = [0   , 7   , 100];
base_colors_y(2,:) = [32  , 107 , 203];
base_colors_y(3,:) = [237 , 255 , 255];
base_colors_y(4,:) = [255 , 170 , 0];
base_colors_y(5,:) = [0   , 2   , 0];

base_colors_x(1) = 0.0;
base_colors_x(2) = 0.16;
base_colors_x(3) = 0.42;
base_colors_x(4) = 0.6425;
base_colors_x(5) = 1.0;

% Compute palette
interp_method = 'linear';
palette_x = linspace(0,1,palette_size);
palette(:,1) = interp1(base_colors_x,base_colors_y(:,1),palette_x, interp_method);
palette(:,2) = interp1(base_colors_x,base_colors_y(:,2),palette_x, interp_method);
palette(:,3) = interp1(base_colors_x,base_colors_y(:,3),palette_x, interp_method);

% Generate LUT
LUT_RED = uint8(palette(:,1));
LUT_GREEN = uint8(palette(:,2));
LUT_BLUE = uint8(palette(:,3));
palette_norm = palette/255.0;