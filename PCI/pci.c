#include "./pci.h"

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) 
{
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;
  
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
  
    outl(0xCF8, address);
    tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}

uint16_t pciCheckVendor(uint8_t bus, uint8_t slot) 
{
    uint16_t vendor, device;
    /* Try and read the first configuration register. Since there are no
     * vendors that == 0xFFFF, it must be a non-existent device. */
    if ((vendor = pciConfigReadWord(bus, slot, 0, 0)) != 0xFFFF) 
    {
       device = pciConfigReadWord(bus, slot, 0, 2);
    } 
    
    return (vendor);
}

const char *get_vendor_name(uint16_t vendorID) {
    switch (vendorID) 
    {
        case 0x8086: return "Intel Corporation";
        case 0x10EC: return "Realtek Semiconductor Co., Ltd.";
        case 0x1022: return "Advanced Micro Devices, Inc.";
        case 0x104C: return "Texas Instruments";
        case 0x168C: return "Qualcomm Atheros";
        case 0x14E4: return "Broadcom Inc.";
        case 0x10DE: return "NVIDIA Corporation";
        case 0x1106: return "VIA Technologies, Inc.";
        case 0x1B36: return "Red Hat, Inc.";
        case 0x1AF4: return "Virtio (QEMU Virtual Devices)";
        case 0x1234: return "Bochs (QEMU Virtual VGA)";
        case 0x106B: return "Apple Inc.";
        case 0x17AA: return "Lenovo";
        case 0x103C: return "Hewlett-Packard (HP)";
        case 0x1166: return "Broadcom / ServerWorks";
        case 0x11AB: return "Marvell Technology Group Ltd.";
        case 0x1274: return "Ensoniq (Creative Labs)";
        case 0x1282: return "Trident Microsystems";
        case 0x15AD: return "VMware Inc.";
        case 0x16C3: return "Intel Mobile Communications";
        case 0x1D6A: return "Google, Inc.";
        case 0x1AE0: return "Amazon Web Services (AWS)";
        case 0x5333: return "S3 Graphics Ltd.";
        case 0x8087: return "Intel Corporation (Wireless)";
        case 0x1180: return "Ricoh Co., Ltd.";
        case 0x12D8: return "Pericom Semiconductor";
        case 0x13F6: return "C-Media Electronics Inc.";
        case 0x125D: return "ESS Technology";
        case 0x1412: return "VIA Technologies (Audio)";
        case 0x15B3: return "Mellanox Technologies";
        case 0x10B7: return "3Com Corporation";
        case 0x13B5: return "ARM Ltd.";
        case 0x12EB: return "Aureal Semiconductor";
        case 0x1095: return "Silicon Image, Inc.";
        case 0x1102: return "Creative Labs";
        case 0x109E: return "Brooktree Corporation";
        case 0x12C3: return "Holtek Semiconductor, Inc.";
        case 0x15E9: return "Belkin Components";
        case 0x14C3: return "Ralink Technology Corp.";
        case 0x104A: return "STMicroelectronics";
        case 0x131F: return "Siig, Inc.";
        case 0x17CB: return "DisplayLink (Video Adapters)";
        case 0x1682: return "Bitland Information Technology Co., Ltd.";
        case 0x14CD: return "Toshiba Corporation";
        case 0x15F4: return "Starkey Laboratories";
        case 0x15C2: return "Teradici Corporation";
        case 0x1737: return "Linksys";
        case 0x18D3: return "NVIDIA Networking";
        case 0x19A2: return "PLX Technology, Inc.";
        case 0x19E5: return "Huawei Technologies Co., Ltd.";
        case 0x1AB8: return "Parallels, Inc.";
        case 0x1D44: return "Google Cloud Devices";
        default: return "Unknown vendor";
    }
}

const char *get_device_name(uint16_t vendorID, uint16_t deviceID) 
{
    return "Unknown device";
}

const char *get_pci_class_name(uint8_t class_code, uint8_t subclass_code) 
{
    for (size_t i = 0; i < sizeof(pci_classes) / sizeof(pci_classes[0]); i++) 
    {
        if (pci_classes[i].class_code == class_code && pci_classes[i].subclass_code == subclass_code) 
        {
            return pci_classes[i].description;
        }
    }
    return "Unknown device";
}

void checkDevice(uint8_t bus, uint8_t device, uint8_t function) 
{
    uint16_t vendorID = pciConfigReadWord(bus, device, function, 0);
    if (vendorID == 0xFFFF) return;

    uint16_t deviceID = pciConfigReadWord(bus, device, function, 2);
    uint8_t classCode = (pciConfigReadWord(bus, device, function, 0xA) >> 8) & 0xFF;
    uint8_t subclass = pciConfigReadWord(bus, device, function, 0xA) & 0xFF;
    uint8_t progIF = (pciConfigReadWord(bus, device, function, 0x8) >> 8) & 0xFF;
    uint8_t revisionID = pciConfigReadWord(bus, device, function, 0x8) & 0xFF;

    print("\n%x:%x.%x %s: %s %s (rev %x)", 
           bus, device, function,
           get_pci_class_name(classCode, subclass),
           get_vendor_name(vendorID), 
           get_device_name(vendorID, deviceID),
           revisionID);

}

void list_pci_devices()
{
    for (int bus = 0; bus < 256; bus++)
    {
        for (int device = 0; device < 32; device++)
        {
            for (int function = 0; function < 8; function++)
            {
                checkDevice(bus, device, function);
            }
        }
    }
}