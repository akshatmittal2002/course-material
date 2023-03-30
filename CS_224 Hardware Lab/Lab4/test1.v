`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:55:03 02/01/2022
// Design Name:   part1_b
// Module Name:   /home/ise/Desktop/CS_224/Lab4/test1.v
// Project Name:  Lab4
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: part1_b
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
	reg a;
	reg clk;

	// Outputs
	wire q0;
	wire q1;
	wire q2;

	// Instantiate the Unit Under Test (UUT)
	part1_b uut (
		.a(a), 
		.clk(clk), 
		.q0(q0), 
		.q1(q1), 
		.q2(q2)
	);
	initial begin
		clk = 1'b0;
		forever #10 clk = ~clk;
	end
	initial begin
		// Initialize Inputs
		a = 1;

		// Wait 100 ns for global reset to finish
        
		// Add stimulus here

	end
      
endmodule

