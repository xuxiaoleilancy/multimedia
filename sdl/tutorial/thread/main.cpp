#include <iostream>
using namespace std;

#include "SDL2/SDL.h"
#include "SDL2/SDL_thread.h"
#include "SDL2/SDL_image.h"

int gotta_go = 0;
int potty = 0;
int thread_func(void* data)
{

	SDL_mutex* pLock = (SDL_mutex*)data;
	int times_went = 0;
	
	while ( gotta_go)
	{
		SDL_mutexP(pLock);
		++potty;
		cout << "�߳�" << SDL_ThreadID() << "����ʹ��potty" << endl;
		if ( potty > 1 )
		{
			cout << "Ŷ����������potty" << endl;
		}
		--potty;
		SDL_mutexV(pLock);
		--times_went;
	}
	cout << "����" << endl;

	return times_went;
}

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return -1;
	}
	const int progeny = 5;

	SDL_Thread* pKids[progeny];
	SDL_mutex* pLock;
	int i;
	int lots;

	pLock = SDL_CreateMutex();

	gotta_go = 1;

	for (int i = 0; i < progeny;++i)
	{
		pKids[i] = SDL_CreateThread(thread_func,"usePotty", pLock);
	}

	SDL_Delay(5 * 1000);
	SDL_mutexP(pLock);
	cout << "���������?" << endl;
	gotta_go = 0;
	SDL_mutexV(pLock);

	for (int i = 0; i < progeny;++i)
	{
		SDL_WaitThread(pKids[i], &lots);
		cout << "�߳�" << i + 1 << "�ù�potty" << lots << "����" << endl;
	}
	SDL_DestroyMutex(pLock);

	SDL_Quit();
	system("pause");
	return 0;
}
