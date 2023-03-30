`timescale 1ns / 1ps
// 32 memory locations
// Each loaction is 8 bit
module sync_sram(out,in,cs,oe,we,address,clk
    );
	 input[7:0] in;
	 input cs,oe,we,clk;
	 input[4:0] address;
	 output[7:0] out;
	 
	 reg[7:0] memory[0:31];
	 reg[7:0] temp_out;
	 integer i;
	 
	 assign out = temp_out;
	 
	 initial
	 begin
		for(i=0; i<32; i=i+1)
		begin
			memory[i] = (i)<<1;
		end
	 end
	 
	 always @(posedge clk)
	 begin
		temp_out = 8'bzzzzzzzz;
		if(cs == 1'b0)
		begin
			if(we == 1'b0) memory[address] = in;
			else if(oe == 1'b0) temp_out = memory[address];
		end
	end
	 
endmodule
