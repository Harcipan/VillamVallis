#ifndef KERTERTEKAD_H_INCLUDED
#define KERTERTEKAD_H_INCLUDED

void tileErtek(DinTomb *kertTartalma, int ertek, int kertX, int kertY)
{
    kertTartalma->adat[kertY][kertX]=ertek;
}

//novesztjuk a novenyt
//tickSpeed: álltalános játéksebesség
//tileState: meg van-e locsolva a noveny
void novenyNovesztes(DinTomb *kertTartalma,int tickSpeed)
{
    for(int i=0; i<kertTartalma->meretSor; i++)
    {
        for(int j=0; j<kertTartalma->meretOszlop; j++)
        {
            if(kertTartalma->adat[i][j]>=1&&kertTartalma->adat[i][j]<=60000)
            {
                int tileState = kertTartalma->adat[i][j]%10;
                kertTartalma->adat[i][j]+=tickSpeed*10*tileState;
            }
        }
    }
}

#endif // KERTERTEKAD_H_INCLUDED
