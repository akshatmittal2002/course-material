`timescale 1ns / 1ps

module rca_delay(sum,a,b,cin
    );
	 input wire[3:0] a,b;
	 input wire cin;
	 output wire[4:0] sum;
	 wire x,y,z;
	 fa_delay f1(sum[0],x,a[0],b[0],cin);
	 fa_delay f2(sum[1],y,a[1],b[1],x);
	 fa_delay f3(sum[2],z,a[2],b[2],y);
	 fa_delay f4(sum[3],sum[4],a[3],b[3],z);
endmodule
