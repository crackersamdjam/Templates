#include <sys/resource.h>
#include <bits/stdc++.h>

int main(){
	const rlim_t kStackSize = 1024 * 1024 * 1024;   // min stack size = 1024 MB = 1 GB
	struct rlimit rl;
	int result = getrlimit(RLIMIT_STACK, &rl);
	if(result == 0){
		if(rl.rlim_cur < kStackSize){
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if(result != 0){
				fprintf(stderr, "setrlimit returned result = %d\n", result);
			}
		}
	}
}
/*
 https://stackoverflow.com/questions/2275550/change-stack-size-for-a-c-application-in-linux-during-compilation-with-gnu-com/2284691#2284691
 Note: even when using this method to increase stack size you should not declare large local variables in main() itself,
 since you may well get a stack overflow as soon as you enter main(),
 before the getrlimit/setrlimit code has had a chance to change the stack size.
 Any large local variables should therefore be defined only in functions which are subsequently called from main(),
 after the stack size has successfully been increased.
 
 Or: In a new terminal, enter `ulimit -s 1024000` and then run executable
 */