`timescale 1ns / 1ps

module mealy_vs_delayed(reset,x,clk,y_mealy,curr_mealy,y_delay,curr_delay
    );
	 input x,clk,reset;
	 output reg y_mealy,y_delay;
	 output reg [1:0] curr_mealy,curr_delay;
	 reg [1:0] next_mealy,next_delay;
	 
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
	 
	 // Delayed Mealy FSM
	 always @(posedge clk)
	 begin
		if(reset) curr_delay = 2'b00;
		else curr_delay = next_delay;
	 end
	 
	 always @(x or curr_delay)
	 begin
		case(curr_delay)
			2'b00 : if(x==1) begin next_delay = 2'b01; #2 y_delay = 0; end
					  else begin next_delay = 2'b00; #2 y_delay = 0; end
			2'b01 : if(x==1) begin next_delay = 2'b01; #2 y_delay = 0; end
					  else begin next_delay = 2'b10; #2 y_delay = 0; end
			2'b10 : if(x==1) begin next_delay = 2'b01; #2 y_delay = 0; end
					  else begin next_delay = 2'b11; #2 y_delay = 0; end
			2'b11 : if(x==1) begin next_delay = 2'b01; #2 y_delay = 1; end
					  else begin next_delay = 2'b00; #2 y_delay = 0; end
		endcase
	 end
endmodule
