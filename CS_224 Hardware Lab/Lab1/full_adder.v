`timescale 1ns / 1ps
module full_adder( sum, cout, a, b, cin
    );
	 input wire a,b,cin;
	 output wire sum, cout;
	 wire x,y,z;
	 half_adder h1(x,y,a,b);
	 half_adder h2(sum,z,x,cin);
	 or gate3(cout,z,y);
endmodule
