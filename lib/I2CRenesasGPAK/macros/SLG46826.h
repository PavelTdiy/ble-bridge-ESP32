// SLG46826.h

#define GreenPAK				"SLG46826"

#define VIRTUAL_INPUTS			0x7A	// I2C Virtual Inputs

#define PATTERN_ID				0xCB	// Unique pattern set in Program Settings

// Counter data holds the number at which the counter will output high
#define CNT0_0_DATA				0xA5    // Counter data for CNT0 LSByte
#define CNT0_1_DATA				0xA6    // Counter data for CNT0 MSByte
#define CNT1_DATA				0xAA    // Counter data for CNT1
#define CNT2_DATA				0xAF    // Counter data for CNT2
#define CNT3_DATA				0xB3    // Counter data for CNT3
#define CNT4_DATA				0xB8    // Counter data for CNT4
#define CNT5_DATA				0xBC    // Counter data for CNT5
#define CNT6_DATA				0xC1	// Counter data for CNT6
#define CNT7_DATA				0xC6	// Counter data for CNT7

// Counted value holds the current value of the GreenPAK's counters while it's counting
#define CNT0_0_VAL				0x7C	// Counted value for CNT0 LSByte
#define CNT0_1_VAL				0x7D	// Counted value for CNT0 MSByte
#define CNT2_VAL				0x7E	// Counted value for CNT2
#define CNT4_VAL				0x7F	// Counted value for CNT4

// Analog comparators outputs
#define ACMP_OUT_BYTE			0x7B	// ACMP Output Byte Address
#define ACMP0H_OUT_BIT			0   	// ACMP0 Output Bit
#define ACMP0H_OUT_BIT_MASK		0x01	// ACMP0 Output Bit mask
#define ACMP1H_OUT_BIT			1   	// ACMP1 Output Bit
#define ACMP1H_OUT_BIT_MASK     0x02	// ACMP1 Output Bit mask
#define ACMP2L_OUT_BIT			2   	// ACMP2 Output Bit
#define ACMP2L_OUT_BIT_MASK     0x04	// ACMP2 Output Bit mask
#define ACMP3L_OUT_BIT			3   	// ACMP3 Output Bit
#define ACMP3L_OUT_BIT_MASK     0x08	// ACMP3 Output Bit mask

// Analog comparators refs
#define ACMP0H_VREF_BYTE        0x89	// ACMP0 Reference Voltage Address
#define ACMP0H_VREF_MASK        0xFC	// ACMP0 Reference Voltage Bit mask (2-7)
#define ACMP1H_VREF_BYTE		0x8A	// ACMP1 Reference Voltage Address
#define ACMP1H_VREF_MASK        0xFC	// ACMP1 Reference Voltage Bit mask (2-7)
#define ACMP2L_VREF_BYTE        0x8B	// ACMP2 Reference Voltage Address
#define ACMP2L_VREF_MASK        0xFC	// ACMP2 Reference Voltage Bit mask (2-7)
#define ACMP3L_VREF_BYTE		0x8C	// ACMP3 Reference Voltage Address
#define ACMP3L_VREF_MASK        0xFC	// ACMP3 Reference Voltage Bit mask (2-7)

//Ripple counter bits
#define RIPPLE_BYTE	 			0xFC	// Ripple counter reg
#define RIPPLE_NSET_MASK		0x07	// Ripple counter nSET value mask (0-2)
#define RIPPLE_END_MASK			0x38	// Ripple counter nSET value mask (3-5)
#define RIPPLE_MODE_BIT			6   	// Ripple counter mode select bit
#define RIPPLE_MODE_BIT_MASK	0x40	// Ripple counter mode select mask

