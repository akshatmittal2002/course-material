`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:00:05 02/01/2022
// Design Name:   part1_a
// Module Name:   /home/ise/Desktop/CS_224/Lab4/test4.v
// Project Name:  Lab4
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: part1_a
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test4;

	// Inputs
	reg a;
	reg clk;

	// Outputs
	wire q0;
	wire q1;
	wire q2;

	// Instantiate the Unit Under Test (UUT)
	part1_a uut (
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
		a=1;
        
		// Add stimulus here

	end
      
endmodule

