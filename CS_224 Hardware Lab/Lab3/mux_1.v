`timescale 1ns / 1ps

module mux_1( out,i0,i1,i2,i3,s0,s1
    );
	 input wire i0,i1,i2,i3,s0,s1;
	 output wire out;
	 wire a0,a1,a2,a3;
	 
	 assign a0 = i0&(~s0)&(~s1) ;
	 assign a1 = i1&(s0)&(~s1) ;
	 assign a2 = i2&(~s0)&(s1) ;
	 assign a3 = i3&(s0)&(s1) ;
	 
	 assign out = a0|a1|a2|a3 ;
	 
endmodule
