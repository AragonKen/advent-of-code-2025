#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 1. read the input line by line
// 2. parse the input to a struct that contains direction and amount
// 3. do the thing

typedef struct {
  char* buffer;
  ssize_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef struct {
  char direction;
  int step;
} Instruction;

Instruction* new_instruction()
{
  Instruction* instruction = malloc(sizeof(Instruction));
  return instruction;
}

void free_instruction(Instruction* instruction)
{
  free(instruction);
}

void parse_input(InputBuffer* input_buffer, Instruction* instruction)
{
  instruction->direction = input_buffer->buffer[0];

  char* step = input_buffer->buffer + 1;
  instruction->step = atoi(step);
}

void read_input(InputBuffer* input_buffer)
{
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) exit(EXIT_FAILURE);
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

int POINTING_TO = 50;
int PASSWORD = 0;

void do_the_thing(Instruction* instruction)
{
  int whole_rotation = instruction->step / 100;
  int step = instruction->step % 100;

  PASSWORD += abs(whole_rotation);

  if (instruction->direction == 'R') {
	POINTING_TO += step;
	if (POINTING_TO >= 100) {
	  PASSWORD += 1;
	  POINTING_TO -= 100;
	}
  }

  if (instruction->direction == 'L') {
	// edge case when turning 0 to 99 will increment the PASSWORD
	if (POINTING_TO == 0) {
	  POINTING_TO -= step;
	  if (POINTING_TO != 0) POINTING_TO += 100;
	} else {
	  POINTING_TO -= step;
	  if (POINTING_TO <= 0) {
		PASSWORD += 1;
		if (POINTING_TO != 0) POINTING_TO += 100;
	  }	  
	}


  }
  printf("Instruction: %dx to %c, Now Pointing to: %d\n", instruction->step, instruction->direction, POINTING_TO); 
  // printf("now pointing to: %d\n", POINTING_TO);
  printf("password: %d\n", PASSWORD);
}

int main(void)
{
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  Instruction* instruction = new_instruction();
  
  while (true) {
	// printf("what is your input: ");
	read_input(input_buffer);
	if (strcmp(input_buffer->buffer, "exit") == 0) {
	  break;
	}

	parse_input(input_buffer, instruction);

	do_the_thing(instruction);
  }
  free_instruction(instruction);


  return 0;
}
