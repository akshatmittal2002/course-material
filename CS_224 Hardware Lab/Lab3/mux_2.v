`timescale 1ns / 1ps

module mux_2( out,i0,i1,i2,i3,s0,s1
    );
	 input wire i0,i1,i2,i3,s0,s1;
	 output reg out;
	 always @(*)
	 begin
			out = (~s0 & ~s1) ? i0 :
						(s0 & ~s1) ? i1 :
							(~s0 & s1) ? i2 : i3 ;
	 end
endmodule
