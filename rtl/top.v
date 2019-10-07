`include "i2c/I2C_HDMI_Config.v"

module top(

    // ADC
    output ADC_CONVST,
    output ADC_SCK,
    output ADC_SDI,
    input  ADC_SDO,

    // ARDUINO
    input [15:0] ARDUINO_IO,
    inout ARDUINO_RESET_N,

    // CLOCK
    input FPGA_CLK1_50,
    input FPGA_CLK2_50,
    input FPGA_CLK3_50,

    // HDMI - I2C
    inout HDMI_I2C_SCL,
    inout HDMI_I2C_SDA,
    input HDMI_TX_INT,

    // HDMI - AUDIO
    inout HDMI_I2S,
    inout HDMI_LRCLK,
    inout HDMI_MCLK,
    inout HDMI_SCLK,

    // HDMI - VIDEO
    output HDMI_TX_CLK,
    output HDMI_TX_DE,
    output [23:0] HDMI_TX_D,
    output HDMI_TX_HS,
    output HDMI_TX_VS,

    input  [1:0] KEY,

    output [7:0] LED,

    input  [3:0] SW
    );

// Signals
wire s_clk74;
wire s_reset_pll;
wire s_reset_n;
wire s_pll_locked;
wire s_hdmi_cfg_ready;

wire s_key_right;
wire s_key_down;

// Put unused audio signals in high-impedence
assign HDMI_I2S   = 1'b z;
assign HDMI_MCLK  = 1'b z;
assign HDMI_LRCLK = 1'b z;
assign HDMI_SCLK  = 1'b z;

assign s_reset_pll = ~ 1;
assign s_reset_n = 1 && s_pll_locked;

//////////////////////////////////////////////////
// PLL
//////////////////////////////////////////////////

pll u_pll(
    .refclk   (FPGA_CLK1_50),
    .rst      (s_reset_pll),
    .outclk_0 (s_clk74),
    .locked   (s_pll_locked)
    );

//////////////////////////////////////////////////
// Mandelbrot
//////////////////////////////////////////////////

mandelbrot_top u_mandelbrot_top(
    .i_clk             (s_clk74),
    .i_reset_n         (s_reset_n),
    .i_enable          (SW[2]),
    .i_video_test      (SW[3]),

    .i_key_up          (s_key_up),
    .i_key_down        (s_key_down),
    .i_key_left        (s_key_left),
    .i_key_right       (s_key_right),
    .i_key_zoom_in     (s_zoom_in),
    .i_key_zoom_out    (s_zoom_out),

    .o_video_enable    (HDMI_TX_DE),
    .o_horizontal_sync (HDMI_TX_HS),
    .o_vertical_sync   (HDMI_TX_VS),
    .o_red             (HDMI_TX_D[23:16]),
    .o_green           (HDMI_TX_D[15:8]),
    .o_blue            (HDMI_TX_D[7:0])
    );

assign s_key_right = ARDUINO_IO[0];
assign s_key_left  = ARDUINO_IO[7];
assign s_key_up    = ARDUINO_IO[2];
assign s_key_down  = ARDUINO_IO[1];
assign s_zoom_in   = ~ KEY[0];
assign s_zoom_out  = ~ KEY[1];
assign HDMI_TX_CLK = s_clk74;

//////////////////////////////////////////////////
// I2C Interface for ADV7513 initial config
//////////////////////////////////////////////////

I2C_HDMI_Config #(
    .CLK_Freq (50000000), // 50MHz
    .I2C_Freq (20000)     // 20kHz
)

I2C_HDMI_Config (
    .iCLK        (FPGA_CLK1_50),
    .iRST_N      (s_reset_n),
    .I2C_SCLK    (HDMI_I2C_SCL),
    .I2C_SDAT    (HDMI_I2C_SDA),
    .HDMI_TX_INT (HDMI_TX_INT),
    .READY       (s_hdmi_cfg_ready)
    );

assign LED0 = s_hdmi_cfg_ready;

endmodule
