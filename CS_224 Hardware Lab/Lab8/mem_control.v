`timescale 1ns / 1ps

module mem_control(start,reset,clk,done,curr,MAR,MBR
    );
	input clk,reset,start;
	output reg done;
	output reg[2:0] curr;
	
	reg[2:0] next;
	reg z,cs,we,oe;
	output reg[5:0] MAR;
	output reg[7:0] MBR;
	
	wire[7:0] temp_in,temp_out;
	assign temp_in = MBR;
	
	sram_chip SC(temp_out,temp_in,cs,oe,we,MAR[4:0]);
	
	always @(*)
	begin
		z = (MAR > 5'b11111) ? 1 : 0;
		done = (curr == 3'b101) ? 1 : 0;
	end
	
	always @(posedge clk)
	begin
		if(reset) curr = 3'b000;
		else curr = next;
	end
	
	always @(z or start or curr)
	begin
		case(curr)
			3'b000 : next = (start == 1) ? 3'b001 : 3'b000;
			3'b001 : next = 3'b010;
			3'b010 : next = 3'b011;
			3'b011 : next = 3'b100;
			3'b100 : next = (z == 1) ? 3'b101 : 3'b001;
			3'b101 : next = 3'b000;
		endcase
	end
	
	always @(*)
	begin
		case(curr)
			3'b000 : begin
				MAR = 0;
				MBR = 100;
				cs = 1;
				oe = 1;
				we = 1;
			end
			3'b001 : begin
				cs = 0;
				oe = 0;
				we = 1;
				MBR = temp_out;
			end
			3'b010 : begin
				MBR = MBR + 1;
			end
			3'b011 : begin
				cs = 0;
				oe = 1;
				we = 0;
			end
			3'b100 : begin
				cs = 1;
				MAR = MAR + 1;
			end
		endcase
	end
endmodule
