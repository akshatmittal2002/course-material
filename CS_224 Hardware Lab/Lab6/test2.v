`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:15:28 02/15/2022
// Design Name:   mealy_vs_delayed
// Module Name:   /home/ise/Desktop/CS_224/Lab6/test2.v
// Project Name:  Lab6
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mealy_vs_delayed
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test2;

	// Inputs
	reg reset;
	reg x;
	reg clk;

	// Outputs
	wire y_mealy;
	wire [1:0] curr_mealy;
	wire y_delay;
	wire [1:0] curr_delay;

	// Instantiate the Unit Under Test (UUT)
	mealy_vs_delayed uut (
		.reset(reset), 
		.x(x), 
		.clk(clk), 
		.y_mealy(y_mealy), 
		.curr_mealy(curr_mealy), 
		.y_delay(y_delay), 
		.curr_delay(curr_delay)
	);

	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end
	initial begin
		// Initialize Inputs
		reset = 0;
		x = 0;
		
		#5
		reset = 1;
		
		#15
		reset = 0;
		
		#10 x = 1;
		#10 x = 0;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 0;
		#10 x = 1;
		reset = 1;
		#10 x = 0;
		reset = 0;
		// Add stimulus here

	end
      
endmodule

