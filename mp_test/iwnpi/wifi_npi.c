/*
* Authors:<jessie.xin@spreadtrum.com>
* Owner:
*/

#include "wifi_npi.h"

char *devname = WIFINPI_DEV_NAME_STA;

int npi_wifi_iface_init(struct device **dev)
{
	//char *devname = CONFIG_WIFI_STA_DRV_NAME;


	ENG_LOG("enter %s\n", __func__);

	if (!devname)
		return NULL;

	*dev = device_get_binding(devname);
//	ENG_LOG("%s dev addr is %p\n", __func__, *dev);
	if (!(*dev)) {
		ENG_LOG("%s() failed to get device %s!\n", __func__, devname);
		return -1;
	}

	ENG_LOG("leaving %s\n", __func__);
	return 0;
}

int npi_get_mac(struct device *dev, char *mac)
{
	struct net_if *iface;

	ENG_LOG("enter %s\n", __func__);

	iface = net_if_lookup_by_dev(dev);
	if (!iface) {
		ENG_LOG("failed to get iface %s!\n", devname);
		return -1;
	}
	memcpy(mac, net_if_get_link_addr(iface)->addr, WIFINPI_ETH_ALEN);
	return 0;
}

int npi_open_station(struct device *dev)
{
	struct wifi_drv_api *mgmt_api =
	    (struct wifi_drv_api *)dev->driver_api;

	ENG_LOG("enter %s\n", __func__);

	if (!mgmt_api->open)
		return -EIO;

	ENG_LOG("leaving %s\n", __func__);
	return mgmt_api->open(dev);
}

int npi_close_station(struct device *dev)
{
	struct wifi_drv_api *mgmt_api =
	    (struct wifi_drv_api *)dev->driver_api;

	ENG_LOG("enter %s\n", __func__);

	if (!mgmt_api->close)
		return -EIO;

	ENG_LOG("leaving %s\n", __func__);
	return mgmt_api->close(dev);
}

int npi_cmd_send_recv(struct device *dev, int ictx_id,
		     char *t_buf, u32_t t_len, char *r_buf,
		     u32_t *r_len)
{
	struct wifi_drv_api *mgmt_api =
	    (struct wifi_drv_api *)dev->driver_api;

	ENG_LOG("enter %s\n", __func__);

	if (!mgmt_api->hw_test)
		return -EIO;

	ENG_LOG("leaving %s\n", __func__);
	return mgmt_api->hw_test(dev, ictx_id, (char *)t_buf, t_len, (char *)r_buf, r_len);
}
