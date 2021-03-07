`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module c17_tb;

reg N1,N2,N3,N6,N7;
wire N22,N23;

c17 uut(.N1(N1),.N2(N2),.N3(N3),.N6(N6),.N7(N7),.N22(N22),.N23(N23));


initial begin
//00000//
N1 <= 0 ; N2 <= 0;  N3 <= 0 ; N6 <= 0 ; N7 <= 0 ;
#10
$display(" input pattern = 00000 --> golden value = 00 "); 
$display(" your answer = ", N22, N23); 
if (N22 == 1'b0 && N23 == 1'b0)
begin
	$display("You're correct1");
end

//10101//
N1 <= 1 ; N2 <= 0;  N3 <= 1 ; N6 <= 0 ; N7 <= 1 ;
#10
$display(" input pattern = 10101 --> golden value = 11 "); 
$display(" your answer = ", N22, N23); 
if (N22 == 1'b1 && N23 == 1'b1)
begin
	$display("You're correct2");
end

//01010//
N1 <= 0 ; N2 <= 1;  N3 <= 0 ; N6 <= 1 ; N7 <= 0 ;
#10
$display(" input pattern = 01010 --> golden value = 11 "); 
$display(" your answer = ", N22, N23); 
if (N22 == 1'b1 && N23 == 1'b1)
begin
	$display("You're correct3");
end

//11011//
N1 <= 1 ; N2 <= 1;  N3 <= 0 ; N6 <= 1 ; N7 <= 1 ;
#10
$display(" input pattern = 11011 --> golden value = 11 "); 
$display(" your answer = ", N22, N23); 
if (N22 == 1'b1 && N23 == 1'b1)
begin
	$display("You're correct4");
end

//11111//
N1 <= 1 ; N2 <= 1;  N3 <= 1 ; N6 <= 1 ; N7 <= 1 ;
#10
$display(" input pattern = 11111 --> golden value = 10 "); 
$display(" your answer = ", N22, N23); 
if (N22 == 1'b1 && N23 == 1'b0)
begin
	$display("You're correct5");
end

end
  
endmodule