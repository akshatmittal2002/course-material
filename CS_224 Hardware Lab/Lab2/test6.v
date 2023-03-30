`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:53:53 01/18/2022
// Design Name:   cla
// Module Name:   /home/ise/Desktop/CS_224/Lab2/test6.v
// Project Name:  Lab2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: cla
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test6;

	// Inputs
	reg [3:0] a;
	reg [3:0] b;
	reg cin;

	// Outputs
	wire [4:0] sum;

	// Instantiate the Unit Under Test (UUT)
	cla uut (
		.sum(sum), 
		.a(a), 
		.b(b), 
		.cin(cin)
	);

	initial begin
	$monitor ("\n\ta = %b [%d],  b = %b [%d],  cin = %b,  sum = %b [%d]",a,a,b,b,cin,sum,sum);
		// Initialize Inputs
		a = 4'b0000;
		b = 4'b0000;
		cin = 0;

		// Wait 100 ns for global reset to finish
		#100;
		
		a = 4'b0110;
		b = 4'b1100;
		cin = 1;
		
		#100;
		
		a = 4'b1101;
		b = 4'b0011;
		cin = 0;
		
		#100;
		
		a = 4'b1111;
		b = 4'b1111;
		cin = 1;
	end
      
endmodule

