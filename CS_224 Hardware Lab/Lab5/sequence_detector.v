`timescale 1ns / 1ps

module sequence_detector(x,reset,clk,y
    );
	 input x,clk,reset;
	 output reg y;
	 reg [1:0] curr, next;

	 always @(posedge clk)
	 begin
		if(reset) curr = 2'b00;
		else curr = next;
	 end
	 
	 always @(x or curr)
	 begin
		case(curr)
			2'b00 : next = x ? 2'b01 : 2'b00;
			2'b01 : next = x ? 2'b01 : 2'b10;
			2'b10 : next = x ? 2'b01 : 2'b11;
			2'b11 : next = x ? 2'b01 : 2'b00;
		endcase
	 end
	 
	 always @(curr)
	 begin
		case(curr)
			2'b00 : y = 0;
			2'b01 : y = 0;
			2'b10 : y = 0;
			2'b11 : y = 1;
		endcase
	 end

endmodule
