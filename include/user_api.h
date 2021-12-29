#ifndef __USER_API_H__
#define __USER_API_H__

/* user mode syscall APIs */
extern int gethid(unsigned int *hid);
extern int fork();
extern int exec(char* file);
extern void exit();

#endif /* __USER_API_H__ */
