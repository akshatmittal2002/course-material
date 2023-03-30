`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:21:34 02/08/2022
// Design Name:   sequencedetector2
// Module Name:   /home/ise/Desktop/CS_224/Lab5/test2.v
// Project Name:  Lab5
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: sequencedetector2
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
	reg x;
	reg clk;
	reg reset;

	// Outputs
	wire y;
	wire [2:0] curr;

	// Instantiate the Unit Under Test (UUT)
	sequencedetector2 uut (
		.x(x), 
		.clk(clk), 
		.reset(reset), 
		.y(y), 
		.curr(curr)
	);

	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end
	initial begin
		$monitor($time,", x = %b, y = %b, reset = %b, current state = %d\n",x,y,reset,curr);
		x = 0;
		#5 reset = 1;
		#10 reset = 0;
		
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
		reset = 1;
		#10 reset = 0;
		x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
		#10 x = 0;
		#10 x = 1;
	end
      
endmodule

