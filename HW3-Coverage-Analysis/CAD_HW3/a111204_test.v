module test;

reg[7:0] in;
reg clk,reset;
wire[7:0] out;

initial begin
	clk=0;
	forever
    #5 clk = !clk;
end

initial begin
    $dumpfile("cpu.vcd");
    $dumpvars;	
end

cpu cc(.in(in), .clk(clk), .reset(reset), .out(out));

initial begin
	in    =8'b00000000;
	reset =1'b1;

//write your test pattern----------------

#20 in    =8'b01100111;     //input RegA 0111
	reset =1'b0;

#20 in    =8'b01101000;     //input RegA 0111
	reset =1'b0;

#20 in    =8'b01110001;     //input RegB 0001
	reset =1'b0;

#20 in    =8'b01111110;     //input RegB 0001
	reset =1'b0;

#20 in    =8'b00000000;     //C = A + B
    reset =1'b0;
    
#20 in    =8'b00010000;     //C = A - B
    reset =1'b0;

#20 in    =8'b00100000;     //C = A + 1
    reset =1'b0;
    
#20 in    =8'b00110000;     //C = A - 1
    reset =1'b0;
    
#20 in    =8'b01000000;     //C = A + B + 1
    reset =1'b0;
    
// --- above ALU --- 

#20 in    =8'b11100000;     // B = C
    reset =1'b0;

#20 in    =8'b01011111;     //C = -A
    reset =1'b0;

#20 in    =8'b10011111; // Storage C
    reset =1'b0;

#20 in    =8'b10101111; // Load C
    reset =1'b0;

#20 in    =8'b00110000;     //C = A - 1
    reset =1'b0;

#20 in    =8'b10011111; // Storage C
    reset =1'b0;

#20 in    =8'b10101111; // Load C
    reset =1'b0;

#20 in    =8'b01011111;     //C = -A
    reset =1'b0;

#20 in    =8'b10011111; // Storage C
    reset =1'b0;

#20 in    =8'b10101111; // Load C
    reset =1'b0;

// ---

#20 in    =8'b00000000;
    reset =1'b1;

#20 in    =8'b00110000;     //C = A - 1
    reset =1'b0;
#20 in    =8'b11010000; // A = C
    reset =1'b0;
#20 in    =8'b01011111;     //C = -A
    reset =1'b0;
#20 in    =8'b11010000; // A = C
    reset =1'b0;

#20 in    =8'b10001111; // memory
    reset =1'b0;

// ---
    
#20 in    =8'b10111111; // Output C
    reset =1'b0;

#20 in    =8'b11001111; // Output Mem
    reset =1'b0;

#20 in    =8'b00000000; 
    reset =1'b0;

#20 in    =8'b11001111; // Output Mem
    reset =1'b0;

#20 in    =8'b00000000; 
    reset =1'b1;
// ---

#20 in    =8'b11111111;
    reset =1'b0;

//----------------------------------------
#10  $finish;

end
endmodule
