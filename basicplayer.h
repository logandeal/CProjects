#ifndef _basicplayer_H
#define _basicplayer_H
typedef struct _BasicPlayer
{
    int id;
    char name[256];
} BasicPlayer;

typedef enum _Stat
{
    ATBATS,
    WALKS,
    SINGLES,
    DOUBLES,
    TRIPLES,
    HOMERUNS,
} Stat;

int GetNextPlayer(BasicPlayer * pPlayer);
void ResetToFirstPlayer();

int GetStat(int id, Stat stat);
#endif