#ifndef STRACE_XLAT_H
#define STRACE_XLAT_H

# include <stdint.h>

struct xlat {
	uint64_t val;
	const char *str;
};

# define XLAT(val)			{ (unsigned)(val), #val }
# define XLAT_PAIR(val, str)		{ (unsigned)(val), str  }
# define XLAT_TYPE(type, val)		{     (type)(val), #val }
# define XLAT_TYPE_PAIR(type, val, str)	{     (type)(val), str  }
# define XLAT_END			{		0, 0    }
const char *
xlookup(const struct xlat *xlat, const uint64_t val);
int
printxvals(const uint64_t val, const char *dflt, const struct xlat *xlat, ...);

#endif /* !STRACE_XLAT_H */
