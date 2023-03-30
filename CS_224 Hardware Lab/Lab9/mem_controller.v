`timescale 1ns / 1ps

module mem_controller(S,reset,clk
	);
	input S,reset,clk;
	
	parameter t0 = 5'b00000;
	parameter t1 = 5'b00001;
	parameter t2 = 5'b00010;
	parameter t3 = 5'b00011;
	parameter t4 = 5'b00100;
	parameter t5 = 5'b00101;
	parameter t6 = 5'b00110;
	parameter t7 = 5'b00111;
	parameter t8 = 5'b01000;
	parameter t9 = 5'b01001;
	parameter t10 = 5'b01010;
	parameter t11 = 5'b01011;
	parameter t12 = 5'b01100;
	parameter t13 = 5'b01101;
	parameter t14 = 5'b01110;
	parameter t15 = 5'b01111;
	parameter t16 = 5'b10000;
	parameter t17 = 5'b10001;
	parameter t18 = 5'b10010;
	parameter t19 = 5'b10011;
	parameter t20 = 5'b10100;
	parameter t21 = 5'b10101;
	parameter t22 = 5'b10110;
	parameter t23 = 5'b10111;
	parameter t24 = 5'b11000;
	parameter t25 = 5'b11001;
	parameter t26 = 5'b11010;
	parameter t27 = 5'b11011;
	parameter t28 = 5'b11100;
	parameter t29 = 5'b11101;
	parameter t30 = 5'b11110;
	parameter t31 = 5'b11111;
	
	reg ss_cs, ss_we, ss_oe, rf_we; // control signals for sram and reg file
	reg [7:0] ss_data_in = 0, rf_data_in, tmp; // data in buses for sram and reg file
	wire [7:0] ss_data_out, rf_data_out; // data out buses for sram and reg file
	reg [4:0] ss_address; // address buse for sram
	reg [3:0] rf_reg_id; // address buse for reg file
	
	// alu inputs and outputs
	wire alu_cout;
	wire [7:0] alu_out;
	reg [7:0] tmp1, tmp2;
	reg [2:0] op = 0;
	
	// internal variables
	reg [4:0] curr_state, next_state;
	reg P = 0;
	reg [4:0] count, count_alu;
	reg enable;
	
	sync_sram SS(ss_data_out, ss_data_in, ss_cs, ss_oe, ss_we, ss_address, clk);
	reg_file RF(rf_data_out, rf_data_in, rf_we, rf_reg_id, clk);
	ALU alu(alu_cout, alu_out, tmp1, tmp2, 0, op, enable);
	
	//Changing curr state
	always @ (posedge clk or posedge reset)
	begin
		if(reset) curr_state = t0;
		else curr_state = next_state;
	end
	
	// control path
	always @ (curr_state or S or P)
	begin
		case (curr_state)
			t0 : next_state = (P == 1) ? t10 : ((S == 1) ? t1 : t0);
			t1 : next_state = t2;
			t2 : next_state = t3;
			t3 : next_state = t4;
			t4 : next_state = t5;
			t5 : next_state = t6;
			t6 : next_state = t7;
			t7 : next_state = t8;
			t8 : next_state = t9;
			t9 : next_state = (count == 3'b000) ? t0 : t1;
			t10 : next_state = t11;
			t11 : next_state = t12;
			t12 : next_state = t13;
			t13 : next_state = t14;
			t14 : next_state = t15;
			t15 : next_state = t16;
			t16 : next_state = t17;
			t17 : next_state = t18;
			t18 : next_state = t19;
			t19 : next_state = t20;
			t20 : next_state = t21;
			t21 : next_state = t22;
			t22 : next_state = (count_alu == 3'b000) ? t0 : t10;
		endcase
	end
	
	// data path
	always @(curr_state)
	begin
		case (curr_state)
			// reading and writing
			// Initialisation
			t0: begin
				count = 7;
				count_alu = 3;
				ss_address = 0;
				ss_cs = 1;
				rf_we = 1;
				rf_reg_id = 0;
				rf_data_in = 0;
				tmp1 = 0;
				tmp2 = 0;
				if(P == 1) ss_address = ss_address + count;
			end
			// read from sram
			t2: begin
				count = count-1;
				ss_cs = 0;
				ss_we = 1;
				ss_oe = 0;
				rf_we = 1;
			end
			// write to reg file
			t4: begin
				tmp = ss_data_out;
				rf_we = 0;
				rf_data_in = tmp;
			end
			// disable write to reg file and disable sram
			t6: begin
				ss_cs = 1;			
				rf_we = 1;
			end
			// incrementing addresses
			t8: begin
				ss_address = ss_address + 1;
				rf_reg_id = rf_reg_id + 1;
				P = (count == 0) ? 1 : 0;
			end
			
			// alu operations and writing to sram
			// disable ALU
			t11: begin
				tmp1 = 0;
				tmp2 = 0;
				enable = 1;
			end
			// read first operand and increment address
			t13: begin
				tmp1 = rf_data_out;
				rf_reg_id = rf_reg_id + 1;
			end
			// read second operand and enable ALU
			t15: begin
				tmp2 = rf_data_out;
				enable = 0;
			end
			// Write the output of ALU to sram
			t17: begin
				ss_cs = 0;
				ss_we = 0;
				ss_oe=1;
				ss_data_in = alu_out;
			end
			// disable ALU and read sram
			t19: begin
				ss_cs = 0;
				ss_we = 1;
				ss_oe = 0;
				enable = 1;
			end
			// increment addresses and disable sram
			t21: begin
				ss_cs = 1;
				rf_we = 1;
				ss_address = ss_address + 1;
				rf_reg_id = rf_reg_id + 1;
				count_alu = count_alu - 1;
				op = op + 1;
				P = (count_alu == 0) ? 0 : 1;
			end
		endcase
		$display($time,",  curr=%d,  ss_add=%d,  ss_in=%d,  ss_out=%d,  rf_id=%d,  rf_in=%d,  rf_out=%d,  alu_out=%d", curr_state, ss_address, ss_data_in, ss_data_out, rf_reg_id, rf_data_in, rf_data_out, alu_out);
	end
endmodule
