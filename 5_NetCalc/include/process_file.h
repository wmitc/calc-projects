#ifndef PARSE_H
#define PARSE_H

#include <stdint.h>
#include <stdlib.h>

int process_file(const char *file,
                 const char *input_dir,
                 const char *output_dir);

int process_buffer(const uint8_t *buffer,
                 size_t input_size,
                 uint8_t **output_buf,
                 size_t *output_size);

#endif
