/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "GameManager.h"

using namespace SDLCore;

int main(int argc, char* args[]){

	SDLCore::GameManager* Manager = SDLCore::GameManager::Instance();

	Manager->Run();
	Manager->Release();

	return 0;
}
