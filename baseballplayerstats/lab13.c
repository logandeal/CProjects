#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "basicplayer.h"

struct playerstats
{
    double atbats;
    double walks;
    double singles;
    double doubles;
    double triples;
    double homeruns;
    double battingavg;
    double onbpct;
    double slugpct;
    char name[16];
};
struct playerstats stats;
struct playerstats* statslist;
int playercount = 0;

void pad(int pad,char*string)
{
    int padding = pad-strlen(string);
    for(int i=1;i<=padding;i++)
    {
        putchar(' ');
    }
    printf("%s ",string);
}

void GetAllStats(BasicPlayer player)
{
    stats.atbats = GetStat(player.id,ATBATS);
    stats.walks = GetStat(player.id,WALKS);
    stats.singles = GetStat(player.id,SINGLES);
    stats.doubles = GetStat(player.id,DOUBLES);
    stats.triples = GetStat(player.id,TRIPLES);
    stats.homeruns = GetStat(player.id,HOMERUNS);
    strcpy(stats.name,player.name);
    
    stats.battingavg = (stats.singles + stats.doubles + stats.triples + stats.homeruns)/(stats.atbats);
    stats.onbpct = (stats.singles + stats.doubles + stats.triples + stats.homeruns + stats.walks)/(stats.atbats + stats.walks);
    stats.slugpct = (stats.singles + 2*stats.doubles + 3*stats.triples + 4*stats.homeruns)/(stats.atbats);

    statslist[playercount].atbats = stats.atbats;
    statslist[playercount].walks = stats.walks;
    statslist[playercount].singles = stats.singles;
    statslist[playercount].doubles = stats.doubles;
    statslist[playercount].triples = stats.triples;
    statslist[playercount].homeruns = stats.homeruns;
    statslist[playercount].battingavg = stats.battingavg;
    statslist[playercount].onbpct = stats.onbpct;
    statslist[playercount].slugpct = stats.slugpct;
    strcpy(statslist[playercount].name,stats.name);
    //statslist[playercount].name = stats.name;

    playercount++;
}

int countPlayers(BasicPlayer player)
{
    int totalplayers = 0;
    while(GetNextPlayer(&player))
    {
        totalplayers++;
    }
    ResetToFirstPlayer();
    return totalplayers;
}

void header()
{ 
   pad(5,"AVG");
   pad(5,"OBP");
   pad(5,"SLUG");
   printf("NAME\n");
}

int main(void)
{
    BasicPlayer player;

    int totalplayers = countPlayers(player);

    statslist = malloc(sizeof(struct playerstats)*totalplayers);
    
    printf("*** Initial order ***\n");
    header();
    
    while (GetNextPlayer(&player))
    {
        GetAllStats(player);
        printf("%.3f %.3f %.3f %s\n",stats.battingavg,stats.onbpct,stats.slugpct,player.name);
    }

    printf("*** By Average ***\n");
    header();
    
    for(int i=0;i<playercount-1;i++)
    {
        for(int j=0;j<playercount-1-i;j++)
        {
            if(statslist[j].battingavg > statslist[j+1].battingavg)
            {
                double temp;
                char nametemp[31];
                temp = statslist[j].battingavg;
                statslist[j].battingavg = statslist[j+1].battingavg;
                statslist[j+1].battingavg = temp;

                temp = statslist[j].atbats;
                statslist[j].atbats = statslist[j+1].atbats;
                statslist[j+1].atbats = temp;

                temp = statslist[j].walks;
                statslist[j].walks = statslist[j+1].walks;
                statslist[j+1].walks = temp;

                temp = statslist[j].singles;
                statslist[j].singles = statslist[j+1].singles;
                statslist[j+1].singles = temp;

                temp = statslist[j].doubles;
                statslist[j].doubles = statslist[j+1].doubles;
                statslist[j+1].doubles = temp;

                temp = statslist[j].triples;
                statslist[j].triples = statslist[j+1].triples;
                statslist[j+1].triples = temp;

                temp = statslist[j].homeruns;
                statslist[j].homeruns = statslist[j+1].homeruns;
                statslist[j+1].homeruns = temp;

                temp = statslist[j].onbpct;
                statslist[j].onbpct = statslist[j+1].onbpct;
                statslist[j+1].onbpct = temp;

                temp = statslist[j].slugpct;
                statslist[j].slugpct = statslist[j+1].slugpct;
                statslist[j+1].slugpct = temp;

                strcpy(nametemp,statslist[j].name);
                strcpy(statslist[j].name,statslist[j+1].name);
                strcpy(statslist[j+1].name,nametemp);
            }
        }
    }
    
    for(int i=0;i<playercount;i++)
    {
        printf("%.3f %.3f %.3f %s\n",statslist[i].battingavg,statslist[i].onbpct,statslist[i].slugpct,statslist[i].name);
    }

    free(statslist);
}


