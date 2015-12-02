#include <stdio.h>
#include <Windows.h>

void referencia(int* b){
	
	*b = 8;

}

int main(int argc, const char* argv[])
{
	int a = 0;
	int* b = NULL;

	b = new int (9);

	referencia(b);
	
	printf("%d", *b);

	delete b;

  system("pause");
}

