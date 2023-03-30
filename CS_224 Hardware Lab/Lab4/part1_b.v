`timescale 1ns / 1ps

module part1_b(a,clk,q0,q1,q2
    );
	 input a,clk;
	 output reg q0,q1,q2;
	 always @(posedge clk)
	 begin
		q2 = q1;
		q1 = q0;
		q0 = a;
	 end
endmodule
