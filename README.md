# 42_philosopher
42서울 Philosophers

실행방법 (macOS기준)
```
cd philo
make
./philo 수 수명(ms) 식사시간(ms) 잠자는시간(ms) 횟수(선택)
```

인자
- 철학자의 수 (number_of_philosophers)
테이블에 앉아 있는 철학자의 수와 포크의 수

- 철학자의 수명 (time_to_die)
밀리초 단위로, 철학자가 마지막으로 밥을 먹은 지 'time_to_die' 시간만큼이 지나거나, 프로그램 시작 후 'time_to_die' 시간만큼이 지나면 해당 철학자는 사망합니다.

- 밥을 먹는데 걸리는 시간 (time_to_eat)
밀리초 단위로, 철학자가 밥을 먹는 데 걸리는 시간입니다. 해당 시간동안, 철학자는 두 개의 포크를 소유하고 있어야 합니다.

- 잠자는 시간 (time_to_sleep)
밀리초 단위로, 잠을 자는 데 소모되는 시간입니다.

- 각 철학자가 최소한 밥을 먹어야 하는 횟수(number_of_times_each_philosopher_must_eat)
해당 인자값은 선택사항입니다. 모든 철학자가 'number_of_times_each_philosopher_must_eat' 횟수만큼 밥을 먹었다면, 시뮬레이션이 종료됩니다. 해당 값이 명시되어 있지 않다면, 철학자가 한 명이라도 사망할 때까지 시뮬레이션은 계속됩니다.
