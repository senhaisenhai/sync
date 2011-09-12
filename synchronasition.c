/*
 * =====================================================================================
 *
 *       Filename:  synchronasition.c
 *
 *    Description:  fork fibonnacci
 *
 *        Version:  1.0
 *        Created:  2011年09月12日 11时59分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  XaoQin (), senhaisenhai@163.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SEQUENCE 10

typedef struct{
long fib_sequence[MAX_SEQUENCE]; //max sequence
int sequcen_size;//length of fib 
}shared_data;
//calc the 'a'th fib number
int fib(int a)
{

if ( a<0 ) {
	printf( "error\n" );
	return(0);
}
else if(a==0)
{
return(0);
}
else if (a>0&&a<=2 ) {
return 1;
}
else{
return(fib(a-1)+fib(a-2));
}
}

	int
main( int argc, char **argv )
{
if(*argv[1]-'0'>=MAX_SEQUENCE) //test if the number is greater than 10
{
	printf( "argv %d\n", *argv[1]-'0' );
printf( "in put a number less than 10\n" );
}
else
{
int segment_id;//the id for the shared memory segment
shared_data* shared_para=NULL;//a pointer to the shared memory segment
segment_id=shmget(IPC_PRIVATE, sizeof(shared_data), S_IRUSR|S_IWUSR);//allocate memory
shared_para=(shared_data*)shmat(segment_id, NULL, 0);//attach memory;
shared_para->sequcen_size=*argv[1]-'0';//the length of the fib 
pid_t pid; 
pid=fork();//fork a number
if(pid==0)
{//child
//fibonnacci(shared_para->sequcen_size);
int j;
for ( j = 0; j < shared_para->sequcen_size; j++ ) {
	shared_para->fib_sequence[j]=fib(j);
}//calc the fib and write it to the shared memory
}
else if(pid>0)
{//father
wait(NULL);
int i;
for(i=0;i<shared_para->sequcen_size;i++)
{
printf( "%ld \n", shared_para->fib_sequence[i] );
}//write the fib to screen
shmdt(shared_para);//detach the shared memory segment
shmctl(segment_id, IPC_RMID, NULL); //remove the shared momory segment
}
}
return 0;
}


















