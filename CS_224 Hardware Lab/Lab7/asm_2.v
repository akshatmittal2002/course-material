`timescale 1ns / 1ps

module asm_2(out,curr, B,A,reset,clk,s,done
    );
	input[3:0] A,B;
	input clk,reset,s;
	output reg[3:0] out;
	output reg done;
	output reg[2:0] curr;
	
	reg[2:0] idx, next;
	reg z;
	
	always @(*)
	begin
		z = (idx == 3'b100) ? 1 : 0;
		done = (curr == 3'b111) ? 1 : 0;
	end
	
	always @(posedge clk)
	begin
		if(reset) curr = 3'b000;
		else curr = next;
	end
	
	always @(z or s or curr)
	begin
		case(curr)
			3'b000 : next = (s == 1) ? 3'b001 : 3'b000;
			3'b001 : next = 3'b010;
			3'b010 : next = 3'b011;
			3'b011 : next = (z == 0) ? 3'b100 : 3'b111;
			3'b100 : next = 3'b101;
			3'b101 : next = (z == 0) ? 3'b110 : 3'b111;
			3'b110 : next = 3'b010;
			3'b111 : next = 3'b000;
		endcase
	end
	
	always @(*)
	begin
		case(curr)
			3'b001 : idx = 3'b000;
			3'b010 : out[idx] = A[idx] & B[idx];
			3'b011 : idx = idx + 3'b001;
			3'b100 : out[idx] = A[idx] | B[idx];
			3'b101 : idx = idx + 3'b001;
		endcase
	end
endmodule
