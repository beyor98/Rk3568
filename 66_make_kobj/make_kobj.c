#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>


struct kobject *mykobject01;
struct kobject *mykobject02;
struct kobject *mykobject03;

struct kobj_type mytype;


static int mykobj_init(void)
{
	int ret;
	
    mykobject01 = kobject_create_and_add("mykobject01", NULL);
    mykobject02 = kobject_create_and_add("mykobject02", mykobject01);

    mykobject03 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    ret = kobject_init_and_add(mykobject03, &mytype, NULL, "%s", "mykobject03");
    
	return ret;
}

static void mykobj_exit(void)
{
    kobject_put(mykobject01);
    kobject_put(mykobject02);
    kobject_put(mykobject03);
} 

module_init(mykobj_init);
module_exit(mykobj_exit);

MODULE_LICENSE("GPL");