// GPIO pins values - Matrix inputs
#define PIN_1_BYTE				0x75	// PIN1 GPIO14 byte address
#define	PIN_1_BIT				5       // PIN1 GPIO14 bit number within byte
#define	PIN_1_BIT_MASK			0x20	// PIN1 GPIO14 bit mask
#define PIN_2_BYTE				0x75	// PIN2 GPIO13 byte address
#define	PIN_2_BIT				4       // PIN2 GPIO13 bit number within byte
#define	PIN_2_BIT_MASK			0x10	// PIN2 GPIO13 bit mask
#define PIN_3_BYTE				0x75	// PIN3 GPIO12 byte address
#define	PIN_3_BIT				3       // PIN3 GPIO12 bit number within byte
#define	PIN_3_BIT_MASK			0x08	// PIN3 GPIO12 bit mask
#define PIN_4_BYTE				0x75	// PIN4 GPIO11 byte address
#define	PIN_4_BIT				2       // PIN4 GPIO11 bit number within byte
#define	PIN_4_BIT_MASK			0x04	// PIN4 GPIO11 bit mask
#define PIN_5_BYTE				0x75	// PIN5 GPIO10 byte address
#define	PIN_5_BIT				1       // PIN5 GPIO10 bit number within byte
#define	PIN_5_BIT_MASK			0x02	// PIN5 GPIO10 bit mask
#define PIN_6_BYTE				0x75	// PIN6 GPIO9 byte address
#define	PIN_6_BIT				0       // PIN6 GPIO9 bit number within byte
#define	PIN_6_BIT_MASK			0x01	// PIN6 GPIO9 bit mask
// PIN7 - VDD2
#define PIN_8_BYTE				0x74	// PIN8 GPIO8 byte address
#define	PIN_8_BIT				7       // PIN8 GPIO8 bit number within byte
#define	PIN_8_BIT_MASK			0x80	// PIN8 GPIO8 bit mask
// PIN9 GPO7, PIN11 GPO6 - only outputs
// PIN10 - GND
// PIN12 SDA, PIN13 SCL - not reconfigured to IO in SLG46826
#define PIN_14_BYTE				0x74	// PIN14 GPIO5 byte address
#define	PIN_14_BIT				6       // PIN14 GPIO5 bit number within byte
#define	PIN_14_BIT_MASK			0x40	// PIN14 GPIO5 bit mask
#define PIN_15_BYTE				0x74	// PIN15 GPIO4 byte address
#define	PIN_15_BIT				5       // PIN15 GPIO4 bit number within byte
#define	PIN_15_BIT_MASK			0x20	// PIN15 GPIO4 bit mask
#define PIN_16_BYTE				0x74	// PIN16 GPIO3 byte address
#define	PIN_16_BIT				4       // PIN16 GPIO3 bit number within byte
#define	PIN_16_BIT_MASK			0x10	// PIN16 GPIO3 bit mask
#define PIN_17_BYTE				0x74	// PIN17 GPIO2 byte address
#define	PIN_17_BIT				3       // PIN17 GPIO2 bit number within byte
#define	PIN_17_BIT_MASK			0x08	// PIN17 GPIO2 bit mask
#define PIN_18_BYTE				0x74	// PIN18 GPIO1 byte address
#define	PIN_18_BIT				2       // PIN18 GPIO1 bit number within byte
#define	PIN_18_BIT_MASK			0x04	// PIN18 GPIO1 bit mask
#define PIN_19_BYTE				0x74	// PIN19 GPIO0 byte address
#define	PIN_19_BIT				1       // PIN19 GPIO0 bit number within byte
#define	PIN_19_BIT_MASK			0x02	// PIN19 GPIO0 bit mask
// PIN20 - VDD


#pragma region: unused makros
// #define RAM_BYTE_0				0xD8	// User configurable RAM/OTP Byte 0
// #define RAM_BYTE_1				0xD9	// User configurable RAM/OTP Byte 1
// #define RAM_BYTE_2				0xDA	// User configurable RAM/OTP Byte 2
// #define RAM_BYTE_3				0xDB	// User configurable RAM/OTP Byte 3
// #define RAM_BYTE_4				0xDC	// User configurable RAM/OTP Byte 4
// #define RAM_BYTE_5				0xDD	// User configurable RAM/OTP Byte 5
// #define RAM_BYTE_6				0xDE	// User configurable RAM/OTP Byte 6
// #define RAM_BYTE_7				0xDF	// User configurable RAM/OTP Byte 7
// #define RAM_BYTE_8				0xD0	// User configurable RAM/OTP Byte 8
// #define RAM_BYTE_9				0xD1	// User configurable RAM/OTP Byte 9
// #define RAM_BYTE_10				0xD2	// User configurable RAM/OTP Byte 10
// #define RAM_BYTE_11				0xD3	// User configurable RAM/OTP Byte 11
// #define RAM_BYTE_12				0xD4	// User configurable RAM/OTP Byte 12
// #define RAM_BYTE_13				0xD5	// User configurable RAM/OTP Byte 13
// #define RAM_BYTE_14				0xD6	// User configurable RAM/OTP Byte 14
// #define RAM_BYTE_15				0xD7	// User configurable RAM/OTP Byte 15

#pragma endregion