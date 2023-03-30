`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   09:15:49 03/29/2022
// Design Name:   mem_controller
// Module Name:   /home/ise/Desktop/CS_224/Lab10/test1.v
// Project Name:  Lab10
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mem_controller
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test1;

	// Inputs
	reg S;
	reg reset;
	reg clk;

	// Instantiate the Unit Under Test (UUT)
	mem_controller uut (
		.S(S), 
		.reset(reset), 
		.clk(clk)
	);
	
	initial begin
		clk = 0;
		forever #1 clk = ~clk;
	end
	
	initial begin
		reset = 1;
		S = 0;
		#4 reset = 0;
		#100 S = 1;
		#4 S = 0;
	end
      
endmodule

