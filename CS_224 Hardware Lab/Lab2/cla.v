`timescale 1ns / 1ps

module cla(sum,a,b,cin);
	 input wire[3:0] a,b;
	 input wire cin;
	 output wire[4:0] sum;
	 
	 wire c0,c1,c2,c3,c4;
	 wire g0,g1,g2,g3;
	 wire p0,p1,p2,p3;
	 
	 half h1(g0,p0,a[0],b[0]);
	 half h2(g1,p1,a[1],b[1]);
	 half h3(g2,p2,a[2],b[2]);
	 half h4(g3,p3,a[3],b[3]);
	 
	 assign c0 = cin;
	 assign c1 = g0|(p0&c0);
	 assign c2 = g1|(p1&c1);
	 assign c3 = g2|(p2&c2);
	 assign c4 = g3|(p3&c3);
	 
	 xor gate1(sum[0],p0,c0);
	 xor gate2(sum[1],p1,c1);
	 xor gate3(sum[2],p2,c2);
	 xor gate4(sum[3],p3,c3);
	 assign sum[4] = c4;
	 
endmodule

module half( cout,sum, a, b);
	 input wire a,b;
	 output wire sum,cout;
	 and gate1(cout,a,b);
	 xor gate2(sum,a,b);
endmodule
