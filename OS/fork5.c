/*
 * Write a program that creates two children, and connects the standard
output of one to the standard input of the other, using the
pipe() system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

