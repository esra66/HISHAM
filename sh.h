#ifndef _SH_H_
#define _SH_H_

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define C_AND		   2
#define C_CHAIN	           3
#define C_NORM	           0
#define C_OR		   1
#define H_FILE	".simple_shell_history"
#define H_MAX	          4096
#define U_GETLINE          0
#define U_STRTOK           0
#define CONV_TO_UNSIGNED   2
#define CONV_TO_LOW	   1
#define R_BUF             1024
#define W_BUF             1024
#define BUF_CLEAR         -1

/**
 * struct lststring - linked list.
 * @num: an integer representing a numerical value.
 * @str: a pointer to a character array representing a string value.
 * @next: a pointer to the next node in the list.
 */
typedef struct lststring
{
	int num;
	char *str;
	struct lststring *next;
} list_t;

/**
 * struct CommandInfo - This is a definition of a struct.
 * @argument_list: An array of strings generated from arguments.
 * @arguments: string containing the command arguments.
 * @argument_count: The number of arguments.
 * @command_path: The path to the current command.
 * @input_fd: The file descriptor used for reading input.
 * @command_buffer: Address of pointer to command buffer.
 * @exit_code: The error code for exit().
 * @command_history: A linked list containing command history.
 * @program_name: The name of the program.
 * @command_aliases: A linked list containing command aliases.
 * @environment_changed: If true, the environment was changed.
 * @history_line_number: The line number in the command history file.
 * @modified_environment: A custom modified copy of the environment.
 * @count_line: If true, this line of input will be counted.
 * @return_status: the return status of the last exec'd command.
 * @environment: A linked list containing environment variables.
 * @command_type: Command type (||, &&, ;).
 * @error_count: The number of errors encountered.
 */
typedef struct CommandInfo
{
	char **argument_list;
	char *arguments;
	int argument_count;
	char *command_path;
	int input_fd;
	char **command_buffer;
	int exit_code;
	list_t *command_history;
	char *program_name;
	list_t *command_aliases;
	int environment_changed;
	int history_line_number;
	char **modified_environment;
	int count_line;
	int return_status;
	list_t *environment;
	int command_type;
	unsigned int error_count;
} info_t;

#define INIT_INFO \
{NULL, NULL, 0, NULL, 0, NULL, 0, NULL, NULL, NULL, 0, 0, NULL, 0, 0, NULL, \
	0, 0}

extern char **environ;

/**
 * struct builtin_fun - containing builtin functions.
 * @type: Command flag.
 * @func: Function.
 */
typedef struct builtin_fun
{
	char *type;
	int (*func)(info_t *);
} builtin_t;

/*Functions*/
int interactive(info_t *info);
int is_delimiter(char d, char *delim);
int _isalpha(int d);
int _atoi(char *str);
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhistory(info_t *inform);
int unset_alias(info_t *infor, char *st);
int set_alias(info_t *info, char *str1);
int print_alias(list_t *nd1);
int _myalias(info_t *info);
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *var_nam);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int pop_env_list(info_t *info);
void _eputs(char *st);
int _eputchar(char A);
int _putfd(char A, int f_des);
int _putsfd(char *st, int f_desc);
int _atoierr(char *st);
void print_err(info_t *info, char *err_st);
int print_deci(int input, int f_desc);
char *conv_num(long int numb, int base, int flag);
void rm_comments(char *buffer);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *des, char *src, int n);
char *_strchr(char *st, char c);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
void info_clear(info_t *info);
void info_set(info_t *info, char **av);
void info_free(info_t *info, int free_all);
ssize_t input_buf(info_t *info, char **buff, size_t *length);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buff, size_t *x);
int _getline(info_t *info, char **ptr, size_t *length);
void sign_handle(__attribute__((unused))int sig_num);
char *get_hisfile(info_t *info);
int wr_history(info_t *info);
int re_history(info_t *info);
int build_his_t(info_t *info, char *buffer, int line_count);
int renum_his(info_t *info);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *x);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *head);
char **conv_list_to_str(list_t *head);
size_t print_list(const list_t *header);
list_t *node_starts_with(list_t *nd, char *pre, char ch);
ssize_t get_node_index(list_t *h, list_t *nd);
int main(int ac, char **av);
int free_ptr(void **p);
char *_memset(char *A, char B, unsigned int C);
void free_str(char **pptr);
void *_realloc(void *ptr1, unsigned int o_size, unsigned int n_size);
int hsh(info_t *info, char **av);
int fd_builtin(info_t *info);
void fd_cmd(info_t *info);
void cmd_fork(info_t *info);
int is_command(info_t *info, char *path1);
char *duplicate_ch(char *str_path, int start1, int stop2);
char *fd_path(info_t *info, char *str_path, char *comd);
int _strlen(char *str);
char *starts_with(const char *str, const char *prefex);
char *_strcat(char *dest, char *sour);
int _strcmp(char *st1, char *st2);
char *_strcpy(char *dest, char *sour);
char *_strdup(const char *st);
void _puts(char *st);
int _putchar(char c);
char **strtow(char *str, char *d);
char **strtow2(char *string, char deli);
int ischain(info_t *info, char *buff, size_t *ptr);
void ck_chain(info_t *info, char *buff, size_t *ptr, size_t k, size_t length);
int rep_alias(info_t *info);
int rep_vars(info_t *info);
int rep_str(char **old_string, char *new_string);

#endif
