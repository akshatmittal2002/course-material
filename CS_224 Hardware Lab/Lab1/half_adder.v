`timescale 1ns / 1ps
module half_adder( sum, carry, a, b
    );
	 input wire a,b;
	 output wire sum,carry;
	 and gate1(carry,a,b);
	 xor gate2(sum,a,b);
endmodule
