#include <pthread.h>

int main()
{
	Aufgabe2_1_1(NULL);
	Aufgabe2_1_2(NULL);
	return 0;
}

void Aufgabe2_1_1((void *) Eingabe)
{
//2.1.1 Tutotübung
	int a, b, c, d, e, f;
	//Prpgramm 1:
	int A = a-b;
	int B = c+d;
	int C = e-f;
	//Programm 2:
	int d1 = A;
	int d2 = B;
	int d3 = C;
	int d4 = d1 * d2;
	int D = d4 / d3;

	int u, v, w, r, t, q, p, h;
	int e1 = v+w;
	int e2 = r-t;
	int e3 = q+p;
	int e4 = u/e1;
	int e5 = e4*e2;
	int e6 = e5*e3;
	int E = e6/h;
	//Ende
}

void Aufgabe2_1_2 ((void *) Eingabe)
{
//2.1.2 Tutorübung
	//Programm 1':
	pthread_mutex_t mutex = _PTHREAD_MUTEX_INITIALIZER;
	//concurrent-begin:
	pthread_mutex_lock(&mutex);
	int d1 = a-b;
	int d2 = c+d;
	int d3 = e-f;
	int e1 = v+w;
	int e2 = r-t;
	int e3 = q+p;
	pthread_mutex_unlock(&mutex);
	//concurrent-end
	//Programm 2':
	//concurrent-begin:
	pthread_mutex_lock(&mutex);
	int d4 = d1 * d2;
	int e5 = e4*e2;
	//concurrent-end
	pthread_mutex_unlock(&mutex);
	//concurrent-begin
	pthread_mutex_lock(&mutex);
	int D = d4 / d3;
	int e6 = e5*e3;
	//concurrent-end
	pthread_mutex_unlock(&mutex);
	//concurrent-begin
	pthread_mutex_lock(&mutex);
	int E = e6/h;
	//concurrent-end
	pthread_mutex_unlock(&mutex);
}
