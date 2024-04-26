#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/configfs.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/sysfs.h>


int mybus_match(struct device *dev, struct device_driver *drv)
{

    return (strcmp(dev_name(dev), drv->name) == 0);
}

int mybus_probe(struct device *dev)
{
    struct device_driver *drv = dev ->driver;
    if(drv->probe)
    {
        drv->probe(dev);
    }
    return 0;
}



struct bus_type mybus = {
    .name = "mybus",
    .match = mybus_match,
    .probe = mybus_probe,
};

ssize_t mybus_show(struct bus_type *bus, char *buf)
{
    ssize_t ret;
    sprintf(buf, "%s\n", mybus_show);

    return ret;
}

ssize_t mybus_store(struct bus_type *bus, const char *buf, size_t count)
{
    ssize_t ret = 0;
    sprintf(buf, "%s\n", mybus_store);

    return ret;
}

struct bus_attribute mybus_attr = {
    .attr = {
        .name = "value",
        .mode = 0664,
    },
    .show = mybus_show,
    .store = mybus_store,
};


static int bus_init(void)
{
	int ret = 0;

	ret = bus_register(&mybus);
	ret = bus_create_file(&mybus, &mybus_attr);
  
	return ret;
}

static void bus_exit(void)
{
    bus_remove_file(&mybus, &mybus_attr);
    bus_unregister(&mybus);
} 

module_init(bus_init);
module_exit(bus_exit);

MODULE_LICENSE("GPL");
