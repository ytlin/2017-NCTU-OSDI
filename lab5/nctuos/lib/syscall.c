#include <inc/syscall.h>
#include <inc/trap.h>

#define SYSCALL_NOARG(name, ret_t) \
   ret_t name(void) { return syscall((SYS_##name), 0, 0, 0, 0, 0); }


static inline int32_t
syscall(int num, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5)
{
	int32_t ret;

	// Generic system call: pass system call number in AX,
	// up to five parameters in DX, CX, BX, DI, SI.
	// Interrupt kernel with T_SYSCALL.
	//
	// The "volatile" tells the assembler not to optimize
	// this instruction away just because we don't use the
	// return value.
	//
	// The last clause tells the assembler that this can
	// potentially change the condition codes and arbitrary
	// memory locations.

	asm volatile("int %1\n"
		: "=a" (ret)
		: "i" (T_SYSCALL),
		  "a" (num),
		  "d" (a1),
		  "c" (a2),
		  "b" (a3),
		  "D" (a4),
		  "S" (a5)
		: "cc", "memory");

	return ret;
}


SYSCALL_NOARG(getc, int)

void
puts(const char *s, size_t len)
{
	syscall(SYS_puts,(uint32_t)s, len, 0, 0, 0);
}

/* TODO: Lab 5
 * Please add interface needed for 
 * sleep, settextcolor, kill_self, fork, getpid, cls, get_num_free_page,
 * and get_num_used_page
 * Those syscall interface are needed by shell.c to implement basic 
 * function of the shell
 *
 * HINT: You can use SYSCALL_NOARG to save your time.
 */
int32_t get_num_used_page(void) {
    return syscall(SYS_get_num_used_page, 0, 0, 0, 0, 0);
}

int32_t cls(void) {
    return syscall(SYS_cls, 0, 0, 0, 0, 0);
}

int32_t get_num_free_page(void) {
    return syscall(SYS_get_num_free_page, 0, 0, 0, 0, 0);
}

unsigned long get_ticks(void) {
    return syscall(SYS_get_ticks, 0, 0, 0, 0, 0);
}

void settextcolor(unsigned char forecolor, unsigned char backcolor) {
    syscall(SYS_settextcolor, forecolor, backcolor, 0, 0, 0);
}

int32_t fork(void) {
    return syscall(SYS_fork, 0, 0, 0, 0, 0);
}

int32_t getpid(void) {
    return syscall(SYS_getpid, 0, 0, 0, 0, 0);
}

void kill_self() {
    syscall(SYS_kill, 0, 0, 0, 0, 0);
}

void sleep(uint32_t ticks) {
    syscall(SYS_sleep, ticks, 0, 0, 0, 0);
}

