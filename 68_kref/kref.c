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

void mytype_release(struct kobject *kobj)
{
    printk("This is mytype_release\n");
    kfree(kobj);
}


struct kobj_type mytype = {
    .release = mytype_release,
};


static int mykref_init(void)
{
	int ret;
	
    mykest = kset_create_and_add("mykest", NULL, NULL);
    
    mykobject01 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    mykobject01->kset = mykest;
    ret = kobject_init_and_add(mykobject01, &mytype, NULL, "%s", "mykobject01");
    printk("mykobject01->kref = %d\n", mykobject01->kref.refcount.refs.counter);

    mykobject02 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    mykobject02->kset = mykest;
    ret = kobject_init_and_add(mykobject02, &mytype, mykobject01, "%s", "mykobject02");

    mykobject03 = kzalloc(sizeof(struct kobject), GFP_KERNEL);
    mykobject03->kset = mykest;
    ret = kobject_init_and_add(mykobject03, &mytype, mykobject02, "%s", "mykobject03");
    
    printk("mykobject01->kref = %d\n", mykobject01->kref.refcount.refs.counter);
    printk("mykobject02->kref = %d\n", mykobject02->kref.refcount.refs.counter);
    printk("mykobject03->kref = %d\n", mykobject03->kref.refcount.refs.counter);
    
	return ret;
}

static void mykref_exit(void)
{
    kobject_put(mykobject01);
    printk("\nmykobject01->kref = %d\n", mykobject01->kref.refcount.refs.counter);
    printk("mykobject02->kref = %d\n", mykobject02->kref.refcount.refs.counter);
    printk("mykobject03->kref = %d\n\n", mykobject03->kref.refcount.refs.counter);

    kobject_put(mykobject02);
    printk("mykobject01->kref = %d\n", mykobject01->kref.refcount.refs.counter);
    printk("mykobject02->kref = %d\n", mykobject02->kref.refcount.refs.counter);
    printk("mykobject03->kref = %d\n\n", mykobject03->kref.refcount.refs.counter);

    kobject_put(mykobject03);
    printk("mykobject01->kref = %d\n", mykobject01->kref.refcount.refs.counter);
    printk("mykobject02->kref = %d\n", mykobject02->kref.refcount.refs.counter);
    printk("mykobject03->kref = %d\n\n", mykobject03->kref.refcount.refs.counter);

    kset_unregister(mykest);
    printk("mykobject01->kref = %d\n", mykobject01->kref.refcount.refs.counter);
    printk("mykobject02->kref = %d\n", mykobject02->kref.refcount.refs.counter);
    printk("mykobject03->kref = %d\n\n", mykobject03->kref.refcount.refs.counter);
} 

module_init(mykref_init);
module_exit(mykref_exit);

MODULE_LICENSE("GPL");
