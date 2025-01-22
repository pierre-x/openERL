# openERL
Open source firmware for EDF ERL-DLE-A01 energy monitor

# Disclamer
The continuation of this Readme is in French, as this project only applies to French Linky electricity meters.

# Démontage

<img src="https://github.com/user-attachments/assets/58cc414a-30e1-4425-a2bf-172b16ab8816" width=30% height=30%>

# Pinout du tag-connect sur la carte ERL
<img width="297" alt="tag_pinout" src="https://github.com/user-attachments/assets/57aaa45e-9f56-4bfa-bb66-49d6c404d360" />

⚠️ ce pinout ne respecte pas celui de l'ESP32-prog au travers d'un tag-connect TC2030-IDC

# Spécification du tag-connect TC2030-IDC

<img width="595" alt="image" src="https://github.com/user-attachments/assets/3fb30695-9a50-414a-8c4a-32665b288733" />

# Spécification de l'ESP32-prog

![image](https://github.com/user-attachments/assets/2cc44ec6-9a4a-4b16-8d27-656a42debeec)

# Dump de la liaison série

Au démarrage la liaison série nous donne des informations intéressantes :

```
screen /dev/tty.usbserial-1101 115200
I (474) cpu_start: Pro cpu up.
I (474) cpu_start: Starting app cpu, entry point is 0x40080fb4
I (0) cpu_start: App cpu up.
I (488) cpu_start: Pro cpu start user code
I (488) cpu_start: cpu freq: 80000000
I (488) cpu_start: Application information:
I (492) cpu_start: Project name:     erl
I (497) cpu_start: App version:      turtle-25
I (502) cpu_start: Compile time:     Jul 21 2022 15:17:36
I (508) cpu_start: ELF file SHA256:  e385c00bc1658f0d...
I (514) cpu_start: ESP-IDF:          v4.3.2
I (519) heap_init: Initializing. RAM available for dynamic allocation:
I (526) heap_init: At 3FFAFF10 len 000000F0 (0 KiB): DRAM
I (532) heap_init: At 3FFB6388 len 00001C78 (7 KiB): DRAM
I (538) heap_init: At 3FFB9A20 len 00004108 (16 KiB): DRAM
I (545) heap_init: At 3FFCB9C8 len 00014638 (81 KiB): DRAM
I (551) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (557) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (564) heap_init: At 4009D27C len 00002D84 (11 KiB): IRAM
I (571) spi_flash: detected chip: gd
I (574) spi_flash: flash io: dio
I (578) flash_encrypt: Flash encryption mode is RELEASE
I (596) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (597) ERL_MAIN: fw=turtle-25
I (777) ERL_MAIN: hw=LACROIX-ERL-DLE-A01
I (777) ERL_MAIN: uid=bf6cd136-2a71-4bff-9a04-0530da3bd84d
```
