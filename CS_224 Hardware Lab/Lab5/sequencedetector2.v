`timescale 1ns / 1ps

module sequencedetector2(x,clk,reset,y,curr
    );
	 input x,clk,reset;
	 output reg y;
	 output reg [2:0] curr;
	 reg [2:0] next;
	 always @(posedge clk)
	 begin
		if(reset) curr = 3'b000; // Start State
		else curr = next;
	 end
	 
	 always @(x or curr)
	 begin
		case(curr)
			3'b000 : next = x ? 3'b001 : 3'b000;
			3'b001 : next = x ? 3'b001 : 3'b010;
			3'b010 : next = x ? 3'b011 : 3'b000;
			3'b011 : next = x ? 3'b001 : 3'b100;
			3'b100 : next = x ? 3'b101 : 3'b000;
			3'b101 : next = x ? 3'b001 : 3'b100; // Final State
		endcase
	 end
	 
	 always @(curr)
	 begin
		y = (curr == 3'b101) ? 1 : 0;
	 end


endmodule
