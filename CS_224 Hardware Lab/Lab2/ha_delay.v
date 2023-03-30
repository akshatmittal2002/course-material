`timescale 1ns / 1ps
module ha_delay( sum, carry, a, b
    );
	 input wire a,b;
	 output wire sum,carry;
	 and gate1(carry,a,b);
	 xor #1 gate2(sum,a,b);
endmodule

