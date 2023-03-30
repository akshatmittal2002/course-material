`timescale 1ns / 1ps

module ALU( ans,cout,a,b,cin,control
    );
	 input wire[3:0] a,b;
	 input wire[2:0] control;
	 input wire cin;
	 output reg[3:0] ans;
	 output reg cout;
	 
	 always @(*)
	 begin
			cout = 1'b0;
			case(control)
					3'b000 : {cout,ans} = a+b+cin ; // Add a,b,cin
					3'b001 : {cout,ans} = a-b-cin; //Subtact b from a with cin as borrow-in and cout as borrow-out.
					3'b010 : ans = a | b ; // Bitwise or of a,b
					3'b011 : ans = a & b ; // Bitwise and of a,b
					3'b100 : ans = {a[2:0] , 1'b0} ; // Left Shift
					3'b101 : ans = {1'b0 , a[3:1]} ; // Right Shift
					3'b110 : ans = {a[2:0] , a[3]} ; // Left Rotate
					3'b111 : ans = {a[0] , a[3:1]} ; // Right Rotate
			endcase
	 end
endmodule
