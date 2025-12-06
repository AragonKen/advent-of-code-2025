#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_MAX_SIZE 640

void get_file_content(char *filename, char *destination_ptr)
{
  FILE *fileptr = fopen(filename, "r");
  
  fgets(destination_ptr, INPUT_MAX_SIZE, fileptr);

  fclose(fileptr);
}

void number_to_string(uint64_t number, char** destination)
{
  char num_string_reverse[32];

  int index = 0;
  while (number != 0) {
	uint64_t digit = number % 10;

	num_string_reverse[index] = '0' + digit;

	number = number / 10;
	index++;
  }
  
  *destination = malloc(index + 1);

  for (int i = 0; i < index; i++) {
   	(*destination)[i] = num_string_reverse[index - 1 - i];
  }

  (*destination)[index] = '\0';
}

int is_occour_sequence(char* id, int num_of_sequence)
{
  if (strlen(id) % num_of_sequence != 0) return 0; 
  int pointer_distance = strlen(id) / num_of_sequence;
  // printf("=============================\n");
  // printf("currently checking id %s if contains %d repeated number sequence, with each sequence has distance of %d \n", id, num_of_sequence, pointer_distance);

  int current_index = 0;
  while (current_index < pointer_distance) {
	for (int current_pointer = 1; current_pointer < num_of_sequence; current_pointer++) {
	  char pointer_1 = *(id + current_index);
	  char pointer_n = *(id + current_index + (current_pointer * pointer_distance));
	  /* printf("comparing \n" */
	  /* 		 "pointer 0 at position %d with value %c \n" */
	  /* 		 "pointer %d at position %d with value %c\n", */
	  /* 		 current_index, pointer_1, */
	  /* 		 current_pointer, (current_index + (current_pointer * pointer_distance)), pointer_n */
	  /* 		 ); */
	  
	  if (pointer_1 != pointer_n) {
		return 0;
	  }
	}

	current_index += 1;
  }

  // printf("==========================\n");

  return 1;
}

int check_is_invalid_id(char *id)
{
  if (strlen(id) == 2 || strlen(id) == 3 || strlen(id) == 5 || strlen(id) == 7) {
	return is_occour_sequence(id, strlen(id));
  }

  for (int divider = 2; divider <= strlen(id) / 2; divider++) {
	if (strlen(id) % divider != 0) continue;
	if (is_occour_sequence(id, divider) == 1) return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
	printf("please provide input file");
	return 0;
  }
  
  char input[640];
  get_file_content(argv[1], input);
  printf("input content: %s", input);
  char* range_saveptr;
  uint64_t password = 0;
  
  for (char* current_range = strtok_r(input, ",", &range_saveptr); current_range != NULL; current_range = strtok_r(NULL, ",", &range_saveptr)) {
	char *min_range_char = strtok(current_range, "-");
	char *max_range_char = strtok(NULL, "-");

	uint64_t min_range = strtoull(min_range_char, NULL, 10);
	uint64_t max_range = strtoull(max_range_char, NULL, 10);
	printf("current range in digit: %llu - %llu \n", min_range, max_range);

	for (uint64_t i = min_range; i <= max_range; i++) {
	  char *current_num_str;
	  number_to_string(i, &current_num_str);


	  if (check_is_invalid_id(current_num_str) == 1) {
		printf("%llu is invalid token, %llu + %llu = %llu\n", i, password, i, password + i);
		password += i;
	  }
	}
  }

  printf("password: %llu\n", password);
  
  return 0;
}
