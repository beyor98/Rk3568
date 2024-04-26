#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>


struct kobject *mykobject01;

ssize_t show_myvalue1(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    ssize_t count;
    dump_stack();
    count = sprintf(buf, "show_myvalue1\n");
    return count;
}

ssize_t store_myvalue1(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    printk("buf is %s\n", buf);
    return count;
}

ssize_t show_myvalue2(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    ssize_t count;
    count = sprintf(buf, "show_myvalue1\n");
    return count;
}

ssize_t store_myvalue2(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    printk("buf is %s\n", buf);
    return count;
}

struct kobj_attribute value1 = __ATTR(value1, 0664, show_myvalue1, store_myvalue1);
struct kobj_attribute value2 = __ATTR(value2, 0664, show_myvalue2, store_myvalue2);

struct attribute *attr[] = {
    &value1.attr,
    &value2.attr,
    NULL,
};

const struct attribute_group my_attr_group = {
    .attrs = attr,
    .name = "my_attr",
};

static int mykobj_init(void)
{
	int ret;

    mykobject01 = kobject_create_and_add("mykobject01", NULL);
    ret = sysfs_create_group(mykobject01, &my_attr_group);
	return ret;
}

static void mykobj_exit(void)
{
    kobject_put(mykobject01);
} 

module_init(mykobj_init);
module_exit(mykobj_exit);

MODULE_LICENSE("GPL");
