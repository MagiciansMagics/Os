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

void checkDevice(uint8_t bus, uint8_t device) 
{
    uint8_t function = 0;
    uint16_t vendorID = pciConfigReadWord(bus, device, function, 0);
    if (vendorID == 0xFFFF) return; // Device doesn't exist

    // Read device and class information
    uint16_t deviceID = pciConfigReadWord(bus, device, function, 2);
    uint8_t classCode = (pciConfigReadWord(bus, device, function, 0xA) >> 8) & 0xFF;
    uint8_t subclass = (pciConfigReadWord(bus, device, function, 0xA)) & 0xFF;
    uint8_t headerType = (pciConfigReadWord(bus, device, function, 0xE) >> 8) & 0xFF;

    // Print or handle device information
    print("\nPCI Device found - Bus: %d, Device: %d, Vendor: %x, Device: %x, Class: %x, Subclass: %x",
           bus, device, vendorID, deviceID, classCode, subclass);

    if (headerType & 0x80) 
    {
        for (function = 1; function < 8; function++) 
        {
            vendorID = pciConfigReadWord(bus, device, function, 0);
            if (vendorID != 0xFFFF) 
            {
                deviceID = pciConfigReadWord(bus, device, function, 2);
                classCode = (pciConfigReadWord(bus, device, function, 0xA) >> 8) & 0xFF;
                subclass = (pciConfigReadWord(bus, device, function, 0xA)) & 0xFF;
                print("PCI Function found - Bus: %d, Device: %d, Function: %d, Vendor: %x, Device: %x, Class: %x, Subclass: %x\n",
                       bus, device, function, vendorID, deviceID, classCode, subclass);
            }
        }
    }
}

void list_pci_devices()
{
    for (int bus = 0; bus < 256; bus++)
    {
        for (int device = 0; device < 32; device++)
        {
            checkDevice(bus, device);
        }
    }
}