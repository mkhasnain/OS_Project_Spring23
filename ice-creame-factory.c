#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/syscall.h>
#include <linux/kernel.h>

#define priceFlav_1 1.05
#define priceFlav_2 2.00
#define priceFlav_3 1.67
#define priceTopp_1 0.8
#define priceTopp_2 0.5

int ticket = 30, _flavors[30] = {29, 34, 18}, _toppings[2] = {20, 34};
double revenue = 0.0;

sem_t ticketC, flavorC, f1, f2, f3, toppingC, t1, t2, paymentC;

void *iceCream(void *_id);

int main()
{
	int noC;
	printf("\n\nEnter Number of Customers [1-%d]: ",ticket);
	scanf("%d", &noC);
	printf("\n\n");

	if(noC > ticket || noC <= 0){
		printf("\n\nInvalid Input\n\n");
		return 0;
	}	
	int _id[noC];	
	for(int i=0; i<noC; i++){
		_id[i] = i+100;
	}
	
	sem_init(&ticketc,0, 1);

	sem_init(&flavorC, 0, 3);
	sem_init(&f1, 0, 1);
	sem_init(&f2, 0, 1);
	sem_init(&f3, 0, 1);

	sem_init(&toppingC, 0, 2);
	sem_init(&t1, 0, 1);
	sem_init(&t2, 0, 1);

	sem_init(&paymentC, 0, 1);
	pthread_t _customer [noC];

	for(int i=0; i<noC; i++){
		pthread_create(&_customer[i], 0, &iceCream, (void*) &_id[i]);
	}
	
	for(int i=0; i<noC; i++){
		pthread_join(_customer[i], NULL);
	}

	printf("\n\nBusiness Journal - At Closing\n\n");
	printf("Number of Customers: %d", noC);
	printf("\nRevenue Generated: $ %f", revenue);
	printf("\nTickets Remaining: %d\n\n", ticket);

	sem_destroy(&ticketc);

	sem_destroy(&flavorC);
	sem_destroy(&f1);
	sem_destroy(&f2);
	sem_destroy(&f3);

	sem_destroy(&toppingC);
	sem_destroy(&t1);
	sem_destroy(&t2);

	sem_destroy(&paymentc);
	return 0;
}

void *iceCream(void *_id){
	int _ID = (int)_id, checkRaceCond_1 = 0; 
	double bill = 0.0;

	sem_wait(&ticketc);

	if(ticket <= 0)	{
		printf("\nCustomer [%d]: Leaving Shop. [REASON]: Tickets Finished\n", _ID);
		syscall (335, "Leaving Shop. [REASON]: Tickets Finished\n",_ID);
		sleep (1);
		pthread_exit(NULL);
	}
	ticket--;

	printf("Customer [%d] Got Ticket.\n", _ID);
	syscall (335, "Got Ticket.\n",_ID);

	sem_post(&ticketc);
	sleep (2);

	sem_wait(&flavorC);

	if(_flavors[0] <= 0 && _flavors[1] <= 0 && _flavors[2] <= 0){
		syscall (335, "Leaving Shop. [REASON]: Flavours Finished\n", __ID);
		sleep (1);
		pthread_exit (NULL);
	}
	else{
		sem_wait(&f1);

		if(_flavors [0] > 0){
			_flavors [0]--;
			checkRaceCond_1++;
			bill = bill+ priceFlav_1;
			printf("\nCustomer [%d]: Got Flavour [0].\n", _ID);
			syscall(335, "Got Flavour [0].\n",_ID);"
			sleep (1);
		}

		sem_post(&f1);
		sem_wait(&f2);

		if(_flavors [1] > 0){
			_flavors[1]--
			checkRaceCond_1++;
			bill = bill + priceFlav_2;
			printf("Customer[%d]: Got Flavour [1].\n", _ID);
			syscall(335, "Got Flavour [1].\n",_ID);
			sleep(1);
		}

		sem_post(&f2);
		sem_wait(&f3);

		if(_flavors [2] > 0){
			_flavors[2]--;
			checkRaceCond_1++;
			bill = bill + priceFlav_3;
			printf("Customer [%d]: Got Flavour [2].\n", _ID);
			syscall(335, "Got Flavour [2].\n",_ID);
			sleep(1);
		}

		sem_post(&f3);
		if (checkRaceCond_1 == 0){		
			printf("\nCustomer [%d]: Leaving Shop. [REASON]: Flavours Finished\n", _ID);
			syscall(335, "Leaving Shop. [REASON]: Flavours Finished\n",_ID);
			sleep(1);
			pthread_exit(NULL);
		}
	}

	printf("\nCustomer [%d]: Got Flavour(s). Leaving Flavor Counter\n", _ID);
	syscall(335, "Got Flavour(s). Leaving Flavor Counter\n", _ID);

	sem_post(&flavorC);
	sem_wait(&toppingC);
	sem_wait(&t1);

	if(_toppings [0] > 0){		
		_toppings [0]--;
		bill = bill + priceTopp_1;
	}

	sem_post(&t1);
	sem_wait(&t2);

	if(_toppings [1] > 0){
		_toppings [1]--;
		bill = bill + priceTopp_2;
	}

	sem_post(&t2);
	printf("\nCustomer [%d]: Leaving Topping Counter.\n", _ID);
	syscall(335, "Leaving Topping Counter.\n",_ID);

	sem_post(&toppingC);
	sleep(2);
	sem_wait(&payment();
	revenue = revenue + bill;

	printf("\nCustomer[%d]: Billed: $ %f.\n", _ID, bill);
	char a[100];
	sprintf(a, "Billed: $ %f.\n",bill);
	syscall(335,a,_ID);

	sem_post(&paymentC();

	sleep(2);

	printf("\nCustomer [%d]: Leaving Ice-Cream Shop.\n\n", _ID);
	syscall(335, "Leaving Ice-Cream Shop.\n\n",_ID);

	return NULL;
}
