`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:28:51 01/18/2022
// Design Name:   rca_delay
// Module Name:   /home/ise/Desktop/CS_224/Lab2/test2.v
// Project Name:  Lab2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: rca_delay
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
	reg [3:0] a;
	reg [3:0] b;
	reg cin;

	// Outputs
	wire [4:0] sum;

	// Instantiate the Unit Under Test (UUT)
	rca_delay uut (
		.sum(sum), 
		.a(a), 
		.b(b), 
		.cin(cin)
	);

	initial begin
	$monitor ($time,",  a = %b,  b = %b,  cin = %b,  sum = %b\n",a,b,cin,sum);
	
		a = 4'b0000;
		b = 4'b0000;
		cin = 0;

		#20;
		
		a = 4'b0001;
		b = 4'b0001;
		cin = 0;

	end
      
endmodule

