#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

struct mykobj{ 
    struct kobject kobj;
    int value1;
    int value2;
}; 

struct mykobj *mykobject01;

ssize_t show_myvalue1(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    ssize_t count;
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    //count = sprintf(buf, "show_myvalue1\n");
    count = sprintf(buf, "%d\n", mykobject01->value1);
    return count;
}

ssize_t store_myvalue1(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    //printk("buf is %s\n", buf);
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    sscanf(buf, "%d\n", &mykobject01->value1);
    return count;
}

ssize_t show_myvalue2(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    ssize_t count;
    //count = sprintf(buf, "show_myvalue1\n");
    count = sprintf(buf, "%d\n", mykobject01->value2);
    return count;
}

ssize_t store_myvalue2(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    //printk("buf is %s\n", buf);
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    sscanf(buf, "%d\n", &mykobject01->value2);
    return count;
}

struct kobj_attribute value1 = __ATTR(value1, 0664, show_myvalue1, store_myvalue1);
struct kobj_attribute value2 = __ATTR(value2, 0664, show_myvalue2, store_myvalue2);

struct attribute *myattr[] = {
    &value1.attr,
    &value2.attr,
    NULL,
};


void mytype_release(struct kobject *kobj)
{
    struct mykobj *mykobject01 = container_of(kobj, struct mykobj, kobj);
    kfree(mykobject01);
}

ssize_t myshow(struct kobject *kobj, struct attribute *attr, char *buf)
{
    ssize_t count;
    struct kobj_attribute *kobj_attr = container_of(attr, struct kobj_attribute, attr);
    count = kobj_attr->show(kobj, kobj_attr, buf);
    
    return count;
}

ssize_t mystore(struct kobject *kobj, struct attribute *attr, const char *buf, size_t size)
{
    struct kobj_attribute *kobj_attr = container_of(attr, struct kobj_attribute, attr);
    
    return kobj_attr->store(kobj, kobj_attr, buf, size);
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
