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


### register pointers

Course says AHB1EN. No such thing for this board.

> After each device reset, all peripheral clocks are disabled (except for the SRAM and Flash). Before using a peripheral you have to enable its clock in the RCC\_AHBENR, RCC\_APB2ENR or RCC\_APB1ENR register.

> 7.4.6 AHB peripheral clock enable register (RCC\_AHBENR) Address offset: 0x14 Reset value: 0x0000 0014

```c
...
#define RCC_BASE (RCC_BUS_BASE + RCC_OFFSET)
#define RCC_AHBEN_OFFSET 0x0014UL
#define RCC_AHBENR (RCC_BASE+RCC_AHBEN_OFFSET)
```

Control clock for GPIOA

> Bit 17 IOPAEN: I/O port A clock enable Set and cleared by software. 0: I/O port A clock disabled 1: I/O port A clock enabled

```c
#define RCC_AHBEN_GPIOAEN (1UL << 17)
```


### registers

GPIO ports have at least two registers - direction register and data register.

[Reference Manual](stm32f030r8-reference-manual.pdf) search for **moder**

> 8.4.1 GPIO port mode register (GPIOx\_MODER) (x =A..D, F) Address offset:0x00 Reset values:
>
> -   0x2800 0000 for port A
> -   0x0000 0000 for other ports

```c
#define GPIO_MODER_OFFSET 0x0000UL
#define GPIOA_MODER (GPIOA_BASE+GPIO_MODER_OFFSET)
```

So what do we write to the GPIOA\_MODER?

> Bits 2y+1:2y MODERy[1:0]: Port x configuration bits (y = 0..15) These bits are written by software to configure the I/O mode. 00: Input mode (reset state) 01: General purpose output mode 10: Alternate function mode 11: Analog mode

We want general output so bits 11:10 should be 0:1. BUT since we know the register was reset and the from this the reset values are 0

> Address offset:0x00 Reset values: 0x2800 0000 for port A 0x0000 0000 for other ports

we can just set bit 10 to 1. But here we zero it anyway for fun

```c
/*
 * (1UL<<10) set bit 10
 * ~(1UL<<11) mask to clear bit 11
 */

```

we need to write to out put data register

> GPIO port output data register (GPIOx\_ODR) (x = A..D, F) Address offset: 0x14 Reset value: 0x0000 0000

```c
#define ODR_OFFSET 0x14UL
#define GPIOA_ODR (GPIOA_BASE+ODR_OFFSET)
```