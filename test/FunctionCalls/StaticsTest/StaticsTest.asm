@256
D=A
@SP
M=D
@RET_CALL_0
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@SP
AM=M+1
A=A-1
M=D
@ARG
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@SP
AM=M+1
A=A-1
M=D
@0
D=A
@SP
D=M-D
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
(RET_CALL_0)
(IF_CMP_TRUE)
@SP
A=M
M=-1
@R15
A=M
0;JMP
(Class1.set)
@0
D=A
(LOOP_Class1.set)
D=D-1
@SP
AM=M+1
A=A-1
M=0
@LOOP_Class1.set
D;JGT
@SP
M=M-1
@0
D=A
@ARG
A=M+D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@Class1.0
M=D
@1
D=A
@ARG
A=M+D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@Class1.1
M=D
@0
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@R13
M=D
@5
D=A
@R13
A=M-D
D=M
@R14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@R13
A=M-1
D=M
@THAT
M=D
@2
D=A
@R13
A=M-D
D=M
@THIS
M=D
@3
D=A
@R13
A=M-D
D=M
@ARG
M=D
@4
D=A
@R13
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP
(Class1.get)
@0
D=A
(LOOP_Class1.get)
D=D-1
@SP
AM=M+1
A=A-1
M=0
@LOOP_Class1.get
D;JGT
@SP
M=M-1
@Class1.0
D=M
@SP
AM=M+1
A=A-1
M=D
@Class1.1
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@LCL
D=M
@R13
M=D
@5
D=A
@R13
A=M-D
D=M
@R14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@R13
A=M-1
D=M
@THAT
M=D
@2
D=A
@R13
A=M-D
D=M
@THIS
M=D
@3
D=A
@R13
A=M-D
D=M
@ARG
M=D
@4
D=A
@R13
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP
(Class2.set)
@0
D=A
(LOOP_Class2.set)
D=D-1
@SP
AM=M+1
A=A-1
M=0
@LOOP_Class2.set
D;JGT
@SP
M=M-1
@0
D=A
@ARG
A=M+D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@Class2.0
M=D
@1
D=A
@ARG
A=M+D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@Class2.1
M=D
@0
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@R13
M=D
@5
D=A
@R13
A=M-D
D=M
@R14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@R13
A=M-1
D=M
@THAT
M=D
@2
D=A
@R13
A=M-D
D=M
@THIS
M=D
@3
D=A
@R13
A=M-D
D=M
@ARG
M=D
@4
D=A
@R13
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP
(Class2.get)
@0
D=A
(LOOP_Class2.get)
D=D-1
@SP
AM=M+1
A=A-1
M=0
@LOOP_Class2.get
D;JGT
@SP
M=M-1
@Class2.0
D=M
@SP
AM=M+1
A=A-1
M=D
@Class2.1
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@LCL
D=M
@R13
M=D
@5
D=A
@R13
A=M-D
D=M
@R14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@R13
A=M-1
D=M
@THAT
M=D
@2
D=A
@R13
A=M-D
D=M
@THIS
M=D
@3
D=A
@R13
A=M-D
D=M
@ARG
M=D
@4
D=A
@R13
A=M-D
D=M
@LCL
M=D
@R14
A=M
0;JMP
(Sys.init)
@0
D=A
(LOOP_Sys.init)
D=D-1
@SP
AM=M+1
A=A-1
M=0
@LOOP_Sys.init
D;JGT
@SP
M=M-1
@6
D=A
@SP
AM=M+1
A=A-1
M=D
@8
D=A
@SP
AM=M+1
A=A-1
M=D
@RET_CALL_1
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@SP
AM=M+1
A=A-1
M=D
@ARG
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@SP
AM=M+1
A=A-1
M=D
@2
D=A
@SP
D=M-D
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class1.set
0;JMP
(RET_CALL_1)
@SP
AM=M-1
D=M
@5
M=D
@23
D=A
@SP
AM=M+1
A=A-1
M=D
@15
D=A
@SP
AM=M+1
A=A-1
M=D
@RET_CALL_2
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@SP
AM=M+1
A=A-1
M=D
@ARG
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@SP
AM=M+1
A=A-1
M=D
@2
D=A
@SP
D=M-D
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class2.set
0;JMP
(RET_CALL_2)
@SP
AM=M-1
D=M
@5
M=D
@RET_CALL_3
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@SP
AM=M+1
A=A-1
M=D
@ARG
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@SP
AM=M+1
A=A-1
M=D
@0
D=A
@SP
D=M-D
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class1.get
0;JMP
(RET_CALL_3)
@RET_CALL_4
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL
D=M
@SP
AM=M+1
A=A-1
M=D
@ARG
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT
D=M
@SP
AM=M+1
A=A-1
M=D
@0
D=A
@SP
D=M-D
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class2.get
0;JMP
(RET_CALL_4)
(Sys.init$WHILE)
@Sys.init$WHILE
0;JMP
