
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

/* Clean the list for the next call */
void	polish_list(t_list **list)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (!buf || !clean)
		return ;
	last = find_last_node(*list);
	i = 0;
	while (last->str_buf[i] && last->str_buf[i] != '\n')
		i++;
	k = 0;
	while (last->str_buf[i] && last->str_buf[++i])
		buf[k++] = last->str_buf[i];
	buf[k] = '\0';
	clean->str_buf = buf;
	clean->next = NULL;
	dealloc(list, clean, buf);
}

/* Build the next line from list */
char	*get_line(t_list *list)
{
	int		len;
	char	*line;

	if (!list)
		return (NULL);
	len = len_to_newline(list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	copy_str(list, line);
	return (line);
}

/* Add a new node at the end of the list */
void	append(t_list **list, char *buf)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->str_buf = buf;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		last = find_last_node(*list);
		last->next = new;
	}
}

/* Create or update list with new data from fd */
void	create_list(t_list **list, int fd)
{
	char	*buf;
	int		r;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
		{
			free(buf);
			return ;
		}
		buf[r] = '\0';
		append(list, buf);
	}
}

/* Main get_next_line function */
char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	line = get_line(list);
	polish_list(&list);
	return (line);
}