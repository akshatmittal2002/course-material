`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:14:25 03/08/2022
// Design Name:   sram_chip
// Module Name:   /home/ise/Desktop/CS_224/Lab8/test1.v
// Project Name:  Lab8
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: sram_chip
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
	reg [7:0] in;
	reg cs;
	reg oe;
	reg we;
	reg [4:0] address;

	// Outputs
	wire [7:0] out;

	// Instantiate the Unit Under Test (UUT)
	sram_chip uut (
		.out(out), 
		.in(in), 
		.cs(cs), 
		.oe(oe), 
		.we(we), 
		.address(address)
	);

	initial begin
		$monitor($time," address=%d, input=%d, cs=%b, oe=%b, we=%b, output=%d",address,in,cs,oe,we,out);

		in = 8'b10010010;
		cs = 0;
		oe = 0;
		we = 1;
		address = 5'b11111;
		#10
		address = 5'b10000;
		#10
		we = 0;
		#10
		we = 1;
		#10
		address = 5'b10101;
		cs = 1;
	end
endmodule
