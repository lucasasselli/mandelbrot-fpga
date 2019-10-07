%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CLEAR ENVIRONMENT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% LOAD CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Ts = 1.35E-8;

% Algorithm
MAX_ITERATIONS = 128;
Z_BUS_TYPE = fixdt(1,18,15);

% Other
BUTTON_CLOCK_DIV = 65536;
BUTTON_DEBOUNCE = round(0.01/(Ts*BUTTON_CLOCK_DIV));
BUTTON_POLLING = round(0.01/(Ts*BUTTON_CLOCK_DIV));
ZOOM_FACTOR = 0.98;
TRASLATION_FACTOR = 0.1;

% Screen
config_screen_720p;
%config_screen_dummy;

% Useful stuff
generate_palette;
generate_preview;