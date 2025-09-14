all: day1 day2 day3 day4 day6 day7 day8 day9 day9_part2 day10 day11 day14 day14test day15 day17 day17test day19 day21

CFLAGS = -O3 -Wall -Wextra --std=gnu99
CPPFLAGS = -O3 -Wall -Wextra --std=c++17

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

day7: day7.c
	gcc -o $@ $(CFLAGS) $< -lm

day8: day8.cpp
	g++ -o $@ $(CPPFLAGS) $<

day9: day9.cpp
	g++ -o $@ $(CPPFLAGS) $<

day9_part2: day9_part2.cpp
	g++ -o $@ $(CPPFLAGS) $<

day10: day10.cpp
	g++ -o $@ $(CPPFLAGS) $<

day11: day11.cpp
	g++ -o $@ $(CPPFLAGS) $<

day14: day14.c
	gcc -o $@ $(CFLAGS) $<

day14test: day14.c
	gcc -g -o $@ -D TEST $(CFLAGS) $<

day15: day15.cpp
	g++ -o $@ $(CPPFLAGS) $<

day16: day16.cpp
	g++ -o $@ $(CPPFLAGS) $<

day17: day17.c
	gcc -o $@ $(CFLAGS) $<

day17test: day17.c
	gcc -o $@ -D TEST $(CFLAGS) $<

day19: day19.cpp
	g++ -o $@ $(CPPFLAGS) $<

day21: day21.cpp
	# g++ -o $@ $(CPPFLAGS) $<
	g++ -g -o $@ -Wall -Wextra --std=c++17 $<

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

test7: day7
	diff <(./day7 < day7.example.in) day7.example.out
	diff <(./day7 < day7.in) day7.out

test8: day8
	diff <(./day8 < day8.example.in) day8.example.out
	diff <(./day8 < day8.in) day8.out

test9: day9 day9_part2
	diff <(./day9 < day9.example.in) day9.example.out
	diff <(./day9 < day9.in) day9.out
	diff <(./day9_part2 < day9.example.in) day9_part2.example.out
	diff <(./day9_part2 < day9.in) day9_part2.out

test10: day10
	diff <(./day10 < day10.example.in) day10.example.out
	diff <(./day10 < day10.in) day10.out

test11: day11
	diff <(./day11 < day11.example.in) day11.example.out
	diff <(./day11 < day11.in) day11.out

test12:
	diff <(./day12.py < day12.example.in) day12.example.out
	diff <(./day12.py < day12.example2.in) day12.example2.out
	diff <(./day12.py < day12.example3.in) day12.example3.out
	diff <(./day12.py < day12.example4.in) day12.example4.out
	diff <(./day12.py < day12.example5.in) day12.example5.out
	diff <(./day12.py < day12.in) day12.out

test13:
	diff <(./day13.py < day13.example.in) day13.example.out
	diff <(./day13.py < day13.in) day13.out

test14: day14 day14test
	diff <(./day14test < day14.example.in) day14.example.out
	diff <(./day14 < day14.in) day14.out

test15: day15
	diff <(./day15 < day15.example2.in) day15.example2.out
	diff <(./day15 < day15.example.in) day15.example.out
	diff <(./day15 < day15.example3.in) day15.example3.out
	diff <(./day15 < day15.in) day15.out

test16: day16
	diff <(./day16 < day16.example.in) day16.example.out
	diff <(./day16 < day16.in) day16.out

test17: day17 day17test
	diff <(./day17test < day17.example.in) day17.example.out
	diff <(./day17 < day17.example2.in) day17.example2.out
	diff <(./day17 < day17.in) day17.out

test18:
	diff <(python day18_example.py day18.example.in) day18.example.out
	diff <(python day18.py day18.in) day18.out

test19: day19
	diff <(./day19 < day19.example.in) day19.example.out
	diff <(./day19 < day19.in) day19.out

test21: day21
	diff <(./day21 < day21.example.in) day21.example.out
	diff <(./day21 < day21.in) day21.out

test: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test17 test18 test19 test21

clean:
	rm day1 day2 day3 day4 day6 day7 day8 day9 day9_part2 day10 day11 day14 day14test day15 day16 day17 day17test day19 day21
