#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>


struct kobject *mykobject03;

void mytype_release(struct kobject *kobj)
{
    printk("This is mytype_release\n");
    kfree(kobj);
}

struct kobj_type mytype = {
    .release = mytype_release,
};

static int mykobj_init(void)
{
	int ret;

    mykobject03 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    ret = kobject_init_and_add(mykobject03, &mytype, NULL, "%s", "mykobject03");
    
	return ret;
}

static void mykobj_exit(void)
{
    kobject_put(mykobject03);
} 

module_init(mykobj_init);
module_exit(mykobj_exit);

MODULE_LICENSE("GPL");
