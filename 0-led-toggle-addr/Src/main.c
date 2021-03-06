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

#define RCC_AHBEN_OFFSET 0x0014UL
#define RCC_AHBENR (* (volatile int *) (RCC_BASE + RCC_AHBEN_OFFSET))

#define GPIOA_EN (1UL << 17)

#define GPIO_MODER_OFFSET 0x0000UL
#define GPIOA_MODER (* (volatile int *) (GPIOA_BASE + GPIO_MODER_OFFSET))

#define ODR_OFFSET 0x14UL
#define GPIOA_ODR (* (volatile int *) (GPIOA_BASE + ODR_OFFSET))

#define PIN5 (1U << 5)
#define LED_PIN PIN5

int main(void)
{
     /* 1 enable clock access */
     RCC_AHBENR |= GPIOA_EN;

     /* 2 set PA5 as output */
     GPIOA_MODER |= (1U<<10); /* bit 10 to 1 */
     GPIOA_MODER &=~(1U<<11); /* bit 11 to 0 */

     while(1){
          /* /\* set PA5 high *\/ */
          /* GPIOA_ODR |= LED_PIN; */
          /* toggle */
          GPIOA_ODR ^= LED_PIN;
          for(int i =0; i <= 100000; i++){
          }
     }
}
