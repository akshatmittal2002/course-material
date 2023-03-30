`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:48:15 02/22/2022
// Design Name:   asm_2
// Module Name:   /home/ise/Desktop/CS_224/Lab7/test2.v
// Project Name:  Lab7
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: asm_2
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
	reg [3:0] B;
	reg [3:0] A;
	reg reset;
	reg clk;
	reg s;

	// Outputs
	wire [3:0] out;
	wire [2:0] curr;
	wire done;

	// Instantiate the Unit Under Test (UUT)
	asm_2 uut (
		.out(out), 
		.curr(curr), 
		.B(B), 
		.A(A), 
		.reset(reset), 
		.clk(clk), 
		.s(s), 
		.done(done)
	);
	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end
	initial begin
		// Initialize Inputs
		A = 4'b1001;
		B = 4'b1111;
		reset = 1;
		s = 0;
		#15 reset = 0;
		#20 s=1;
		#20 s=0;
		
        
		// Add stimulus here

	end
      
endmodule

