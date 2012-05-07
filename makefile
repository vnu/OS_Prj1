
all: Compare MyCompress MyDecompress ForkCompress PipeCompress ParFork MiniShell MoreShell DupShell ParThread 
exes = Compare MyCompress MyDecompress ForkCompress PipeCompress ParFork  MiniShell MoreShell DupShell ParThread

Compare: Compare.c osheaders.h
	g++ Compare.c -o Compare

MyCompress: MyCompress.c osheaders.h
	g++ MyCompress.c -o MyCompress
	
MyDecompress: MyDecompress.c osheaders.h
	g++ MyDecompress.c -o MyDecompress
	
ForkCompress: ForkCompress.c osheaders.h
	g++ ForkCompress.c -o ForkCompress
	
PipeCompress: PipeCompress.c osheaders.h
	g++ PipeCompress.c -o PipeCompress
	
ParFork: ParFork.c osheaders.h
	g++ ParFork.c -o ParFork
	
MiniShell: MiniShell.c osheaders.h
	g++ MiniShell.c -o MiniShell
	
MoreShell: MoreShell.c osheaders.h
	g++ MoreShell.c -o MoreShell
	
DupShell: DupShell.c osheaders.h
	g++ DupShell.c -o DupShell
	
ParThread: ParThread.c osheaders.h
	g++ ParThread.c -o ParThread -pthread


clean:
	rm $(exes)
	
	


