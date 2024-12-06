all: day1 day2 day3 day4 day6

CFLAGS = -O3 -Wall -Wextra --std=gnu99

day1: day1.c
	gcc -o $@ $(CFLAGS) $<

day2: day2.c
	gcc -o $@ $(CFLAGS) $<

day3: day3.c
	gcc -o $@ $(CFLAGS) $<

day4: day4.c
	gcc -o $@ $(CFLAGS) $<

day6: day6.c
	gcc -o $@ $(CFLAGS) $<

test1: day1
	diff <(./day1 < day1.example.in) day1.example.out
	diff <(./day1 < day1.in) day1.out

test2: day2
	diff <(./day2 < day2.example.in) day2.example.out
	diff <(./day2 < day2.in) day2.out

test3: day3
	diff <(./day3 < day3.example.in) day3.example.out
	diff <(./day3 < day3.example2.in) day3.example2.out
	diff <(./day3 < day3.in) day3.out

test4: day4
	diff <(./day4 < day4.example.in) day4.example.out
	diff <(./day4 < day4.in) day4.out

test5:
	diff <(./day5.py < day5.example.in) day5.example.out
	diff <(./day5.py < day5.in) day5.out

test6: day6
	diff <(./day6 < day6.example.in) day6.example.out
	diff <(./day6 < day6.in) day6.out

test: test1 test2 test3 test4 test5 test6

clean:
	rm day1 day2 day3 day4
