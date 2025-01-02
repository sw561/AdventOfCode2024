#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef long long ll;

typedef struct state {
	ll a, b, c;
	int p; // Instruction pointer
} state;

void show(state * s) {
	printf("(A,B,C): (%lld,%lld,%lld)\n", s->a, s->b, s->c);
}

void show_program(int * program, int program_size)
{
	for (int i=0; i < program_size; i++) {
		printf("%d,", program[i]);
	}
	printf("\n");
}

ll combo_operand(state * s, int operand)
{
	if (operand <= 3) return operand;
	switch (operand) {
		case 4:
			return s->a;
		case 5:
			return s->b;
		case 6:
			return s->c;
		default:
			assert(false && "Unreachable");
	}
}

int operate_to_stdout(state * s, int * program, int program_size)
{
	while (s->p >= 0 && s->p < program_size) {
	const int op = program[s->p];
	const int operand = program[s->p + 1];
	ll num, den;

	switch (op) {
		case 0:
			num = s->a;
			den = 1 << combo_operand(s, operand);
			s->a = num / den;
			s->p += 2;
			break;
		case 1:
			s->b ^= operand;
			s->p += 2;
			break;
		case 2:
			s->b = combo_operand(s, operand) % 8;
			s->p += 2;
			break;
		case 3:
			if (s->a != 0) {
				s->p = operand;
			} else {
				s->p += 2;
			}
			break;
		case 4:
			s->b ^= s->c;
			s->p += 2;
			break;
		case 5:
			s->p += 2;
			return combo_operand(s, operand) % 8;
			break;
		case 6:
			num = s->a;
			den = 1 << combo_operand(s, operand);
			s->b = num / den;
			s->p += 2;
			break;
		case 7:
			num = s->a;
			den = 1 << combo_operand(s, operand);
			s->c = num / den;
			s->p += 2;
			break;
	}
	}

	return -1;
}

void operate(state * s, int * program, int program_size)
{
	bool first_output = true;
	while (true) {
		int r = operate_to_stdout(s, program, program_size);
		if (r == -1) break;

		if (!first_output) {
			printf(",");
		} else {
			first_output = false;
		}
		printf("%d", r);
	}
	printf("\n");
}

int run_to_output(state * s, int * program, int program_size, ll a)
{
	s->a = a;
	s->b = 0;
	s->c = 0;
	s->p = 0;
	int ret = operate_to_stdout(s, program, program_size);
	return ret;
}

ll attempt(ll a, state * s, int * program, int program_size, int i)
{
	for (int a_end=0; a_end < 8; a_end++) {
		ll new_a = a * 8 + a_end;
		memset(s, 0, sizeof(state));
		s->a = new_a;
		int r = operate_to_stdout(s, program, program_size);
		if (r == program[i]) {

			if (i==0) {
				return new_a;
			}

			ll a_ret = attempt(new_a, s, program, program_size, i-1);
			if (a_ret >= 0) {
				return a_ret;
			}
		}
	}

	return -1;
}

int main()
{
	state s = {0};
	char * buffer = NULL;
	size_t n = 0;

	getline(&buffer, &n, stdin);
	sscanf(buffer, "Register A: %lld", &s.a);
	getline(&buffer, &n, stdin);
	sscanf(buffer, "Register B: %lld", &s.b);
	getline(&buffer, &n, stdin);
	sscanf(buffer, "Register C: %lld", &s.c);
	// Read empty line
	getline(&buffer, &n, stdin);
	getline(&buffer, &n, stdin);

	int * program = malloc(100 * sizeof(int));
	int program_size = 0;

	int n_read;
	sscanf(buffer, "Program: %n", &n_read);
	int offset = n_read;

	while (sscanf(&buffer[offset], "%d,%n", &program[program_size], &n_read) > 0) {
		program_size++;
		offset += n_read;
	}

	// show(&s);
	// show_program(program, program_size);

	printf("Part 1: ");
	operate(&s, program, program_size);
	// show(&s);

#ifndef TEST
	ll a = attempt(0, &s, program, program_size, program_size-1);
	printf("Part 2: %lld\n", a);
#endif

	free(program);
	free(buffer);
	return 0;
}
