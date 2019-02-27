
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 08/21/2018 at 16:35
// Component: NtanGLCDB_v1_00
module NtanGLCDB_v1_00 (
	output  cs,
	output  oe,
	output [7:0] Q,
	output  rd,
	output  wr,
	input   clock,
	input   reset
);

//`#start body` -- edit after this line, do not edit this line

//        Your code goes here

localparam ST_IDLE      = 3'b000;
localparam ST_LOAD_DATA = 3'b010;
localparam ST_WRITE_1   = 3'b011;
localparam ST_WRITE_2   = 3'b001;
localparam ST_LOAD_LO   = 3'b110;
localparam ST_COUNT_LO  = 3'b111;
localparam ST_LOAD_HI   = 3'b101;
localparam ST_COUNT_HI  = 3'b100;

wire data_ready = 1'b1;
wire read_request = 1'b1;
wire z0_detect;
wire z1_detect;

reg [2:0] state;
reg cs_reg;
reg oe_reg;
reg rd_reg;
reg wr_reg;

assign cs = cs_reg;
assign oe = oe_reg;
assign rd = rd_reg;
assign wr = wr_reg;

// State machine
always @(posedge reset or posedge clock) begin
    if (reset) begin
        state <= ST_IDLE;
    end else casez (state)
        ST_IDLE: begin
            if (data_ready) begin
                state <= ST_LOAD_DATA;
            end else if (read_request) begin
                state <= ST_LOAD_LO;
            end
        end
        ST_LOAD_DATA: begin
            state <= ST_WRITE_1;
        end
        ST_WRITE_1: begin
            state <= ST_WRITE_2;
        end
        ST_WRITE_2: begin
            if (data_ready) begin
                state <= ST_LOAD_DATA;
            end else begin
                state <= ST_IDLE;
            end
        end
        ST_LOAD_LO: begin
            state <= ST_COUNT_LO;
        end
        ST_COUNT_LO: begin
            if (z0_detect) begin
                state <= ST_LOAD_HI;
            end
        end
        ST_LOAD_HI: begin
            state <= ST_COUNT_HI;
        end
        ST_COUNT_HI: begin
            if (z1_detect) begin
                state <= ST_IDLE;
            end
        end
        default: begin
            state <= ST_IDLE;
        end
    endcase
end

always @(posedge reset or posedge clock) begin
    if (reset) begin
        cs_reg <= 1'b0;
    end else casez (state)
        ST_LOAD_DATA, ST_WRITE_1,
        ST_LOAD_LO, ST_COUNT_LO: begin
            cs_reg <= 1'b1;
        end
        default: begin
            cs_reg <= 1'b0;
        end
    endcase
end

always @(posedge reset or posedge clock) begin
    if (reset) begin
        rd_reg <= 1'b0;
    end else casez (state)
        ST_LOAD_LO, ST_COUNT_LO: begin
            rd_reg <= 1'b1;
        end
        default: begin
            rd_reg <= 1'b0;
        end
    endcase
end

always @(posedge reset or posedge clock) begin
    if (reset) begin
        wr_reg <= 1'b0;
    end else casez (state)
        ST_LOAD_DATA: begin
            wr_reg <= 1'b1;
        end
        default: begin
            wr_reg <= 1'b0;
        end
    endcase
end

always @(posedge reset or posedge clock) begin
    if (reset) begin
        oe_reg <= 1'b0;
    end else casez (state)
        ST_LOAD_DATA, ST_WRITE_1: begin
            oe_reg <= 1'b1;
        end
        default: begin
            oe_reg <= 1'b0;
        end
    endcase
end



cy_psoc3_dp #(.cy_dpconfig(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0: IDLE*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1: LOAD_DATA: Load Data from F1 into A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2: WRITE_1: Drive parallel output by A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3: WRITE_2: Keep HOLD time*/
    `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4: COUNT_HI: Decrement A1 until Z1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___D1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5: LOAD_HI: Load D1 into A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6: LOAD_LO: Load D0 into A0*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7: COUNT_LO: Decrement A0 until Z0*/
    8'hFF, 8'h00,  /*CFG9:  */
    8'hFF, 8'hFF,  /*CFG11-10:  */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:  */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:  */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:  */
}
)) DP(
        /*  input                   */  .reset(reset),
        /*  input                   */  .clk(clock),
        /*  input   [02:00]         */  .cs_addr(state),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(z0_detect),
        /*  output                  */  .ff0(),
        /*  output                  */  .ce1(),
        /*  output                  */  .cl1(),
        /*  output                  */  .z1(z1_detect),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat(),
        
        /* input                    */  .ci(1'b0),     // Carry in from previous stage
        /* output                   */  .co(),         // Carry out to next stage
        /* input                    */  .sir(1'b0),    // Shift in from right side
        /* output                   */  .sor(),        // Shift out to right side
        /* input                    */  .sil(1'b0),    // Shift in from left side
        /* output                   */  .sol(),        // Shift out to left side
        /* input                    */  .msbi(1'b0),   // MSB chain in
        /* output                   */  .msbo(),       // MSB chain out
        /* input [01:00]            */  .cei(2'b0),    // Compare equal in from prev stage
        /* output [01:00]           */  .ceo(),        // Compare equal out to next stage
        /* input [01:00]            */  .cli(2'b0),    // Compare less than in from prv stage
        /* output [01:00]           */  .clo(),        // Compare less than out to next stage
        /* input [01:00]            */  .zi(2'b0),     // Zero detect in from previous stage
        /* output [01:00]           */  .zo(),         // Zero detect out to next stage
        /* input [01:00]            */  .fi(2'b0),     // 0xFF detect in from previous stage
        /* output [01:00]           */  .fo(),         // 0xFF detect out to next stage
        /* input [01:00]            */  .capi(2'b0),   // Software capture from previous stage
        /* output [01:00]           */  .capo(),       // Software capture to next stage
        /* input                    */  .cfbi(1'b0),   // CRC Feedback in from previous stage
        /* output                   */  .cfbo(),       // CRC Feedback out to next stage
        /* input [07:00]            */  .pi(8'b0),     // Parallel data port
        /* output [07:00]           */  .po(Q[7:0])    // Parallel data port
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
