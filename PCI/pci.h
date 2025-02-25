#ifndef _PCI_H_
#define _PCI_H_

#include <stdint.h>
#include "../graphics/font/print.h"
#include "../Include/IoPorts.h"

#pragma once

struct PCI_CLASS_LIST 
{
    uint8_t class_code;
    uint8_t subclass_code;
    const char *description;
};

static const struct PCI_CLASS_LIST pci_classes[] =
{
    // Mass Storage Controller
    {0, 0, ""},
    {0, 1, "VGA-Compatible Unclassified Device"},
    {1, 1, "IDE Controller"},
    {1, 2, "Floppy Disk Controller"},
    {1, 3, "IPI Bus Controller"},
    {1, 4, "RAID Contoller"},
    {1, 5, "ATA Controller"},
    {1, 6, "Serial ATA Contoller"},
    {1, 7, "Serial Attached SCSI Contoller"},
    {1, 8, "Non-Volatile Memory Controller"},
    {1, 0x80, "Other Mass Storage Controller"},
    // Network Controller
    {2, 0, "Ethernet Controller"},
    {2, 1, "Token Ring Controller"},
    {2, 2, "FDDI Controller"},
    {2, 3, "ATM Controller"},
    {2, 4, "ISDN Controller"},
    {2, 5, "WorldFip Controller"},
    {2, 6, "PICMG 2.14 Multi Computing Controller"},
    {2, 7, "Infiniband Controller"},
    {2, 8, "Fabric Controller"},
    {2, 0x80, "Other Network Controller"},
    // Display Controller
    {3, 0, "VGA Compatible Controller"},
    {3, 1, "XGA Controller"},
    {3, 2, "3D Controller (Not VGA Compatible)"},
    {3, 0x80, "Other Display Controller"},
    // Multimedia Controller
    {4, 0, "Multimedia Video Controller"},
    {4, 1, "Multimedia Audio Controller"},
    {4, 2, "Computer Telephony Device"},
    {4, 3, "Audio Device"},
    {4, 0x80, "Other Multimedia Controller"},
    // Memory Controller
    {5, 0, "RAM Controller"},
    {5, 1, "Flash Controller"},
    {5, 0x80, "Other Memory Controller"},
    // Bridge
    {6, 0, "Host Bridge"},
    {6, 1, "ISA Bridge"},
    {6, 2, "EISA Bridge"},
    {6, 3, "MCA Bridge"},
    {6, 4, "PCI-to-PCI Bridge"},
    {6, 5, "PCMCIA Bridge"},
    {6, 6, "NuBus Bridge"},
    {6, 7, "CardBus Bridge"},
    {6, 8, "RACEway Bridge"},
    {6, 9, "PCI-to-PCI Bridge"},
    {6, 0x0a, "InfiniBand-to-PCI Host Bridge"},
    {6, 0x80, "Other Bridge"},
    // Simple Communication Controller
    {7, 0, "Serial Controller"},
    {7, 1, "Parallel Controller"},
    {7, 2, "Multiport Serial Controller"},
    {7, 3, "Modem"},
    {7, 4, "IEEE 488.1/2 (GPIB) Controller"},
    {7, 5, "Smart Card Controller"},
    {7, 0x80, "Other Simple Communation Controller"},
    // Base System Peripheral
    {8, 0, "PIC"},
    {8, 1, "DMA Controller"},
    {8, 2, "Timer"},
    {8, 3, "RTC Controller"},
    {8, 4, "PCI Hot-Plug Controller"},
    {8, 5, "SD Host Controller"},
    {8, 6, "IOMMU"},
    {8, 0x80, "Other Base System Peripheral"},
    // Input Device Conroller
    {9, 0, "Keyboard Controller"},
    {9, 1, "Digitizer Pen"},
    {9, 2, "Mouse Controller"},
    {9, 3, "Scanner Controller"},
    {9, 4, "Gameport Controller"},
    {9, 0x80, "Other Input Device Controller"},
    // Docking Station
    {0xA, 0, "Generic"},
    {0xA, 0x80, "Other Docking Station"},
    // Processor
    {0xB, 0, "386"},
    {0xB, 1, "486"},
    {0xB, 2, "Pentium"},
    {0xB, 3, "Pentium Pro"},
    {0xB, 10, "Alpha"},
    {0xB, 20, "PowerPc"},
    {0xB, 30, "MIPS"},
    {0xB, 40, "Co-Processor"},
    {0xB, 0x80, "Other Processor"},
    // Serial Bus Controller
    {0xC, 0, "FireWire (IEEE 1394) Controller"},
    {0xC, 1, "ACCESS Bus Controller"},
    {0xC, 2, "SSA"},
    {0xC, 3, "USB Controller"},
    {0xC, 4, "Fibre Channel"},
    {0xC, 5, "SMBus Controller"},
    {0xC, 6, "InfiniBand Controller"},
    {0xC, 7, "IPMI Interface"},
    {0xC, 8, "SERCOS Interface (IEC 61491)"},
    {0xC, 9, "CANBus Controller"},
    {0xC, 0x80, "Other Serial Bus Controller"},
    // Wireless Controller
    {0xD, 0, "iRDA Compatible Controller"},
    {0xD, 1, "Consumer IR Controller"},
    {0xD, 10, "RF Controller"},
    {0xD, 11, "Bluetooth Controller"},
    {0xD, 12, "Broadband Controller"},
    {0xD, 20, "Ethernet Controller (802.1a)"},
    {0xD, 21, "Ethernet Controller (802.1b)"},
    {0xD, 0x80, "Other Wireless Controller"},
    // Intelligent Controller
    {0xE, 0, "I20"},
    // Satellite Communication Controller
    {0xF, 1, "Satellite TV Controller"},
    {0xF, 2, "Satellite Audio Controller"},
    {0xF, 3, "Satellite Voice Controller"},
    {0xF, 4, "Satellite Data Controller"},
    // Encryption Controller
    {0x10, 0, "Network and Computing Encryption/Decryption"},
    {0x10, 10, "Entainment Encryption/Decryption"},
    {0x10, 0x80, "Other Encryption Controller"},
    // Signal Processing Controller
    {0x11, 0, "DPIO Modules"},
    {0x11, 1, "Performance Counters"},
    {0x11, 10, "Communication Syncronizer"},
    {0x11, 20, "Signal Processing Management"},
    {0x11, 0x80, "Other Signal Processing Controller"},
};

void list_pci_devices();

#endif