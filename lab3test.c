#include "types.h"
#include "user.h"
int thread_increment = 0;
void kthread(int *a, char*b){
	printf(1,"Inside thread %d, value passed in is %d and string %s\n", getpid(), *a, b);
	exit();
}
void Lockthread(lock_t *lock, int *a){
	lock_acquire(lock);
	int i, temp;
	temp=thread_increment;
	printf(1,"Thread %d locked. Incrementing global variable by %d...\n", getpid(), *a);
	for(i=0; i<*a; i++)
		thread_increment+=1;
	printf(1,"Done. Global variable was %d now %d. Unlocking...\n", temp, thread_increment);
	lock_release(lock);
	exit();
}
int main(){
	int a=5, i1=100, i2=1000;
	char *b = "Mmmm... Milk";
	lock_t lock;
	printf(1,"Createing new thread, passing in %d and %s\n", a, b);
	thread_create((void (*)(void *, void *))kthread, &a, b);
	printf(1,"Join returned %d\nCreating two new threads and locking them...\n", thread_join());
	lock_init(&lock);
	thread_create((void (*)(void *, void *))Lockthread, &lock, &i1);
	thread_create((void (*)(void *, void *))Lockthread, &lock, &i2);
	i1=thread_join();
	i2=thread_join();
	printf(1,"Join returned %d\n", i1);
	printf(1,"Join returned %d\n", i2);
	exit();
}

