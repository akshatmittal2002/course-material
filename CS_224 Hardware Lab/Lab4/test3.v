`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:13:35 02/01/2022
// Design Name:   register_4bit_inc
// Module Name:   /home/ise/Desktop/CS_224/Lab4/test3.v
// Project Name:  Lab4
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: register_4bit_inc
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test3;

	// Inputs
	reg [3:0] d;
	reg clk;
	reg load;
	reg clear;
	reg inc;

	// Outputs
	wire [3:0] q;

	// Instantiate the Unit Under Test (UUT)
	register_4bit_inc uut (
		.q(q), 
		.d(d), 
		.clk(clk), 
		.load(load), 
		.clear(clear), 
		.inc(inc)
	);
	initial begin
		clk = 1'b0;
		forever #10 clk = ~clk;
	end
	initial begin

		d = 4'b0110;
		load = 1;
		clear = 0;
		inc = 0;
		
		#25;
		d = 4'b1110;
		load = 0;
		clear = 0;
		inc = 1;
		
		#40;
		d = 4'b1110;
		load = 0;
		clear = 1;
		inc = 0;
		
		#20;
		d = 4'b0001;
		load = 0;
		clear = 1;
		inc = 1;
		
		#20;
		d = 4'b0010;
		load = 1;
		clear = 1;
		inc = 0;
		
		#20;
		d = 4'b0001;
		load = 1;
		clear = 0;
		inc = 1;
		#20;
		load = 1'b0;
		#20;
		d = 4'b0001;
		load = 1;
		clear = 1;
		inc = 1;
	end
      
endmodule

