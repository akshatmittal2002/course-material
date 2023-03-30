`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   09:57:58 01/25/2022
// Design Name:   mux_2
// Module Name:   /home/ise/Desktop/CS_224/Lab3/test_2.v
// Project Name:  Lab3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mux_2
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_2;

	// Inputs
	reg i0;
	reg i1;
	reg i2;
	reg i3;
	reg s0;
	reg s1;

	// Outputs
	wire out;

	// Instantiate the Unit Under Test (UUT)
	mux_2 uut (
		.out(out), 
		.i0(i0), 
		.i1(i1), 
		.i2(i2), 
		.i3(i3), 
		.s0(s0), 
		.s1(s1)
	);

	initial begin
		// Initialize Inputs
		i0 = 0;
		i1 = 1;
		i2 = 0;
		i3 = 1;
		s0 = 0;
		s1 = 0;

		#100;
		
		i0 = 0;
		i1 = 1;
		i2 = 0;
		i3 = 1;
		s0 = 1;
		s1 = 0;

		#100;
		
		i0 = 0;
		i1 = 1;
		i2 = 0;
		i3 = 1;
		s0 = 0;
		s1 = 1;

		#100;
		
		i0 = 0;
		i1 = 1;
		i2 = 0;
		i3 = 1;
		s0 = 1;
		s1 = 1;

		#100;

	end
      
endmodule

