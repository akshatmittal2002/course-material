`timescale 1ns / 1ps
// 16 memory locations
// Each loaction is 8 bit
module reg_file(out,in,we,reg_id,clk
    );
	 input[7:0] in;
	 input we,clk;
	 input[3:0] reg_id;
	 output[7:0] out;
	 
	 reg[7:0] memory[0:15];
	 
	 assign out = memory[reg_id];
	 
	 /*integer i;
	 initial
	 begin
		for(i=0; i<16; i=i+1)
		begin
			memory[i] = 0;
		end
	 end*/
	 
	 always @(posedge clk)
	 begin
		if(we == 1'b0) memory[reg_id] = in;
	end
	 
endmodule
