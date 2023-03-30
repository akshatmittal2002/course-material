`timescale 1ns / 1ps

module fa_delay( sum, cout, a, b, cin
    );
	 input wire a,b,cin;
	 output wire sum, cout;
	 assign #2 cout = (a&b)|(b&cin)|(cin&a);
	 assign #2 sum = a^b^cin;
endmodule
