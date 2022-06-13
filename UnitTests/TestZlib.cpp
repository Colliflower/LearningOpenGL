#include "pch.h"
#include "../LearningOpenGL/Zlib.h"
#include <random>

using namespace trv;

TEST(TestZlib, TestDeflate)
{
	static const std::vector<unsigned char> data { 0x58, 0xc3,0xed, 0x58, 0xdb, 0x0d, 0xc3, 0x20, 0x0c, 0x04, 0x94, 0x59, 0x9a, 0x4a, 0xec, 0x96, 0x61, 0xba, 0x1b, 0x52, 0x9a, 0x65, 0xe8, 0x4f, 0x91, 0x8c, 0x8b, 0xc1, 0xe6, 0xd1, 0xa0, 0x28, 0x48, 0xf9, 0x08, 0xc2, 0xe4, 0xb8, 0x3b, 0x1b, 0x88, 0xf6, 0xde, 0x7b, 0x35, 0x41, 0x33, 0x6a, 0x92, 0x36, 0x0d, 0x90, 0xa5, 0x25, 0xd8, 0xed, 0x47, 0xf4, 0x6e, 0x9f, 0x8f, 0xf3, 0x18, 0xb1, 0xdb, 0xaa, 0xec, 0xb6, 0x9e, 0x27, 0x0d, 0x66, 0x83, 0xea, 0xe3, 0x36, 0x2d, 0xc9, 0x9a, 0x1f, 0x29, 0x10, 0x13, 0xee, 0xf5, 0xae, 0x96, 0xca, 0xf4, 0x96, 0xa2, 0x56, 0x2a, 0xd3, 0xe2, 0x0d, 0x4e, 0xdf, 0xf5, 0xd2, 0xb7, 0xc5, 0x80, 0x30, 0xb6, 0xe4, 0x17, 0x83, 0x03, 0xe1, 0x93, 0xa2, 0x1c, 0x1b, 0x32, 0x09, 0x20, 0x8c, 0x89, 0x62, 0x89, 0xf9, 0x93, 0xd2, 0x40, 0xb3, 0x51, 0x60, 0x6a, 0x7c, 0x14, 0xe6, 0xa2, 0xcc, 0x1c, 0xa5, 0x2f, 0x1c, 0x9c, 0x5b, 0x6d, 0x09, 0x54, 0x69, 0x4c, 0x60, 0x0c, 0xca, 0x65, 0xa4, 0x79, 0xcf, 0x61, 0x86, 0x35, 0x06, 0x7d, 0x6b, 0xce, 0xdd, 0x37, 0x48, 0xc3, 0x31, 0x64, 0x75, 0x26, 0x7d, 0xe7, 0xc6, 0x66, 0x5d, 0x7a, 0x16, 0x25, 0x89, 0x81, 0xf1, 0x62, 0x4d, 0x2e, 0xf5, 0x46, 0xb3, 0x42, 0x02, 0x09, 0x06, 0xfa, 0x87, 0x34, 0x45, 0xb3, 0x8e, 0x04, 0x43, 0x81, 0xc8, 0x1e, 0x03, 0x5a, 0x8b, 0x19, 0x59, 0x69, 0x89, 0x12, 0x51, 0x3c, 0x8f, 0x70, 0x8a, 0x5c, 0x2d, 0x0b, 0xa2, 0x3a, 0xd2, 0x22, 0x15, 0x17, 0x84, 0xa8, 0xa0, 0xb5, 0xee, 0x35, 0x5d, 0x4f, 0xf1, 0x29, 0x56, 0xa8, 0xba, 0x30, 0x0c, 0x48, 0x8a, 0xe6, 0xdc, 0x75, 0xc2, 0xed, 0x87, 0x48, 0x4e, 0x16, 0x90, 0x9a, 0xfb, 0x8a, 0x34, 0xe6, 0xbe, 0x72, 0x5e, 0xf3, 0xee, 0xdb, 0x73, 0x2b, 0xd0, 0xf7, 0xff, 0x11, 0xd4, 0x3e, 0x8e, 0xee, 0xa7, 0x58, 0x70, 0xca, 0x24, 0x84 };
	//char data[] = { 0x58, 0xc3, 0x00, 0x00, 0x01, 0xFF, 0xFE, 0xad };
	std::vector<unsigned char> output;
	DeflateArgs args{true, data,  output};
	
	decompress(args);
}

TEST(TestZlib, PeekLitteByteLittleBit)
{
	static const std::vector<unsigned char> input1 {0b00100101, 0b01000010 };
	
	BitConsumer<std::endian::little> consumer(input1);

	uint16_t result = consumer.peek_bits<uint16_t, std::endian::little>(1);
	EXPECT_EQ(result, 0b1);

	result = consumer.peek_bits<uint16_t, std::endian::little>(3);
	EXPECT_EQ(result, 0b101);

	result = consumer.peek_bits<uint16_t, std::endian::little>(6);
	EXPECT_EQ(result, 0b100101);

	result = consumer.peek_bits<uint16_t, std::endian::little>(10);
	EXPECT_EQ(result, 0b1000100101);

	result = consumer.peek_bits<uint16_t, std::endian::little>(16);
	EXPECT_EQ(result, 0b0100001000100101);
}

TEST(TestZlib, PeekLitteByteBigBit)
{
	static const std::vector<unsigned char> input1 { 0b00100101, 0b01000010 };

	BitConsumer<std::endian::little> consumer(input1);

	uint16_t result = consumer.peek_bits<uint16_t, std::endian::big>(1);
	EXPECT_EQ(result, 0b1);

	result = consumer.peek_bits<uint16_t, std::endian::big>(3);
	EXPECT_EQ(result, 0b101);

	result = consumer.peek_bits<uint16_t, std::endian::big>(6);
	EXPECT_EQ(result, 0b101001);

	result = consumer.peek_bits<uint16_t, std::endian::big>(10);
	EXPECT_EQ(result, 0b1010010001);

	result = consumer.peek_bits<uint16_t, std::endian::big>(16);
	EXPECT_EQ(result, 0b1010010001000010);
}

