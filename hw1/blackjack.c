/* EECS 22 BlackJack      */
/* Mario Ruiz ID:46301389 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	int card, total=0, dealer_total=0, choice, x=1,ace=1 ;
	printf("***********************************\n");
	printf("** Welcome to EECS 22 BlackJack! **\n");
	printf("***********************************\n");
	
	srand(time(NULL));
	card = (rand()%13) + 1;
	card = (card > 10) ? 10:card;

	if (card == 1) 
	{
		printf("Your card is an Ace.\nWould you like its value to be 1 or 11.\n");
		scanf("%d",&ace);
		card = (ace == 11) ? 11:card;
	}
	printf("Your first card is:%d \n",card);
	printf("Do you want another card? \n");
	printf("Type 1 for Yes, 0 for No: \n");
	total = total + card;
	scanf("%d",&choice);
	
	while (choice == 1)
	{
		card = (rand() %13)+1;
		card = (card > 10) ? 10:card;
		if (card == 1)
		{
			printf("Your card is an Ace.\nWould you like its value to be 1 or 11.\n");
			scanf("%d",&ace);
			card = (ace == 11) ? 11:card;
		}
		printf("Your next card is:%d \n",card);
		total = total + card;
		printf("Your combined value is:%d \n",total);
		if (total > 21)
		{
			printf("Sorry. You lose! \n");
			x=0;
			break;
		}
		printf("Do you want another card? \n");
		printf("Type 1 for Yes, 0 for No: \n");
		scanf("%d",&choice);
	}
	while (x == 1)
	{
		card = (rand() %13)+1;
		card = (card > 10) ? 10:card;
		dealer_total = dealer_total + card;
		printf("Dealer draws another card.\n");
		printf("Dealer's card is:%d\n",card);
		printf("Dealer's value is %d, you have %d. \n",dealer_total,total);
		if (dealer_total > 21)
		{	
			printf("Dealer loses. You win! \n");
			break;
		}
		if (dealer_total >= total)
		{
			printf("Sorry. You lose! \n");
			break;
		}
	}
	return(0);
}
