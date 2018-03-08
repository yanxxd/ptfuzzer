#include "pt.h"

int main()
{
	int status;
	run_t run = {
        	.pid = 0,
        	.persistentPid = 0,
        	.persistentSock = -1,
        	.tmOutSignaled = false
    	};

	perf_init();
	
	pid_t pid;        //进程标识符
	pid = fork();     //创建一个新的进程
	if(pid<0)
	{
		printf("创建进程失败!");
		exit(1);
	}
	else if(pid==0)   //如果pid为0则表示当前执行的是子进程
	{
		printf("这是子进程,进程标识符是%d\n",getpid());
		
		for(int i = 1; i <= 100; i++)
		{
			printf("%d", i);
		}
		printf("\n");
		sleep(3);
		exit(0);
	}
	
	else          //否则为父进程
	{
		printf("这是父进程,进程标识符是%d\n",getpid());
		
		perf_config(pid, &run);
		
		if(waitpid(pid, &status, 0) <= 0)
		{
			perror("Error: ");
			exit(1);
		}
		
		perf_reap(&run);
		print_bitmap();
	}
	
	return 0;
}
