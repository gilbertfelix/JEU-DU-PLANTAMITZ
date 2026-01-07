#include "header.h"

HANDLE thread_musique = NULL;
int musique_active = 1;

/*DWORD WINAPI jouer_musique_thread(LPVOID param){
    while(musique_active){
        PlaySound(TEXT("musique.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(1000);
    }
    return 0;
}*/

void demarrer_musique(){
    musique_active = 1;
     PlaySound(TEXT("musique.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    //thread_musique = CreateThread(NULL, 0, jouer_musique_thread, NULL, 0, NULL);
}

void arreter_musique(){
    musique_active =0;
    PlaySound(NULL, 0, 0);
    /*if(thread_musique){
        WaitForSingleObject(thread_musique, INFINITE);
        CloseHandle(thread_musique);
        thread_musique = NULL;
    }*/
}

void toggle_musique(){
    if(musique_active){
        arreter_musique();
        printf("\n Musique désactivée \n");
    } else {
        demarrer_musique();
        printf("\n Musique activée \n");
    }
}
