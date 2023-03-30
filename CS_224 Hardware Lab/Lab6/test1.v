`timescale 1ns / 1ps

module test1;

	// Inputs
	reg reset;
	reg x;
	reg clk;

	// Outputs
	wire y_mealy;
	wire [1:0] curr_mealy;
	wire y_moore;
	wire [2:0] curr_moore;

	// Instantiate the Unit Under Test (UUT)
	moore_vs_mealy uut (
		.reset(reset), 
		.x(x), 
		.clk(clk), 
		.y_mealy(y_mealy), 
		.curr_mealy(curr_mealy), 
		.y_moore(y_moore), 
		.curr_moore(curr_moore)
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
