
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
// Generated on 08/21/2018 at 14:19
// Component: NtanGLCDB_v1_00
module NtanGLCDB_v1_00 (
	output  cs,
	output  oe,
	output [7:0] Q,
	output  rd,
	output  wr,
	input   clock
);

//`#start body` -- edit after this line, do not edit this line

//        Your code goes here
assign cs = 1'b0;
assign oe = 1'b0;
assign rd = 1'b0;
assign wr = 1'b0;
assign Q[7:0] = 8'b00000000;

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
