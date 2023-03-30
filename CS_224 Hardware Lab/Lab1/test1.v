`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:44:52 01/11/2022
// Design Name:   ripple_carry_adder
// Module Name:   /home/ise/Desktop/CS_224/Lab1/test1.v
// Project Name:  Lab1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ripple_carry_adder
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
	reg [3:0] a;
	reg [3:0] b;
	reg cin;

	// Outputs
	wire [3:0] sum;
	wire cout;

	// Instantiate the Unit Under Test (UUT)
	ripple_carry_adder uut (
		.sum(sum), 
		.cout(cout), 
		.a(a), 
		.b(b), 
		.cin(cin)
	);

	initial begin
		// Initialize Inputs
		a = 4'b1111;
		b = 4'b1111;
		cin = 1'b1;

		// Wait 100 ns for global reset to finish
		#100;
		a = 4'b1001;
		b = 4'b0111;
		cin = 1'b1;
        
		// Add stimulus here

	end
      
endmodule

