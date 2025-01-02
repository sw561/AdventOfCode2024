#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

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

int operate(state * s, int * program, int program_size)
{
	static bool first_output = true;

	if (s->p + 1 >= program_size){
		return -1;
	}

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
			if (!first_output) printf(",");
			printf("%lld", combo_operand(s, operand) % 8);
			first_output = false;
			s->p += 2;
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

	return 0;
}

int main()
{
	state s = {0};
	char * buffer = NULL;
	size_t n = 0;

	scanf("Register A: %lld", &s.a);
	scanf("Register B: %lld", &s.b);
	scanf("Register C: %lld", &s.c);

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

	while(operate(&s, program, program_size) == 0) {
		// printf("A = %lld, B = %lld, C = %lld\n", s.a, s.b, s.c);
	}

	printf("\n");
	// show(&s);

	free(program);
	free(buffer);
	return 0;
}
