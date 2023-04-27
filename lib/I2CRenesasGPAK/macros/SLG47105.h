// SLG46826.h

#define GreenPAK				"SLG47105"

#define VIRTUAL_INPUTS			0x4C	// I2C Virtual Inputs

#define PATTERN_ID				0xF8	// Unique pattern set in Program Settings

// Counter data holds the number at which the counter will output high
#define CNT0_0_DATA				0x7F    // Counter data for CNT0 LSByte
#define CNT0_1_DATA				0x80    // Counter data for CNT0 MSByte
#define CNT1_DATA				0x82    // Counter data for CNT1
#define CNT2_DATA				0x84    // Counter data for CNT2
#define CNT3_DATA				0x86    // Counter data for CNT3
#define CNT4_DATA				0x88    // Counter data for CNT4

// Counted value holds the current value of the GreenPAK's counters while it's counting
#define CNT0_0_VAL				0x89	// Counted value for CNT0 LSByte
#define CNT0_1_VAL				0x8A	// Counted value for CNT0 MSByte
#define CNT4_VAL				0x8B	// Counted value for CNT2


// Changing PWM duty
#define PWM0_DUTY               0xA1	// PWM0 macrocell initial duty register
#define PWM0_UPDATE_BYTE        0xA2    // I2C trigger for PWM0 updating
#define PWM0_UPDATE_BIT         0       // I2C trigger for PWM0 updating
#define PWM1_DUTY               0xA3	// PWM1 macrocell initial duty register
#define PWM1_UPDATE_BYTE        0xA2    // I2C trigger for PWM1 updating
#define PWM1_UPDATE_BIT         1       // I2C trigger for PWM1 updating

// GPIO pins values - Matrix inputs
#define PIN_2_BYTE				0x4B	// PIN2 GPIO0 byte address
#define	PIN_2_BIT				2       // PIN2 GPIO0 bit number within byte
#define	PIN_2_BIT_MASK			0x04	// PIN2 GPIO0 bit mask

#define PIN_3_BYTE				0x4B	// PIN3 GPI byte address
#define	PIN_3_BIT				3       // PIN3 GPI bit number within byte
#define	PIN_3_BIT_MASK			0x08	// PIN3 GPI bit mask

#define PIN_14_BYTE				0x4B	// PIN14 GPIO1 byte address
#define	PIN_14_BIT				4       // PIN14 GPIO1 bit number within byte
#define	PIN_14_BIT_MASK			0x10	// PIN14 GPIO1 bit mask

#define PIN_15_BYTE				0x4C	// PIN15 GPIO2 byte address
#define	PIN_15_BIT				0       // PIN15 GPIO2 bit number within byte
#define	PIN_15_BIT_MASK			0x01	// PIN15 GPIO2 bit mask

#define PIN_16_BYTE				0x4C	// PIN16 GPIO3 byte address
#define	PIN_16_BIT				1       // PIN16 GPIO3 bit number within byte
#define	PIN_16_BIT_MASK			0x01	// PIN16 GPIO3 bit mask

#define PIN_17_BYTE				0x4B	// PIN17 GPIO4 byte address
#define	PIN_17_BIT				5       // PIN17 GPIO4 bit number within byte
#define	PIN_17_BIT_MASK			0x20	// PIN17 GPIO4 bit mask

#define PIN_19_BYTE				0x4B	// PIN19 GPIO5 byte address
#define	PIN_19_BIT				6       // PIN19 GPIO5 bit number within byte
#define	PIN_19_BIT_MASK			0x40	// PIN19 GPIO5 bit mask

#define PIN_20_BYTE				0x4B	// PIN20 GPIO6 byte address
#define	PIN_20_BIT				7       // PIN20 GPIO6 bit number within byte
#define	PIN_20_BIT_MASK_MASK			0x80	// PIN20 GPIO6 bit mask

// Analog comparators
#define ACMP_OUT_BYTE			0x4D	// ACMP Output Byte Address
#define ACMP0H_OUT_BIT			6   	// ACMP0 Output Bit
#define ACMP0H_OUT_BIT_MASK     0x40	// ACMP0 Output Bit mask
#define ACMP0H_VREF_BYTE        0x55	// ACMP0 Reference Voltage Address
#define ACMP0H_VREF_MASK        0xFC	// ACMP0 Reference Voltage Bit mask (2-7)
#define ACMP1H_OUT_BIT			7   	// ACMP1 Output Bit
#define ACMP1H_OUT_BIT_MASK     0x80	// ACMP1 Output Bit mask
#define ACMP1H_VREF_BYTE        0x56	// ACMP1 Reference Voltage Address
#define ACMP1H_VREF_MASK        0xFC	// ACMP1 Reference Voltage Bit mask (2-7)

// Differential amplifier with integrator
#define DIFINT_BYTE			    0x4D	// Diff Int Outputs Byte Address
#define DIFINT_UPWARD_BIT		4   	// Diff Int Upward Bit
#define DIFINT_UPWARD_BIT_MASK  0x10	// Diff Int Upward Bit mask
#define DIFINT_EQUAL_BIT        5   	// Diff Int Equal Bit
#define DIFINT_EQUAL_BIT_MASK   0x20	// Diff Int Equal Bit mask
#define DIFINT_VREF				0x53	// Diff Int Reference Voltage Address
#define DIFINT_VREF_MASK        0x3F	// Diff Int Reference Voltage Bit mask (0-6)

// Current comparators
#define CSCMP_OUT_BYTE			0x4E	// Current Sense CMP0
#define CSCMP0_OUT_BIT			0   	// CSCMP0 Output Bit
#define CSCMP0_OUT_BIT_MASK     0x01	// CSCMP0 Output Bit mask
#define CSCMP1_OUT_BIT			1   	// CSCMP1 Output Bit
#define CSCMP1_OUT_BIT_MASK     0x02	// CSCMP1 Output Bit mask