TEST(TestZlib, PeekBigByteLittleBit)
{
	static const std::vector<unsigned char> input1 { 0b10100100, 0b01000010 };

	BitConsumer<std::endian::big> consumer(input1);

	uint16_t result = consumer.peek_bits<uint16_t, std::endian::little>(1);
	EXPECT_EQ(result, 0b1);

	result = consumer.peek_bits<uint16_t, std::endian::little>(3);
	EXPECT_EQ(result, 0b101);

	result = consumer.peek_bits<uint16_t, std::endian::little>(6);
	EXPECT_EQ(result, 0b100101);

	result = consumer.peek_bits<uint16_t, std::endian::little>(10);
	EXPECT_EQ(result, 0b1000100101);

	result = consumer.peek_bits<uint16_t, std::endian::little>(16);
	EXPECT_EQ(result, 0b0100001000100101);
}

TEST(TestZlib, PeekBigByteBigBit)
{
	static const std::vector<unsigned char> input1 { 0b10100100, 0b01000010 };

	BitConsumer<std::endian::big> consumer(input1);

	uint16_t result = consumer.peek_bits<uint16_t, std::endian::big>(1);
	EXPECT_EQ(result, 0b1);

	result = consumer.peek_bits<uint16_t, std::endian::big>(3);
	EXPECT_EQ(result, 0b101);

	result = consumer.peek_bits<uint16_t, std::endian::big>(6);
	EXPECT_EQ(result, 0b101001);

	result = consumer.peek_bits<uint16_t, std::endian::big>(10);
	EXPECT_EQ(result, 0b1010010001);

	result = consumer.peek_bits<uint16_t, std::endian::big>(16);
	EXPECT_EQ(result, 0b1010010001000010);
}

TEST(TestZlib, ConsumeLitteByteLittleBit)
{
	static const std::vector<unsigned char> input1 { 0b00110010, 0b00001110, 0b00001111, 0b00111110 };

	BitConsumer<std::endian::little> consumer(input1);

	uint16_t result = consumer.consume_bits<uint16_t, std::endian::little>(2);
	EXPECT_EQ(result, 0b10);

	result = consumer.consume_bits<uint16_t, std::endian::little>(4);
	EXPECT_EQ(result, 0b1100);

	result = consumer.consume_bits<uint16_t, std::endian::little>(6);
	EXPECT_EQ(result, 0b111000);

	result = consumer.consume_bits<uint16_t, std::endian::little>(8);
	EXPECT_EQ(result, 0b11110000);

	result = consumer.consume_bits<uint16_t, std::endian::little>(10);
	EXPECT_EQ(result, 0b1111100000);
}

TEST(TestZlib, ConsumeLitteByteBigBit)
{
	static const std::vector<unsigned char> input1 { 0b00110010, 0b00001110, 0b00001111, 0b00111110 };

	BitConsumer<std::endian::little> consumer(input1);

	uint16_t result = consumer.consume_bits<uint16_t, std::endian::big>(2);
	EXPECT_EQ(result, 0b1);

	result = consumer.consume_bits<uint16_t, std::endian::big>(4);
	EXPECT_EQ(result, 0b11);

	result = consumer.consume_bits<uint16_t, std::endian::big>(6);
	EXPECT_EQ(result, 0b111);

	result = consumer.consume_bits<uint16_t, std::endian::big>(8);
	EXPECT_EQ(result, 0b1111);

	result = consumer.consume_bits<uint16_t, std::endian::big>(10);
	EXPECT_EQ(result, 0b11111);
}

TEST(TestZlib, ConsumeBigByteLittleBit)
{
	static const std::vector<unsigned char> input1 { 0b01001100, 0b01110000, 0b11110000, 0b01111100 };

	BitConsumer<std::endian::big> consumer(input1);

	uint16_t result = consumer.consume_bits<uint16_t, std::endian::little>(2);
	EXPECT_EQ(result, 0b10);

	result = consumer.consume_bits<uint16_t, std::endian::little>(4);
	EXPECT_EQ(result, 0b1100);

	result = consumer.consume_bits<uint16_t, std::endian::little>(6);
	EXPECT_EQ(result, 0b111000);

	result = consumer.consume_bits<uint16_t, std::endian::little>(8);
	EXPECT_EQ(result, 0b11110000);

	result = consumer.consume_bits<uint16_t, std::endian::little>(10);
	EXPECT_EQ(result, 0b1111100000);
}

TEST(TestZlib, ConsumeBigByteBigBit)
{
	static const std::vector<unsigned char> input1 { 0b01001100, 0b01110000, 0b11110000, 0b01111100 };

	BitConsumer<std::endian::big> consumer(input1);

	uint16_t result = consumer.consume_bits<uint16_t, std::endian::big>(2);
	EXPECT_EQ(result, 0b1);

	result = consumer.consume_bits<uint16_t, std::endian::big>(4);
	EXPECT_EQ(result, 0b11);

	result = consumer.consume_bits<uint16_t, std::endian::big>(6);
	EXPECT_EQ(result, 0b111);

	result = consumer.consume_bits<uint16_t, std::endian::big>(8);
	EXPECT_EQ(result, 0b1111);

	result = consumer.consume_bits<uint16_t, std::endian::big>(10);
	EXPECT_EQ(result, 0b11111);
}
