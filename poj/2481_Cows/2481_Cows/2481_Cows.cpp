// 2481_Cows.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <algorithm>

#define MAX_N 100005
int n, s, e;

struct Node
{
    int s;
    int e;
    int index;
    int num;
    int result;
};

Node cows[MAX_N];

bool operator < (const Node& first, const Node& second)
{
    if (first.e > second.e)
        return true;
    if (first.e < second.e)
        return false;
    return first.s < second.s;
}

// compare index
bool cmp(const Node& first, const Node& second)
{
    return first.index < second.index;
}

int lowbit(int x)
{
    return x & (-x);
}

void update(int idx)
{
    while (idx <= MAX_N)
    {
        cows[idx].num++;
        idx += lowbit(idx);
    }
}

int sum(int idx)
{
    int _sum = 0;
    while (idx > 0)
    {
        _sum += cows[idx].num;
        idx -= lowbit(idx);
    }
    return _sum;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    while (scanf("%d", &n) != EOF)
    {
        if (n == 0)
            break;

        memset(cows, 0, sizeof(cows));

        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &s, &e);
            cows[i].s = s + 1;
            cows[i].e = e + 1;
            cows[i].index = i;
            cows[i].num = 0;
            cows[i].result = 0;
        }

        std::sort(cows, cows + n);

        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                update(cows[i].s);
            }
            else if (cows[i - 1].s == cows[i].s && cows[i - 1].e == cows[i].e)
            {
                cows[i].result = cows[i - 1].result;
                update(cows[i].s);
            }
            else
            {
                cows[i].result = sum(cows[i].s);
                update(cows[i].s);
            }
        }

        std::sort(cows, cows + n, cmp);
        for (int i = 0; i < n; i++)
        {
            if (i != 0)
            {
                printf(" ");
            }
            printf("%d", cows[i].result);
        }
        printf("\n");
    }
    
	return 0;
}

