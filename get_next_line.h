#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

/* Linked list structure */
typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

/* Main function */
char	*get_next_line(int fd);

/* Utility functions */
int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	dealloc(t_list **list, t_list *clean_node, char *buf);

/* Helpers in main file */
void	polish_list(t_list **list);
char	*get_line(t_list *list);
void	append(t_list **list, char *buf);
void	create_list(t_list **list, int fd);

#endif
