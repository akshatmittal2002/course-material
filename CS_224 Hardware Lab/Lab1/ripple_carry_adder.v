`timescale 1ns / 1ps
module ripple_carry_adder(sum, cout, a,b,cin
    );
	 input wire[3:0] a,b;
	 input wire cin;
	 output wire[3:0] sum;
	 output wire cout;
	 wire x,y,z;
	 full_adder f1(sum[0],x,a[0],b[0],cin);
	 full_adder f2(sum[1],y,a[1],b[1],x);
	 full_adder f3(sum[2],z,a[2],b[2],y);
	 full_adder f4(sum[3],cout,a[3],b[3],z);
endmodule
