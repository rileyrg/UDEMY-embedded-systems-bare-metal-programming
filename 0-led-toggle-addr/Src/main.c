// Port : A
// Pin : 5
#define PERIPH_BASE 0x40000000UL

#define AHB2_PERIPH_OFFSET 0x08000000UL
#define AHB2_PERIPH_BASE (PERIPH_BASE + AHB2_PERIPH_OFFSET)
#define GPIOA_BUS_BASE AHB2_PERIPH_BASE
#define GPIOA_OFFSET 0x0000UL
#define GPIOA_BASE (GPIOA_BUS_BASE + GPIOA_OFFSET)

#define AHB1_PERIPH_OFFSET 0x20000UL
#define AHB1_PERIPH_BASE (PERIPH_BASE + AHB1_PERIPH_OFFSET)
#define RCC_BUS_BASE AHB1_PERIPH_BASE
#define RCC_OFFSET 0x1000UL
#define RCC_BASE (RCC_BUS_BASE + RCC_OFFSET)
