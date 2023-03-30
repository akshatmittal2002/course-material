`timescale 1ns / 1ps

module register_4bit(q,d,clk,load,clear
    );
	 input clk,load,clear;
	 input[3:0] d;
	 output reg[3:0] q;
	 always @(posedge clk)
	 begin
		q = clear ? 0 :
				load ? d :
					q ;
	 end
endmodule
