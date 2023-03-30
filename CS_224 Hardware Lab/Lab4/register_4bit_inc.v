`timescale 1ns / 1ps

module register_4bit_inc(q,d,clk,load,clear,inc
    );
	 input clk,load,clear,inc;
	 input[3:0] d;
	 output reg[3:0] q;
	 always @(posedge clk)
	 begin
		q = clear ? 0 :
				load ? d :
					(inc ? (q+1) : q);
	 end
endmodule
