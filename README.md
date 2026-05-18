## Как запустить?

`g++ main.cpp -std=c++20 -o main`

`./main > output.txt`

Обязательно >= C++ 20

## Графики

Измерялись среднее время (в микросекундах) и среднее количество сравнений символов между собой.

![Графики](Графики1.png)
![Графики](Графики2.png)
![Графики](Графики3.png)

Тернарный QuickSort работает примерно так же по времени как и обычный, скорее всего это из-за большего числа рекурсивных вызовов

Строковый MergeSort довольно сильно выигрывает у обычного, но обе реализации довольно медленные по сравнению со всем остальным.

Ну и побеждает по времени RadixSort с переключением на QuickSort

## Посылки

https://dsahse25.contest.codeforces.com/group/SLdI1pWUpC/contest/691754/submission/375012156

https://dsahse25.contest.codeforces.com/group/SLdI1pWUpC/contest/691754/submission/375012198

https://dsahse25.contest.codeforces.com/group/SLdI1pWUpC/contest/691754/submission/375012357

https://dsahse25.contest.codeforces.com/group/SLdI1pWUpC/contest/691754/submission/375012394