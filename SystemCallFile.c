//SYSTEM CALL FILE

#include <linux/kernel.h>
#include <linux/syscalls.h>

asmlinkage long sys_PrintStatement( char *buff ,int number){
	printk("\n[ICECREAM SHOP]: Customer[%d]:%s",number,buff);
	return 0;
}
