# Udemy Course

Following a udemy course and keeping notes etc.

<https://www.udemy.com/course/embedded-systems-bare-metal-programming/learn/lecture/26702490#overview>


# ST Docs


## reference manual

<stm32f030r8-reference-manual.pdf>


## datasheet

<stm32f030r8-datasheet.pdf>


## userguide

<nucleo-stm32f030r8-userguide.pdf>


# [0-led-toggle-addr](0-led-toggle-addr/)


## locate led

[video](https://www.udemy.com/course/embedded-systems-bare-metal-programming/learn/lecture/26702988#questions)


### port and pin

Need to reference [user manual](nucleo-stm32f030r8-userguide.pdf).

> User LD2: the green LED is a user LED connected to ARDUINO ® signal D13 corresponding to STM32 I/O PA5 (pin 21)


## defining address of modules

[video](https://www.udemy.com/course/embedded-systems-bare-metal-programming/learn/lecture/26702598#questions)

Refer to the [datasheet](stm32f030r8-datasheet.pdf)

Search for memory mapping. Peripherals.

> memory range : x4000 0000-0x4800 17ff

```c
#define PERIPH_BASE 0x40000000ul
```

Now need to look at the register boundary address tables.

Here we see that the different peripherals are on different buses. The BLOCK DIAGRAM depicts these buses.

> APB: Advanced Peripheral Bus AHB: Advanced High Performance Bus

We see GPIO PORT A is connected to AHB.

Below the memory map, you'll see a table depicting the boundary addresses.

| Bus  | Boundary Address          | Size | Peripheral |
| AHB2 | 0x4800 0000 - 0x4800 03FF | 1KB  | GPIOA      |

Bringing all the offsets and bases etc together:-

```c
#define PERIPH_BASE 0x40000000UL

#define AHB2_PERIPH_OFFSET 0x08000000UL
#define AHB2_PERIPH_BASE (PERIPH_BASE + AHB2_PERIPH_OFFSET)
#define GPIOA_BUS_BASE AHB2_PERIPH_BASE
#define GPIOA_OFFSET 0x0000UL
#define GPIOA_BASE (GPIOA_BUS_BASE + GPIOA_OFFSET)
```

Similar for RCC

```c
#define AHB1_PERIPH_OFFSET 0x20000UL
#define AHB1_PERIPH_BASE (PERIPH_BASE + AHB1_PERIPH_OFFSET)
#define RCC_BUS_BASE AHB1_PERIPH_BASE
#define RCC_OFFSET 0x1000UL
#define RCC_BASE (RCC_BUS_BASE + RCC_OFFSET)
```


## creating required registers using available docs

[video](https://www.udemy.com/course/embedded-systems-bare-metal-programming/learn/lecture/26702606#questions)

We want to create pointers to the registers needs to control these peripherals. We'll find in in the [reference manual](stm32f030r8-reference-manual.pdf).

Course says AHB1EN. No such thing for this board.

> After each device reset, all peripheral clocks are disabled (except for the SRAM and Flash). Before using a peripheral you have to enable its clock in the RCC\_AHBENR, RCC\_APB2ENR or RCC\_APB1ENR register.

> 7.4.6 AHB peripheral clock enable register (RCC\_AHBENR) Address offset: 0x14 Reset value: 0x0000 0014

```c
...
#define RCC_BASE (RCC_BUS_BASE + RCC_OFFSET)
#define RCC_AHBEN_OFFSET 0x0014UL
#define RCC_AHBEN_R (RCC_BASE+RCC_AHBEN_OFFSET)
```