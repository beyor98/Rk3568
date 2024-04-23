#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>

struct mykobj{ 
    struct kobject kobj;
    int value1;
    int value2;
};

struct mykobj *mykobject01;

void mytype_release(struct kobject *kobj)
{
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    printk("This is mytype_release\n");
    kfree(mykobject01);
}

struct attribute value1 = {
    .name = "value1",
    .mode = 0666,
};

struct attribute value2 = {
    .name = "value2",
    .mode = 0666,
};

struct attribute *myattr[] = {
    &value1,
    &value2,
    NULL,
};

ssize_t myshow(struct kobject *kobj, struct attribute *attr, char *buf)
{
    ssize_t count;
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    
    if(strcmp(attr->name, "value1")==0)
    {
        count = sprintf(buf, "%d\n", mykobject01->value1);
    }
    if(strcmp(attr->name, "value2")==0)
    {
        count = sprintf(buf, "%d\n", mykobject01->value2);
    }
    
    return count;
}

ssize_t mystore(struct kobject *kobj, struct attribute *attr, const char *buf, size_t size)
{
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    
    if(strcmp(attr->name, "value1")==0)
    {
        sscanf(buf, "%d\n", &mykobject01->value1);
    }
    if(strcmp(attr->name, "value2")==0)
    {
        sscanf(buf, "%d\n", &mykobject01->value2);
    }
    
    return size;
}

struct sysfs_ops myops = {
    .show = myshow,
    .store = mystore,
};


struct kobj_type mytype = {
    .release = mytype_release,
    .default_attrs = myattr,
    .sysfs_ops = &myops,
};

static int mykobj_init(void)
{
	int ret;

    mykobject01 = kzalloc(sizeof(struct mykobj), GFP_KERNEL);
    mykobject01->value1 = 1;
    mykobject01->value2 = 1;
    ret = kobject_init_and_add(&mykobject01->kobj, &mytype, NULL, "%s", "mykobject01");
    
	return ret;
}

static void mykobj_exit(void)
{
    kobject_put(&mykobject01->kobj);
} 

module_init(mykobj_init);
module_exit(mykobj_exit);

MODULE_LICENSE("GPL");
