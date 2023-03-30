`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:19:12 01/25/2022
// Design Name:   ALU
// Module Name:   /home/ise/Desktop/CS_224/Lab3/test_3.v
// Project Name:  Lab3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ALU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_3;

	// Inputs
	reg [3:0] a;
	reg [3:0] b;
	reg cin;
	reg [2:0] control;

	// Outputs
	wire [3:0] ans;
	wire cout;

	// Instantiate the Unit Under Test (UUT)
	ALU uut (
		.ans(ans), 
		.cout(cout), 
		.a(a), 
		.b(b), 
		.cin(cin), 
		.control(control)
	);

	initial begin
	$monitor("\ta=%b,  b=%b,  cin=%b,  control=%b,  ans=%b,  cout=%b\n",a,b,cin,control,ans,cout);
		// Initialize Inputs
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b1;
		control = 3'b000;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b1;
		control = 3'b001;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b0;
		control = 3'b010;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b0;
		control = 3'b011;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b0;
		control = 3'b100;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b0;
		control = 3'b101;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b0;
		control = 3'b110;
		#100;
		
		a = 4'b0110;
		b = 4'b1010;
		cin = 1'b0;
		control = 3'b111;
		#100;
        
		// Add stimulus here

	end
      
endmodule

