`timescale 1ns / 1ps

module asm(out,curr, B,A,reset,clk,s,done
    );
	input[3:0] A,B;
	input clk,reset,s;
	output reg[3:0] out;
	output reg done;
	output reg[1:0] curr;
	
	reg[2:0] idx;
	reg[1:0] next;
	reg z;
	
	always @(*)
	begin
		z = (idx == 3'b100) ? 1 : 0;
		done = (z == 1) ? 1 : 0;
	end
	
	always @(posedge clk)
	begin
		if(reset) curr = 2'b00;
		else curr = next;
	end
	
	always @(z or s or curr)
	begin
		case(curr)
			2'b00 : next = (s == 1) ? 2'b01 : 2'b00;
			2'b01 : next = 2'b10;
			2'b10 : next = (z == 1) ? 2'b00 : 2'b11;
			2'b11 : next = (z == 1) ? 2'b00 : 2'b10;
		endcase
	end
	
	always @(*)
	begin
		case(curr)
			2'b01 : idx = 3'b000;
			2'b10 : begin out[idx] = A[idx] & B[idx]; idx = idx + 3'b001; end
			2'b11 : begin out[idx] = A[idx] | B[idx]; idx = idx + 3'b001; end
		endcase
	end
endmodule
