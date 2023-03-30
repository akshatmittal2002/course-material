`timescale 1ns / 1ps

module test1;

	reg S;
	reg reset;
	reg clk;

	mem_controller uut (
		.S(S), 
		.reset(reset), 
		.clk(clk)
	);
	
	initial begin
		clk = 0;
		forever #1 clk = ~clk;
	end
	
	initial begin
		reset = 1;
		S = 0;
		#4 reset = 0;
		#100 S = 1;
		#4 S = 0;
	end
      
endmodule
