`timescale 1ns / 1ps
// 16 memory locations
// Each loaction is 16 bit
module reg_file(out,in,we,reg_id,clk
    );
	 input[15:0] in;
	 input we,clk;
	 input[3:0] reg_id;
	 output[15:0] out;
	 
	 reg[15:0] memory[0:15];
	 
	 assign out = memory[reg_id];
	 
	 always @(negedge clk)
	 begin
		if(we == 1'b0) memory[reg_id] = in;
	end
	 
endmodule
