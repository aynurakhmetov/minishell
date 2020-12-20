#include "libft.h"
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	dst_len = ft_strlen(dst);
	i = dst_len;
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