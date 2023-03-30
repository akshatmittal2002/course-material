`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:26:53 02/01/2022
// Design Name:   register_4bit
// Module Name:   /home/ise/Desktop/CS_224/Lab4/test2.v
// Project Name:  Lab4
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: register_4bit
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
	reg [3:0] d;
	reg clk;
	reg load;
	reg clear;

	// Outputs
	wire [3:0] q;

	// Instantiate the Unit Under Test (UUT)
	register_4bit uut (
		.q(q), 
		.d(d), 
		.clk(clk), 
		.load(load), 
		.clear(clear)
	);
	
	initial begin
		clk = 1'b0;
		forever #10 clk = ~clk;
	end
	initial begin
	
		d = 4'b0110;
		load = 1'b1;
		clear = 1'b0;
		
		#25;
		d = 4'b0011;
		load = 1'b1;
		clear = 1'b1;
		
		#20;
		clear = 1'b0;
		
		#20;
		d = 4'b1010;
		load = 1'b1;
		
		#20;
		clear = 1'b1;
		load = 1'b0;
	end
      
endmodule

