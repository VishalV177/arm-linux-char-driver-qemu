#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/string.h>

#define DEVICE_NAME "mysensor"

static int major;
static struct cdev mysensor_cdev;
static char msg[64] = "sensor_value=0\n";

static ssize_t mysensor_read(struct file *f, char __user *buf,
                             size_t len, loff_t *off)
{
	return simple_read_from_buffer(buf, len, off, msg, strlen(msg));
}

static const struct file_operations mysensor_fops = {
	.owner = THIS_MODULE,
	.read  = mysensor_read,
};

static int __init mysensor_init(void)
{
	dev_t dev;
	int ret;

	ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
	if (ret < 0)
		return ret;
	major = MAJOR(dev);

	cdev_init(&mysensor_cdev, &mysensor_fops);
	ret = cdev_add(&mysensor_cdev, dev, 1);
	if (ret < 0) {
		unregister_chrdev_region(dev, 1);
		return ret;
	}

	pr_info("mysensor: loaded, major=%d\n", major);
	return 0;
}

static void __exit mysensor_exit(void)
{
	cdev_del(&mysensor_cdev);
	unregister_chrdev_region(MKDEV(major, 0), 1);
	pr_info("mysensor: unloaded\n");
}

module_init(mysensor_init);
module_exit(mysensor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vishal Venkatesh");
MODULE_DESCRIPTION("Minimal character device driver - sensor placeholder");
