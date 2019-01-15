#pragma once

/** \brief A Function To Read input file and write into output file
  * \param input name of the file to read from
  * \param output name of the file to write into
  * \return Output status, true if all operations are succesful
  * 
  * This method reads input file line-by-line.
  * Checks if each line is a valid whole number.
  * Stores number of line read, sum and average of all whole 
  * numbers read from line into output file.
  */
extern "C" int analyse(const char* input, const char* output);