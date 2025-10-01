#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	size_t	s_len;

	s_len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (s_len + 1));
	i = -1;
	if (dest == NULL)
		return (NULL);
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	stsub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	stsub = 0;
	while (stsub < len && s[start])
	{
		sub[stsub] = s[start];
		start++;
		stsub++;
	}
	sub[stsub] = '\0';
	return (sub);
}

char	*strip_quotes(char *content)
{
	int		i;
	int		k;
	char	q;
	char	*res;

	i = 0;
	k = 0;
	q = 0;
    res = malloc(ft_strlen(content) + 1);
    if (!res)
        return (NULL);
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '"')
		{
            if (!q)
            {
			    q = content[i++];
			    continue ;
            }
            else if (content[i] == q)
            {
                q = 0;
                i++;
                continue ;
            }
		}
		res[k++] = content[i++];
	}
    res[k] = '\0';
	return (res);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);
    printf("%s\n", strip_quotes(argv[1]));
    return (0);
}