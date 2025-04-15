// includes/file_io.h
// This header includes functions for validating and processing directories
#ifndef FILE_IO_H
#define FILE_IO_H

int is_directory(const char *dir);
int process_dir(const char *input_dir, const char *output_dir);

#endif
