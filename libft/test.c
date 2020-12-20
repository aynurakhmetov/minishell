#include "libft.h"
#include <string.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	m;

	m = 0;
	while (str[m] != '\0')
	{
		m = m + 1;
	}
	return (m);
}

size_t		ft_strlcat_deep(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	dst_len = ft_strlen(dst);
	i = dst_len;
	printf("check %zu\n", (dstsize -1));
	while (i < (dstsize - 1) && src[i - dst_len] != '\0' && dstsize >= dst_len)
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	if (dstsize >= dst_len)
		dst[i] = '\0';
	if (dstsize < dst_len)
		dst_len = dstsize;
	return (ft_strlen(src) + dst_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	const char	*ndst;
	const char	*nsrc;
	size_t		i;
	size_t		dlen;

	ndst = dst;
	nsrc = src;
	i = dsize;
	while (i-- != 0 && *dst != '\0')
		dst++;
	dlen = dst - ndst;
	i = dsize - dlen;
	if (i-- == 0)
		return (dlen + ft_strlen(src));
	while (*src != '\0')
	{
		if (i != 0)
		{
			*dst++ = *src;
			i--;
		}
		src++;
	}
	*dst = '\0';
	return (dlen + (src - nsrc));
}

int main (void)
{
    char src[7] = "toto";
    char dest[8] = "";
    char dest2[8] = "";
    char dest3[8] = "";

    printf("my strlcat   - %zu\n", ft_strlcat(dest, src, 0));
    printf("my strlcat   - %s\n", dest);
    printf("deep strlcat - %zu\n", ft_strlcat_deep(dest2, src, 0));
    printf("deep strlcat - %s\n", dest2);
    printf("orig strlcat - %zu\n", strlcat(dest3, src, 0));
    printf("orig strlcat - %s\n", dest3);
    return (0);
}