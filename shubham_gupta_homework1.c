#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void recursion(int H,int C,const char *filename);
int main(int argc, char *argv[])
{
	int H,C;
	if(argc<3 || argc>3){
		fprintf(stderr,"3 input including output command should be given");
	}
	else{
	H = atoi(argv[1]);
	C = atoi(argv[2]);
	if(H<=0 || C<=0){
		fprintf(stderr, "Wrong input argument are passed\n");
	}
	else{
	const char *filename = argv[0];
	int ind = 2*H;
		printf("%*s" "(%u): Process starting\n",ind," ",getpid());
		printf("%*s" "(%u): Parent's id = %u\n",ind," ",getpid(),getppid());
		printf("%*s" "(%u): Height in the tree = %d\n",ind," ",getpid(),H);
		printf("%*s" "(%u): Creating %d children at height %d\n",ind," ",getpid(),C,H-1);
	if(H>1)
	{	
	recursion(H-1,C,filename);	
	}
	printf("%*s" "(%u):Terminating at height %d.\n",ind," ",getpid(),H);
	}
	}
	return 0;	
}	
void recursion(int H,int C,const char *filename){
	pid_t *childpid = (pid_t *)malloc(sizeof(pid_t)*C);
	if(childpid == NULL){
	fprintf(stderr,"Could not create memory\n");
	}
	else
	{
	char h[64];	
	sprintf(h,"%d",H);
	char c[64];
	sprintf(c,"%d",C);
	for(int i=0;i<C;i++){		
		childpid[i] = fork();		
		if(childpid[i] == 0){
			if( execlp(filename,filename,h,c,
			(char *) NULL) == -1) 
		printf("(%u):Error in exec command",getpid());
		exit(-1);
	}
	 if(childpid[i] == -1){
		printf("(%u):Error in fork",getpid());
	}
	if(childpid[i] == 1){
		fprintf(stderr,"Parent in Child fork\n");
	}	
	}	
	for(int j=0;j<C;j++){
	int status;
	while(waitpid(childpid[j],&status,0) != childpid[j] || !WIFEXITED(status));
	}
	free(childpid);
	}
}

