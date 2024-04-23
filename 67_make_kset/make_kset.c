#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>


struct kobject *mykobject01;
struct kobject *mykobject02;
struct kobject *mykobject03;

struct kset *mykest;

struct kobj_type mytype;


static int mykobj_init(void)
{
	int ret;
	
    mykest = kset_create_and_add("mykest", NULL, NULL);

    mykobject01 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    mykobject01->kset = mykest;
    ret = kobject_init_and_add(mykobject01, &mytype, NULL, "%s", "mykobject01");

    mykobject02 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    mykobject02->kset = mykest;
    ret = kobject_init_and_add(mykobject02, &mytype, mykobject01, "%s", "mykobject02");

	return ret;
}

static void mykobj_exit(void)
{
    kobject_put(mykobject01);
    kobject_put(mykobject02);
    kset_unregister(mykest);
} 

module_init(mykobj_init);
module_exit(mykobj_exit);

MODULE_LICENSE("GPL");
