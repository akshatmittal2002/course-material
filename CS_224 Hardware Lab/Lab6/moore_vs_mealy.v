`timescale 1ns / 1ps

module moore_vs_mealy(reset,x,clk,y_mealy,curr_mealy,y_moore,curr_moore
    );
	 input x,clk,reset;
	 output reg y_mealy,y_moore;
	 output reg [2:0] curr_moore;
	 reg [2:0] next_moore;
	 output reg [1:0] curr_mealy;
	 reg [1:0] next_mealy;
	 
	 // Moore FSM
	 always @(posedge clk)
	 begin
		if(reset) curr_moore = 3'b000;
		else curr_moore = next_moore;
	 end
	 
	 always @(x or curr_moore)
	 begin
		case(curr_moore)
			3'b000 : next_moore = x ? 3'b001 : 3'b000;
			3'b001 : next_moore = x ? 3'b001 : 3'b010;
			3'b010 : next_moore = x ? 3'b001 : 3'b011;
			3'b011 : next_moore = x ? 3'b100 : 3'b000;
			3'b100 : next_moore = x ? 3'b001 : 3'b010;
		endcase
	 end
	 
	 always @(curr_moore)
	 begin
		y_moore = (curr_moore == 3'b100) ? 1 : 0;
	 end
	 
	 // Mealy FSM
	 always @(posedge clk)
	 begin
		if(reset) curr_mealy = 2'b00;
		else curr_mealy = next_mealy;
	 end
	 
	 always @(x or curr_mealy)
	 begin
		case(curr_mealy)
			2'b00 : if(x==1) begin next_mealy = 2'b01; y_mealy = 0; end
					  else begin next_mealy = 2'b00; y_mealy = 0; end
			2'b01 : if(x==1) begin next_mealy = 2'b01; y_mealy = 0; end
					  else begin next_mealy = 2'b10; y_mealy = 0; end
			2'b10 : if(x==1) begin next_mealy = 2'b01; y_mealy = 0; end
					  else begin next_mealy = 2'b11; y_mealy = 0; end
			2'b11 : if(x==1) begin next_mealy = 2'b01; y_mealy = 1; end
					  else begin next_mealy = 2'b00; y_mealy = 0; end
		endcase
	 end
endmodule
