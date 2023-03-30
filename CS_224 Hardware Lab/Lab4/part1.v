`timescale 1ns / 1ps

module part1(a,clk,q0,q1,q2
    );
	 input a,clk;
	 output reg q0,q1,q2;
	 always @(posedge clk)
	 begin
		q0 <= a;
		q1 <= q0;
		q2 <= q1;
	 end
endmodule
