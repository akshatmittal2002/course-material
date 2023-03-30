`timescale 1ns / 1ps

module test1;

	// Inputs
	reg x;
	reg reset;
	reg clk;

	// Outputs
	wire y;

	// Instantiate the Unit Under Test (UUT)
	sequence_detector uut (
		.x(x), 
		.reset(reset), 
		.clk(clk), 
		.y(y)
	);

	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end
	initial begin
		x = 0;
		#5 reset = 1;
		#10 reset = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 0;
		
	end
      
endmodule

