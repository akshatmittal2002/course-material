`timescale 1ns / 1ps

module mem_controller(S,reset,clk
	);
	input S,reset,clk;
	
	parameter T0 = 5'b00000;
	parameter T1 = 5'b00001;
	parameter T2 = 5'b00010;
	parameter T3 = 5'b00011;
	parameter T4 = 5'b00100;
	parameter T5 = 5'b00101;
	parameter T6 = 5'b00110;
	parameter T7 = 5'b00111;
	parameter T8 = 5'b01000;
	parameter T9 = 5'b01001;
	parameter T10 = 5'b01010;
	parameter T11 = 5'b01011;
	parameter T12 = 5'b01100;
	parameter T13 = 5'b01101;
	parameter T14 = 5'b01110;
	parameter T15 = 5'b01111;
	parameter T16 = 5'b10000;
	parameter T17 = 5'b10001;
	parameter T18 = 5'b10010;
	parameter T19 = 5'b10011;
	parameter T20 = 5'b10100;
	parameter T21 = 5'b10101;
	parameter T22 = 5'b10110;
	parameter T23 = 5'b10111;
	parameter T24 = 5'b11000;
	parameter T25 = 5'b11001;
	parameter T26 = 5'b11010;
	parameter T27 = 5'b11011;
	parameter T28 = 5'b11100;
	parameter T29 = 5'b11101;
	parameter T30 = 5'b11110;
	parameter T31 = 5'b11111;
	
	reg ss_cs, ss_we, ss_oe, rf_we; // control signals for sram and reg file
	reg [15:0] ss_data_in = 0, rf_data_in, tmp; // data in buses for sram and reg file
	wire [15:0] ss_data_out, rf_data_out; // data out buses for sram and reg file
	reg [4:0] ss_address; // address buse for sram
	reg [3:0] rf_reg_id; // address buse for reg file
	
	// alu inputs and outputs
	wire alu_cout;
	wire [15:0] alu_out;
	reg [15:0] tmp1, tmp2;
	reg [3:0] op = 0;
	
	// internal variables
	reg [4:0] curr_state, next_state;
	reg P = 0;
	reg [4:0] count, count_alu;
	reg enable, is_direct;
	
	sync_sram SS(ss_data_out, ss_data_in, ss_cs, ss_oe, ss_we, ss_address, clk);
	reg_file RF(rf_data_out, rf_data_in, rf_we, rf_reg_id, clk);
	ALU alu(alu_cout, alu_out, tmp1, tmp2, 0, op[2:0], enable);
	
	//Changing curr state
	always @ (posedge clk or posedge reset)
	begin
		if(reset) curr_state = T0;
		else curr_state = next_state;
	end
	
	// control path
	always @ (curr_state or S or P)
	begin
		case (curr_state)
			T0 : next_state = (P == 1) ? T11 : ((S == 1) ? T1 : T0);
			T1 : next_state = T2;
			T2 : next_state = T3;
			T3 : next_state = T4;
			T4 : next_state = (count == 3'b000) ? T5 : T1;
			T5 : next_state = T6;
			T6 : next_state = T7;
			T7 : next_state = T8;
			T8 : next_state = T9;
			T9 : next_state = T10;
			T10 : next_state = T11;
			T11 : next_state = T12;
			T12 : next_state = T13;
			T13 : next_state = T14;
			T14 : next_state = T15;
			T15 : next_state = T16;
			T16 : next_state = T17;
			T17 : next_state = T18;
			T18 :  next_state = (count_alu == 3'b000) ? T0 : T11;
		endcase
	end
	
	// data path
	always @(curr_state)
	begin
		case (curr_state)
			// reading and writing
			// Initialisation
			T0 : begin
				count = 6;
				count_alu = 3;
				// count_ins = 3;
				ss_address = 0;
				ss_cs = 1;
				rf_we = 1;
				rf_reg_id = 0;
				rf_data_in = 0;
				tmp1 = 0;
				tmp2 = 0;
				// if(P == 1) ss_address = ss_address + count_ins;
				// if(Q == 1) ss_address = ss_address + count;
 			end
			// read from sram
			T1 : begin
				count = count-1;
				ss_cs = 0;
				ss_we = 1;
				ss_oe = 0;
				rf_we = 1;
			end
			// write to reg file
			T2 : begin
				tmp = ss_data_out;
				rf_we = 0;
				rf_data_in = tmp;
			end
			// disable write to reg file and disable sram
			T3 : begin
				ss_cs = 1;			
				rf_we = 1;
			end
			// incrementing addresses
			T4 : begin
				ss_address = ss_address + 1;
				rf_reg_id = rf_reg_id + 1;
				P = (count == 0) ? 1 : 0;
			end
			
			// Put Instrictions in R6, R7 and R8
			T5 : begin
				tmp = 16'b0000100100000001; // R0 + R1 = R9
				rf_we = 0;
				rf_data_in = tmp;
			end
			T6 : begin
				rf_we = 1;
				rf_reg_id = rf_reg_id + 1;
			end
			T7 : begin
				tmp = 16'b0001101000100011; // R2 + R3 = R10
				rf_we = 0;
				rf_data_in = tmp;
			end
			T8 : begin
				rf_we = 1;
				rf_reg_id = rf_reg_id + 1;
			end
			T9 : begin
				tmp = 16'b1011101101000101; // R4 + 5 = R11
				rf_we = 0;
				rf_data_in = tmp;
			end
			T10 : begin
				rf_we = 1;
				rf_reg_id = rf_reg_id + 1;
			end
			
			// alu operations and writing to reg_file
			// disable ALU
			T11 : begin
				tmp1 = 0;
				tmp2 = 0;
				enable = 1;
			end
			T12 : begin
				rf_reg_id = 6 + (3 - count_alu);
			end
			// read first operand and increment address
			T13 : begin
				tmp = rf_data_out;
				rf_reg_id = {12'b000000000000,tmp[7:4]};
			end
			// read second operand and enable ALU
			T14 : begin
				tmp1 = rf_data_out;
				rf_reg_id = {12'b000000000000,tmp[3:0]};
			end
			// read second operand and enable ALU
			T15 : begin
				op = {12'b000000000000,tmp[14:12]};
				is_direct = tmp[15];
				tmp2 = (is_direct == 0) ? rf_data_out : ({12'b000000000000,tmp[3:0]});
				enable = 0;
			end
			// Write the output of ALU to sram
			T16 : begin
				rf_we = 0;
				rf_data_in = alu_out;
				rf_reg_id = {12'b000000000000,tmp[11:8]};
			end
			// disable ALU and read sram
			T17 : begin
				enable = 1;
				rf_we = 1;
			end
			// increment addresses and disable sram
			T18 : begin
				count_alu = count_alu - 1;
				P = (count_alu == 0) ? 0 : 1;
			end
		endcase
		$display($time,",  curr=%d,  ss_add=%d,  ss_in=%d,  ss_out=%d,  rf_id=%d,  rf_in=%d,  rf_out=%d,  alu_out=%d, tmp=%d, op=%d, tmp1=%d, tmp2=%d, is_direct=%d", curr_state, ss_address, ss_data_in, ss_data_out, rf_reg_id, rf_data_in, rf_data_out, alu_out, tmp, op, tmp1, tmp2, is_direct);
	end
endmodule
