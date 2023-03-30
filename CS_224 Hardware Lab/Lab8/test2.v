`timescale 1ns / 1ps

module test2;
	reg start;
	reg reset;
	reg clk;
	wire done;
	wire [2:0] curr;
	wire [4:0] MAR;
	wire [7:0] MBR;
	mem_control uut (
		.start(start), 
		.reset(reset), 
		.clk(clk), 
		.done(done), 
		.curr(curr), 
		.MAR(MAR), 
		.MBR(MBR)
	);
	initial begin
		clk = 0;
		forever #1 clk = ~clk;
	end
	initial begin
		$monitor("Current_state=%d, MAR=%d, MBR=%d, Done=%d",curr,MAR,MBR,done);
		reset = 1;
		start = 0;
		#2 reset = 0;
		#10 start = 1;
		#300 start = 0;
	end
endmodule

