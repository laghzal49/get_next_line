#include "get_next_line.h"
#include <stdlib.h>

/* Check if there is a '\n' in the list */
int	found_newline(t_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

/* Return the last node of the list */
t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/* Copy chars from list into str until '\n' or end */
void	copy_str(t_list *list, char *str)
{
	int	i;
	int	k;

	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->str_buf[i];
			i++;
		}
		list = list->next;
	}
	str[k] = '\0';
}

/* Get length up to and including '\n' */
int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
				return (len + 1);
			len++;
			i++;
		}
		list = list->next;
	}
	return (len);
}

/* Free all nodes, then reset or clean the list */
void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node && clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}