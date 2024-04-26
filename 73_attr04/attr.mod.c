#include <linux/module.h>
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x9d7fbf35, "module_layout" },
	{ 0xbbc9ee2e, "kobject_put" },
	{ 0x2a0c8109, "sysfs_create_group" },
	{ 0x161c5d7d, "kobject_create_and_add" },
	{ 0x7c32d0f0, "printk" },
	{ 0x6b2dc060, "dump_stack" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

