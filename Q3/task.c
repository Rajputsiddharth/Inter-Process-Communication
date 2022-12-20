#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/cred.h>
// Declare a module parameter for the process PID
int process_pid = 0;
module_param(process_pid, int, 0644);
MODULE_PARM_DESC(process_pid, "PID of the process to search for");

// This function is called when the module is loaded
static int __init process_info_init(void)
{
    // Find the task_struct for the process with the specified PID
    struct task_struct *task = pid_task(find_vpid(process_pid), PIDTYPE_PID);

    // Check if a matching process was found
    if (!task) {
        // No matching process was found
        printk(KERN_ERR "Error: Process with PID %d not found\n", process_pid);
        return -ENOENT;
    }

    // Extract the requested information from the task_struct
    pid_t pid = task->pid;
    kuid_t uid = task->cred->uid;
    pid_t pgid = task->group_leader->pid;
    char *cmd_path = task->comm;

    // Print the extracted information to the kernel log buffer
    printk(KERN_INFO "Process information:\n");
    printk(KERN_INFO "  PID: %d\n", pid);
    printk(KERN_INFO "  UID: %d\n", uid);
    printk(KERN_INFO "  PGID: %d\n", pgid);
    printk(KERN_INFO "  Command path: %s\n", cmd_path);

    return 0;
}

// This function is called when the module is unloaded
static void __exit process_info_exit(void)
{
    // Nothing to do here
}

module_init(process_info_init);
module_exit(process_info_exit);

MODULE_LICENSE("GPL");
