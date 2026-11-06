#include <stdio.h>

#define CACHE_SIZE 4

int cache[CACHE_SIZE];
int refBit[CACHE_SIZE];
int hand = 0;

void displayCache()
{
    int i;
    printf("Cache: ");
    for(i = 0; i < CACHE_SIZE; i++)
    {
        if(cache[i] == -1)
            printf("- ");
        else
            printf("%d ", cache[i]);
    }
    printf("\n");
}

int search(int page)
{
    int i;
    for(i = 0; i < CACHE_SIZE; i++)
    {
        if(cache[i] == page)
            return i;
    }
    return -1;
}

void secondChance(int page)
{
    int pos = search(page);

    if(pos != -1)
    {
        printf("Page %d -> HIT\n", page);
        refBit[pos] = 1;
        return;
    }

    printf("Page %d -> MISS\n", page);

    while(1)
    {
        if(cache[hand] == -1)
        {
            cache[hand] = page;
            refBit[hand] = 1;
            hand = (hand + 1) % CACHE_SIZE;
            break;
        }

        if(refBit[hand] == 0)
        {
            cache[hand] = page;
            refBit[hand] = 1;
            hand = (hand + 1) % CACHE_SIZE;
            break;
        }

        refBit[hand] = 0;
        hand = (hand + 1) % CACHE_SIZE;
    }
}

int main()
{
    int i;
    int hits = 0, misses = 0;

    int pages[] = {1,2,3,1,4,5,1,2,6,3,7};
    int n = sizeof(pages)/sizeof(pages[0]);

    for(i = 0; i < CACHE_SIZE; i++)
    {
        cache[i] = -1;
        refBit[i] = 0;
    }

    printf("Second Chance Cache Management\n\n");

    for(i = 0; i < n; i++)
    {
        if(search(pages[i]) != -1)
            hits++;
        else
            misses++;

        secondChance(pages[i]);
        displayCache();
        printf("\n");
        }
        printf("Hits   : %d\n", hits);
    printf("Misses : %d\n", misses);
    printf("Hit Ratio = %.2f%%\n", (hits * 100.0) / (hits + misses));

    return 0;
}

