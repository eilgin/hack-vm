@JUMP_CMP_TRUE
0;JMP
(IF_CMP_TRUE)
@SP
A=M
M=-1
@R15
A=M
0;JMP
(JUMP_CMP_TRUE)
@3030
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@3
M=D
@3040
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@4
M=D
@32
D=A
@SP
AM=M+1
A=A-1
M=D
@2
D=A
@THIS
D=M+D
@R14
M=D
@SP
AM=M-1
D=M
@R14
A=M
M=D
@46
D=A
@SP
AM=M+1
A=A-1
M=D
@6
D=A
@THAT
D=M+D
@R14
M=D
@SP
AM=M-1
D=M
@R14
A=M
M=D
@3
D=M
@SP
AM=M+1
A=A-1
M=D
@4
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M+D
@2
D=A
@THIS
A=M+D
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
@6
D=A
@THAT
A=M+D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M+D