#include <stdint.h>

#define RBUFP(p,pos) (((uint8_t*)(p)) + (pos))
#define RBUFB(p,pos) (*(uint8_t*)RBUFP((p),(pos)))
#define RBUFW(p,pos) (*(uint16_t*)RBUFP((p),(pos)))
#define RBUFL(p,pos) (*(uint32_t*)RBUFP((p),(pos)))
#define RBUFF(p,pos) (*(float*)RBUFP((p),(pos)))

#define WBUFP(p,pos) (((uint8_t*)(p)) + (pos))
#define WBUFB(p,pos) (*(uint8_t*)WBUFP((p),(pos)))
#define WBUFW(p,pos) (*(uint16_t*)WBUFP((p),(pos)))
#define WBUFL(p,pos) (*(uint32_t*)WBUFP((p),(pos)))
#define WBUFF(p,pos) (*(float*)WBUFP((p),(pos)))

uint32_t packBitsBE(uint8_t* target, uint64_t value, int32_t bitOffset, uint8_t lengthInBit)
{
	return packBitsBE(target, value, 0, bitOffset, lengthInBit);
}

uint32_t packBitsBE(uint8_t* target, uint64_t value, int32_t byteOffset, int32_t bitOffset, uint8_t lengthInBit)
{
	byteOffset += (bitOffset >> 3);										//correct bitOffsets>=8
	bitOffset %= 8;

	uint64_t bitmask = 0xFFFFFFFFFFFFFFFFLL;								//Generate bitmask

	bitmask >>= (64 - lengthInBit);
	bitmask <<= bitOffset;

	value <<= bitOffset;												//shift value
	value &= bitmask;

	bitmask ^= 0xFFFFFFFFFFFFFFFFLL;									//invert bitmask

	if ((lengthInBit + bitOffset) <= 8)									//write shifted value to target
	{
		uint8_t* dataPointer = (uint8_t*)&target[byteOffset];

		uint8_t bitmaskUC = (uint8_t)bitmask;
		uint8_t valueUC = (uint8_t)value;

		*dataPointer &= bitmaskUC;
		*dataPointer |= valueUC;
	}
	else if ((lengthInBit + bitOffset) <= 16)
	{
		uint16_t* dataPointer = (uint16_t*)&target[byteOffset];

		uint16_t bitmaskUC = (uint16_t)bitmask;
		uint16_t valueUC = (uint16_t)value;

		*dataPointer &= bitmaskUC;
		*dataPointer |= valueUC;
	}
	else if ((lengthInBit + bitOffset) <= 32)
	{
		uint32_t* dataPointer = (uint32_t*)&target[byteOffset];

		uint32_t bitmaskUC = (uint32_t)bitmask;
		uint32_t valueUC = (uint32_t)value;

		*dataPointer &= bitmaskUC;
		*dataPointer |= valueUC;
	}
	else if ((lengthInBit + bitOffset) <= 64)
	{
		uint64_t* dataPointer = (uint64_t*)&target[byteOffset];

		*dataPointer &= bitmask;
		*dataPointer |= value;
	}
	else
	{
		//ShowError("Pack Bits Error: packBitsBE(...) not implemented for targetsizes above 64 bits.\n Targetsize: %d\n", (lengthInBit + bitOffset));
	}
	return ((byteOffset << 3) + bitOffset + lengthInBit);
}


uint64_t unpackBitsBE(uint8_t* target, int32_t bitOffset, uint8_t lengthInBit)
{
	return unpackBitsBE(target, 0, bitOffset, lengthInBit);
}

uint64_t unpackBitsBE(uint8_t* target, int32_t byteOffset, int32_t bitOffset, uint8_t lengthInBit)
{
	byteOffset += (bitOffset >> 3);
	bitOffset %= 8;

	uint64_t bitmask = 0xFFFFFFFFFFFFFFFFLL;

	bitmask >>= (64 - lengthInBit);
	bitmask <<= bitOffset;

	uint64_t retVal;

	if ((lengthInBit + bitOffset) <= 8)
	{
		uint8_t* dataPointer = (uint8_t*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint8_t)bitmask) >> bitOffset;
	}
	else if ((lengthInBit + bitOffset) <= 16)
	{
		uint16_t* dataPointer = (uint16_t*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint16_t)bitmask) >> bitOffset;
	}
	else if ((lengthInBit + bitOffset) <= 32)
	{
		uint32_t* dataPointer = (uint32_t*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint32_t)bitmask) >> bitOffset;
	}
	else if ((lengthInBit + bitOffset) <= 64)
	{
		uint64_t* dataPointer = (uint64_t*)&target[byteOffset];

		retVal = ((*dataPointer)&(uint64_t)bitmask) >> bitOffset;
	}
	else
	{
		//ShowError("Unpack Bits Error: unpackBits(...) not implemented for targetsizes above 64 bits.\n Targetsize: %d\n", (lengthInBit + bitOffset));
		return 0;
	}
	return retVal;
}